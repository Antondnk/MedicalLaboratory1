#pragma once
#include "LabException.h"

class NotFoundException : public LabException {
public:
    explicit NotFoundException(const std::string& msg = "ќшибка: Ёлемент не найден в системе!")
        : LabException(msg) {
    }

    std::string get_exception_category() const override {
        return "Container Error";
    }
};