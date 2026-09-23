#include "TestResult.h"

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

// Реализация оператора ==
bool TestResult::operator==(const TestResult& other) const {
    // Результаты равны, если совпадает имя анализа И дата сдачи
    return (this->get_analysis_name() == other.get_analysis_name()) && (this->date == other.date);
}

// Реализация оператора вывода
ostream& operator<<(ostream& os, const TestResult& obj) {
    os << "[" << obj.date << "] Анализ: " << obj.analysis.get_name()
        << " | Результат: " << obj.value << " (" << obj.status << ")";
    return os;
}

// Реализация дружественной функции
bool is_critical(const TestResult& obj) {
    // Эта функция НЕ принадлежит классу, но благодаря friend 
    // она спокойно читает приватное поле obj.value!
    double max_allowed = obj.analysis.get_max_normal() * 1.5; // Норма превышена на 50%
    return obj.value > max_allowed;
}