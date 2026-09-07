#pragma once
#include <string>
#include "Analysis.h" // Подключаем наш первый класс, чтобы TestResult о нем знал

class TestResult {
private:
    Analysis analysis; // Тот самый объект анализа (Композиция)
    std::string date;  // Дата сдачи анализа (например, "10.09.2023")
    double value;      // Само значение (результат)
    std::string status; // Статус (в норме, выше, ниже)

    // Это ПРИВАТНЫЙ метод. Мы не хотим, чтобы кто-то снаружи сам писал "В норме".
    // Класс должен сам это высчитывать на основе value и норм анализа.
    void calculateStatus();

public:
    // Конструктор. Мы передаем готовый анализ, дату и результат.
    TestResult(const Analysis& analysis, const std::string& date, double value);

    // Геттеры
    std::string getDate() const;
    std::string getAnalysisName() const;
    double getValue() const;
    std::string getStatus() const;

    // Вывод информации на экран
    void printInfo() const;
};