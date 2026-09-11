#include "C:\Users\user\Desktop\ПНАЯВУ_3сем\MedicalLaboratory1\include\Patient.h"
#include <iostream>

using namespace std;

Patient::Patient(const string& fullName) : fullName(fullName) {}//реализация конструктора

bool Patient::addTestResult(const TestResult& result) //реализация добавления результата (С ПРОВЕРКОЙ ОГРАНИЧЕНИЯ)
{
    //использование константной ссылки (const auto&), чтобы не копировать данные и работать быстро
    for (const auto& existingResult : results) {

        //проверка ограничения: совпадают ли название анализа И дата
        if (existingResult.getAnalysisName() == result.getAnalysisName() &&
            existingResult.getDate() == result.getDate()) {

            cout << "[ОШИБКА] Пациент " << fullName << " уже сдавал анализ '"
                << result.getAnalysisName() << "' в дату " << result.getDate() << "!\n";
            return false; //Отклонение добавления, возвращение лжи
        }
    }

    //Если цикл прошел и не нашел совпадений, значит всё окей
    
    results.push_back(result);      //Метод push_back() добавляет элемент в конец вектора
    return true;
}

//Вывод полной карточки пациента
void Patient::printMedicalRecord() const {
    cout << "========================================\n";
    cout << "Медицинская карта пациента: " << fullName << "\n";
    cout << "Количество сданных анализов: " << results.size() << "\n"; //Метод size() возвращает размер вектора
    cout << "История анализов:\n";

    //цикл для вывода всех результатов
    for (const auto& result : results) {
        result.printInfo();
    }
    cout << "========================================\n";
}