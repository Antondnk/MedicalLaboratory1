#include "TestResult.h"
#include <iostream>

// Реализация конструктора
TestResult::TestResult(const Analysis& analysis, const std::string& date, double value)
    : analysis(analysis), date(date), value(value) {
    // Вызываем нашу приватную функцию сразу при создании объекта!
    // Благодаря этому статус автоматически посчитается и запишется.
    calculateStatus();
}

// Та самая скрытая (инкапсулированная) логика
void TestResult::calculateStatus() {
    // Объект analysis знает свои нормы, мы просто просим их через геттеры
    if (value < analysis.getMinNormal()) {
        status = "Ниже нормы";
    }
    else if (value > analysis.getMaxNormal()) {
        status = "Выше нормы";
    }
    else {
        status = "В норме";
    }
}

// Реализация геттеров
std::string TestResult::getDate() const { return date; }
// Обрати внимание: мы получаем имя анализа, обращаясь к объекту analysis внутри нас
std::string TestResult::getAnalysisName() const { return analysis.getName(); }
double TestResult::getValue() const { return value; }
std::string TestResult::getStatus() const { return status; }

// Вывод на экран
void TestResult::printInfo() const {
    std::cout << "[" << date << "] Анализ: " << analysis.getName()
        << " | Результат: " << value << " (" << status << ")" << std::endl;
}