#pragma once
#include "LabException.h"

// Попытка создать объект, который уже существует (дубликат).
class DuplicateIdException : public LabException {
public:
    explicit DuplicateIdException(const std::string& msg = "Элемент с таким идентификатором уже существует.")
        : LabException(msg) {
    }

    std::string get_exception_category() const override {
        return "Domain Error";
    }
};
