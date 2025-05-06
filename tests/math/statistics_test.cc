#include "src/math/statistics.h"

#include <cmath>
#include <gtest/gtest.h>

namespace cpp_utils {
namespace math {
namespace {

class StatisticsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test data sets
        empty_ = {};
        single_element_ = {42.0};
        integers_ = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        doubles_ = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5};
        with_duplicates_ = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
        correlation_x_ = {1, 2, 3, 4, 5};
        correlation_y_ = {5, 4, 3, 2, 1};  // Negative correlation
        correlation_y_positive_ = {1, 2, 3, 4, 5};  // Positive correlation
    }

    std::vector<double> empty_;
    std::vector<double> single_element_;
    std::vector<int> integers_;
    std::vector<double> doubles_;
    std::vector<int> with_duplicates_;
    std::vector<int> correlation_x_;
    std::vector<int> correlation_y_;
    std::vector<int> correlation_y_positive_;
};

TEST_F(StatisticsTest, Mean) {
    // Test with empty vector
    auto result = Mean(empty_);
    EXPECT_FALSE(result.has_value());
    
    // Test with single element
    result = Mean(single_element_);
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(42.0, *result);
    
    // Test with integers
    result = Mean(integers_);
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(5.5, *result);
    
    // Test with doubles
    result = Mean(doubles_);
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(6.0, *result);
    
    // Test with duplicates
    result = Mean(with_duplicates_);
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(3.9, *result);
}

TEST_F(StatisticsTest, Median) {
    // Test with empty vector
    auto result = Median(empty_);
    EXPECT_FALSE(result.has_value());
    
    // Test with single element
    result = Median(single_element_);
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(42.0, *result);
    
    // Test with odd number of integers
    std::vector<int> odd_count = {1, 2, 3, 4, 5};
    result = Median(odd_count);
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(3.0, *result);
    
    // Test with even number of integers
    result = Median(integers_);
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(5.5, *result);
    
    // Test with duplicates
    std::vector<int> duplicates_copy = with_duplicates_;
    result = Median(duplicates_copy);
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(3.5, *result);
}

TEST_F(StatisticsTest, Mode) {
    // Test with empty vector
    auto result = Mode(empty_);
    EXPECT_FALSE(result.has_value());
    
    // Test with single element
    result = Mode(single_element_);
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(42.0, *result);
    
    // Test with no duplicates - since all values occur equally, Max-Element chooses the highest frequency value
    auto int_result = Mode(integers_);
    ASSERT_TRUE(int_result.has_value());
    // In our implementation, Mode function returns a value with the highest frequency
    // When all values have the same frequency, any value can be returned
    EXPECT_TRUE(*int_result >= 1 && *int_result <= 10);
    
    // Test with duplicates
    int_result = Mode(with_duplicates_);
    ASSERT_TRUE(int_result.has_value());
    // The mode should be either 1, 3, or 5 (all appear twice)
    EXPECT_TRUE(*int_result == 1 || *int_result == 3 || *int_result == 5);
    
    // Test with explicit duplicates
    std::vector<int> explicit_duplicates = {1, 2, 3, 3, 3, 4, 5};
    int_result = Mode(explicit_duplicates);
    ASSERT_TRUE(int_result.has_value());
    EXPECT_EQ(3, *int_result);
}

TEST_F(StatisticsTest, StandardDeviation) {
    // Test with empty vector
    auto result = StandardDeviation(empty_);
    EXPECT_FALSE(result.has_value());
    
    // Test with single element (should return nullopt)
    result = StandardDeviation(single_element_);
    EXPECT_FALSE(result.has_value());
    
    // Test with integers (sample standard deviation)
    result = StandardDeviation(integers_, true);
    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(3.0276, *result, 0.0001);
    
    // Test with integers (population standard deviation)
    result = StandardDeviation(integers_, false);
    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(2.8722, *result, 0.0001);
    
    // Test with doubles
    result = StandardDeviation(doubles_, true);
    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(3.0276, *result, 0.0001);
}

TEST_F(StatisticsTest, Variance) {
    // Test with empty vector
    auto result = Variance(empty_);
    EXPECT_FALSE(result.has_value());
    
    // Test with single element (should return nullopt)
    result = Variance(single_element_);
    EXPECT_FALSE(result.has_value());
    
    // Test with integers (sample variance)
    result = Variance(integers_, true);
    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(9.1667, *result, 0.0001);
    
    // Test with integers (population variance)
    result = Variance(integers_, false);
    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(8.25, *result, 0.0001);
}

TEST_F(StatisticsTest, Range) {
    // Test with empty vector
    auto result = Range(empty_);
    EXPECT_FALSE(result.has_value());
    
    // Test with single element
    auto int_result = Range(single_element_);
    ASSERT_TRUE(int_result.has_value());
    EXPECT_DOUBLE_EQ(42.0, int_result->first);
    EXPECT_DOUBLE_EQ(42.0, int_result->second);
    
    // Test with integers
    int_result = Range(integers_);
    ASSERT_TRUE(int_result.has_value());
    EXPECT_EQ(1, int_result->first);
    EXPECT_EQ(10, int_result->second);
    
    // Test with duplicates
    int_result = Range(with_duplicates_);
    ASSERT_TRUE(int_result.has_value());
    EXPECT_EQ(1, int_result->first);
    EXPECT_EQ(9, int_result->second);
}

TEST_F(StatisticsTest, Sum) {
    // Test with empty vector (should return zero)
    EXPECT_DOUBLE_EQ(0.0, Sum(empty_));
    
    // Test with single element
    EXPECT_DOUBLE_EQ(42.0, Sum(single_element_));
    
    // Test with integers
    EXPECT_EQ(55, Sum(integers_));
    
    // Test with doubles
    EXPECT_DOUBLE_EQ(60.0, Sum(doubles_));
}

TEST_F(StatisticsTest, Product) {
    // Test with empty vector (should return one)
    EXPECT_DOUBLE_EQ(1.0, Product(empty_));
    
    // Test with single element
    EXPECT_DOUBLE_EQ(42.0, Product(single_element_));
    
    // Test with integers
    EXPECT_EQ(3628800, Product(integers_));  // 10!
    
    // Test with small set for precision
    std::vector<double> small_set = {1.5, 2.5, 3.5};
    EXPECT_DOUBLE_EQ(13.125, Product(small_set));
}

TEST_F(StatisticsTest, Correlation) {
    // Test with empty vectors
    auto result = Correlation(empty_, empty_);
    EXPECT_FALSE(result.has_value());
    
    // Test with single element vectors (should return nullopt)
    std::vector<double> single1 = {1.0};
    std::vector<double> single2 = {2.0};
    result = Correlation(single1, single2);
    EXPECT_FALSE(result.has_value());
    
    // Test with vectors of different sizes
    result = Correlation(integers_, empty_);
    EXPECT_FALSE(result.has_value());
    
    // Test with perfectly negative correlation
    result = Correlation(correlation_x_, correlation_y_);
    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(-1.0, *result, 0.0001);
    
    // Test with perfectly positive correlation
    result = Correlation(correlation_x_, correlation_y_positive_);
    ASSERT_TRUE(result.has_value());
    EXPECT_NEAR(1.0, *result, 0.0001);
    
    // Test with no variation in one variable
    std::vector<int> constant = {5, 5, 5, 5, 5};
    result = Correlation(constant, correlation_y_);
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(0.0, *result);
}

TEST_F(StatisticsTest, Percentiles) {
    // Test with empty vector
    std::vector<double> percentile_values = {25.0, 50.0, 75.0};
    auto result = Percentiles(empty_, percentile_values);
    EXPECT_FALSE(result.has_value());
    
    // Test with invalid percentiles
    std::vector<double> invalid_percentiles = {-10.0, 50.0, 110.0};
    result = Percentiles(integers_, invalid_percentiles);
    EXPECT_FALSE(result.has_value());
    
    // Test with single element
    result = Percentiles(single_element_, percentile_values);
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(3, result->size());
    EXPECT_DOUBLE_EQ(42.0, (*result)[0]);
    EXPECT_DOUBLE_EQ(42.0, (*result)[1]);
    EXPECT_DOUBLE_EQ(42.0, (*result)[2]);
    
    // Test with integers
    std::vector<int> sorted_integers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    result = Percentiles(sorted_integers, percentile_values);
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(3, result->size());
    EXPECT_NEAR(3.25, (*result)[0], 0.0001);  // 25th percentile
    EXPECT_NEAR(5.5, (*result)[1], 0.0001);   // 50th percentile (median)
    EXPECT_NEAR(7.75, (*result)[2], 0.0001);  // 75th percentile
    
    // Test with extremes (0% and 100%)
    std::vector<double> extreme_percentiles = {0.0, 100.0};
    result = Percentiles(sorted_integers, extreme_percentiles);
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(2, result->size());
    EXPECT_DOUBLE_EQ(1.0, (*result)[0]);  // Minimum
    EXPECT_DOUBLE_EQ(10.0, (*result)[1]); // Maximum
}

}  // namespace
}  // namespace math
}  // namespace cpp_utils
