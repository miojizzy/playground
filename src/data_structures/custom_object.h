/**
 * @file custom_object.h
 * @brief custom_object.
 */

#ifndef CPP_UTILS_LIB_SRC_DATA_STRUCTURES_CUSTOM_OBJECT_H_
#define CPP_UTILS_LIB_SRC_DATA_STRUCTURES_CUSTOM_OBJECT_H_

#include <optional>
#include <string>
#include <string_view>
#include <iostream>

namespace cpp_utils::data_structures {

class CustomObject {
public:
    CustomObject(const std::string& name, int value): name_(name), value_(value) {
        std::cout << "CustomObject created: " << name_ << ", " << value_ << std::endl;
    }
    ~CustomObject() {
        std::cout << "CustomObject destroyed: " << name_ << ", " << value_ << std::endl;
    }

    CustomObject(const CustomObject& other) {
        name_ = other.name_;
        value_ = other.value_;
        std::cout << "CustomObject copied: " << name_ << ", " << value_ << std::endl;
    }
    CustomObject& operator=(const CustomObject& other) {
        name_ = other.name_;
        value_ = other.value_;
        std::cout << "CustomObject assign copied: " << name_ << ", " << value_ << std::endl;
    }
    CustomObject(CustomObject&& other) {
        name_ = std::move(other.name_);
        value_ = std::move(other.value_);
        std::cout << "CustomObject moved: " << name_ << ", " << value_ << std::endl;
    }
    CustomObject& operator=(CustomObject&& other) {
        name_ = std::move(other.name_);
        value_ = std::move(other.value_);
        std::cout << "CustomObject assign moved: " << name_ << ", " << value_ << std::endl;
    }

    std::string GetName() const { return name_; }
    int GetValue() const { return value_; }

    void SetName(const std::string& name) { name_ = name; }
    void SetValue(int value) { value_ = value; }

    void Print() const { std::cout << "CustomObject: " << name_ << ", " << value_ << std::endl; }

    bool operator==(const CustomObject& other) const {
        return name_ == other.name_ && value_ == other.value_;
    }
    bool operator!=(const CustomObject& other) const {
        return !(*this == other);
    }
    bool operator<(const CustomObject& other) const {
        return value_ < other.value_ || (value_ == other.value_ && name_ < other.name_);
    }
    bool operator>(const CustomObject& other) const {
        return other < *this;
    }
    bool operator<=(const CustomObject& other) const {
        return !(other < *this);
    }
    bool operator>=(const CustomObject& other) const {
        return !(*this < other);
    }
    
private:
    std::string name_;
    int value_;
};

}  // namespace cpp_utils::data_structures

#endif  // CPP_UTILS_LIB_SRC_DATA_STRUCTURES_CUSTOM_OBJECT_H_
