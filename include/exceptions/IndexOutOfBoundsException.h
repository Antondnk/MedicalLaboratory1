#pragma once
#include "LabException.h"

// Обращение к элементу коллекции за пределами допустимого диапазона.
class IndexOutOfBoundsException : public LabException {
public:
    explicit IndexOutOfBoundsException(const std::string& msg = "Индекс выходит за границы коллекции.")
        : LabException(msg) {
    }

    std::string get_exception_category() const override {
        return "Container Error";
    }
};
