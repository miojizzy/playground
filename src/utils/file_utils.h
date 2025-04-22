/**
 * @file file_utils.h
 * @brief Utility functions for file operations.
 */

#ifndef CPP_UTILS_LIB_SRC_UTILS_FILE_UTILS_H_
#define CPP_UTILS_LIB_SRC_UTILS_FILE_UTILS_H_

#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace cpp_utils {
namespace utils {

/**
 * @brief Reads the entire contents of a file.
 * @param filename The path to the file.
 * @return An optional containing the file contents if successful, or std::nullopt otherwise.
 */
std::optional<std::string> ReadFile(const std::filesystem::path& filename);

/**
 * @brief Writes data to a file, overwriting any existing content.
 * @param filename The path to the file.
 * @param data The data to write.
 * @return True if the operation was successful, false otherwise.
 */
bool WriteFile(const std::filesystem::path& filename, std::string_view data);

/**
 * @brief Appends data to a file.
 * @param filename The path to the file.
 * @param data The data to append.
 * @return True if the operation was successful, false otherwise.
 */
bool AppendToFile(const std::filesystem::path& filename, std::string_view data);

/**
 * @brief Reads a file line by line.
 * @param filename The path to the file.
 * @return An optional containing the lines if successful, or std::nullopt otherwise.
 */
std::optional<std::vector<std::string>> ReadLines(const std::filesystem::path& filename);

/**
 * @brief Checks if a file exists.
 * @param filename The path to the file.
 * @return True if the file exists, false otherwise.
 */
bool FileExists(const std::filesystem::path& filename);

/**
 * @brief Creates a directory if it doesn't exist.
 * @param directory The path to the directory.
 * @return True if the directory was created or already exists, false otherwise.
 */
bool CreateDirectory(const std::filesystem::path& directory);

/**
 * @brief Gets the size of a file.
 * @param filename The path to the file.
 * @return An optional containing the file size if successful, or std::nullopt otherwise.
 */
std::optional<std::uintmax_t> GetFileSize(const std::filesystem::path& filename);

/**
 * @brief Lists all files in a directory.
 * @param directory The path to the directory.
 * @return An optional containing the file paths if successful, or std::nullopt otherwise.
 */
std::optional<std::vector<std::filesystem::path>> ListFiles(const std::filesystem::path& directory);

/**
 * @brief Lists all files in a directory that match a pattern.
 * @param directory The path to the directory.
 * @param extension The file extension to match (e.g., ".txt").
 * @return An optional containing the file paths if successful, or std::nullopt otherwise.
 */
std::optional<std::vector<std::filesystem::path>> ListFilesWithExtension(
    const std::filesystem::path& directory, std::string_view extension);

}  // namespace utils
}  // namespace cpp_utils

#endif  // CPP_UTILS_LIB_SRC_UTILS_FILE_UTILS_H_
