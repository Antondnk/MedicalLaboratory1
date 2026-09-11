#include <iostream>
#include <string>
#include <vector>
#include "C:\Users\user\Desktop\ПНАЯВУ_3сем\MedicalLaboratory1\include\Analysis.h"
#include "C:\Users\user\Desktop\ПНАЯВУ_3сем\MedicalLaboratory1\include\TestResult.h"
#include "C:\Users\user\Desktop\ПНАЯВУ_3сем\MedicalLaboratory1\include\Patient.h"
#define cleanbuf 1000
using namespace std;

int main() {
    //Поддержка русского языка в консоли
    setlocale(LC_ALL, "Russian");

    //Создание хранилища доступных анализов для нашей лаборатории
    vector<Analysis> availableAnalyses;
    availableAnalyses.push_back(Analysis("Общий анализ крови", "Гематология", 50.0, 4.0, 9.0));
    availableAnalyses.push_back(Analysis("Уровень глюкозы", "Биохимия", 30.0, 3.3, 5.5));
    availableAnalyses.push_back(Analysis("Холестерин", "Биохимия", 40.0, 3.2, 5.2));

    cout << "=== ДОБРО ПОЖАЛОВАТЬ В МЕДИЦИНСКУЮ ЛАБОРАТОРИЮ ===\n\n";

    //Регистрация пациента
    cout << "Введите ФИО пациента для регистрации: ";
    string patientName;
    //getline для чтения строки с пробелами (Иванов Иван Иванович)
    getline(cin, patientName);
    Patient currentPatient(patientName);

    int choice = -1;

    //Главный цикл меню
    while (choice != 0) {
        cout << "\n--- ГЛАВНОЕ МЕНЮ ---\n";
        cout << "1. Показать список доступных анализов\n";
        cout << "2. Изменить стоимость анализа\n";
        cout << "3. Сдать анализ (добавить результат пациенту)\n";
        cout << "4. Показать медицинскую карту пациента\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        cin >> choice;

        //Если пользователь ввел букву вместо цифры, предотвращаем бесконечный цикл
        if (cin.fail()) {
            cin.clear(); //Очищаем флаг ошибки
            cin.ignore(cleanbuf, '\n'); //Пропускаем кривой ввод
            cout << "Ошибка ввода! Введите число.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            cout << "\n--- ДОСТУПНЫЕ АНАЛИЗЫ ---\n";
            for (size_t i = 0; i < availableAnalyses.size(); ++i) {
                cout << i + 1 << ". ";
                availableAnalyses[i].printInfo();
            }
            break;
        }
        case 2: {
            cout << "\nВведите номер анализа для изменения цены (1 - " << availableAnalyses.size() << "): ";
            int index;
            cin >> index;

            if (index >= 1 && index <= availableAnalyses.size()) {
                cout << "Текущая стоимость: " << availableAnalyses[index - 1].getCost() << " руб.\n";
                cout << "Введите новую стоимость: ";
                double newCost;
                cin >> newCost;

                availableAnalyses[index - 1].setCost(newCost);
                cout << "Стоимость успешно изменена!\n";
            }
            else {
                cout << "Неверный номер анализа!\n";
            }
            break;
        }
        case 3: {
            cout << "\nВведите номер анализа, который сдает пациент (1 - " << availableAnalyses.size() << "): ";
            int index;
            cin >> index;

            if (index >= 1 && index <= availableAnalyses.size()) {
                cin.ignore(cleanbuf, '\n');

                cout << "Введите дату сдачи (например, 10.09.2023): ";
                string date;
                getline(cin, date);

                cout << "Введите полученный результат (число): ";
                double value;
                cin >> value;

                //Создание объекта результата
                TestResult newResult(availableAnalyses[index - 1], date, value);

                //проверка на дубликаты
                if (currentPatient.addTestResult(newResult)) {
                    cout << "Результат успешно добавлен в карту!\n";
                }
            }
            else {
                cout << "Неверный номер анализа!\n";
            }
            break;
        }
        case 4: {
            cout << "\n";
            currentPatient.printMedicalRecord();
            break;
        }
        case 0: {
            cout << "Завершение работы программы. Будьте здоровы!\n";
            break;
        }
        default: {
            cout << "Неизвестная команда. Попробуйте снова.\n";
            break;
        }
        }
    }
    return 0;
}