#include "Patient.h"
#include <algorithm>

Patient::Patient() : fullName("") {}

Patient::Patient(const string& fullName) : fullName(fullName) {}

string Patient::get_full_name() const { return fullName; }

const vector<TestResult>& Patient::get_results() const { return results; }

// Булевая функция-проверка
bool Patient::has_result(const TestResult& result) const {
    for (const auto& res : results) {
        if (res == result) {
            return true;
        }
    }
    return false;
}

// Добавление строго без cout
Patient& Patient::operator+=(const TestResult& result) {
    results.push_back(result);
    return *this;
}

// Удаление строго без cout
Patient& Patient::operator-=(const TestResult& result) {
    auto it = std::find(results.begin(), results.end(), result);
    if (it != results.end()) {
        results.erase(it);
    }
    return *this;
}

ostream& operator<<(ostream& os, const Patient& obj) {
    os << "Пациент: " << obj.fullName << "\n";
    os << "----------------------------------------\n";
    if (obj.results.empty()) {
        os << "Результаты анализов отсутствуют.\n";
    }
    else {
        for (const auto& res : obj.results) {
            os << res << "\n";
        }
    }
    return os;
}