/**
 * @file statistics.h
 * @brief Statistical utilities and functions.
 */

#ifndef CPP_UTILS_LIB_SRC_MATH_STATISTICS_H_
#define CPP_UTILS_LIB_SRC_MATH_STATISTICS_H_

#include <algorithm>
#include <cmath>
#include <numeric>
#include <optional>
#include <unordered_map>
#include <vector>

namespace cpp_utils {
namespace math {

/**
 * @brief Computes the mean of a vector of values.
 * @tparam T The numeric type.
 * @param values The values to compute the mean of.
 * @return The mean of the values, or std::nullopt if the vector is empty.
 */
template <typename T>
std::optional<double> Mean(const std::vector<T>& values) {
    if (values.empty()) {
        return std::nullopt;
    }
    
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    return sum / values.size();
}

/**
 * @brief Computes the median of a vector of values.
 * @tparam T The numeric type.
 * @param values The values to compute the median of.
 * @return The median of the values, or std::nullopt if the vector is empty.
 */
template <typename T>
std::optional<double> Median(std::vector<T> values) {
    if (values.empty()) {
        return std::nullopt;
    }
    
    std::sort(values.begin(), values.end());
    
    size_t size = values.size();
    if (size % 2 == 0) {
        // Even number of elements, return average of middle two
        return (static_cast<double>(values[size / 2 - 1]) + 
                static_cast<double>(values[size / 2])) / 2.0;
    } else {
        // Odd number of elements, return middle element
        return static_cast<double>(values[size / 2]);
    }
}

/**
 * @brief Computes the mode of a vector of values.
 * @tparam T The type of values.
 * @param values The values to compute the mode of.
 * @return The mode of the values, or std::nullopt if the vector is empty.
 */
template <typename T>
std::optional<T> Mode(const std::vector<T>& values) {
    if (values.empty()) {
        return std::nullopt;
    }
    
    std::unordered_map<T, int> counts;
    for (const auto& value : values) {
        counts[value]++;
    }
    
    T mode = values[0];
    int max_count = 0;
    
    for (const auto& [value, count] : counts) {
        if (count > max_count) {
            mode = value;
            max_count = count;
        }
    }
    
    return mode;
}

/**
 * @brief Computes the variance of a vector of values.
 * @tparam T The numeric type.
 * @param values The values to compute the variance of.
 * @param sample Whether to use the sample variance (n-1 denominator).
 * @return The variance of the values, or std::nullopt if the vector
 *         has fewer than 2 elements.
 */
template <typename T>
std::optional<double> Variance(const std::vector<T>& values, bool sample = true) {
    if (values.size() < 2) {
        return std::nullopt;
    }
    
    auto mean_opt = Mean(values);
    if (!mean_opt) {
        return std::nullopt;
    }
    
    double mean = *mean_opt;
    double sum_squared_diff = 0.0;
    
    for (const auto& value : values) {
        double diff = static_cast<double>(value) - mean;
        sum_squared_diff += diff * diff;
    }
    
    double denominator = sample ? (values.size() - 1) : values.size();
    return sum_squared_diff / denominator;
}

/**
 * @brief Computes the standard deviation of a vector of values.
 * @tparam T The numeric type.
 * @param values The values to compute the standard deviation of.
 * @param sample Whether to use the sample standard deviation (n-1 denominator).
 * @return The standard deviation of the values, or std::nullopt if the vector
 *         has fewer than 2 elements.
 */
template <typename T>
std::optional<double> StandardDeviation(const std::vector<T>& values, bool sample = true) {
    auto variance_opt = Variance(values, sample);
    if (!variance_opt) {
        return std::nullopt;
    }
    
    return std::sqrt(*variance_opt);
}

/**
 * @brief Computes the minimum and maximum values in a vector.
 * @tparam T The type of values.
 * @param values The values to find the range of.
 * @return A pair containing the minimum and maximum values, or std::nullopt if the vector is empty.
 */
template <typename T>
std::optional<std::pair<T, T>> Range(const std::vector<T>& values) {
    if (values.empty()) {
        return std::nullopt;
    }
    
    auto [min_it, max_it] = std::minmax_element(values.begin(), values.end());
    return std::make_pair(*min_it, *max_it);
}

/**
 * @brief Computes the sum of a vector of values.
 * @tparam T The numeric type.
 * @param values The values to sum.
 * @return The sum of the values.
 */
template <typename T>
T Sum(const std::vector<T>& values) {
    return std::accumulate(values.begin(), values.end(), T{});
}

/**
 * @brief Computes the product of a vector of values.
 * @tparam T The numeric type.
 * @param values The values to multiply.
 * @return The product of the values.
 */
template <typename T>
T Product(const std::vector<T>& values) {
    return std::accumulate(values.begin(), values.end(), T{1}, 
                          std::multiplies<T>());
}

/**
 * @brief Computes the Pearson correlation coefficient between two vectors.
 * @tparam T1 The numeric type of the first vector.
 * @tparam T2 The numeric type of the second vector.
 * @param x The first vector.
 * @param y The second vector.
 * @return The correlation coefficient, or std::nullopt if the vectors have different sizes
 *         or fewer than 2 elements.
 */
template <typename T1, typename T2>
std::optional<double> Correlation(const std::vector<T1>& x, const std::vector<T2>& y) {
    if (x.size() != y.size() || x.size() < 2) {
        return std::nullopt;
    }
    
    // Calculate means
    auto mean_x_opt = Mean(x);
    auto mean_y_opt = Mean(y);
    
    if (!mean_x_opt || !mean_y_opt) {
        return std::nullopt;
    }
    
    double mean_x = *mean_x_opt;
    double mean_y = *mean_y_opt;
    
    // Calculate the numerator (covariance) and denominators (std dev of x and y)
    double numerator = 0.0;
    double denominator_x = 0.0;
    double denominator_y = 0.0;
    
    for (size_t i = 0; i < x.size(); ++i) {
        double diff_x = static_cast<double>(x[i]) - mean_x;
        double diff_y = static_cast<double>(y[i]) - mean_y;
        
        numerator += diff_x * diff_y;
        denominator_x += diff_x * diff_x;
        denominator_y += diff_y * diff_y;
    }
    
    if (denominator_x == 0.0 || denominator_y == 0.0) {
        return 0.0;  // No correlation if there's no variation in one of the variables
    }
    
    return numerator / std::sqrt(denominator_x * denominator_y);
}

/**
 * @brief Computes percentiles for a vector of values.
 * @tparam T The numeric type.
 * @param values The values to compute percentiles for.
 * @param percentiles The percentiles to compute (0-100).
 * @return A vector of percentile values, or std::nullopt if the vector is empty.
 */
template <typename T>
std::optional<std::vector<double>> Percentiles(std::vector<T> values, 
                                             const std::vector<double>& percentiles) {
    if (values.empty() || percentiles.empty()) {
        return std::nullopt;
    }
    
    // Check if all percentiles are in valid range [0, 100]
    for (double p : percentiles) {
        if (p < 0.0 || p > 100.0) {
            return std::nullopt;
        }
    }
    
    std::sort(values.begin(), values.end());
    const size_t n = values.size();
    std::vector<double> result;
    result.reserve(percentiles.size());
    
    for (double p : percentiles) {
        if (p == 0.0) {
            result.push_back(static_cast<double>(values.front()));
            continue;
        }
        if (p == 100.0) {
            result.push_back(static_cast<double>(values.back()));
            continue;
        }
        
        double index = p / 100.0 * (n - 1);
        size_t lower_idx = static_cast<size_t>(std::floor(index));
        size_t upper_idx = static_cast<size_t>(std::ceil(index));
        
        if (lower_idx == upper_idx) {
            // Direct hit on an existing element
            result.push_back(static_cast<double>(values[lower_idx]));
        } else {
            // Linear interpolation between two adjacent elements
            double weight = index - lower_idx;
            double lower_value = static_cast<double>(values[lower_idx]);
            double upper_value = static_cast<double>(values[upper_idx]);
            result.push_back(lower_value + weight * (upper_value - lower_value));
        }
    }
    
    return result;
}

}  // namespace math
}  // namespace cpp_utils

#endif  // CPP_UTILS_LIB_SRC_MATH_STATISTICS_H_
