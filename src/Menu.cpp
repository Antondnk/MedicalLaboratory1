#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>
#include "Analysis.h"
#include "TestResult.h"
#include "Patient.h"

#define cleanbuf 1000
using namespace std;

void show_menu() {
    cout << "\n--- ГЛАВНОЕ МЕНЮ ---\n";
    cout << "1. Показать список доступных анализов\n";
    cout << "2. Изменить стоимость анализа\n";
    cout << "3. Сдать анализ (добавить результат пациенту)\n";
    cout << "4. Показать медицинскую карту пациента\n";
    cout << "5. Добавить новый вид анализа\n";
    cout << "6. Удалить вид анализа\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

void process_choice(int choice, vector<Analysis>& availableAnalyses, Patient& currentPatient) {
    switch (choice) {
    case 1: {
        cout << "\n--- ДОСТУПНЫЕ АНАЛИЗЫ ---\n";
        for (size_t i = 0; i < availableAnalyses.size(); ++i) {
            cout << i + 1 << ". ";
            availableAnalyses[i].print_info();
        }
        break;
    }
    case 2: {
        cout << "\nВведите номер анализа для изменения цены (1 - " << availableAnalyses.size() << "): ";
        int index;
        cin >> index;

        if (index >= 1 && index <= availableAnalyses.size()) {
            cout << "Текущая стоимость: " << availableAnalyses[index - 1].get_cost() << " руб.\n";
            cout << "Введите новую стоимость: ";
            double newCost;
            cin >> newCost;

            availableAnalyses[index - 1].set_cost(newCost);
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

            cout << "Введите дату сдачи (например, 10.09.2026): ";
            string date;
            getline(cin, date);

            cout << "Введите полученный результат (число): ";
            double value;
            cin >> value;

            TestResult newResult(availableAnalyses[index - 1], date, value);

            if (currentPatient.add_test_result(newResult)) {
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
        currentPatient.print_medical_record();
        break;
    }
    case 5: {
        cin.ignore(cleanbuf, '\n');
        string name, category;
        double cost, minNormal, maxNormal;
        cout << "Введите название анализа: ";
        getline(cin, name);
        cout << "Введите категорию анализа: ";
        getline(cin, category);
        cout << "Введите стоимость: ";
        cin >> cost;
        cout << "Введите минимальную норму: ";
        cin >> minNormal;
        cout << "Введите максимальную норму: ";
        cin >> maxNormal;

        availableAnalyses.push_back(Analysis(name, category, cost, minNormal, maxNormal));
        cout << "Новый вид анализа успешно добавлен!\n";
        break;
    }
    case 6: {
        cout << "Введите номер анализа для удаления (1 - " << availableAnalyses.size() << "): ";
        int index;
        cin >> index;
        if (index >= 1 && index <= availableAnalyses.size()) {
            availableAnalyses.erase(availableAnalyses.begin() + index - 1);
            cout << "Анализ успешно удален!\n";
        }
        else {
            cout << "Неверный номер анализа!\n";
        }
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

void run_menu() {
    vector<Analysis> availableAnalyses;
    availableAnalyses.push_back(Analysis("Общий анализ крови", "Гематология", 50.0, 4.0, 9.0));
    availableAnalyses.push_back(Analysis("Уровень глюкозы", "Биохимия", 30.0, 3.3, 5.5));
    availableAnalyses.push_back(Analysis("Холестерин", "Биохимия", 40.0, 3.2, 5.2));

    cout << "=== ДОБРО ПОЖАЛОВАТЬ В МЕДИЦИНСКУЮ ЛАБОРАТОРИЮ ===\n\n";

    cout << "Введите ФИО пациента для регистрации: ";
    string patientName;

    getline(cin, patientName);
    Patient currentPatient(patientName);

    int choice = -1;

    while (choice != 0) {
        show_menu();

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(cleanbuf, '\n');
            cout << "Ошибка ввода! Введите число.\n";
            continue;
        }

        process_choice(choice, availableAnalyses, currentPatient);
    }
}