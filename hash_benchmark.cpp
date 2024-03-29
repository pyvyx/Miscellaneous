#include <string_view>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <string>
#include <utility>

#include "Hash.h"
#include "Profiler.h"

#define NUMBER_OF_STRINGS 10000
#define MAX_STRING_SIZE   10000

typedef std::vector<char> char_array;
char_array charset()
{
    //Change this to suit
    return char_array(
        { '0','1','2','3','4',
        '5','6','7','8','9',
        'A','B','C','D','E','F',
        'G','H','I','J','K',
        'L','M','N','O','P',
        'Q','R','S','T','U',
        'V','W','X','Y','Z',
        'a','b','c','d','e','f',
        'g','h','i','j','k',
        'l','m','n','o','p',
        'q','r','s','t','u',
        'v','w','x','y','z'
        });
};

// given a function that generates a random character,
// return a string of the requested length
std::string random_string(size_t length, std::function<char(void)> rand_char)
{
    std::string str(length, 0);
    std::generate_n(str.begin(), length, rand_char);
    return str;
}


std::vector<std::string> GenerateStrings(size_t count)
{
    const auto ch_set = charset();

    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, ch_set.size() - 1);
    auto randchar = [ch_set, &dist, &rng]() {return ch_set[dist(rng)]; };

    auto rnum = [](unsigned int min, unsigned int max) {
        static std::random_device dev;
        static std::mt19937 mrng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max); // distribution in range [1, 6]
        return dist6(mrng);
        };

    std::vector<std::string> strings;
    strings.reserve(count);

    for (size_t i = 0; i < count; ++i)
    {
        strings.emplace_back(random_string(rnum(0, MAX_STRING_SIZE), randchar));
    }
    return strings;
}


int main()
{
    Profiler::Start();
    std::vector<std::pair<double, std::string>> times;
    const std::vector<std::string> strings = GenerateStrings(NUMBER_OF_STRINGS);

    auto Measure = [&](std::string (*hashfunc)(std::string_view str), std::string name)
    {
        for (const std::string& s : strings)
        {
            Profiler::Start();
            hashfunc(s);
            Profiler::End();
        }
        times.push_back({Profiler::Average(Profiler::Conversion::Milliseconds), name});
        std::cout << name.append(14 - name.size(), ' ') << ": ";
        Profiler::Log(Profiler::Conversion::Milliseconds);
    };

    auto MeasureChar = [&](const char* (*hashfunc)(const char* str), std::string name)
    {
        for (const std::string& s : strings)
        {
            Profiler::Start();
            hashfunc(s.c_str());
            Profiler::End();
        }
        times.push_back({Profiler::Average(Profiler::Conversion::Milliseconds), name});
        std::cout << name.append(14 - name.size(), ' ') << ": ";
        Profiler::Log(Profiler::Conversion::Milliseconds);
    };

    Profiler::End();
    std::cout << "Finished generating strings, starting ";
    Profiler::Log(Profiler::Conversion::Seconds);

    Measure(Hash::sha1, "C++ Sha1");
    Measure(Hash::sha224, "C++ Sha244");
    Measure(Hash::sha256, "C++ Sha256");
    Measure(Hash::sha384, "C++ Sha384");
    Measure(Hash::sha512, "C++ Sha512");
    Measure(Hash::sha512_224, "C++ Sha512/224");
    Measure(Hash::sha512_256, "C++ Sha512/256");
    
    Measure(Hash::sha3_224, "C++ Sha3-244");
    Measure(Hash::sha3_256, "C++ Sha3-256");
    Measure(Hash::sha3_384, "C++ Sha3-384");
    Measure(Hash::sha3_512, "C++ Sha3-512");

    Measure(Hash::md5, "C++ MD5");


    MeasureChar(hash_sha1_easy, "C Sha1");
    MeasureChar(hash_sha224_easy, "C Sha244");
    MeasureChar(hash_sha256_easy, "C Sha256");
    MeasureChar(hash_sha384_easy, "C Sha384");
    MeasureChar(hash_sha512_easy, "C Sha512");

    MeasureChar(hash_sha3_224_easy, "C Sha3-244");
    MeasureChar(hash_sha3_256_easy, "C Sha3-256");
    MeasureChar(hash_sha3_384_easy, "C Sha3-384");
    MeasureChar(hash_sha3_512_easy, "C Sha3-512");

    MeasureChar(hash_md5_easy, "C MD5");

    std::cout << "\nStrings: " << NUMBER_OF_STRINGS << ", Max chars per string: " << MAX_STRING_SIZE << std::endl;
    
    std::pair<double, std::string> fastest = times[0];
    std::pair<double, std::string> slowest = times[0];
    for (const auto& p : times)
    {
        if (p.first < fastest.first) fastest = p;
        if (p.first > slowest.first) slowest = p;
    }
    
    std::cout << "Winner: " << fastest.second << " " << fastest.first << std::endl;
    std::cout << "Slowest: " << slowest.second << " " << slowest.first << std::endl;
}