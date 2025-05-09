/**
 * @file custom_object_example.cc
 * @brief Examples showcasing the CustomObject data structure.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "src/data_structures/custom_object.h"

namespace cpp_utils {
namespace examples {

void RunCustomObjectExample() {
  std::cout << "CustomObject Examples" << std::endl;
  std::cout << "====================" << std::endl;
  
  // Basic construction and usage
  std::cout << "\n1. Basic construction and properties:" << std::endl;
  data_structures::CustomObject obj1("example_object", 100);
  
  std::cout << "Object properties - Name: " << obj1.GetName() 
            << ", Value: " << obj1.GetValue() << std::endl;
  
  // Using the Print method
  std::cout << "\nUsing the Print method:" << std::endl;
  obj1.Print();
  
  // Modifying object properties
  std::cout << "\n2. Modifying object properties:" << std::endl;
  obj1.SetName("modified_name");
  obj1.SetValue(200);
  
  std::cout << "After modification - ";
  obj1.Print();
  
  // Copy constructor
  std::cout << "\n3. Copy semantics:" << std::endl;
  std::cout << "Creating copy of the object:" << std::endl;
  data_structures::CustomObject copy_obj(obj1);
  
  std::cout << "Original: ";
  obj1.Print();
  std::cout << "Copy: ";
  copy_obj.Print();
  
  std::cout << "Modifying copy:" << std::endl;
  copy_obj.SetValue(300);
  copy_obj.SetName("copy_modified");
  
  std::cout << "After modifying copy - Original: ";
  obj1.Print();
  std::cout << "Modified copy: ";
  copy_obj.Print();
  
  // Move semantics
  std::cout << "\n4. Move semantics:" << std::endl;
  data_structures::CustomObject move_source("move_source", 500);
  std::cout << "Source before move: ";
  move_source.Print();
  
  std::cout << "Creating new object with std::move:" << std::endl;
  data_structures::CustomObject move_target(std::move(move_source));
  
  std::cout << "Target after move: ";
  move_target.Print();
  
  // Using comparison operators
  std::cout << "\n5. Comparison operations:" << std::endl;
  data_structures::CustomObject a("object_a", 10);
  data_structures::CustomObject b("object_b", 10);
  data_structures::CustomObject c("object_c", 20);
  data_structures::CustomObject a_clone("object_a", 10);
  
  std::cout << "a == a_clone: " << (a == a_clone ? "true" : "false") << std::endl;
  std::cout << "a != b: " << (a != b ? "true" : "false") << std::endl;
  std::cout << "a < b: " << (a < b ? "true" : "false") << std::endl;
  std::cout << "c > a: " << (c > a ? "true" : "false") << std::endl;
  std::cout << "a <= a_clone: " << (a <= a_clone ? "true" : "false") << std::endl;
  std::cout << "c >= b: " << (c >= b ? "true" : "false") << std::endl;
  
  // Using CustomObject in standard containers and algorithms
  std::cout << "\n6. Using CustomObject with STL:" << std::endl;
  std::vector<data_structures::CustomObject> objects;
  
  objects.push_back(data_structures::CustomObject("third", 30));
  objects.push_back(data_structures::CustomObject("first", 10));
  objects.push_back(data_structures::CustomObject("second", 20));
  
  std::cout << "Vector of CustomObjects (unsorted):" << std::endl;
  for (const auto& obj : objects) {
    obj.Print();
  }
  
  // Sort objects based on CustomObject's < operator
  std::sort(objects.begin(), objects.end());
  
  std::cout << "\nVector of CustomObjects (sorted by value and name):" << std::endl;
  for (const auto& obj : objects) {
    obj.Print();
  }
  
  std::cout << std::endl;
}

}  // namespace examples
}  // namespace cpp_utils