#include "TestResult.h"
#include "exceptions/Exceptions.h"

TestResult::TestResult()
    : analysis(nullptr), date(""), value(0.0), status("Неизвестно") {
}

bool TestResult::is_valid_date(const string& date) {
    if (date.length() != 10) return false;
    if (date[2] != '.' || date[5] != '.') return false;

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    }

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (month < 1 || month > 12) return false;
    if (year < 1900 || year > 2100) return false;

    int days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[2] = 29;
    }
    return day >= 1 && day <= days_in_month[month];
}

TestResult::TestResult(const Analysis* analysis, const string& date, double value)
    : analysis(analysis), date(date), value(value) {
    if (!analysis) {
        throw InvalidDataException("Для результата не указан анализ.");
    }
    if (!is_valid_date(date)) {
        throw InvalidDataException("Неверная дата \"" + date + "\". Нужен формат ДД.ММ.ГГГГ (например, 10.09.2026).");
    }
    if (!(value >= 0)) {
        throw InvalidDataException("Результат анализа не может быть отрицательным.");
    }
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