#pragma once
#include "LabException.h"

class DuplicateIdException : public LabException {
public:
    explicit DuplicateIdException(const std::string& msg = "ќшибка: Ёлемент с таким идентификатором уже существует!")
        : LabException(msg) {
    }

    std::string get_exception_category() const override {
        return "Domain Error";
    }
};