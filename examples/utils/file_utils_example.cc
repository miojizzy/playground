/**
 * @file file_utils_example.cc
 * @brief Examples showcasing the file utility functions.
 */

#include <iostream>
#include <string>
#include <vector>

#include "src/utils/file_utils.h"

namespace cpp_utils {
namespace examples {

void RunFileUtilsExample() {
  std::cout << "File Utilities Examples" << std::endl;
  std::cout << "======================" << std::endl;
  
  std::string filename = "/tmp/cpp_utils_example.txt";
  std::string content = "This is a test file.\nCreated by cpp_utils library example.";
  
  // Write to file
  std::cout << "Writing to " << filename << std::endl;
  auto write_result = utils::WriteFile(filename, content);
  
  if (write_result) {
    std::cout << "File written successfully." << std::endl;
  } else {
    std::cout << "Failed to write file." << std::endl;
    return;
  }
  
  // Read file content
  auto read_result = utils::ReadFile(filename);
  if (read_result) {
    std::cout << "File content read (" << read_result->size() << " bytes):" << std::endl;
    std::cout << "---" << std::endl << *read_result << std::endl << "---" << std::endl;
  } else {
    std::cout << "Failed to read file." << std::endl;
  }
  
  // Read file lines
  auto lines_result = utils::ReadLines(filename);
  if (lines_result) {
    std::cout << "File lines (" << lines_result->size() << " lines):" << std::endl;
    for (const auto& line : *lines_result) {
      std::cout << "  " << line << std::endl;
    }
  } else {
    std::cout << "Failed to read file lines." << std::endl;
  }
  
  // Append to file
  std::string additional_content = "\nThis line was appended.";
  auto append_result = utils::AppendToFile(filename, additional_content);
  
  if (append_result) {
    std::cout << "\nContent appended successfully." << std::endl;
    
    // Read the updated file
    auto updated_content = utils::ReadFile(filename);
    if (updated_content) {
      std::cout << "Updated file content:" << std::endl;
      std::cout << "---" << std::endl << *updated_content << std::endl << "---" << std::endl;
    }
  } else {
    std::cout << "Failed to append to file." << std::endl;
  }
  
  std::cout << std::endl;
}

}  // namespace examples
}  // namespace cpp_utils