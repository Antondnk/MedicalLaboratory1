#pragma once
#include <string>
#include <iostream>
#include "Analysis.h"

using namespace std;

class TestResult {
private:
    Analysis analysis;
    string date;
    double value;
    string status;

    void calculate_status();

public:
    TestResult(const Analysis& analysis, const string& date, double value);

    string get_date() const;
    string get_analysis_name() const;
    double get_value() const;
    string get_status() const;

    // 1. Перегрузка оператора равенства (проверка на дубликаты)
    bool operator==(const TestResult& other) const;

    // 2. Дружественная функция для перегрузки вывода (вместо print_info)
    friend ostream& operator<<(ostream& os, const TestResult& obj);

    // 3. Дополнительная дружественная функция (по заданию!)
    // У нее будет прямой доступ к private полю value
    friend bool is_critical(const TestResult& obj);
};