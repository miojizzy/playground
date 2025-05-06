#include "src/utils/string_utils.h"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <sstream>

namespace cpp_utils {
namespace utils {

std::vector<std::string> Split(std::string_view input, char delimiter) {
    std::vector<std::string> result;
    
    // Handle empty input
    if (input.empty()) {
        return result;
    }
    
    std::string current;
    
    for (char c : input) {
        if (c == delimiter) {
            // Add current token to result, even if empty
            result.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    
    // Add the last token
    result.push_back(current);
    
    return result;
}

std::string Join(const std::vector<std::string>& strings, std::string_view delimiter) {
    std::ostringstream result;
    bool first = true;
    
    for (const auto& s : strings) {
        if (!first) {
            result << delimiter;
        }
        result << s;
        first = false;
    }
    
    return result.str();
}

std::string Trim(std::string_view s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        ++start;
    }
    
    auto end = s.end();
    while (start != end && std::isspace(*(end - 1))) {
        --end;
    }
    
    return std::string(start, end);
}

std::string ToLower(std::string_view s) {
    std::string result(s);
    std::transform(result.begin(), result.end(), result.begin(),
                  [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string ToUpper(std::string_view s) {
    std::string result(s);
    std::transform(result.begin(), result.end(), result.begin(),
                  [](unsigned char c) { return std::toupper(c); });
    return result;
}

bool StartsWith(std::string_view s, std::string_view prefix) {
    return s.size() >= prefix.size() && s.substr(0, prefix.size()) == prefix;
}

bool EndsWith(std::string_view s, std::string_view suffix) {
    return s.size() >= suffix.size() && 
           s.substr(s.size() - suffix.size(), suffix.size()) == suffix;
}

std::string Replace(std::string_view s, std::string_view from, std::string_view to, bool replace_all) {
    if (from.empty()) return std::string(s);
    
    std::string result(s);
    size_t pos = 0;
    
    // For replace_all, handle all occurrences
    if (replace_all) {
        while ((pos = result.find(from, pos)) != std::string::npos) {
            result.replace(pos, from.length(), to);
            pos += to.length();
        }
    } 
    // For single replacement, handle just the first occurrence
    else {
        if ((pos = result.find(from, 0)) != std::string::npos) {
            result.replace(pos, from.length(), to);
        }
    }
    
    return result;
}

std::optional<int> ToInt(std::string_view s) {
    if (s.empty()) {
        return std::nullopt;
    }
    
    auto trimmed = Trim(s);
    if (trimmed.empty()) {
        return std::nullopt;
    }
    
    // Check for non-numeric characters
    for (char c : trimmed) {
        if (c != '-' && c != '+' && !std::isdigit(static_cast<unsigned char>(c))) {
            return std::nullopt;
        }
    }
    
    try {
        int result = std::stoi(std::string(trimmed));
        return result;
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

std::optional<double> ToDouble(std::string_view s) {
    if (s.empty()) {
        return std::nullopt;
    }
    
    auto trimmed = Trim(s);
    if (trimmed.empty()) {
        return std::nullopt;
    }
    
    // Check for valid floating-point format
    bool has_digit = false;
    bool has_dot = false;
    bool has_exp = false;
    
    for (size_t i = 0; i < trimmed.size(); i++) {
        char c = trimmed[i];
        
        if (std::isdigit(static_cast<unsigned char>(c))) {
            has_digit = true;
        } else if (c == '.') {
            if (has_dot) {
                return std::nullopt;  // Multiple decimal points
            }
            has_dot = true;
        } else if (c == 'e' || c == 'E') {
            if (has_exp || !has_digit) {
                return std::nullopt;  // Multiple exponents or exponent without digits
            }
            has_exp = true;
        } else if ((c == '-' || c == '+') && 
                  (i == 0 || trimmed[i-1] == 'e' || trimmed[i-1] == 'E')) {
            // Sign is allowed at the start or after an exponent
        } else {
            return std::nullopt;  // Invalid character
        }
    }
    
    if (!has_digit) {
        return std::nullopt;  // No digits found
    }
    
    try {
        double result = std::stod(std::string(trimmed));
        return result;
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

}  // namespace utils
}  // namespace cpp_utils
