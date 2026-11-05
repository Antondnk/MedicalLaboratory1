#pragma once
#include "LabException.h"

// Обращение к несуществующему объекту: пустой список, результата нет у пациента.
class NotFoundException : public LabException {
public:
    explicit NotFoundException(const std::string& msg = "Элемент не найден в системе.")
        : LabException(msg) {
    }

    std::string get_exception_category() const override {
        return "Container Error";
    }
};
