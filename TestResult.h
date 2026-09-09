#pragma once
#include <string>
#include "Analysis.h"

using namespace std;

class TestResult {
private:
    Analysis analysis; //объект анализа (Композиция)
    string date;  //Дата сдачи анализа (например, "10.09.2023")
    double value;      //Само значение (результат)
    string status; //Статус (в норме, выше, ниже)

    //Это ПРИВАТНЫЙ метод. Мы не хотим, чтобы кто-то снаружи сам писал "В норме"
    //Класс должен сам это высчитывать на основе value и норм анализа
    void calculateStatus();

public:
    //Конструктор. Передача готового анализа, даты и результата
    TestResult(const Analysis& analysis, const string& date, double value);

    //Геттеры
    string getDate() const;
    string getAnalysisName() const;
    double getValue() const;
    string getStatus() const;

    //Вывод информации на экран
    void printInfo() const;
};