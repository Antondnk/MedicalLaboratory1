#pragma once
#include <string>
#include <vector>       //библиотека для работы с векторами (коллекциями)
#include "TestResult.h" 

using namespace std;

class Patient 
{
private:
    string fullName;            //ФИО пациента
    vector<TestResult> results; //вектор результатов

public:
    
    Patient(const string& fullName);//Конструктор

    //метод добавления нового результата
    //возвращает bool (true - успешно добавлено, false - ошибка ограничения)
    bool addTestResult(const TestResult& result);

    //метод вывода всей медицинской карты
    void printMedicalRecord() const;
};