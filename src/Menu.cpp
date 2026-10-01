#include "Menu.h"
#include <iostream>
#include <limits>

using namespace std;

Menu::Menu() {
    // Начальные тестовые данные разных типов
    availableAnalyses.push_back(new BloodAnalysis("Общий анализ крови", "Гематология", 500.0, 4.0, 9.0, true, 150.0));
    availableAnalyses.push_back(new UrineAnalysis("Анализ мочи по Нечипоренко", "Клиника", 300.0, 0.0, 2000.0, true, 50.0));
    availableAnalyses.push_back(new GeneticAnalysis("ПЦР-тест на инфекции", "Генетика", 1200.0, 0.0, 0.0, "BRCA1", 1.5));
}

Menu::~Menu() {
    clear_memory();
}

void Menu::clear_memory() {
    for (Analysis* ptr : availableAnalyses) {
        delete ptr; // Освобождение динамической памяти
    }
    availableAnalyses.clear();
}

void Menu::display_analyses() const {
    if (availableAnalyses.empty()) {
        cout << "Список анализов пуст.\n";
        return;
    }
    cout << "\n=== СПИСОК ДОСТУПНЫХ АНАЛИЗОВ ===\n";
    for (size_t i = 0; i < availableAnalyses.size(); ++i) {
        cout << i + 1 << ". ";
        availableAnalyses[i]->print_info(cout); // Полиморфный вызов
        cout << "\n";
    }
}

void Menu::add_analysis() {
    cout << "\nВыберите тип создаваемого анализа:\n";
    cout << "1. Анализ крови\n";
    cout << "2. Анализ мочи\n";
    cout << "3. Генетический / ПЦР анализ\n";
    cout << "Ваш выбор: ";

    int typeChoice;
    cin >> typeChoice;

    if (typeChoice < 1 || typeChoice > 3) {
        cout << "Неверный выбор типа анализа!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string name, category;
    double baseCost, minN, maxN;

    cout << "Введите название анализа: ";
    getline(cin, name);
    cout << "Введите категорию: ";
    getline(cin, category);
    cout << "Введите базовую стоимость: ";
    cin >> baseCost;
    cout << "Введите нижнюю границу нормы: ";
    cin >> minN;
    cout << "Введите верхнюю границу нормы: ";
    cin >> maxN;

    Analysis* newAnalysis = nullptr;

    if (typeChoice == 1) {
        bool fasting;
        double reagentCost;
        cout << "Требуется сдача натощак (1 - Да, 0 - Нет): ";
        cin >> fasting;
        cout << "Введите стоимость реагентов: ";
        cin >> reagentCost;

        newAnalysis = new BloodAnalysis(name, category, baseCost, minN, maxN, fasting, reagentCost);
    }
    else if (typeChoice == 2) {
        bool sterile;
        double containerCost;
        cout << "Нужен стерильный контейнер (1 - Да, 0 - Нет): ";
        cin >> sterile;
        cout << "Введите стоимость контейнера: ";
        cin >> containerCost;

        newAnalysis = new UrineAnalysis(name, category, baseCost, minN, maxN, sterile, containerCost);
    }
    else if (typeChoice == 3) {
        string gene;
        double multiplier;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введите ген-маркер: ";
        getline(cin, gene);
        cout << "Введите коэффициент сложности (например, 1.5): ";
        cin >> multiplier;

        newAnalysis = new GeneticAnalysis(name, category, baseCost, minN, maxN, gene, multiplier);
    }

    if (newAnalysis) {
        availableAnalyses.push_back(newAnalysis);
        cout << "Анализ успешно добавлен!\n";
    }
}

void Menu::delete_analysis() {
    if (availableAnalyses.empty()) {
        cout << "Список анализов пуст.\n";
        return;
    }
    display_analyses();
    cout << "Выберите номер анализа для удаления: ";
    int index;
    cin >> index;
    if (index < 1 || index > static_cast<int>(availableAnalyses.size())) {
        cout << "Неверный номер!\n";
        return;
    }

    // Удаляем объект из динамической памяти перед исключением из вектора
    delete availableAnalyses[index - 1];
    availableAnalyses.erase(availableAnalyses.begin() + (index - 1));
    cout << "Вид анализа успешно удален из системы.\n";
}

void Menu::add_patient() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name;
    cout << "Введите ФИО пациента: ";
    getline(cin, name);

    patients.push_back(Patient(name));
    cout << "Пациент добавлен!\n";
}

void Menu::delete_patient() {
    if (patients.empty()) {
        cout << "Список пациентов пуст.\n";
        return;
    }
    cout << "\nВыберите пациента для удаления:\n";
    for (size_t i = 0; i < patients.size(); ++i) {
        cout << i + 1 << ". " << patients[i].get_full_name() << "\n";
    }
    cout << "Ваш выбор: ";
    int index;
    cin >> index;
    if (index < 1 || index > static_cast<int>(patients.size())) {
        cout << "Неверный номер!\n";
        return;
    }

    patients.erase(patients.begin() + (index - 1));
    cout << "Пациент успешно удален.\n";
}

void Menu::add_test_result_to_patient() {
    if (patients.empty()) {
        cout << "Список пациентов пуст!\n";
        return;
    }
    if (availableAnalyses.empty()) {
        cout << "Список анализов пуст!\n";
        return;
    }

    cout << "\nВыберите пациента:\n";
    for (size_t i = 0; i < patients.size(); ++i) {
        cout << i + 1 << ". " << patients[i].get_full_name() << "\n";
    }
    int pChoice;
    cin >> pChoice;
    if (pChoice < 1 || pChoice > static_cast<int>(patients.size())) {
        cout << "Неверный выбор!\n";
        return;
    }

    display_analyses();
    cout << "Выберите номер анализа: ";
    int aChoice;
    cin >> aChoice;
    if (aChoice < 1 || aChoice > static_cast<int>(availableAnalyses.size())) {
        cout << "Неверный выбор!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string date;
    double val;
    cout << "Введите дату сдачи (ГГГГ-ММ-ДД): ";
    getline(cin, date);
    cout << "Введите полученный результат: ";
    cin >> val;

    TestResult result(availableAnalyses[aChoice - 1], date, val);
    Patient& selectedPatient = patients[pChoice - 1];

    if (selectedPatient.has_result(result)) {
        cout << " Ошибка: У пациента уже зарегистрирован такой результат анализа на эту дату!\n";
    }
    else {
        selectedPatient += result; // Используем перегруженный оператор +=
        cout << " Результат успешно добавлен пациенту.\n";
    }
}

void Menu::remove_test_result_from_patient() {
    if (patients.empty()) {
        cout << "Список пациентов пуст!\n";
        return;
    }

    cout << "\nВыберите пациента:\n";
    for (size_t i = 0; i < patients.size(); ++i) {
        cout << i + 1 << ". " << patients[i].get_full_name() << "\n";
    }
    int pChoice;
    cin >> pChoice;
    if (pChoice < 1 || pChoice > static_cast<int>(patients.size())) {
        cout << "Неверный выбор!\n";
        return;
    }

    Patient& selectedPatient = patients[pChoice - 1];
    const auto& results = selectedPatient.get_results();

    if (results.empty()) {
        cout << "У этого пациента нет зарегистрированных результатов анализов.\n";
        return;
    }

    cout << "\nРезультаты анализов пациента:\n";
    for (size_t i = 0; i < results.size(); ++i) {
        cout << i + 1 << ". " << results[i] << "\n";
    }
    cout << "Выберите номер результата для удаления: ";
    int rChoice;
    cin >> rChoice;
    if (rChoice < 1 || rChoice > static_cast<int>(results.size())) {
        cout << "Неверный выбор!\n";
        return;
    }

    TestResult target = results[rChoice - 1];
    selectedPatient -= target; // Демонстрация работы перегруженного оператора -=
    cout << "Результат анализа успешно удален у пациента.\n";
}

void Menu::display_patients() const {
    if (patients.empty()) {
        cout << "Список пациентов пуст.\n";
        return;
    }
    cout << "\n=== СПИСОК ПАЦИЕНТОВ И ИХ РЕЗУЛЬТАТОВ ===\n";
    for (const auto& patient : patients) {
        cout << patient << "\n";
    }
}

void Menu::run() {
    int choice = 0;
    while (choice != 9) {
        cout << "\n================ МЕНЮ ================\n";
        cout << "1. Показать список доступных анализов\n";
        cout << "2. Добавить новый вид анализа\n";
        cout << "3. Удалить вид анализа\n";
        cout << "4. Добавить пациента\n";
        cout << "5. Удалить пациента\n";
        cout << "6. Внести результат анализа пациенту (+=)\n";
        cout << "7. Удалить результат анализа у пациента (-=)\n";
        cout << "8. Показать карточки всех пациентов\n";
        cout << "9. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: display_analyses(); break;
        case 2: add_analysis(); break;
        case 3: delete_analysis(); break;
        case 4: add_patient(); break;
        case 5: delete_patient(); break;
        case 6: add_test_result_to_patient(); break;
        case 7: remove_test_result_from_patient(); break;
        case 8: display_patients(); break;
        case 9: cout << "Завершение работы программы...\n"; break;
        default: cout << "Неверная команда!\n"; break;
        }
    }
}