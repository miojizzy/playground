/**
 * @file counter_utils_example.cc
 * @brief Examples showcasing the counter utility functions.
 */

#include <iostream>
#include <string>
#include <vector>

#include "src/utils/counter_utils.h"
#include "src/data_structures/custom_object.h"

namespace cpp_utils::examples

// step 1, define a custom counter for CustomObject
template<typename Key>
using ObjCounter = CounterTp<Key, data_structures::CustomObject>;

// step 1.1, (option) define a factory function for creating custom counter 
template<typename Key>
template<typename data_structures::CustomObject>
std::unique_ptr<data_structures::CustomObject> make_counter() {
    return std::make_unique<data_structures::CustomObject>();
}

// step 2, create a counter

void RunCounterUtilsExample() {
    std::cout << "Counter Utilities Examples" << std::endl;
    std::cout << "========================" << std::endl;

    // step 3, create a vector of CustomObject
    std::vector<data_structures::CustomObject> objects;
    objects.push_back(data_structures::CustomObject("first", 10));
    objects.push_back(data_structures::CustomObject("second", 20));
    objects.push_back(data_structures::CustomObject("third", 30));
    objects.push_back(data_structures::CustomObject("fourth", 40));
    objects.push_back(data_structures::CustomObject("fifth", 50));

    // step 2, create a counter
    
    

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

}  // namespace cpp_utils::examples