/**
 * @file example_main.cc
 * @brief Main example showcasing features of the cpp_utils library.
 */

#include <iostream>
#include <string>
#include <vector>

#include "src/utils/string_utils.h"
#include "src/utils/file_utils.h"
#include "src/data_structures/thread_safe_queue.h"
#include "src/data_structures/lru_cache.h"
#include "src/algorithms/sorting.h"
#include "src/math/statistics.h"

int main() {
    std::cout << "C++17 Utility Library Examples" << std::endl;
    std::cout << "============================" << std::endl << std::endl;

    // String utilities example
    std::cout << "String Utilities:" << std::endl;
    std::cout << "----------------" << std::endl;
    
    std::string test_string = "  Hello, World!  ";
    std::cout << "Original string: \"" << test_string << "\"" << std::endl;
    std::cout << "Trimmed: \"" << cpp_utils::utils::Trim(test_string) << "\"" << std::endl;
    std::cout << "Upper case: \"" << cpp_utils::utils::ToUpper(test_string) << "\"" << std::endl;
    std::cout << "Lower case: \"" << cpp_utils::utils::ToLower(test_string) << "\"" << std::endl;
    
    std::string csv = "apple,banana,cherry,date";
    std::cout << "CSV string: \"" << csv << "\"" << std::endl;
    
    auto split_result = cpp_utils::utils::Split(csv, ',');
    std::cout << "Split by comma: ";
    for (const auto& fruit : split_result) {
        std::cout << "\"" << fruit << "\" ";
    }
    std::cout << std::endl;
    
    std::cout << "Joined with semicolon: \"" 
              << cpp_utils::utils::Join(split_result, ";") << "\"" << std::endl;
    
    std::cout << std::endl;
    
    // File utilities example
    std::cout << "File Utilities:" << std::endl;
    std::cout << "--------------" << std::endl;
    
    std::string filename = "/tmp/cpp_utils_example.txt";
    std::string test_content = "This is a test file.\nCreated by cpp_utils library example.";
    
    std::cout << "Writing to " << filename << std::endl;
    if (cpp_utils::utils::WriteFile(filename, test_content)) {
        std::cout << "File written successfully." << std::endl;
        
        auto content = cpp_utils::utils::ReadFile(filename);
        if (content) {
            std::cout << "File content read (" << content->size() << " bytes):" << std::endl;
            std::cout << "---" << std::endl;
            std::cout << *content << std::endl;
            std::cout << "---" << std::endl;
        }
        
        auto lines = cpp_utils::utils::ReadLines(filename);
        if (lines) {
            std::cout << "File lines (" << lines->size() << " lines):" << std::endl;
            for (const auto& line : *lines) {
                std::cout << "  " << line << std::endl;
            }
        }
    }
    
    std::cout << std::endl;
    
    // Sorting algorithms example
    std::cout << "Sorting Algorithms:" << std::endl;
    std::cout << "------------------" << std::endl;
    
    std::vector<int> numbers = {9, 1, 8, 2, 7, 3, 6, 4, 5};
    std::cout << "Original vector: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    auto numbers_copy = numbers;
    cpp_utils::algorithms::QuickSort(numbers_copy);
    std::cout << "After QuickSort: ";
    for (int num : numbers_copy) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    numbers_copy = numbers;
    cpp_utils::algorithms::MergeSort(numbers_copy);
    std::cout << "After MergeSort: ";
    for (int num : numbers_copy) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    numbers_copy = numbers;
    cpp_utils::algorithms::HeapSort(numbers_copy);
    std::cout << "After HeapSort: ";
    for (int num : numbers_copy) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    numbers_copy = numbers;
    cpp_utils::algorithms::CountingSort(numbers_copy, 9);
    std::cout << "After CountingSort: ";
    for (int num : numbers_copy) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    std::cout << std::endl;
    
    // Statistics examples
    std::cout << "Statistics Functions:" << std::endl;
    std::cout << "--------------------" << std::endl;
    
    std::vector<double> data = {12.5, 10.0, 15.3, 9.8, 8.2, 13.7, 14.5, 11.2};
    std::cout << "Data set: ";
    for (double val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    auto mean = cpp_utils::math::Mean(data);
    auto median = cpp_utils::math::Median(data);
    auto stddev = cpp_utils::math::StandardDeviation(data);
    auto range = cpp_utils::math::Range(data);
    
    if (mean) {
        std::cout << "Mean: " << *mean << std::endl;
    }
    
    if (median) {
        std::cout << "Median: " << *median << std::endl;
    }
    
    if (stddev) {
        std::cout << "Standard Deviation: " << *stddev << std::endl;
    }
    
    if (range) {
        std::cout << "Range: [" << range->first << ", " << range->second << "]" << std::endl;
    }
    
    std::vector<double> percentile_values = {25.0, 50.0, 75.0, 90.0};
    auto percentiles = cpp_utils::math::Percentiles(data, percentile_values);
    
    if (percentiles) {
        std::cout << "Percentiles:" << std::endl;
        for (size_t i = 0; i < percentile_values.size(); ++i) {
            std::cout << "  " << percentile_values[i] << "%: " << (*percentiles)[i] << std::endl;
        }
    }
    
    std::cout << std::endl;
    
    // Data structures examples
    std::cout << "Data Structures:" << std::endl;
    std::cout << "---------------" << std::endl;
    
    // LRU Cache example
    cpp_utils::data_structures::LRUCache<std::string, int> cache(3);
    
    std::cout << "LRU Cache with capacity 3:" << std::endl;
    cache.Put("one", 1);
    cache.Put("two", 2);
    cache.Put("three", 3);
    
    std::cout << "After adding three items:" << std::endl;
    std::cout << "Contains 'one': " << (cache.Contains("one") ? "yes" : "no") << std::endl;
    std::cout << "Contains 'two': " << (cache.Contains("two") ? "yes" : "no") << std::endl;
    std::cout << "Contains 'three': " << (cache.Contains("three") ? "yes" : "no") << std::endl;
    
    // Add one more item, which should evict the least recently used item
    cache.Put("four", 4);
    
    std::cout << "After adding 'four':" << std::endl;
    std::cout << "Contains 'one': " << (cache.Contains("one") ? "yes" : "no") << std::endl;
    std::cout << "Contains 'two': " << (cache.Contains("two") ? "yes" : "no") << std::endl;
    std::cout << "Contains 'three': " << (cache.Contains("three") ? "yes" : "no") << std::endl;
    std::cout << "Contains 'four': " << (cache.Contains("four") ? "yes" : "no") << std::endl;
    
    // Access 'two', making it the most recently used
    auto val = cache.Get("two");
    std::cout << "Got 'two': " << (val ? std::to_string(*val) : "not found") << std::endl;
    
    // Now add one more item, which should evict the next least recently used
    cache.Put("five", 5);
    
    std::cout << "After accessing 'two' and adding 'five':" << std::endl;
    std::cout << "Contains 'two': " << (cache.Contains("two") ? "yes" : "no") << std::endl;
    std::cout << "Contains 'three': " << (cache.Contains("three") ? "yes" : "no") << std::endl;
    std::cout << "Contains 'four': " << (cache.Contains("four") ? "yes" : "no") << std::endl;
    std::cout << "Contains 'five': " << (cache.Contains("five") ? "yes" : "no") << std::endl;
    
    return 0;
}
