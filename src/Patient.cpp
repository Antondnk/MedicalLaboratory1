#include "Patient.h"

using namespace std;

Patient::Patient(const string& fullName) : fullName(fullName) {}

// Реализация оператора += (Добавление)
Patient& Patient::operator+=(const TestResult& result) {
    for (const auto& existingResult : results) {
        // МАГИЯ С++: Здесь используется наш перегруженный оператор == из TestResult!
        if (existingResult == result) {
            cout << "[ОШИБКА] Операция невозможна! Пациент " << fullName << " уже сдавал анализ '"
                << result.get_analysis_name() << "' в эту дату!\n";
            return *this; // Возвращаем пациента без изменений
        }
    }

    results.push_back(result);
    return *this;
}

// Реализация оператора -= (Удаление)
Patient& Patient::operator-=(const TestResult& result) {
    // Используем итератор для прохода по вектору и удаления
    for (auto it = results.begin(); it != results.end(); ++it) {
        if (*it == result) { // Снова используем оператор ==
            results.erase(it);
            cout << "Результат успешно удален из карты!\n";
            return *this;
        }
    }
    // Обработка нештатной ситуации по заданию
    cout << "[ОШИБКА] Операция невозможна! Такого результата в карте пациента нет.\n";
    return *this;
}

// Реализация вывода (Печать карты пациента)
ostream& operator<<(ostream& os, const Patient& obj) {
    os << "========================================\n";
    os << "Медицинская карта пациента: " << obj.fullName << "\n";
    os << "Количество сданных анализов: " << obj.results.size() << "\n";
    os << "История анализов:\n";

    for (const auto& result : obj.results) {
        // МАГИЯ С++: Здесь вызывается оператор << из класса TestResult!
        os << result << "\n";
    }
    os << "========================================\n";
    return os;
}