#pragma once
#include "LabException.h"

class FileOpenException : public LabException {
public:
    explicit FileOpenException(const std::string& msg = "Не удалось открыть файл.")
        : LabException(msg) {
    }

    std::string get_exception_category() const override {
        return "IO Error";
    }
};
