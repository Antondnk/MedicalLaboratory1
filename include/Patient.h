#pragma once
#include <string>
#include <vector>      
#include <iostream>
#include "TestResult.h" 

using namespace std;

class Patient
{
private:
    string fullName;
    vector<TestResult> results;

public:
    Patient(const string& fullName);

    // 1. Перегрузка += для добавления результата (управление набором объектов)
    Patient& operator+=(const TestResult& result);

    // 2. Перегрузка -= для удаления результата (управление набором объектов)
    Patient& operator-=(const TestResult& result);

    // 3. Дружественная функция вывода карточки пациента (вместо print_medical_record)
    friend ostream& operator<<(ostream& os, const Patient& obj);
};