/**
 * @file string_utils_example.cc
 * @brief Examples showcasing the string utility functions.
 */

#include <iostream>
#include <string>
#include <vector>

#include "src/utils/string_utils.h"

namespace cpp_utils {
namespace examples {

void RunStringUtilsExample() {
  std::cout << "String Utilities Examples" << std::endl;
  std::cout << "========================" << std::endl;
  
  // Split and Join
  std::string csv = "one,two,three,four,five";
  std::cout << "Original string: " << csv << std::endl;
  
  auto parts = utils::Split(csv, ',');
  std::cout << "Split by comma:" << std::endl;
  for (const auto& part : parts) {
    std::cout << "  " << part << std::endl;
  }
  
  std::string joined = utils::Join(parts, " | ");
  std::cout << "Joined with ' | ': " << joined << std::endl;
  
  // Trim, ToLower, ToUpper, etc.
  std::string padded = "  Hello, World!  ";
  std::cout << "\nPadded string: \"" << padded << "\"" << std::endl;
  std::cout << "Trimmed: \"" << utils::Trim(padded) << "\"" << std::endl;
  
  std::cout << "To upper: \"" << utils::ToUpper(padded) << "\"" << std::endl;
  std::cout << "To lower: \"" << utils::ToLower(padded) << "\"" << std::endl;
  
  // String checks
  std::string test = "Hello, World!";
  std::cout << "\nTest string: \"" << test << "\"" << std::endl;
  std::cout << "Starts with \"Hello\": " 
            << (utils::StartsWith(test, "Hello") ? "yes" : "no") << std::endl;
  std::cout << "Ends with \"World!\": " 
            << (utils::EndsWith(test, "World!") ? "yes" : "no") << std::endl;
  
  // Replace
  std::cout << "\nReplace 'World' with 'C++': \"" 
            << utils::Replace(test, "World", "C++") << "\"" << std::endl;
  
  // Conversion functions
  std::string number = "42";
  auto int_result = utils::ToInt(number);
  std::cout << "\nConvert \"" << number << "\" to int: " 
            << (int_result ? std::to_string(*int_result) : "failed") << std::endl;
  
  std::string float_number = "3.14159";
  auto double_result = utils::ToDouble(float_number);
  std::cout << "Convert \"" << float_number << "\" to double: " 
            << (double_result ? std::to_string(*double_result) : "failed") << std::endl;
  
  std::cout << std::endl;
}

}  // namespace examples
}  // namespace cpp_utils