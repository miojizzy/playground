# C++17 Utility Library

A modular C++17 library with reusable components built using Bazel on Linux.

## Features

- Modern C++17 features
- Thread-safe data structures
- String and file utilities
- Sorting algorithms
- Statistical functions
- Comprehensive test coverage
- Well-documented API

## Requirements

- C++17 compatible compiler (GCC 7+ or Clang 5+)
- Bazel build system (0.27.0 or newer)
- Linux environment

## Building the library

```bash
# Build everything
bazel build //...

# Build specific components
bazel build //src/utils:utils
bazel build //src/data_structures:data_structures
