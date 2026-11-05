#include "Patient.h"
#include "Validation.h"
#include "exceptions/Exceptions.h"
#include <algorithm>

Patient::Patient() : fullName("") {}

Patient::Patient(const string& fullName) : fullName(fullName) {
    if (is_blank(fullName)) {
        throw InvalidDataException("ФИО пациента не может быть пустым.");
    }
}

string Patient::get_full_name() const { return fullName; }

const vector<TestResult>& Patient::get_results() const { return results; }

bool Patient::has_result(const TestResult& result) const {
    for (const auto& res : results) {
        if (res == result) {
            return true;
        }
    }
    return false;
}

Patient& Patient::operator+=(const TestResult& result) {
    if (has_result(result)) {
        throw DuplicateIdException("У пациента уже есть результат этого анализа на эту дату.");
    }
    results.push_back(result);
    return *this;
}

Patient& Patient::operator-=(const TestResult& result) {
    auto it = std::find(results.begin(), results.end(), result);
    if (it == results.end()) {
        throw NotFoundException("У пациента нет такого результата анализа.");
    }
    results.erase(it);
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
