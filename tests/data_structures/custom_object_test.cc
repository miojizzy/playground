#include "src/data_structures/custom_object.h"

#include <gtest/gtest.h>
#include <sstream>

namespace cpp_utils {
namespace data_structures {
namespace {

TEST(CustomObjectTest, ConstructorAndAccessors) {
    CustomObject obj("test_object", 42);
    
    EXPECT_EQ("test_object", obj.GetName());
    EXPECT_EQ(42, obj.GetValue());
}

TEST(CustomObjectTest, Setters) {
    CustomObject obj("initial", 10);
    
    obj.SetName("updated");
    obj.SetValue(20);
    
    EXPECT_EQ("updated", obj.GetName());
    EXPECT_EQ(20, obj.GetValue());
}

TEST(CustomObjectTest, CopyConstructor) {
    CustomObject original("original", 100);
    CustomObject copy(original);
    
    EXPECT_EQ("original", copy.GetName());
    EXPECT_EQ(100, copy.GetValue());
    
    // Verify that modifying the copy doesn't affect the original
    copy.SetName("modified");
    copy.SetValue(200);
    
    EXPECT_EQ("original", original.GetName());
    EXPECT_EQ(100, original.GetValue());
}

TEST(CustomObjectTest, CopyAssignment) {
    CustomObject original("original", 100);
    CustomObject copy("copy", 50);
    
    copy = original;
    
    EXPECT_EQ("original", copy.GetName());
    EXPECT_EQ(100, copy.GetValue());
}

TEST(CustomObjectTest, MoveConstructor) {
    CustomObject original("original", 100);
    CustomObject moved(std::move(original));
    
    EXPECT_EQ("original", moved.GetName());
    EXPECT_EQ(100, moved.GetValue());
}

TEST(CustomObjectTest, MoveAssignment) {
    CustomObject original("original", 100);
    CustomObject moved("moved", 50);
    
    moved = std::move(original);
    
    EXPECT_EQ("original", moved.GetName());
    EXPECT_EQ(100, moved.GetValue());
}

TEST(CustomObjectTest, EqualityOperators) {
    CustomObject obj1("name", 10);
    CustomObject obj2("name", 10);
    CustomObject obj3("different", 10);
    CustomObject obj4("name", 20);
    
    EXPECT_TRUE(obj1 == obj2);
    EXPECT_FALSE(obj1 == obj3);
    EXPECT_FALSE(obj1 == obj4);
    
    EXPECT_FALSE(obj1 != obj2);
    EXPECT_TRUE(obj1 != obj3);
    EXPECT_TRUE(obj1 != obj4);
}

TEST(CustomObjectTest, ComparisonOperators) {
    CustomObject obj1("a", 10);
    CustomObject obj2("b", 10);  // Same value but different name
    CustomObject obj3("a", 20);  // Same name but different value
    
    // Test less than
    EXPECT_FALSE(obj1 < obj1);  // An object is not less than itself
    EXPECT_TRUE(obj1 < obj2);   // When values are equal, compare by name
    EXPECT_TRUE(obj1 < obj3);   // Compare primarily by value
    
    // Test greater than
    EXPECT_FALSE(obj1 > obj1);  // An object is not greater than itself
    EXPECT_FALSE(obj1 > obj2);  // When values are equal, compare by name
    EXPECT_FALSE(obj1 > obj3);  // Compare primarily by value
    EXPECT_TRUE(obj3 > obj1);   // Reverse comparison
    
    // Test less than or equal
    EXPECT_TRUE(obj1 <= obj1);  // An object is less than or equal to itself
    EXPECT_TRUE(obj1 <= obj2);
    EXPECT_TRUE(obj1 <= obj3);
    EXPECT_FALSE(obj3 <= obj1);
    
    // Test greater than or equal
    EXPECT_TRUE(obj1 >= obj1);  // An object is greater than or equal to itself
    EXPECT_FALSE(obj1 >= obj2);
    EXPECT_FALSE(obj1 >= obj3);
    EXPECT_TRUE(obj3 >= obj1);
}

TEST(CustomObjectTest, Print) {
    CustomObject obj("test_name", 123);
    
    // Redirect cout to our stringstream
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    obj.Print();
    
    // Restore cout
    std::cout.rdbuf(old);
    
    EXPECT_EQ("CustomObject: test_name, 123\n", buffer.str());
}

}  // namespace
}  // namespace data_structures
}  // namespace cpp_utils