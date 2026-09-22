#include "Patient.h"
#include <iostream>

using namespace std;

Patient::Patient(const string& fullName) : fullName(fullName) {}

bool Patient::add_test_result(const TestResult& result)
{
    for (const auto& existingResult : results) {

        if (existingResult.get_analysis_name() == result.get_analysis_name() &&
            existingResult.get_date() == result.get_date()) {

            cout << "[ОШИБКА] Пациент " << fullName << " уже сдавал анализ '"
                << result.get_analysis_name() << "' в дату " << result.get_date() << "!\n";
            return false;
        }
    }
    
    results.push_back(result);
    return true;
}

void Patient::print_medical_record() const {
    cout << "========================================\n";
    cout << "Медицинская карта пациента: " << fullName << "\n";
    cout << "Количество сданных анализов: " << results.size() << "\n";
    cout << "История анализов:\n";

    for (const auto& result : results) {
        result.print_info();
    }
    cout << "========================================\n";
}