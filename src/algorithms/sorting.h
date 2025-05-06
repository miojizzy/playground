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
 * @brief Sorts a range using the quicksort algorithm.
 * @tparam RandomIt The type of iterators.
 * @tparam Compare The type of comparison function.
 * @param first Iterator to the first element.
 * @param last Iterator to one past the last element.
 * @param comp The comparison function (defaults to less than).
 */
template <typename RandomIt, typename Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
void QuickSort(RandomIt first, RandomIt last, Compare comp = Compare{}) {
    if (first >= last) {
        return;
    }
    
    using T = typename std::iterator_traits<RandomIt>::value_type;
    auto size = std::distance(first, last);
    std::function<void(RandomIt, RandomIt)> quicksort_impl = [&](RandomIt low, RandomIt high) {
        if (low < high) {
            // Choose pivot (last element)
            auto pivot_it = std::prev(high);
            auto partition_it = low;
            
            // Partition the array
            for (auto it = low; it != pivot_it; ++it) {
                if (comp(*it, *pivot_it)) {
                    std::swap(*partition_it, *it);
                    ++partition_it;
                }
            }
            
            // Move pivot to its final position
            std::swap(*partition_it, *pivot_it);
            
            // Recursively sort the sub-arrays
            if (partition_it != low) {
                quicksort_impl(low, partition_it);
            }
            if (std::next(partition_it) != high) {
                quicksort_impl(std::next(partition_it), high);
            }
        }
    };
    
    quicksort_impl(first, last);
}

/**
 * @brief Sorts a vector using the quicksort algorithm.
 * @tparam T The type of elements to sort.
 * @param data The vector to sort.
 * @param comp The comparison function (defaults to less than).
 */
template <typename T, typename Compare = std::less<T>>
void QuickSort(std::vector<T>& data, Compare comp = Compare{}) {
    if (!data.empty()) {
        QuickSort(data.begin(), data.end(), comp);
    }
}

/**
 * @brief Sorts a range using the merge sort algorithm.
 * @tparam RandomIt The type of iterators.
 * @tparam Compare The type of comparison function.
 * @param first Iterator to the first element.
 * @param last Iterator to one past the last element.
 * @param comp The comparison function (defaults to less than).
 */
template <typename RandomIt, typename Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
void MergeSort(RandomIt first, RandomIt last, Compare comp = Compare{}) {
    using T = typename std::iterator_traits<RandomIt>::value_type;
    auto dist = std::distance(first, last);
    
    if (dist <= 1) {
        return;
    }
    
    // Internal helper function for merging two sorted sub-ranges
    std::function<void(RandomIt, RandomIt, RandomIt)> merge = [&](RandomIt left, RandomIt middle, RandomIt right) {
        std::vector<T> temp(std::distance(left, right));
        
        auto it1 = left;
        auto it2 = middle;
        auto temp_it = temp.begin();
        
        // Merge elements from both sub-ranges
        while (it1 != middle && it2 != right) {
            if (comp(*it1, *it2)) {
                *temp_it++ = *it1++;
            } else {
                *temp_it++ = *it2++;
            }
        }
        
        // Copy remaining elements from left sub-range
        std::copy(it1, middle, temp_it);
        
        // Copy remaining elements from right sub-range
        std::copy(it2, right, temp_it);
        
        // Copy merged elements back to original range
        std::copy(temp.begin(), temp.end(), left);
    };
    
    // Internal helper function for recursive merge sort
    std::function<void(RandomIt, RandomIt)> mergesort_impl = [&](RandomIt l, RandomIt r) {
        auto dist = std::distance(l, r);
        if (dist <= 1) {
            return;
        }
        
        auto mid = l;
        std::advance(mid, dist / 2);
        
        // Sort first and second halves
        mergesort_impl(l, mid);
        mergesort_impl(mid, r);
        
        // Merge the sorted halves
        merge(l, mid, r);
    };
    
    mergesort_impl(first, last);
}

/**
 * @brief Sorts a vector using the merge sort algorithm.
 * @tparam T The type of elements to sort.
 * @param data The vector to sort.
 * @param comp The comparison function (defaults to less than).
 */
template <typename T, typename Compare = std::less<T>>
void MergeSort(std::vector<T>& data, Compare comp = Compare{}) {
    if (!data.empty()) {
        MergeSort(data.begin(), data.end(), comp);
    }
}

/**
 * @brief Sorts a range using the heap sort algorithm.
 * @tparam RandomIt The type of iterators.
 * @tparam Compare The type of comparison function.
 * @param first Iterator to the first element.
 * @param last Iterator to one past the last element.
 * @param comp The comparison function (defaults to less than).
 */
template <typename RandomIt, typename Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
void HeapSort(RandomIt first, RandomIt last, Compare comp = Compare{}) {
    auto size = std::distance(first, last);
    if (size <= 1) {
        return;
    }
    
    // Define heapify function
    auto heapify = [&](RandomIt begin, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        // Check if left child is larger than root
        if (left < n && comp(*(begin + largest), *(begin + left))) {
            largest = left;
        }
        
        // Check if right child is larger than largest so far
        if (right < n && comp(*(begin + largest), *(begin + right))) {
            largest = right;
        }
        
        // Change root if needed
        if (largest != i) {
            std::swap(*(begin + i), *(begin + largest));
            
            // Recursively heapify the affected sub-tree
            heapify(begin, n, largest);
        }
    };
    
    // Build heap (rearrange array)
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(first, size, i);
    }
    
    // Extract elements from heap one by one
    for (int i = size - 1; i > 0; --i) {
        // Move current root to end
        std::swap(*first, *(first + i));
        
        // Call max heapify on the reduced heap
        heapify(first, i, 0);
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
    if (!data.empty()) {
        HeapSort(data.begin(), data.end(), comp);
    }
}

/**
 * @brief Sorts a range using the insertion sort algorithm.
 * @tparam RandomIt The type of iterators.
 * @tparam Compare The type of comparison function.
 * @param first Iterator to the first element.
 * @param last Iterator to one past the last element.
 * @param comp The comparison function (defaults to less than).
 */
template <typename RandomIt, typename Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
void InsertionSort(RandomIt first, RandomIt last, Compare comp = Compare{}) {
    if (first == last) {
        return;
    }
    
    for (auto it = first + 1; it != last; ++it) {
        auto key = *it;
        auto j = it - 1;
        
        // Move elements from first to it-1 that are greater than key
        // to one position ahead of their current position
        while (j >= first && comp(key, *j)) {
            *(j + 1) = *j;
            --j;
        }
        *(j + 1) = key;
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
    if (!data.empty()) {
        InsertionSort(data.begin(), data.end(), comp);
    }
}

/**
 * @brief Finds the k-th smallest element in an unsorted range.
 * @tparam RandomIt The type of iterators.
 * @tparam Compare The type of comparison function.
 * @param first Iterator to the first element.
 * @param last Iterator to one past the last element.
 * @param k The position of the element to find (0-based, relative to the range).
 * @param comp The comparison function (defaults to less than).
 * @return Iterator to the k-th smallest element.
 */
template <typename RandomIt, typename Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
RandomIt QuickSelectIterator(RandomIt first, RandomIt last, size_t k, Compare comp = Compare{}) {
    using T = typename std::iterator_traits<RandomIt>::value_type;
    auto dist = std::distance(first, last);
    
    assert(k < static_cast<size_t>(dist) && "k must be less than the size of the range");
    
    // Create a copy of the input range to avoid modifying it
    std::vector<T> work_data(first, last);
    
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
    
    std::function<int(int, int, size_t)> quickselect_impl = [&](int low, int high, size_t target_k) {
        if (low == high) {
            return low;
        }
        
        size_t pivot_index = partition(low, high);
        
        if (target_k == pivot_index) {
            return static_cast<int>(pivot_index);
        } else if (target_k < pivot_index) {
            return quickselect_impl(low, static_cast<int>(pivot_index) - 1, target_k);
        } else {
            return quickselect_impl(static_cast<int>(pivot_index) + 1, high, target_k);
        }
    };
    
    int result_index = quickselect_impl(0, static_cast<int>(work_data.size()) - 1, k);
    
    // Return the original iterator advanced by the result index
    return std::next(first, result_index);
}

/**
 * @brief Finds the k-th smallest element in an unsorted range.
 * @tparam RandomIt The type of iterators.
 * @tparam Compare The type of comparison function.
 * @param first Iterator to the first element.
 * @param last Iterator to one past the last element.
 * @param k The position of the element to find (0-based, relative to the range).
 * @param comp The comparison function (defaults to less than).
 * @return The k-th smallest element.
 */
template <typename RandomIt, typename Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
typename std::iterator_traits<RandomIt>::value_type 
QuickSelect(RandomIt first, RandomIt last, size_t k, Compare comp = Compare{}) {
    RandomIt kth_element = QuickSelectIterator(first, last, k, comp);
    return *kth_element;
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
    return QuickSelect(data.begin(), data.end(), k, comp);
}

/**
 * @brief Checks if a range is sorted.
 * @tparam ForwardIt The type of iterators.
 * @tparam Compare The type of comparison function.
 * @param first Iterator to the first element.
 * @param last Iterator to one past the last element.
 * @param comp The comparison function (defaults to less than).
 * @return True if the range is sorted, false otherwise.
 */
template <typename ForwardIt, typename Compare = std::less<typename std::iterator_traits<ForwardIt>::value_type>>
bool IsSorted(ForwardIt first, ForwardIt last, Compare comp = Compare{}) {
    if (first == last) {
        return true;
    }
    
    ForwardIt next = first;
    ++next;
    
    while (next != last) {
        if (comp(*next, *first)) {
            return false;
        }
        ++first;
        ++next;
    }
    
    return true;
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
    return IsSorted(data.begin(), data.end(), comp);
}

// Non-template function declarations (defined in .cc file)

/**
 * @brief Sorts a vector of integers using counting sort.
 * @param data The vector of integers to sort.
 * @param max_value The maximum value in the vector. If not provided, it will be computed.
 */
void CountingSort(std::vector<int>& data, int max_value = -1);

/**
 * @brief Sorts a vector of integers using radix sort.
 * @param data The vector of integers to sort.
 */
void RadixSort(std::vector<int>& data);

}  // namespace algorithms
}  // namespace cpp_utils

#endif  // CPP_UTILS_LIB_SRC_ALGORITHMS_SORTING_H_
