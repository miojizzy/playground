/**
 * @file sorting_example.cc
 * @brief Examples showcasing the sorting algorithms.
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>

#include "src/algorithms/sorting.h"

namespace cpp_utils {
namespace examples {

// Define a simple person structure
struct Person {
  std::string name;
  int age;
  
  // For easier printing
  friend std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p.name << " (" << p.age << ")";
    return os;
  }
};

template <typename T>
void PrintVector(const std::vector<T>& vec) {
  for (const auto& val : vec) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
}

void RunSortingExample() {
  std::cout << "Sorting Algorithms Examples" << std::endl;
  std::cout << "==========================" << std::endl;
  
  // Create a vector with random order of elements
  std::vector<int> data = {9, 1, 8, 2, 7, 3, 6, 4, 5};
  
  std::cout << "Original vector: ";
  PrintVector(data);
  
  // QuickSort example
  {
    std::vector<int> quick_sort_data = data;
    algorithms::QuickSort(quick_sort_data.begin(), quick_sort_data.end());
    std::cout << "After QuickSort: ";
    PrintVector(quick_sort_data);
  }
  
  // MergeSort example
  {
    std::vector<int> merge_sort_data = data;
    algorithms::MergeSort(merge_sort_data.begin(), merge_sort_data.end());
    std::cout << "After MergeSort: ";
    PrintVector(merge_sort_data);
  }
  
  // HeapSort example
  {
    std::vector<int> heap_sort_data = data;
    algorithms::HeapSort(heap_sort_data.begin(), heap_sort_data.end());
    std::cout << "After HeapSort: ";
    PrintVector(heap_sort_data);
  }
  
  // CountingSort example (for integers only)
  {
    std::vector<int> counting_sort_data = data;
    algorithms::CountingSort(counting_sort_data);
    std::cout << "After CountingSort: ";
    PrintVector(counting_sort_data);
  }
  
  // Using custom comparator
  {
    std::vector<int> reverse_sort_data = data;
    std::cout << "\nCustom comparator example (descending order):" << std::endl;
    std::cout << "Original: ";
    PrintVector(reverse_sort_data);
    
    // Use greater comparator for descending order
    algorithms::QuickSort(reverse_sort_data.begin(), reverse_sort_data.end(), 
                         std::greater<int>());
    
    std::cout << "Descending: ";
    PrintVector(reverse_sort_data);
  }
  
  // Sort custom objects
  {
    std::cout << "\nSorting custom objects:" << std::endl;
    
    // Use the Person type defined above
    std::vector<Person> people = {
      {"Alice", 30},
      {"Bob", 25},
      {"Charlie", 35},
      {"David", 20},
      {"Eve", 28}
    };
    
    std::cout << "Original people list:" << std::endl;
    for (const auto& person : people) {
      std::cout << "  " << person << std::endl;
    }
    
    // Sort by age
    algorithms::QuickSort(people.begin(), people.end(), 
                         [](const Person& a, const Person& b) {
                           return a.age < b.age;
                         });
    
    std::cout << "Sorted by age:" << std::endl;
    for (const auto& person : people) {
      std::cout << "  " << person << std::endl;
    }
    
    // Sort by name
    algorithms::QuickSort(people.begin(), people.end(), 
                         [](const Person& a, const Person& b) {
                           return a.name < b.name;
                         });
    
    std::cout << "Sorted by name:" << std::endl;
    for (const auto& person : people) {
      std::cout << "  " << person << std::endl;
    }
  }
  
  std::cout << std::endl;
}

}  // namespace examples
}  // namespace cpp_utils