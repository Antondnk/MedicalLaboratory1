#pragma once
#include "LabException.h"

class InvalidDataException : public LabException {
public:
    explicit InvalidDataException(const std::string& msg = "Ошибка: Переданы недопустимые данные!")
        : LabException(msg) {
    }

    std::string get_exception_category() const override {
        return "Domain Error";
    }
};