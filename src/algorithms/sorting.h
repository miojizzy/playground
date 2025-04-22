/**
 * @file sorting.h
 * @brief Implementations of various sorting algorithms.
 */

#ifndef CPP_UTILS_LIB_SRC_ALGORITHMS_SORTING_H_
#define CPP_UTILS_LIB_SRC_ALGORITHMS_SORTING_H_

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <vector>

namespace cpp_utils {
namespace algorithms {

/**
 * @brief Sorts a vector using the quicksort algorithm.
 * @tparam T The type of elements to sort.
 * @param data The vector to sort.
 * @param comp The comparison function (defaults to less than).
 */
template <typename T, typename Compare = std::less<T>>
void QuickSort(std::vector<T>& data, Compare comp = Compare{}) {
    // Internal helper function
    std::function<void(int, int)> quicksort_impl = [&](int low, int high) {
        if (low < high) {
            // Partition the array
            T pivot = data[high];
            int i = low - 1;
            
            for (int j = low; j < high; ++j) {
                if (comp(data[j], pivot)) {
                    ++i;
                    std::swap(data[i], data[j]);
                }
            }
            
            std::swap(data[i + 1], data[high]);
            int partition_index = i + 1;
            
            // Recursively sort the sub-arrays
            quicksort_impl(low, partition_index - 1);
            quicksort_impl(partition_index + 1, high);
        }
    };
    
    if (!data.empty()) {
        quicksort_impl(0, static_cast<int>(data.size()) - 1);
    }
}

/**
 * @brief Sorts a vector using the merge sort algorithm.
 * @tparam T The type of elements to sort.
 * @param data The vector to sort.
 * @param comp The comparison function (defaults to less than).
 */
template <typename T, typename Compare = std::less<T>>
void MergeSort(std::vector<T>& data, Compare comp = Compare{}) {
    // Internal helper function for merging two sorted sub-arrays
    std::function<void(int, int, int)> merge = [&](int left, int middle, int right) {
        int n1 = middle - left + 1;
        int n2 = right - middle;
        
        // Create temporary arrays
        std::vector<T> L(n1), R(n2);
        
        // Copy data to temporary arrays
        for (int i = 0; i < n1; ++i) {
            L[i] = data[left + i];
        }
        for (int j = 0; j < n2; ++j) {
            R[j] = data[middle + 1 + j];
        }
        
        // Merge the temporary arrays back into data[left..right]
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (comp(L[i], R[j])) {
                data[k] = L[i];
                ++i;
            } else {
                data[k] = R[j];
                ++j;
            }
            ++k;
        }
        
        // Copy the remaining elements of L, if any
        while (i < n1) {
            data[k] = L[i];
            ++i;
            ++k;
        }
        
        // Copy the remaining elements of R, if any
        while (j < n2) {
            data[k] = R[j];
            ++j;
            ++k;
        }
    };
    
    // Internal helper function for recursive merge sort
    std::function<void(int, int)> mergesort_impl = [&](int left, int right) {
        if (left < right) {
            int middle = left + (right - left) / 2;
            
            // Sort first and second halves
            mergesort_impl(left, middle);
            mergesort_impl(middle + 1, right);
            
            // Merge the sorted halves
            merge(left, middle, right);
        }
    };
    
    if (!data.empty()) {
        mergesort_impl(0, static_cast<int>(data.size()) - 1);
    }
}

/**
 * @brief Sorts a vector using the heap sort algorithm.
 * @tparam T The type of elements to sort.
 * @param data The vector to sort.
 * @param comp The comparison function (defaults to less than).
 */
template <typename T, typename Compare = std::less<T>>
void HeapSort(std::vector<T>& data, Compare comp = Compare{}) {
    // Define heapify function using std::function to allow recursion
    std::function<void(int, int)> heapify = [&](int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        // Check if left child is larger than root
        if (left < n && comp(data[largest], data[left])) {
            largest = left;
        }
        
        // Check if right child is larger than largest so far
        if (right < n && comp(data[largest], data[right])) {
            largest = right;
        }
        
        // Change root if needed
        if (largest != i) {
            std::swap(data[i], data[largest]);
            
            // Recursively heapify the affected sub-tree
            heapify(n, largest);
        }
    };
    
    int n = static_cast<int>(data.size());
    
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(n, i);
    }
    
    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; --i) {
        // Move current root to end
        std::swap(data[0], data[i]);
        
        // Call max heapify on the reduced heap
        heapify(i, 0);
    }
}

/**
 * @brief Sorts a vector using the insertion sort algorithm.
 * @tparam T The type of elements to sort.
 * @param data The vector to sort.
 * @param comp The comparison function (defaults to less than).
 */
template <typename T, typename Compare = std::less<T>>
void InsertionSort(std::vector<T>& data, Compare comp = Compare{}) {
    int n = static_cast<int>(data.size());
    for (int i = 1; i < n; ++i) {
        T key = data[i];
        int j = i - 1;
        
        // Move elements of data[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && comp(key, data[j])) {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = key;
    }
}

/**
 * @brief Finds the k-th smallest element in an unsorted vector.
 * @tparam T The type of elements in the vector.
 * @param data The vector to search.
 * @param k The position of the element to find (0-based).
 * @param comp The comparison function (defaults to less than).
 * @return The k-th smallest element.
 */
template <typename T, typename Compare = std::less<T>>
T QuickSelect(const std::vector<T>& data, size_t k, Compare comp = Compare{}) {
    assert(k < data.size());
    
    // Create a copy of the input vector to avoid modifying it
    std::vector<T> work_data = data;
    
    // Internal helper function
    std::function<size_t(int, int)> partition = [&](int low, int high) {
        T pivot = work_data[high];
        int i = low - 1;
        
        for (int j = low; j < high; ++j) {
            if (comp(work_data[j], pivot)) {
                ++i;
                std::swap(work_data[i], work_data[j]);
            }
        }
        
        std::swap(work_data[i + 1], work_data[high]);
        return static_cast<size_t>(i + 1);
    };
    
    std::function<T(int, int, size_t)> quickselect_impl = [&](int low, int high, size_t k) {
        if (low == high) {
            return work_data[low];
        }
        
        size_t pivot_index = partition(low, high);
        
        if (k == pivot_index) {
            return work_data[pivot_index];
        } else if (k < pivot_index) {
            return quickselect_impl(low, static_cast<int>(pivot_index) - 1, k);
        } else {
            return quickselect_impl(static_cast<int>(pivot_index) + 1, high, k);
        }
    };
    
    return quickselect_impl(0, static_cast<int>(work_data.size()) - 1, k);
}

/**
 * @brief Checks if a vector is sorted.
 * @tparam T The type of elements in the vector.
 * @param data The vector to check.
 * @param comp The comparison function (defaults to less than).
 * @return True if the vector is sorted, false otherwise.
 */
template <typename T, typename Compare = std::less<T>>
bool IsSorted(const std::vector<T>& data, Compare comp = Compare{}) {
    if (data.empty() || data.size() == 1) {
        return true;
    }
    
    for (size_t i = 1; i < data.size(); ++i) {
        if (comp(data[i], data[i - 1])) {
            return false;
        }
    }
    
    return true;
}

// Non-template function declarations (defined in .cc file)

/**
 * @brief Sorts a vector of integers using counting sort.
 * @param data The vector of integers to sort.
 * @param max_value The maximum value in the vector.
 */
void CountingSort(std::vector<int>& data, int max_value);

/**
 * @brief Sorts a vector of integers using radix sort.
 * @param data The vector of integers to sort.
 */
void RadixSort(std::vector<int>& data);

}  // namespace algorithms
}  // namespace cpp_utils

#endif  // CPP_UTILS_LIB_SRC_ALGORITHMS_SORTING_H_
