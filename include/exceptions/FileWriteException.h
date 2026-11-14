#pragma once
#include "LabException.h"

class FileWriteException : public LabException {
public:
    explicit FileWriteException(const std::string& msg = "Ошибка записи в файл.")
        : LabException(msg) {
    }

    std::string get_exception_category() const override {
        return "IO Error";
    }
};
