# Architecture Overview

## Overview

The `cpp_utils_lib` is a modern C++17 utility library designed to provide a collection of reusable components for C++ applications. It follows a modular architecture with clear separation of concerns between different utility categories. The library uses Bazel as its build system and is designed for Linux environments.

The library is organized into distinct functional domains, each addressing a specific aspect of utility functionality:

- String manipulation utilities
- File operation utilities
- Thread-safe data structures
- Sorting algorithms
- Mathematical and statistical functions

## System Architecture

### Build System

The project uses Bazel as its build system, which provides:

- Consistent build process across different environments
- Well-defined dependency management
- Parallel build capability
- Incremental compilation
- Integrated testing framework

The Bazel configuration specifies C++17 as the language standard and defines library components as modular, independently buildable units.

### Code Organization

The codebase follows a domain-driven organization structure:

```
cpp_utils_lib/
├── src/                    # Source code organized by domain
│   ├── utils/              # String and file utilities
│   ├── data_structures/    # Thread-safe queue, LRU cache, etc.
│   ├── algorithms/         # Sorting and other algorithms
│   └── math/               # Statistical functions
├── tests/                  # Test code matching the src structure
│   ├── utils/
│   ├── data_structures/
│   └── ...
├── examples/               # Example code demonstrating usage
└── BUILD                   # Root build file
```

This organization allows for:
- Clear component boundaries
- Independent development and testing of components
- Simplified dependency management
- Easy discovery of functionality

## Key Components

### String Utilities (`src/utils/string_utils.h`)

A collection of string manipulation functions including:
- Split: Divides strings by delimiter
- Join: Combines strings with separators
- Trim: Removes whitespace
- Case conversions (ToLower, ToUpper)
- String matching utilities (StartsWith, EndsWith)

The string utilities are implemented as standalone functions rather than as a class, following a functional programming approach that emphasizes simplicity and reusability.

### File Utilities (`src/utils/file_utils.h`)

Provides file system operations including:
- ReadFile: Reads entire file content
- WriteFile: Writes/overwrites file content
- AppendToFile: Adds content to existing files
- ReadLines: Reads files line-by-line

These utilities use C++17's `std::filesystem` for portable file operations and `std::optional` for error handling, avoiding exceptions for better performance and predictability.

### Thread-Safe Queue (`src/data_structures/thread_safe_queue.h`)

A concurrent queue implementation that:
- Provides thread-safe access using mutexes
- Supports blocking operations for producer-consumer patterns
- Includes timeout capabilities for bounded wait times

The implementation uses `std::mutex` and `std::condition_variable` to provide synchronization, following best practices for thread-safe data structures in C++.

### LRU Cache (`src/data_structures/lru_cache.h`)

A Least Recently Used cache implementation that:
- Maintains items in order of access recency
- Automatically evicts least recently used items when capacity is reached
- Provides O(1) lookup and update operations

The implementation combines a doubly-linked list for tracking usage order with an unordered map for fast key lookups.

### Sorting Algorithms (`src/algorithms/sorting.h`)

Various sorting algorithm implementations including:
- QuickSort: General-purpose sorting with O(n log n) average performance
- CountingSort: Integer sorting with O(n + k) performance
- RadixSort: Integer sorting for large ranges

These implementations allow users to select appropriate algorithms based on their specific data characteristics and performance requirements.

### Statistical Functions (`src/math/statistics.h`)

Mathematical utilities for statistical analysis including:
- Mean: Average value calculation
- Median: Middle value determination
- Standard deviation and variance
- Correlation functions

These are implemented as template functions to support different numeric types while maintaining type safety.

## Data Flow

The library components are primarily stateless utility functions with clearly defined inputs and outputs. Where state is maintained (e.g., in the LRU Cache or Thread-Safe Queue), it is encapsulated within the respective classes with well-defined public interfaces.

Typical data flow patterns include:

1. Input validation → Processing → Result generation (for utility functions)
2. State modification → State validation → Result generation (for stateful components)

Error handling is primarily done through return value patterns using `std::optional` rather than exceptions, allowing for more predictable performance characteristics and clearer error propagation.

## External Dependencies

The library has minimal external dependencies to maximize portability and minimize integration complexity:

1. **GoogleTest**: Used for unit testing (managed via Bazel's external dependency system)
2. **Google Benchmark**: Used for performance testing
3. **C++17 Standard Library**: Leveraged extensively for containers, algorithms, and filesystem operations

The deliberate choice to minimize external dependencies:
- Reduces complexity for library users
- Minimizes potential version conflicts
- Simplifies build and deployment processes
- Enhances long-term maintainability

## Testing Strategy

The library employs a comprehensive testing approach:

1. **Unit Tests**: Each component has corresponding unit tests verifying its functionality
2. **Integration Tests**: Examples demonstrate the integration of multiple components
3. **Performance Tests**: Google Benchmark is used for performance-critical components

The tests are organized to mirror the source code structure, maintaining a clear relationship between implementation and verification.

## Deployment Strategy

The library is designed to be included in other C++ projects using Bazel's dependency management. Key aspects of the deployment strategy include:

1. **Header-Only Where Appropriate**: Many components are implemented as header-only libraries to simplify integration
2. **Clear API Boundaries**: Public interfaces are well-documented with extensive comments
3. **Versioned Releases**: The library supports integration via specific versions
4. **Modular Dependencies**: Users can include only the specific components they need

The build configuration allows for both:
- Static linking (for performance-critical applications)
- Dynamic linking (for applications that need to reduce binary size)

## Design Principles

Several key design principles guide the architecture:

1. **Modularity**: Components are designed with minimal interdependencies
2. **Type Safety**: Template programming is used to provide compile-time type checking
3. **Resource Management**: Modern C++ idioms (RAII, smart pointers) ensure proper resource handling
4. **Performance**: Implementations prioritize efficiency while maintaining clarity
5. **Thread Safety**: Concurrent components are explicitly designed and documented for multi-threaded use

These principles ensure the library is robust, efficient, and easy to integrate into various C++ applications.