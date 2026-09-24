    #include "Patient.h"

    using namespace std;

    Patient::Patient(const string& fullName) : fullName(fullName) {}

    Patient& Patient::operator+=(const TestResult& result) {
        for (const auto& existingResult : results) {
            if (existingResult == result) {
                cout << "[ОШИБКА] Операция невозможна! Пациент " << fullName << " уже сдавал анализ '"
                    << result.get_analysis_name() << "' в эту дату!\n";
                return *this;
            }
        }

        results.push_back(result);
        return *this;
    }


    Patient& Patient::operator-=(const TestResult& result) {
        for (auto it = results.begin(); it != results.end(); ++it) {
            if (*it == result) { 
                results.erase(it);
                cout << "Результат успешно удален из карты!\n";
                return *this;
            }
        }
        cout << "[ОШИБКА] Операция невозможна! Такого результата в карте пациента нет.\n";
        return *this;
    }

    ostream& operator<<(ostream& os, const Patient& obj) {
        os << "========================================\n";
        os << "Медицинская карта пациента: " << obj.fullName << "\n";
        os << "Количество сданных анализов: " << obj.results.size() << "\n";
        os << "История анализов:\n";

        for (const auto& result : obj.results) {
            os << result << "\n";
        }
        os << "========================================\n";
        return os;
    }