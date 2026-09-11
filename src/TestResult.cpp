#include "TestResult.h"
#include <iostream>

using namespace std;

//Реализация конструктора
TestResult::TestResult(const Analysis& analysis, const string& date, double value)
    : analysis(analysis), date(date), value(value) {
    //Вызывает приватную функцию сразу при создании объекта
    //Благодаря этому статус автоматически посчитается и запишется
    calculateStatus();
}

void TestResult::calculateStatus() {
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

//Реализация геттеров
string TestResult::getDate() const { return date; }
//получение имени анализа
string TestResult::getAnalysisName() const { return analysis.getName(); }
double TestResult::getValue() const { return value; }
string TestResult::getStatus() const { return status; }

//Вывод на экран
void TestResult::printInfo() const {
    cout << "[" << date << "] Анализ: " << analysis.getName()
        << " | Результат: " << value << " (" << status << ")" << endl;
}