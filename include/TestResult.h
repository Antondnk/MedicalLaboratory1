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

    bool operator==(const TestResult& other) const;

    friend ostream& operator<<(ostream& os, const TestResult& obj);

    friend bool is_critical(const TestResult& obj);
};