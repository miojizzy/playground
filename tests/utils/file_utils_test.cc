#include "src/utils/file_utils.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <gtest/gtest.h>

namespace cpp_utils {
namespace utils {
namespace {

class FileUtilsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary directory for testing
        test_dir_ = std::filesystem::temp_directory_path() / "cpp_utils_file_test";
        if (std::filesystem::exists(test_dir_)) {
            std::filesystem::remove_all(test_dir_);
        }
        std::filesystem::create_directory(test_dir_);
        test_file_ = test_dir_ / "test.txt";
    }

    void TearDown() override {
        // Clean up the temporary directory after tests
        if (std::filesystem::exists(test_dir_)) {
            std::filesystem::remove_all(test_dir_);
        }
    }

    std::filesystem::path test_dir_;
    std::filesystem::path test_file_;
};

TEST_F(FileUtilsTest, ReadWriteFile) {
    const std::string test_content = "This is a test file.\nWith multiple lines.\n";
    
    // Test writing to a file
    EXPECT_TRUE(WriteFile(test_file_, test_content));
    
    // Test reading from a file
    auto result = ReadFile(test_file_);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(test_content, *result);
    
    // Test reading a non-existent file
    std::filesystem::path non_existent_file = test_dir_ / "non_existent.txt";
    result = ReadFile(non_existent_file);
    EXPECT_FALSE(result.has_value());
}

TEST_F(FileUtilsTest, ReadLines) {
    const std::string test_content = "Line 1\nLine 2\nLine 3\n";
    
    // Test writing to a file
    EXPECT_TRUE(WriteFile(test_file_, test_content));
    
    // Test reading lines from a file
    auto result = ReadLines(test_file_);
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(3, result->size());
    EXPECT_EQ("Line 1", (*result)[0]);
    EXPECT_EQ("Line 2", (*result)[1]);
    EXPECT_EQ("Line 3", (*result)[2]);
    
    // Test reading lines from a non-existent file
    std::filesystem::path non_existent_file = test_dir_ / "non_existent.txt";
    result = ReadLines(non_existent_file);
    EXPECT_FALSE(result.has_value());
}

TEST_F(FileUtilsTest, FileExists) {
    // Test with a non-existent file
    EXPECT_FALSE(FileExists(test_file_));
    
    // Create the file and test again
    {
        std::ofstream file(test_file_);
        file << "Test content";
    }
    
    EXPECT_TRUE(FileExists(test_file_));
}

TEST_F(FileUtilsTest, CreateDirectory) {
    std::filesystem::path new_dir = test_dir_ / "new_dir";
    
    // Test creating a new directory
    EXPECT_TRUE(CreateDirectory(new_dir));
    EXPECT_TRUE(std::filesystem::exists(new_dir));
    
    // Test creating a directory that already exists
    EXPECT_TRUE(CreateDirectory(new_dir));
}

TEST_F(FileUtilsTest, GetFileSize) {
    const std::string test_content = "This is a test file.";
    
    // Test getting the size of a non-existent file
    auto result = GetFileSize(test_file_);
    EXPECT_FALSE(result.has_value());
    
    // Create the file and test again
    EXPECT_TRUE(WriteFile(test_file_, test_content));
    
    result = GetFileSize(test_file_);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(test_content.size(), *result);
}

TEST_F(FileUtilsTest, AppendToFile) {
    const std::string initial_content = "Initial content.\n";
    const std::string appended_content = "Appended content.\n";
    
    // Create the file with initial content
    EXPECT_TRUE(WriteFile(test_file_, initial_content));
    
    // Append to the file
    EXPECT_TRUE(AppendToFile(test_file_, appended_content));
    
    // Read the file and verify the content
    auto result = ReadFile(test_file_);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(initial_content + appended_content, *result);
    
    // Test appending to a non-existent file
    std::filesystem::path non_existent_file = test_dir_ / "non_existent.txt";
    EXPECT_TRUE(AppendToFile(non_existent_file, appended_content));
    
    // Verify the file was created with the appended content
    result = ReadFile(non_existent_file);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(appended_content, *result);
}

TEST_F(FileUtilsTest, ListFiles) {
    // Create some test files
    EXPECT_TRUE(WriteFile(test_dir_ / "file1.txt", "Content 1"));
    EXPECT_TRUE(WriteFile(test_dir_ / "file2.txt", "Content 2"));
    EXPECT_TRUE(WriteFile(test_dir_ / "file3.dat", "Content 3"));
    
    // Create a subdirectory
    std::filesystem::path sub_dir = test_dir_ / "sub_dir";
    EXPECT_TRUE(CreateDirectory(sub_dir));
    EXPECT_TRUE(WriteFile(sub_dir / "file4.txt", "Content 4"));
    
    // Test ListFiles
    auto result = ListFiles(test_dir_);
    ASSERT_TRUE(result.has_value());
    
    // Should return 4 entries (3 files + 1 directory)
    EXPECT_EQ(4, result->size());
    
    // Test ListFilesWithExtension
    result = ListFilesWithExtension(test_dir_, ".txt");
    ASSERT_TRUE(result.has_value());
    
    // Should return 2 .txt files in the main directory
    EXPECT_EQ(2, result->size());
    
    // Test with non-existent directory
    std::filesystem::path non_existent_dir = test_dir_ / "non_existent_dir";
    result = ListFiles(non_existent_dir);
    EXPECT_FALSE(result.has_value());
    
    result = ListFilesWithExtension(non_existent_dir, ".txt");
    EXPECT_FALSE(result.has_value());
}

}  // namespace
}  // namespace utils
}  // namespace cpp_utils
