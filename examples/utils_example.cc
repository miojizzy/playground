/**
 * @file utils_example.cc
 * @brief Examples showcasing the utility components.
 */

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

#include "src/utils/string_utils.h"
#include "src/utils/file_utils.h"

void string_utils_examples() {
    std::cout << "String Utilities Examples" << std::endl;
    std::cout << "========================" << std::endl;
    
    // Split and Join
    std::string csv = "one,two,three,four,five";
    std::cout << "Original string: " << csv << std::endl;
    
    auto parts = cpp_utils::utils::Split(csv, ',');
    std::cout << "Split by comma:" << std::endl;
    for (const auto& part : parts) {
        std::cout << "  " << part << std::endl;
    }
    
    std::string joined = cpp_utils::utils::Join(parts, " | ");
    std::cout << "Joined with ' | ': " << joined << std::endl;
    
    // Trim
    std::string padded = "  \t Hello, World! \n  ";
    std::cout << "\nOriginal padded string: \"" << padded << "\"" << std::endl;
    std::cout << "After trimming: \"" << cpp_utils::utils::Trim(padded) << "\"" << std::endl;
    
    // Case conversion
    std::string mixed_case = "Hello, World!";
    std::cout << "\nOriginal string: " << mixed_case << std::endl;
    std::cout << "Lower case: " << cpp_utils::utils::ToLower(mixed_case) << std::endl;
    std::cout << "Upper case: " << cpp_utils::utils::ToUpper(mixed_case) << std::endl;
    
    // StartsWith and EndsWith
    std::string test = "Hello, World!";
    std::cout << "\nString \"" << test << "\":" << std::endl;
    std::cout << "Starts with \"Hello\": " 
              << (cpp_utils::utils::StartsWith(test, "Hello") ? "yes" : "no") << std::endl;
    std::cout << "Starts with \"Hi\": " 
              << (cpp_utils::utils::StartsWith(test, "Hi") ? "yes" : "no") << std::endl;
    std::cout << "Ends with \"World!\": " 
              << (cpp_utils::utils::EndsWith(test, "World!") ? "yes" : "no") << std::endl;
    std::cout << "Ends with \"Earth!\": " 
              << (cpp_utils::utils::EndsWith(test, "Earth!") ? "yes" : "no") << std::endl;
    
    // Replace
    std::string sentence = "The quick brown fox jumps over the lazy dog";
    std::cout << "\nOriginal sentence: " << sentence << std::endl;
    std::cout << "After replacing 'fox' with 'cat': " 
              << cpp_utils::utils::Replace(sentence, "fox", "cat") << std::endl;
    
    // ToInt and ToDouble
    std::string valid_int = "123";
    std::string invalid_int = "123abc";
    std::string valid_double = "123.456";
    std::string invalid_double = "123.456xyz";
    
    std::cout << "\nString to number conversions:" << std::endl;
    auto int_result = cpp_utils::utils::ToInt(valid_int);
    std::cout << "ToInt(\"" << valid_int << "\"): " 
              << (int_result ? std::to_string(*int_result) : "conversion failed") << std::endl;
    
    int_result = cpp_utils::utils::ToInt(invalid_int);
    std::cout << "ToInt(\"" << invalid_int << "\"): " 
              << (int_result ? std::to_string(*int_result) : "conversion failed") << std::endl;
    
    auto double_result = cpp_utils::utils::ToDouble(valid_double);
    std::cout << "ToDouble(\"" << valid_double << "\"): " 
              << (double_result ? std::to_string(*double_result) : "conversion failed") << std::endl;
    
    double_result = cpp_utils::utils::ToDouble(invalid_double);
    std::cout << "ToDouble(\"" << invalid_double << "\"): " 
              << (double_result ? std::to_string(*double_result) : "conversion failed") << std::endl;
    
    std::cout << std::endl;
}

void file_utils_examples() {
    std::cout << "File Utilities Examples" << std::endl;
    std::cout << "======================" << std::endl;
    
    // Create a temporary directory for the examples
    std::filesystem::path temp_dir = "/tmp/cpp_utils_test";
    std::cout << "Creating directory: " << temp_dir << std::endl;
    
    if (cpp_utils::utils::CreateDirectory(temp_dir)) {
        std::cout << "Directory created successfully." << std::endl;
    } else {
        std::cout << "Failed to create directory or it already exists." << std::endl;
    }
    
    // Write file
    std::filesystem::path test_file = temp_dir / "test.txt";
    std::string content = "Line 1: This is a test file.\nLine 2: Created by file_utils.";
    
    std::cout << "\nWriting to file: " << test_file << std::endl;
    if (cpp_utils::utils::WriteFile(test_file, content)) {
        std::cout << "File written successfully." << std::endl;
        
        // Get file size
        auto size = cpp_utils::utils::GetFileSize(test_file);
        if (size) {
            std::cout << "File size: " << *size << " bytes" << std::endl;
        }
        
        // Read file
        auto read_content = cpp_utils::utils::ReadFile(test_file);
        if (read_content) {
            std::cout << "\nRead file content:" << std::endl;
            std::cout << *read_content << std::endl;
        } else {
            std::cout << "Failed to read file." << std::endl;
        }
        
        // Read lines
        auto lines = cpp_utils::utils::ReadLines(test_file);
        if (lines) {
            std::cout << "\nRead file by lines (" << lines->size() << " lines):" << std::endl;
            for (const auto& line : *lines) {
                std::cout << "  " << line << std::endl;
            }
        }
        
        // Append to file
        std::string additional_content = "\nLine 3: This line was appended.";
        std::cout << "\nAppending to file: " << test_file << std::endl;
        if (cpp_utils::utils::AppendToFile(test_file, additional_content)) {
            std::cout << "Content appended successfully." << std::endl;
            
            // Read the updated file
            auto updated_content = cpp_utils::utils::ReadFile(test_file);
            if (updated_content) {
                std::cout << "\nUpdated file content:" << std::endl;
                std::cout << *updated_content << std::endl;
            }
        }
        
        // Create some more files for listing example
        cpp_utils::utils::WriteFile(temp_dir / "file1.txt", "File 1 content");
        cpp_utils::utils::WriteFile(temp_dir / "file2.txt", "File 2 content");
        cpp_utils::utils::WriteFile(temp_dir / "file3.dat", "File 3 content");
        
        // List files
        std::cout << "\nListing all files in " << temp_dir << ":" << std::endl;
        auto all_files = cpp_utils::utils::ListFiles(temp_dir);
        if (all_files) {
            for (const auto& file : *all_files) {
                std::cout << "  " << file.filename() << std::endl;
            }
        }
        
        // List files with specific extension
        std::cout << "\nListing .txt files in " << temp_dir << ":" << std::endl;
        auto txt_files = cpp_utils::utils::ListFilesWithExtension(temp_dir, ".txt");
        if (txt_files) {
            for (const auto& file : *txt_files) {
                std::cout << "  " << file.filename() << std::endl;
            }
        }
    } else {
        std::cout << "Failed to write file." << std::endl;
    }
    
    std::cout << std::endl;
}

int main() {
    std::cout << "Utility Components Examples" << std::endl;
    std::cout << "==========================" << std::endl << std::endl;
    
    string_utils_examples();
    file_utils_examples();
    
    return 0;
}
