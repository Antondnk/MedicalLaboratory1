#pragma once
#include "LabException.h"

// Некорректные данные: пустое имя, отрицательная цена, неверная дата, не число и т.п.
class InvalidDataException : public LabException {
public:
    explicit InvalidDataException(const std::string& msg = "Переданы недопустимые данные.")
        : LabException(msg) {
    }

    std::string get_exception_category() const override {
        return "Domain Error";
    }
};
