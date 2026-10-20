#pragma once
#include <stdexcept>
#include <string>

class LabException : public std::exception {
protected:
    std::string message;
public:
    explicit LabException(const std::string& msg) : message(msg) {}
    virtual ~LabException() = default;

    const char* what() const noexcept override {
        return message.c_str();
    }

    virtual std::string get_exception_category() const = 0;
};