/**
 * @file statistics_example.cc
 * @brief Examples showcasing the statistics functions.
 */

#include <iostream>
#include <iomanip>
#include <vector>

#include "src/math/statistics.h"

namespace cpp_utils {
namespace examples {

template <typename T>
void PrintVector(const std::vector<T>& vec) {
  for (const auto& val : vec) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
}

void RunStatisticsExample() {
  std::cout << "Statistics Examples" << std::endl;
  std::cout << "===================" << std::endl;
  
  // Create a data set
  std::vector<double> data = {12.5, 10.0, 15.3, 9.8, 8.2, 13.7, 14.5, 11.2};
  
  std::cout << "Data set: ";
  PrintVector(data);
  
  // Basic statistics
  auto mean = math::Mean(data);
  if (mean) {
    std::cout << "Mean: " << *mean << std::endl;
  }
  
  auto median = math::Median(data);
  if (median) {
    std::cout << "Median: " << *median << std::endl;
  }
  
  auto mode = math::Mode(data);
  if (mode) {
    std::cout << "Mode: " << *mode << std::endl;
  }
  
  auto std_dev = math::StandardDeviation(data);
  if (std_dev) {
    std::cout << "Standard Deviation: " << std::fixed << std::setprecision(5) << *std_dev << std::endl;
  }
  
  auto range = math::Range(data);
  if (range) {
    std::cout << "Range: [" << range->first << ", " << range->second << "]" << std::endl;
  }
  
  // Percentiles
  std::vector<double> percentiles = {25, 50, 75, 90};
  auto percentile_results = math::Percentiles(data, percentiles);
  
  if (percentile_results) {
    std::cout << "Percentiles:" << std::endl;
    for (size_t i = 0; i < percentiles.size(); ++i) {
      std::cout << "  " << percentiles[i] << "%: " << (*percentile_results)[i] << std::endl;
    }
  }
  
  // Correlation example
  std::cout << "\nCorrelation Examples:" << std::endl;
  
  std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> y_positive = {1.0, 2.0, 3.0, 4.0, 5.0};  // Perfect positive correlation
  std::vector<double> y_negative = {5.0, 4.0, 3.0, 2.0, 1.0};  // Perfect negative correlation
  std::vector<double> y_no_corr = {3.0, 1.0, 5.0, 2.0, 4.0};   // No clear correlation
  
  auto corr_pos = math::Correlation(x, y_positive);
  if (corr_pos) {
    std::cout << "Positive correlation: " << std::fixed << std::setprecision(3) << *corr_pos << std::endl;
  }
  
  auto corr_neg = math::Correlation(x, y_negative);
  if (corr_neg) {
    std::cout << "Negative correlation: " << *corr_neg << std::endl;
  }
  
  auto corr_none = math::Correlation(x, y_no_corr);
  if (corr_none) {
    std::cout << "No clear correlation: " << *corr_none << std::endl;
  }
  
  // Handle edge cases
  std::cout << "\nEdge Cases:" << std::endl;
  
  std::vector<double> empty_data;
  std::cout << "Empty data set mean: " 
            << (math::Mean(empty_data) ? std::to_string(*math::Mean(empty_data)) : "undefined") << std::endl;
  
  std::vector<double> single_element = {42.0};
  std::cout << "Single element data set:" << std::endl;
  std::cout << "  Mean: " << (math::Mean(single_element) ? std::to_string(*math::Mean(single_element)) : "undefined") << std::endl;
  std::cout << "  Standard deviation: " 
            << (math::StandardDeviation(single_element) ? std::to_string(*math::StandardDeviation(single_element)) : "undefined") << std::endl;
  
  std::cout << std::endl;
}

}  // namespace examples
}  // namespace cpp_utils