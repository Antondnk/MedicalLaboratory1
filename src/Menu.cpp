#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu() {
    patients.push_back(Patient("Иванов Иван Иванович"));

    availableAnalyses.push_back(new BloodAnalysis("Общий анализ крови", "Гематология", 18.0, 4.0, 9.0, true, 6.0));
    availableAnalyses.push_back(new UrineAnalysis("Анализ мочи по Нечипоренко", "Клиника", 12.0, 0.0, 2000.0, true, 3.0));
    availableAnalyses.push_back(new GeneticAnalysis("ПЦР-тест на инфекции", "Генетика", 80.0, 0.0, 0.0, "BRCA1", 1.5));
}

Menu::~Menu() {
    clear_memory();
}

void Menu::clear_memory() {
    for (Analysis* ptr : availableAnalyses) {
        delete ptr;
    }
    availableAnalyses.clear();
}

int Menu::read_int(const string& prompt, int minVal, int maxVal) const {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minVal && value <= maxVal) {
            cin.ignore(10000, '\n');
            return value;
        }
        cout << "Ошибка! Введите целое число от " << minVal << " до " << maxVal << ".\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

double Menu::read_double(const string& prompt, double minVal) const {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minVal) {
            cin.ignore(10000, '\n');
            return value;
        }
        cout << "Ошибка! Введите числовое значение (не меньше " << minVal << ").\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

bool Menu::is_valid_date(const string& date) const {
    if (date.length() != 10) return false;
    if (date[2] != '.' || date[5] != '.') return false;

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    }

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (month < 1 || month > 12) return false;
    if (year < 1900 || year > 2100) return false;

    int days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[2] = 29;
    }

    if (day < 1 || day > days_in_month[month]) return false;

    return true;
}

string Menu::read_date(const string& prompt) const {
    string date;
    while (true) {
        cout << prompt;
        getline(cin, date);
        if (is_valid_date(date)) {
            return date;
        }
        cout << "Ошибка ввода! Введите дату в формате ДД.ММ.ГГГГ (например, 10.09.2026).\n";
    }
}

void Menu::display_analyses() const {
    if (availableAnalyses.empty()) {
        cout << "Список доступных анализов пуст.\n";
        return;
    }
    cout << "\n=== СПИСОК ДОСТУПНЫХ АНАЛИЗОВ ===\n";
    for (size_t i = 0; i < availableAnalyses.size(); ++i) {
        cout << i + 1 << ". " << *availableAnalyses[i] << "\n";
    }
}

void Menu::change_analysis_cost() {
    if (availableAnalyses.empty()) {
        cout << "Список анализов пуст.\n";
        return;
    }
    display_analyses();
    int idx = read_int("Выберите номер анализа для изменения стоимости: ", 1, availableAnalyses.size()) - 1;
    double newCost = read_double("Введите новую базовую стоимость: ", 0.0);

    availableAnalyses[idx]->set_base_cost(newCost);
    cout << "Базовая стоимость анализа успешно изменена!\n";
}

void Menu::add_patient() {
    string name;
    while (true) {
        cout << "Введите ФИО нового пациента: ";
        getline(cin, name);

        if (!name.empty() && name.find_first_not_of(" \t") != string::npos) {
            break;
        }
        cout << "Ошибка: ФИО пациента не может быть пустым!\n";
    }

    patients.push_back(Patient(name));
    cout << "Пациент \"" << name << "\" успешно добавлен в базу!\n";
}

void Menu::take_test() {
    if (availableAnalyses.empty()) {
        cout << "Список анализов пуст!\n";
        return;
    }
    if (patients.empty()) {
        cout << "Сначала добавьте хотя бы одного пациента (Пункт 9)!\n";
        return;
    }

    int p_idx = select_patient();

    display_analyses();
    int a_idx = read_int("Введите номер анализа (1 - " + to_string(availableAnalyses.size()) + "): ", 1, availableAnalyses.size()) - 1;
    string date = read_date("Введите дату сдачи (например, 10.09.2026): ");
    double val = read_double("Введите полученный результат (число): ", 0.0);

    TestResult result(availableAnalyses[a_idx], date, val);

    if (patients[p_idx].has_result(result)) {
        cout << " Ошибка: У пациента уже есть этот результат на эту дату!\n";
    }
    else {
        patients[p_idx] += result;
        cout << " Результат анализа успешно добавлен пациенту!\n";

        if (is_critical(result)) {
            cout << " ВНИМАНИЕ: Результат является КРИТИЧЕСКИМ (отклонение от нормы > 20%)!\n";
        }
    }
}

void Menu::display_patient_card() const {
    if (patients.empty()) {
        cout << "Список пациентов пуст.\n";
        return;
    }
    cout << "\n=== МЕДИЦИНСКИЕ КАРТЫ ПАЦИЕНТОВ ===\n";
    for (const auto& patient : patients) {
        cout << patient << "\n";
    }
}

void Menu::add_analysis() {
    cout << "\nВыберите тип создаваемого анализа:\n";
    cout << "1. Анализ крови\n";
    cout << "2. Анализ мочи\n";
    cout << "3. Генетический / ПЦР анализ\n";
    int typeChoice = read_int("Ваш выбор: ", 1, 3);

    string name, category;
    cout << "Введите название анализа: ";
    getline(cin, name);
    cout << "Введите категорию: ";
    getline(cin, category);

    double baseCost = read_double("Введите базовую стоимость: ", 0.0);
    double minN = read_double("Введите нижнюю границу нормы: ", 0.0);
    double maxN = read_double("Введите верхнюю границу нормы: ", minN);

    Analysis* newAnalysis = nullptr;

    if (typeChoice == 1) {
        int fastingInt = read_int("Требуется сдача натощак (1 - Да, 0 - Нет): ", 0, 1);
        double reagentCost = read_double("Введите стоимость реагентов (0 если нет): ", 0.0);
        newAnalysis = new BloodAnalysis(name, category, baseCost, minN, maxN, fastingInt == 1, reagentCost);
    }
    else if (typeChoice == 2) {
        int sterileInt = read_int("Нужен стерильный контейнер (1 - Да, 0 - Нет): ", 0, 1);
        double containerCost = 0.0;
        if (sterileInt == 1) { // Логическая проверка: цена нужна только если контейнер есть
            containerCost = read_double("Введите стоимость контейнера: ", 0.0);
        }
        newAnalysis = new UrineAnalysis(name, category, baseCost, minN, maxN, sterileInt == 1, containerCost);
    }
    else if (typeChoice == 3) {
        string gene;
        cout << "Введите ген-маркер: ";
        getline(cin, gene);
        double multiplier = read_double("Введите коэффициент сложности (например, 1.5): ", 0.1);
        newAnalysis = new GeneticAnalysis(name, category, baseCost, minN, maxN, gene, multiplier);
    }

    if (newAnalysis) {
        availableAnalyses.push_back(newAnalysis);
        cout << "Новый вид анализа успешно добавлен в базу!\n";
    }
}
void Menu::remove_analysis() {
    if (availableAnalyses.empty()) {
        cout << "Список анализов пуст.\n";
        return;
    }
    display_analyses();
    int idx = read_int("Выберите номер анализа для удаления: ", 1, availableAnalyses.size()) - 1;

    Analysis* targetAnalysis = availableAnalyses[idx];

    for (const auto& patient : patients) {
        const auto& results = patient.get_results();
        for (const auto& res : results) {
            if (res.get_analysis() == targetAnalysis) {
                cout << "ОШИБКА: Этот анализ уже сдан пациентом (" << patient.get_full_name()
                    << "). Удаление приведет к повреждению медицинской карты!\n";
                return;
            }
        }
    }

    delete availableAnalyses[idx];
    availableAnalyses.erase(availableAnalyses.begin() + idx);
    cout << "Вид анализа удален из базы.\n";
}

void Menu::remove_test_result() {
    if (patients.empty()) {
        cout << "Список пациентов пуст!\n";
        return;
    }

    int p_idx = select_patient();

    const auto& results = patients[p_idx].get_results();
    if (results.empty()) {
        cout << "У пациента нет результатов анализов для удаления.\n";
        return;
    }

    cout << "\nРезультаты анализов пациента:\n";
    for (size_t i = 0; i < results.size(); ++i) {
        cout << i + 1 << ". " << results[i] << "\n";
    }

    int idx = read_int("Выберите номер результата для удаления: ", 1, results.size()) - 1;
    TestResult target = results[idx];

    patients[p_idx] -= target;
    cout << "Результат анализа удален у пациента.\n";
}

void Menu::compare_analyses() const {
    if (availableAnalyses.size() < 2) {
        cout << "Для сравнения нужно минимум 2 анализа в базе!\n";
        return;
    }
    display_analyses();
    int idx1 = read_int("Выберите номер первого анализа: ", 1, availableAnalyses.size()) - 1;
    int idx2 = read_int("Выберите номер второго анализа: ", 1, availableAnalyses.size()) - 1;

    if (idx1 == idx2) {
        cout << "Вы выбрали один и тот же анализ!\n";
        return;
    }

    const Analysis& a1 = *availableAnalyses[idx1];
    const Analysis& a2 = *availableAnalyses[idx2];

    cout << "\nРезультат сравнения итоговых стоимостей:\n";
    if (a1 > a2) {
        cout << "\"" << a1.get_name() << "\" (" << a1.calculate_total_cost() << " руб.) ДОРОЖЕ, чем \""
            << a2.get_name() << "\" (" << a2.calculate_total_cost() << " руб.).\n";
    }
    else if (a1 < a2) {
        cout << "\"" << a1.get_name() << "\" (" << a1.calculate_total_cost() << " руб.) ДЕШЕВЛЕ, чем \""
            << a2.get_name() << "\" (" << a2.calculate_total_cost() << " руб.).\n";
    }
    else {
        cout << "Итоговая стоимость анализов ОДИНАКОВА (" << a1.calculate_total_cost() << " руб.).\n";
    }
}

int Menu::select_patient() const {
    if (patients.empty()) return -1;
    if (patients.size() == 1) {
        cout << "\nВыбран пациент: " << patients[0].get_full_name() << "\n";
        return 0;
    }
    cout << "\nВыберите пациента:\n";
    for (size_t i = 0; i < patients.size(); ++i) {
        cout << i + 1 << ". " << patients[i].get_full_name() << "\n";
    }
    return read_int("Ваш выбор: ", 1, patients.size()) - 1;
}

void Menu::run() {
    int choice = -1;
    while (choice != 0) {
        cout << "\n--- ГЛАВНОЕ МЕНЮ ---\n";
        cout << "1. Показать список доступных анализов (демо <<)\n";
        cout << "2. Изменить стоимость анализа\n";
        cout << "3. Сдать анализ (демо += и friend is_critical)\n";
        cout << "4. Показать медицинские карты пациентов (демо <<)\n";
        cout << "5. Добавить новый вид анализа (демо >>)\n";
        cout << "6. Удалить вид анализа из базы\n";
        cout << "7. Удалить результат анализа у пациента (демо -=)\n";
        cout << "8. Сравнить стоимость двух анализов (демо > и <)\n";
        cout << "9. Добавить нового пациента\n";
        cout << "0. Выход\n";

        choice = read_int("Выберите действие: ", 0, 9);

        switch (choice) {
        case 1: display_analyses(); break;
        case 2: change_analysis_cost(); break;
        case 3: take_test(); break;
        case 4: display_patient_card(); break;
        case 5: add_analysis(); break;
        case 6: remove_analysis(); break;
        case 7: remove_test_result(); break;
        case 8: compare_analyses(); break;
        case 9: add_patient(); break;
        case 0: cout << "Завершение работы программы...\n"; break;
        }
    }
}