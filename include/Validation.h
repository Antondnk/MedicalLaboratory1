#pragma once
#include <string>

// Строка пустая или состоит только из пробельных символов.
inline bool is_blank(const std::string& s) {
    return s.find_first_not_of(" \t\r\n") == std::string::npos;
}
