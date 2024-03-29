Most of the programs/header files in here are self explanatory

### Hash.h (C/C++)
- SHA-1
- SHA-2 family
    - SHA-224
    - SHA-256
    - SHA-384
    - SHA-512
    - SHA-512/224
    - SHA-512/256
- SHA-3 family
    - SHA3-224
    - SHA3-256
    - SHA3-384
    - SHA3-512
- Shake-128
- Shake-256
- MD5

The documentation is in the header  
The Shake function can not be updated, data has to be supplied in a single string

### hash.zig or hash.cpp
Hash strings, files or directories. Functionality to print all files that are the same in a directory and search for files based on their hash value (C++ only)
- SHA-1
- SHA-2 family
    - SHA-224
    - SHA-256
    - SHA-384
    - SHA-512
    - SHA-512/256
- SHA-3 family
    - SHA3-224
    - SHA3-256
    - SHA3-384
    - SHA3-512
- MD5

### time.cpp
Time utility from Linux for Windows

### Profiler.h
Measure the execution time of code snippets e.g. in loops.  
Example (simplified, from hash_benchmark.cpp)
``` c++
for (const std::string& s : strings)
{
    Profiler::Start();
    sha256(s);
    Profiler::End();
}
Profiler::Log(Profiler::Conversion::Milliseconds); // print to stdout
```

### snake_console.c
A snake implementation meant to be played in the console, supports Windows, Linux and macOS  
Compiling on Windows:
``` bash
gcc snake_console.c -lUser32
```

Compiling on macOS:
``` bash
gcc snake_console.c -framework Carbon
```

For additional information and to change settings
``` bash
./snake --help
```

### cstring.h
Implements the C++ string interface in C

### array.h
C++17 compliant std::array implementation

### stack.h
C++17 compliant std::stack implementation
