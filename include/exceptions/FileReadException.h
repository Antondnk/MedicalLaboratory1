#pragma once
#include "LabException.h"

class FileReadException : public LabException {
public:
    explicit FileReadException(const std::string& msg = "Ошибка чтения файла.")
        : LabException(msg) {
    }

    std::string get_exception_category() const override {
        return "IO Error";
    }
};
