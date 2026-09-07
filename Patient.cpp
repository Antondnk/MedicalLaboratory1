#include "Patient.h"
#include <iostream>

// Реализация конструктора
Patient::Patient(const std::string& fullName) : fullName(fullName) {}

// Реализация добавления результата (С ПРОВЕРКОЙ ОГРАНИЧЕНИЯ)
bool Patient::addTestResult(const TestResult& result) {

    // Это цикл for (range-based), фишка современного C++.
    // Он читается так: "Для каждого существующего результата (existingResult) внутри коллекции (results)..."
    // Мы используем константную ссылку (const auto&), чтобы не копировать данные и работать быстро.
    for (const auto& existingResult : results) {

        // Проверяем наше ограничение: совпадают ли название анализа И дата
        if (existingResult.getAnalysisName() == result.getAnalysisName() &&
            existingResult.getDate() == result.getDate()) {

            std::cout << "[ОШИБКА] Пациент " << fullName << " уже сдавал анализ '"
                << result.getAnalysisName() << "' в дату " << result.getDate() << "!\n";
            return false; // Отклоняем добавление, возвращаем ложь
        }
    }

    // Если цикл прошел и не нашел совпадений, значит всё окей.
    // Метод push_back() добавляет элемент в конец вектора.
    results.push_back(result);
    return true; // Возвращаем истину (успех)
}

// Вывод полной карточки пациента
void Patient::printMedicalRecord() const {
    std::cout << "========================================\n";
    std::cout << "Медицинская карта пациента: " << fullName << "\n";
    std::cout << "Количество сданных анализов: " << results.size() << "\n"; // Метод size() возвращает размер вектора
    std::cout << "История анализов:\n";

    // Снова удобный цикл для вывода всех результатов
    for (const auto& result : results) {
        result.printInfo();
    }
    std::cout << "========================================\n";
}