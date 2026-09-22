#include "TestResult.h"
#include <iostream>

using namespace std;


TestResult::TestResult(const Analysis& analysis, const string& date, double value)
    : analysis(analysis), date(date), value(value) {
    calculate_status();
}

void TestResult::calculate_status() {
    if (value < analysis.get_min_normal()) {
        status = "Ниже нормы";
    }
    else if (value > analysis.get_max_normal()) {
        status = "Выше нормы";
    }
    else {
        status = "В норме";
    }
}


string TestResult::get_date() const { return date; }

string TestResult::get_analysis_name() const { return analysis.get_name(); }
double TestResult::get_value() const { return value; }
string TestResult::get_status() const { return status; }

void TestResult::print_info() const {
    cout << "[" << date << "] Анализ: " << analysis.get_name()
        << " | Результат: " << value << " (" << status << ")" << endl;
}