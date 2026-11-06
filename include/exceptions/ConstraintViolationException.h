#pragma once
#include "LabException.h"


class ConstraintViolationException : public LabException {
public:
    explicit ConstraintViolationException(const std::string& msg = "Нарушено ограничение бизнес-логики.")
        : LabException(msg) {
    }

    std::string get_exception_category() const override {
        return "Domain Error";
    }
};
