#pragma once
#include <string>
#include <vector>      // Подключаем библиотеку для работы с векторами (коллекциями)
#include "TestResult.h" // Пациент должен знать о классе результатов

class Patient {
private:
    std::string fullName;            // ФИО пациента
    std::vector<TestResult> results; // Та самая коллекция (вектор результатов)

public:
    // Конструктор
    Patient(const std::string& fullName);

    // Метод добавления нового результата.
    // Возвращает bool (true - успешно добавлено, false - ошибка ограничения)
    bool addTestResult(const TestResult& result);

    // Метод вывода всей медицинской карты
    void printMedicalRecord() const;
};