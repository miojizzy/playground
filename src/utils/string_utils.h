/**
 * @file string_utils.h
 * @brief Utility functions for string manipulation.
 */

#ifndef CPP_UTILS_LIB_SRC_UTILS_STRING_UTILS_H_
#define CPP_UTILS_LIB_SRC_UTILS_STRING_UTILS_H_

#include <algorithm>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace cpp_utils {
namespace utils {

/**
 * @brief Splits a string by a delimiter.
 * @param input The string to split.
 * @param delimiter The delimiter to split by.
 * @return A vector of string pieces.
 */
std::vector<std::string> Split(std::string_view input, char delimiter);

/**
 * @brief Joins a vector of strings with a delimiter.
 * @param strings The strings to join.
 * @param delimiter The delimiter to join with.
 * @return The joined string.
 */
std::string Join(const std::vector<std::string>& strings, std::string_view delimiter);

/**
 * @brief Trims whitespace from both ends of a string.
 * @param s The string to trim.
 * @return The trimmed string.
 */
std::string Trim(std::string_view s);

/**
 * @brief Converts a string to lowercase.
 * @param s The string to convert.
 * @return The lowercase string.
 */
std::string ToLower(std::string_view s);

/**
 * @brief Converts a string to uppercase.
 * @param s The string to convert.
 * @return The uppercase string.
 */
std::string ToUpper(std::string_view s);

/**
 * @brief Checks if a string starts with a prefix.
 * @param s The string to check.
 * @param prefix The prefix to check for.
 * @return True if the string starts with the prefix, false otherwise.
 */
bool StartsWith(std::string_view s, std::string_view prefix);

/**
 * @brief Checks if a string ends with a suffix.
 * @param s The string to check.
 * @param suffix The suffix to check for.
 * @return True if the string ends with the suffix, false otherwise.
 */
bool EndsWith(std::string_view s, std::string_view suffix);

/**
 * @brief Replaces occurrences of a substring with another substring.
 * @param s The original string.
 * @param from The substring to replace.
 * @param to The replacement substring.
 * @param replace_all If true, replaces all occurrences; otherwise, only the first one.
 * @return The modified string.
 */
std::string Replace(std::string_view s, std::string_view from, std::string_view to, bool replace_all = false);

/**
 * @brief Converts a string to an integer, handling errors gracefully.
 * @param s The string to convert.
 * @return An optional containing the integer if conversion succeeded, or std::nullopt otherwise.
 */
std::optional<int> ToInt(std::string_view s);

/**
 * @brief Converts a string to a double, handling errors gracefully.
 * @param s The string to convert.
 * @return An optional containing the double if conversion succeeded, or std::nullopt otherwise.
 */
std::optional<double> ToDouble(std::string_view s);

}  // namespace utils
}  // namespace cpp_utils

#endif  // CPP_UTILS_LIB_SRC_UTILS_STRING_UTILS_H_
