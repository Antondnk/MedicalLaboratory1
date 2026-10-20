#pragma once
#include "LabException.h"

class IndexOutOfBoundsException : public LabException {
public:
    explicit IndexOutOfBoundsException(const std::string& msg = "Ошибка: Индекс выходит за границы коллекции!")
        : LabException(msg) {
    }

    std::string get_exception_category() const override {
        return "Container Error";
    }
};