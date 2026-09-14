#include "TestResult.h"
#include <iostream>

using namespace std;


TestResult::TestResult(const Analysis& analysis, const string& date, double value)
    : analysis(analysis), date(date), value(value) {
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


string TestResult::getDate() const { return date; }

string TestResult::getAnalysisName() const { return analysis.getName(); }
double TestResult::getValue() const { return value; }
string TestResult::getStatus() const { return status; }

void TestResult::printInfo() const {
    cout << "[" << date << "] Анализ: " << analysis.getName()
        << " | Результат: " << value << " (" << status << ")" << endl;
}