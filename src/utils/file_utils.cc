#include "src/utils/file_utils.h"

#include <fstream>
#include <iostream>
#include <system_error>

namespace cpp_utils {
namespace utils {

std::optional<std::string> ReadFile(const std::filesystem::path& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return std::nullopt;
    }
    
    file.seekg(0, std::ios::end);
    const auto size = file.tellg();
    if (size < 0) {
        return std::nullopt;
    }
    
    std::string buffer(static_cast<size_t>(size), '\0');
    file.seekg(0);
    if (!file.read(buffer.data(), size)) {
        return std::nullopt;
    }
    
    return buffer;
}

bool WriteFile(const std::filesystem::path& filename, std::string_view data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        return false;
    }
    
    file.write(data.data(), static_cast<std::streamsize>(data.size()));
    return file.good();
}

bool AppendToFile(const std::filesystem::path& filename, std::string_view data) {
    std::ofstream file(filename, std::ios::binary | std::ios::app);
    if (!file) {
        return false;
    }
    
    file.write(data.data(), static_cast<std::streamsize>(data.size()));
    return file.good();
}

std::optional<std::vector<std::string>> ReadLines(const std::filesystem::path& filename) {
    std::ifstream file(filename);
    if (!file) {
        return std::nullopt;
    }
    
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    if (file.bad()) {
        return std::nullopt;
    }
    
    return lines;
}

bool FileExists(const std::filesystem::path& filename) {
    std::error_code ec;
    return std::filesystem::exists(filename, ec) && !ec;
}

bool CreateDirectory(const std::filesystem::path& directory) {
    std::error_code ec;
    return std::filesystem::create_directories(directory, ec) || !ec;
}

std::optional<std::uintmax_t> GetFileSize(const std::filesystem::path& filename) {
    std::error_code ec;
    auto size = std::filesystem::file_size(filename, ec);
    if (ec) {
        return std::nullopt;
    }
    return size;
}

std::optional<std::vector<std::filesystem::path>> ListFiles(const std::filesystem::path& directory) {
    std::error_code ec;
    if (!std::filesystem::exists(directory, ec) || ec) {
        return std::nullopt;
    }
    
    std::vector<std::filesystem::path> files;
    for (const auto& entry : std::filesystem::directory_iterator(directory, ec)) {
        if (ec) {
            return std::nullopt;
        }
        files.push_back(entry.path());
    }
    
    return files;
}

std::optional<std::vector<std::filesystem::path>> ListFilesWithExtension(
    const std::filesystem::path& directory, std::string_view extension) {
    std::error_code ec;
    if (!std::filesystem::exists(directory, ec) || ec) {
        return std::nullopt;
    }
    
    std::vector<std::filesystem::path> files;
    for (const auto& entry : std::filesystem::directory_iterator(directory, ec)) {
        if (ec) {
            return std::nullopt;
        }
        if (entry.is_regular_file() && entry.path().extension() == extension) {
            files.push_back(entry.path());
        }
    }
    
    return files;
}

}  // namespace utils
}  // namespace cpp_utils
