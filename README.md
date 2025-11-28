# Ray Tracer Challenge

A test-driven implementation of a 3D ray tracer in C++.

## Building

This project uses CMake for building. You'll need:
- CMake 3.10 or higher
- A C++17 compatible compiler
- Catch2 (header-only testing framework)

### Setting up Catch2

Catch2 is a header-only testing framework. You can either:

1. **Download Catch2 manually:**
   ```bash
   mkdir -p tests
   cd tests
   curl -L https://github.com/catchorg/Catch2/releases/download/v3.5.0/catch.hpp -o catch2/catch.hpp
   ```

2. **Or use CMake FetchContent (recommended):**
   The CMakeLists.txt can be updated to automatically download Catch2.

### Building the project

```bash
mkdir build
cd build
cmake ..
make
```

### Running tests

```bash
cd build
./tests
```

## Project Structure

- `include/tuple.h` - Tuple class definition
- `src/tuple.cpp` - Tuple implementation
- `tests/test_tuple.cpp` - Test cases for tuples

## Features Implemented

- Tuple class with x, y, z, w components
- Point factory function (w=1.0)
- Vector factory function (w=0.0)
- Floating point comparison with EPSILON
- Test cases covering all scenarios from the book
