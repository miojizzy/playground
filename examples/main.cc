/**
 * @file main.cc
 * @brief Main example program showcasing all components of the cpp_utils library.
 */

#include <iostream>

// Forward declarations of example functions
namespace cpp_utils {
namespace examples {

void RunStringUtilsExample();
void RunFileUtilsExample();
void RunLRUCacheExample();
void RunThreadSafeQueueExample();

}  // namespace examples
}  // namespace cpp_utils

int main() {
  std::cout << "C++17 Utility Library Examples" << std::endl;
  std::cout << "=============================" << std::endl << std::endl;

  // Utils examples
  cpp_utils::examples::RunStringUtilsExample();
  std::cout << std::endl;
  
  cpp_utils::examples::RunFileUtilsExample();
  std::cout << std::endl;

  // Data Structures examples
  cpp_utils::examples::RunLRUCacheExample();
  std::cout << std::endl;
  
  cpp_utils::examples::RunThreadSafeQueueExample();
  std::cout << std::endl;

  return 0;
}