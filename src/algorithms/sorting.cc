#include "src/algorithms/sorting.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <vector>

namespace cpp_utils {
namespace algorithms {

// CountingSort implementation
void CountingSort(std::vector<int>& data, int max_value) {
    int size = static_cast<int>(data.size());
    if (size <= 1) {
        return;
    }
    
    // Create a count array to store count of each number
    std::vector<int> count(max_value + 1, 0);
    
    // Store count of each number
    for (int i = 0; i < size; ++i) {
        count[data[i]]++;
    }
    
    // Change count[i] so that count[i] now contains
    // actual position of this number in output array
    for (int i = 1; i <= max_value; ++i) {
        count[i] += count[i - 1];
    }
    
    // Build the output array
    std::vector<int> output(size);
    for (int i = size - 1; i >= 0; --i) {
        output[count[data[i]] - 1] = data[i];
        count[data[i]]--;
    }
    
    // Copy the output array to data
    for (int i = 0; i < size; ++i) {
        data[i] = output[i];
    }
}

// RadixSort implementation
void RadixSort(std::vector<int>& data) {
    if (data.empty()) {
        return;
    }
    
    // Find the maximum number to know number of digits
    int max_num = *std::max_element(data.begin(), data.end());
    
    // Do counting sort for every digit
    for (int exp = 1; max_num / exp > 0; exp *= 10) {
        int size = static_cast<int>(data.size());
        std::vector<int> output(size);
        std::vector<int> count(10, 0);
        
        // Store count of occurrences in count[]
        for (int i = 0; i < size; ++i) {
            count[(data[i] / exp) % 10]++;
        }
        
        // Change count[i] so that count[i] now contains actual
        // position of this digit in output[]
        for (int i = 1; i < 10; ++i) {
            count[i] += count[i - 1];
        }
        
        // Build the output array
        for (int i = size - 1; i >= 0; --i) {
            output[count[(data[i] / exp) % 10] - 1] = data[i];
            count[(data[i] / exp) % 10]--;
        }
        
        // Copy the output array to data[]
        for (int i = 0; i < size; ++i) {
            data[i] = output[i];
        }
    }
}

}  // namespace algorithms
}  // namespace cpp_utils
