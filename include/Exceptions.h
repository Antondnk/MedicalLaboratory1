#pragma once
#include <stdexcept>
#include <string>

class LabException : public std::exception {
protected:
    std::string message;
public:
    explicit LabException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class IndexOutOfBoundsException : public LabException {
public:
    explicit IndexOutOfBoundsException(const std::string& msg = "Ошибка: Индекс выходит за границы коллекции!")
        : LabException(msg) {
    }
};

class NotFoundException : public LabException {
public:
    explicit NotFoundException(const std::string& msg = "Ошибка: Элемент не найден в системе!")
        : LabException(msg) {
    }
};

class DuplicateIdException : public LabException {
public:
    explicit DuplicateIdException(const std::string& msg = "Ошибка: Элемент с таким идентификатором уже существует!")
        : LabException(msg) {
    }
};

class InvalidDataException : public LabException {
public:
    explicit InvalidDataException(const std::string& msg = "Ошибка: Переданы недопустимые или некорректные данные!")
        : LabException(msg) {
    }
};

class ConstraintViolationException : public LabException {
public:
    explicit ConstraintViolationException(const std::string& msg = "Ошибка: Нарушено ограничение бизнес-логики!")
        : LabException(msg) {
    }
};