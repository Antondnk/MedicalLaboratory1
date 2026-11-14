#pragma once
#include <string>

class Logger {
public:
    static std::string timestamp();
    static void append(const std::string& path, const std::string& message);
};
