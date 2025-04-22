#include "src/utils/string_utils.h"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <sstream>

namespace cpp_utils {
namespace utils {

std::vector<std::string> Split(std::string_view input, char delimiter) {
    std::vector<std::string> result;
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
    
    // Find and replace the first occurrence
    if ((pos = result.find(from, pos)) != std::string::npos) {
        result.replace(pos, from.length(), to);
        pos += to.length();
        
        // If replace_all is true, continue replacing remaining occurrences
        if (replace_all) {
            while ((pos = result.find(from, pos)) != std::string::npos) {
                result.replace(pos, from.length(), to);
                pos += to.length();
            }
        }
    }
    
    return result;
}

std::optional<int> ToInt(std::string_view s) {
    int result;
    auto trimmed = Trim(s);
    const auto [ptr, ec] = std::from_chars(trimmed.data(), trimmed.data() + trimmed.size(), result);
    if (ec == std::errc()) {
        return result;
    }
    return std::nullopt;
}

std::optional<double> ToDouble(std::string_view s) {
    try {
        auto trimmed = Trim(s);
        double result = std::stod(std::string(trimmed));
        return result;
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

}  // namespace utils
}  // namespace cpp_utils
