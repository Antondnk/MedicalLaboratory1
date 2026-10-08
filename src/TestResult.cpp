#include "TestResult.h"

TestResult::TestResult()
    : analysis(nullptr), date(""), value(0.0), status("Неизвестно") {
}

TestResult::TestResult(const Analysis* analysis, const string& date, double value)
    : analysis(analysis), date(date), value(value) {
    calculate_status();
}

void TestResult::calculate_status() {
    if (!analysis) {
        status = "Нет данных об анализе";
        return;
    }
    if (value < analysis->get_min_normal()) {
        status = "Ниже нормы";
    }
    else if (value > analysis->get_max_normal()) {
        status = "Выше нормы";
    }
    else {
        status = "Норма";
    }
}

const Analysis* TestResult::get_analysis() const { return analysis; }
string TestResult::get_date() const { return date; }
double TestResult::get_value() const { return value; }
string TestResult::get_status() const { return status; }

bool TestResult::operator==(const TestResult& other) const {
    if (!analysis || !other.analysis) return false;
    return (analysis->get_name() == other.analysis->get_name()) && (date == other.date);
}

ostream& operator<<(ostream& os, const TestResult& obj) {
    os << "Дата: " << obj.date << " | ";
    if (obj.analysis) {
        os << "Анализ: " << obj.analysis->get_name()
            << " [" << obj.analysis->get_type() << "]";
    }
    else {
        os << "Анализ: Неизвестен";
    }
    os << " | Результат: " << obj.value
        << " | Статус: " << obj.status;
    return os;
}

bool is_critical(const TestResult& obj) {
    if (!obj.analysis) return false;
    double minN = obj.analysis->get_min_normal();
    double maxN = obj.analysis->get_max_normal();

    return (obj.value < minN * 0.8) || (obj.value > maxN * 1.2);
}