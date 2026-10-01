#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "TestResult.h"

using namespace std;

class Patient {
private:
    string fullName;
    vector<TestResult> results;

public:
    Patient();
    explicit Patient(const string& fullName);

    string get_full_name() const;
    const vector<TestResult>& get_results() const;

    // Отдельная булевая функция для проверки наличия дубликата
    bool has_result(const TestResult& result) const;

    // Операторы ТОЛЬКО меняют состояние объектов (БЕЗ cout)
    Patient& operator+=(const TestResult& result);
    Patient& operator-=(const TestResult& result);

    friend ostream& operator<<(ostream& os, const Patient& obj);
};