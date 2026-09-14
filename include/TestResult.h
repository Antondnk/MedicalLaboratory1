#pragma once
#include <string>
#include "Analysis.h"

using namespace std;

class TestResult {
private:
    Analysis analysis;
    string date;
    double value;
    string status;

    void calculateStatus();

public:
    TestResult(const Analysis& analysis, const string& date, double value);

    string getDate() const;
    string getAnalysisName() const;
    double getValue() const;
    string getStatus() const;

    void printInfo() const;
};