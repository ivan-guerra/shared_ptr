# Shared Pointer

This repo includes a header-only implementation of a shared pointer similar to
the one provided by C++'s STL.

### Running the Tests

This is a header only library meaning you could take the header
[`shared_ptr/include/memory/shared_ptr.hpp`](include/memory/shared_ptr.hpp) and
integrate it into your project. That said, it may be useful to build, run, and
experiment with the unit tests.

To build, you will need the following libraries and tools installed:

* CMake3.27+
* C++ compiler supporting C++20 features

To build and run the unit tests:

1. Change directory to the `shared_ptr/scripts/` directory.

2. Run the build script:
```bash
./build.sh [DEBUG]
```

3. Navigate to the `shared_ptr/build/`.

4. Run CTest:
```bash
ctest
```
