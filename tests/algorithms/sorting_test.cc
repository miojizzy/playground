#include "src/algorithms/sorting.h"

#include <algorithm>
#include <functional>
#include <random>
#include <vector>
#include <gtest/gtest.h>

namespace cpp_utils {
namespace algorithms {
namespace {

class SortingTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create various test vectors
        empty_ = {};
        single_element_ = {42};
        sorted_ = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        reverse_sorted_ = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        duplicates_ = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
        
        // Create a random vector
        std::random_device rd;
        std::mt19937 g(rd());
        random_.resize(1000);
        std::iota(random_.begin(), random_.end(), 0);  // Fill with 0, 1, 2, ...
        std::shuffle(random_.begin(), random_.end(), g);
    }

    std::vector<int> empty_;
    std::vector<int> single_element_;
    std::vector<int> sorted_;
    std::vector<int> reverse_sorted_;
    std::vector<int> duplicates_;
    std::vector<int> random_;
};

TEST_F(SortingTest, QuickSort) {
    // Test with empty vector
    auto test_vector = empty_;
    QuickSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with single element
    test_vector = single_element_;
    QuickSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with sorted vector
    test_vector = sorted_;
    QuickSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with reverse sorted vector
    test_vector = reverse_sorted_;
    QuickSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with duplicates
    test_vector = duplicates_;
    QuickSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with random vector
    test_vector = random_;
    QuickSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with custom comparator (sort descending)
    test_vector = random_;
    QuickSort(test_vector, std::greater<int>());
    EXPECT_TRUE(IsSorted(test_vector, std::greater<int>()));
}

TEST_F(SortingTest, MergeSort) {
    // Test with empty vector
    auto test_vector = empty_;
    MergeSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with single element
    test_vector = single_element_;
    MergeSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with sorted vector
    test_vector = sorted_;
    MergeSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with reverse sorted vector
    test_vector = reverse_sorted_;
    MergeSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with duplicates
    test_vector = duplicates_;
    MergeSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with random vector
    test_vector = random_;
    MergeSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with custom comparator (sort descending)
    test_vector = random_;
    MergeSort(test_vector, std::greater<int>());
    EXPECT_TRUE(IsSorted(test_vector, std::greater<int>()));
}

TEST_F(SortingTest, HeapSort) {
    // Test with empty vector
    auto test_vector = empty_;
    HeapSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with single element
    test_vector = single_element_;
    HeapSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with sorted vector
    test_vector = sorted_;
    HeapSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with reverse sorted vector
    test_vector = reverse_sorted_;
    HeapSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with duplicates
    test_vector = duplicates_;
    HeapSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with random vector
    test_vector = random_;
    HeapSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with custom comparator (sort descending)
    test_vector = random_;
    HeapSort(test_vector, std::greater<int>());
    EXPECT_TRUE(IsSorted(test_vector, std::greater<int>()));
}

TEST_F(SortingTest, InsertionSort) {
    // Test with empty vector
    auto test_vector = empty_;
    InsertionSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with single element
    test_vector = single_element_;
    InsertionSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with sorted vector
    test_vector = sorted_;
    InsertionSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with reverse sorted vector
    test_vector = reverse_sorted_;
    InsertionSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with duplicates
    test_vector = duplicates_;
    InsertionSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with custom comparator (sort descending)
    test_vector = duplicates_;
    InsertionSort(test_vector, std::greater<int>());
    EXPECT_TRUE(IsSorted(test_vector, std::greater<int>()));
    
    // Don't test with the large random vector - insertion sort is slow for large inputs
}

TEST_F(SortingTest, CountingSort) {
    // Test with empty vector
    auto test_vector = empty_;
    CountingSort(test_vector, 0);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with single element
    test_vector = single_element_;
    CountingSort(test_vector, 42);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with sorted vector
    test_vector = sorted_;
    CountingSort(test_vector, 10);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with reverse sorted vector
    test_vector = reverse_sorted_;
    CountingSort(test_vector, 10);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with duplicates
    test_vector = duplicates_;
    CountingSort(test_vector, 9);
    EXPECT_TRUE(IsSorted(test_vector));
}

TEST_F(SortingTest, RadixSort) {
    // Test with empty vector
    auto test_vector = empty_;
    RadixSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with single element
    test_vector = single_element_;
    RadixSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with sorted vector
    test_vector = sorted_;
    RadixSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with reverse sorted vector
    test_vector = reverse_sorted_;
    RadixSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with duplicates
    test_vector = duplicates_;
    RadixSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
    
    // Test with random vector
    test_vector = random_;
    RadixSort(test_vector);
    EXPECT_TRUE(IsSorted(test_vector));
}

TEST_F(SortingTest, QuickSelect) {
    // Test with a simple vector
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    
    // Find the minimum element (k=0)
    int result = QuickSelect(data, 0);
    EXPECT_EQ(1, result);
    
    // Find the maximum element (k=size-1)
    result = QuickSelect(data, data.size() - 1);
    EXPECT_EQ(9, result);
    
    // Find the median
    result = QuickSelect(data, data.size() / 2);
    
    // Sort the vector to verify
    std::vector<int> sorted_data = data;
    std::sort(sorted_data.begin(), sorted_data.end());
    EXPECT_EQ(sorted_data[sorted_data.size() / 2], result);
    
    // Test with the random vector
    int random_index = random_.size() / 3;
    std::vector<int> sorted_random = random_;
    std::sort(sorted_random.begin(), sorted_random.end());
    
    result = QuickSelect(random_, random_index);
    EXPECT_EQ(sorted_random[random_index], result);
}

TEST_F(SortingTest, IsSorted) {
    EXPECT_TRUE(IsSorted(empty_));
    EXPECT_TRUE(IsSorted(single_element_));
    EXPECT_TRUE(IsSorted(sorted_));
    EXPECT_FALSE(IsSorted(reverse_sorted_));
    EXPECT_FALSE(IsSorted(duplicates_));
    EXPECT_FALSE(IsSorted(random_));
    
    // Test with custom comparator
    EXPECT_TRUE(IsSorted(reverse_sorted_, std::greater<int>()));
    EXPECT_FALSE(IsSorted(sorted_, std::greater<int>()));
}

}  // namespace
}  // namespace algorithms
}  // namespace cpp_utils
