#include "src/utils/string_utils.h"

#include <gtest/gtest.h>

namespace cpp_utils {
namespace utils {
namespace {

TEST(StringUtilsTest, Split) {
    std::string input = "one,two,three,four";
    auto result = Split(input, ',');
    
    ASSERT_EQ(4, result.size());
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("two", result[1]);
    EXPECT_EQ("three", result[2]);
    EXPECT_EQ("four", result[3]);
    
    // Test with empty string
    result = Split("", ',');
    EXPECT_TRUE(result.empty());
    
    // Test with no delimiters
    result = Split("single", ',');
    ASSERT_EQ(1, result.size());
    EXPECT_EQ("single", result[0]);
    
    // Test with consecutive delimiters
    result = Split("one,,two", ',');
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("two", result[2]);
}

TEST(StringUtilsTest, Join) {
    std::vector<std::string> strings = {"one", "two", "three"};
    std::string result = Join(strings, ", ");
    
    EXPECT_EQ("one, two, three", result);
    
    // Test with empty vector
    EXPECT_EQ("", Join(std::vector<std::string>{}, ", "));
    
    // Test with single element
    EXPECT_EQ("single", Join(std::vector<std::string>{"single"}, ", "));
}

TEST(StringUtilsTest, Trim) {
    EXPECT_EQ("hello", Trim("  hello  "));
    EXPECT_EQ("hello", Trim("hello  "));
    EXPECT_EQ("hello", Trim("  hello"));
    EXPECT_EQ("hello", Trim("hello"));
    EXPECT_EQ("", Trim("   "));
    EXPECT_EQ("", Trim(""));
    EXPECT_EQ("hello world", Trim("  hello world  "));
    EXPECT_EQ("hello\tworld", Trim("  hello\tworld  "));
}

TEST(StringUtilsTest, ToLower) {
    EXPECT_EQ("hello, world!", ToLower("HELLO, World!"));
    EXPECT_EQ("hello", ToLower("hello"));
    EXPECT_EQ("123", ToLower("123"));
    EXPECT_EQ("", ToLower(""));
}

TEST(StringUtilsTest, ToUpper) {
    EXPECT_EQ("HELLO, WORLD!", ToUpper("HELLO, World!"));
    EXPECT_EQ("HELLO", ToUpper("hello"));
    EXPECT_EQ("123", ToUpper("123"));
    EXPECT_EQ("", ToUpper(""));
}

TEST(StringUtilsTest, StartsWith) {
    EXPECT_TRUE(StartsWith("Hello, World!", "Hello"));
    EXPECT_TRUE(StartsWith("Hello", "Hello"));
    EXPECT_FALSE(StartsWith("Hello, World!", "World"));
    EXPECT_FALSE(StartsWith("Hello", "HelloWorld"));
    EXPECT_TRUE(StartsWith("Hello", ""));
    EXPECT_FALSE(StartsWith("", "Hello"));
    EXPECT_TRUE(StartsWith("", ""));
}

TEST(StringUtilsTest, EndsWith) {
    EXPECT_TRUE(EndsWith("Hello, World!", "World!"));
    EXPECT_TRUE(EndsWith("Hello", "Hello"));
    EXPECT_FALSE(EndsWith("Hello, World!", "Hello"));
    EXPECT_FALSE(EndsWith("Hello", "HelloWorld"));
    EXPECT_TRUE(EndsWith("Hello", ""));
    EXPECT_FALSE(EndsWith("", "Hello"));
    EXPECT_TRUE(EndsWith("", ""));
}

TEST(StringUtilsTest, Replace) {
    EXPECT_EQ("Hxllo, World!", Replace("Hello, World!", "e", "x"));
    EXPECT_EQ("Hello, World!", Replace("Hello, World!", "z", "x"));
    EXPECT_EQ("Hxllo, World!", Replace("Hello, World!", "e", "x"));
    EXPECT_EQ("Hello, Cat!", Replace("Hello, World!", "World", "Cat"));
    EXPECT_EQ("", Replace("", "Hello", "World"));
    // Test multiple replacements - both occurrences of 'o' replaced
    EXPECT_EQ("Hellx, Wxrld!", Replace("Hello, World!", "o", "x", true));
    // Test single replacement - only first occurrence
    EXPECT_EQ("Hellx, World!", Replace("Hello, World!", "o", "x", false));
}

TEST(StringUtilsTest, ToInt) {
    auto result = ToInt("123");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(123, *result);
    
    result = ToInt("-123");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(-123, *result);
    
    result = ToInt("  123  ");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(123, *result);
    
    result = ToInt("123abc");
    EXPECT_FALSE(result.has_value());
    
    result = ToInt("");
    EXPECT_FALSE(result.has_value());
    
    result = ToInt("   ");
    EXPECT_FALSE(result.has_value());
}

TEST(StringUtilsTest, ToDouble) {
    auto result = ToDouble("123.45");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(123.45, *result);
    
    result = ToDouble("-123.45");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(-123.45, *result);
    
    result = ToDouble("  123.45  ");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(123.45, *result);
    
    result = ToDouble("123");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(123.0, *result);
    
    result = ToDouble("123.45abc");
    EXPECT_FALSE(result.has_value());
    
    result = ToDouble("");
    EXPECT_FALSE(result.has_value());
    
    result = ToDouble("   ");
    EXPECT_FALSE(result.has_value());
}

}  // namespace
}  // namespace utils
}  // namespace cpp_utils
