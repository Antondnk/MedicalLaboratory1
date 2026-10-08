#pragma once
#include <string>
#include <iostream>
#include "Analysis.h"

using namespace std;

class TestResult {
private:
    const Analysis* analysis;
    string date;
    double value;
    string status;

    void calculate_status();

public:
    TestResult();
    TestResult(const Analysis* analysis, const string& date, double value);

    const Analysis* get_analysis() const;
    string get_date() const;
    double get_value() const;
    string get_status() const;

    bool operator==(const TestResult& other) const;

    friend ostream& operator<<(ostream& os, const TestResult& obj);
    friend bool is_critical(const TestResult& obj);
};