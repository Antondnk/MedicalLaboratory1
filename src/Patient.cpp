#include "Patient.h"
#include <iostream>

using namespace std;

Patient::Patient(const string& fullName) : fullName(fullName) {}

bool Patient::addTestResult(const TestResult& result)
{
    for (const auto& existingResult : results) {

        if (existingResult.getAnalysisName() == result.getAnalysisName() &&
            existingResult.getDate() == result.getDate()) {

            cout << "[ОШИБКА] Пациент " << fullName << " уже сдавал анализ '"
                << result.getAnalysisName() << "' в дату " << result.getDate() << "!\n";
            return false;
        }
    }
    
    results.push_back(result);
    return true;
}

void Patient::printMedicalRecord() const {
    cout << "========================================\n";
    cout << "Медицинская карта пациента: " << fullName << "\n";
    cout << "Количество сданных анализов: " << results.size() << "\n";
    cout << "История анализов:\n";

    for (const auto& result : results) {
        result.printInfo();
    }
    cout << "========================================\n";
}