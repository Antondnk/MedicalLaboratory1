#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>
#include "Analysis.h"
#include "TestResult.h"
#include "Patient.h"
#include <cctype>

const int cleanbuf = 1000;
using namespace std;

bool isValidDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[2] != '.' || date[5] != '.') return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return false;
    }
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year < 1900 || year > 2100) return false;
    return true;
}

void show_menu() {
    cout << "\n--- ГЛАВНОЕ МЕНЮ ---\n";
    cout << "1. Показать список доступных анализов (демо <<)\n";
    cout << "2. Изменить стоимость анализа\n";
    cout << "3. Сдать анализ (демо += и friend is_critical)\n";
    cout << "4. Показать медицинскую карту пациента (демо <<)\n";
    cout << "5. Добавить новый вид анализа (демо >>)\n";
    cout << "6. Удалить вид анализа из базы\n";
    cout << "7. Удалить результат анализа у пациента (демо -=)\n";
    cout << "8. Сравнить стоимость двух анализов (демо > и <)\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

void process_choice(int choice, vector<Analysis>& availableAnalyses, Patient& currentPatient) {
    switch (choice) {
    case 1: {
        cout << "\n--- ДОСТУПНЫЕ АНАЛИЗЫ ---\n";
        for (size_t i = 0; i < availableAnalyses.size(); ++i) {
            // ИСПОЛЬЗУЕМ ПЕРЕГРУЖЕННЫЙ <<
            cout << i + 1 << ". " << availableAnalyses[i] << "\n";
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

            string date;
            while (true) {
                cout << "Введите дату сдачи (например, 10.09.2026): ";
                getline(cin, date);

                if (isValidDate(date)) {
                    break;
                }
                cout << "Ошибка! Неверный формат даты. Попробуйте снова.\n";
            }
            cout << "Введите полученный результат (число): ";
            double value;
            cin >> value;

            TestResult newResult(availableAnalyses[index - 1], date, value);

            currentPatient += newResult;

            if (is_critical(newResult)) {
                cout << "!!! ВНИМАНИЕ !!! Критический результат отклонения от нормы! Срочно обратитесь к врачу!\n";
            }
        }
        else {
            cout << "Неверный номер анализа!\n";
        }
        break;
    }
    case 4: {
        cout << "\n";

        cout << currentPatient;
        break;
    }
    case 5: {

        Analysis newAnalysis;
        cin >> newAnalysis;
        availableAnalyses.push_back(newAnalysis);
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
    case 7: {

        cout << "\nВведите номер анализа из базы, который нужно удалить из карты пациента (1 - " << availableAnalyses.size() << "): ";
        int index;
        cin >> index;
        if (index >= 1 && index <= availableAnalyses.size()) {
            cin.ignore(cleanbuf, '\n');
            cout << "Введите дату сдачи для удаления (например, 10.09.2026): ";
            string date;
            getline(cin, date);

            TestResult dummyResult(availableAnalyses[index - 1], date, 0);

            currentPatient -= dummyResult;
        }
        else {
            cout << "Неверный номер анализа!\n";
        }
        break;
    }
    case 8: {

        if (availableAnalyses.size() < 2) {
            cout << "Недостаточно анализов в базе для сравнения.\n";
            break;
        }
        cout << "\nСравним первый и второй анализ в базе:\n";
        cout << "1: " << availableAnalyses[0].get_name() << " (" << availableAnalyses[0].get_cost() << " руб.)\n";
        cout << "2: " << availableAnalyses[1].get_name() << " (" << availableAnalyses[1].get_cost() << " руб.)\n";

        if (availableAnalyses[0] > availableAnalyses[1]) {
            cout << "Вывод: Первый анализ дороже второго.\n";
        }
        else if (availableAnalyses[0] < availableAnalyses[1]) {
            cout << "Вывод: Первый анализ дешевле второго.\n";
        }
        else {
            cout << "Вывод: Анализы стоят одинаково.\n";
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