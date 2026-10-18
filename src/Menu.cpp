#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu() {
    patients.add(Patient("Иванов Иван Иванович"));

    availableAnalyses.add(new BloodAnalysis("Общий анализ крови", "Гематология", 18.0, 4.0, 9.0, true, 6.0));
    availableAnalyses.add(new UrineAnalysis("Анализ мочи по Нечипоренко", "Клиника", 12.0, 0.0, 2000.0, true, 3.0));
    availableAnalyses.add(new GeneticAnalysis("ПЦР-тест на инфекции", "Генетика", 80.0, 0.0, 0.0, "BRCA1", 1.5));
}

Menu::~Menu() {
    clear_memory();
}

void Menu::clear_memory() {
    for (int i = 0; i < availableAnalyses.size(); ++i) {
        delete availableAnalyses.get(i);
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
        throw NotFoundException("Список доступных анализов пуст.");
    }
    cout << "\n=== СПИСОК ДОСТУПНЫХ АНАЛИЗОВ ===\n";
    for (int i = 0; i < availableAnalyses.size(); ++i) {
        cout << i + 1 << ". " << *availableAnalyses.get(i) << "\n";
    }
}

void Menu::change_analysis_cost() {
    if (availableAnalyses.empty()) {
        throw NotFoundException("Список анализов пуст.");
    }
    display_analyses();
    int idx = read_int("Выберите номер анализа для изменения стоимости: ", 1, availableAnalyses.size()) - 1;
    double newCost = read_double("Введите новую базовую стоимость: ", 0.0);

    availableAnalyses.get(idx)->set_base_cost(newCost);
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

    patients.add(Patient(name));
    cout << "Пациент \"" << name << "\" успешно добавлен в базу!\n";
}

void Menu::take_test() {
    if (availableAnalyses.empty()) {
        throw NotFoundException("Список анализов пуст!");
    }
    if (patients.empty()) {
        throw NotFoundException("Сначала добавьте хотя бы одного пациента!");
    }

    int p_idx = select_patient();
    display_analyses();
    int a_idx = read_int("Введите номер анализа: ", 1, availableAnalyses.size()) - 1;
    string date = read_date("Введите дату сдачи (например, 10.09.2026): ");
    double val = read_double("Введите полученный результат (число): ", 0.0);

    TestResult result(availableAnalyses.get(a_idx), date, val);

    if (patients.get(p_idx).has_result(result)) {
        throw DuplicateIdException("Ошибка: У пациента уже есть этот результат на эту дату!");
    }

    patients.get(p_idx) += result;
    cout << "Результат анализа успешно добавлен пациенту!\n";

    if (is_critical(result)) {
        cout << "ВНИМАНИЕ: Результат является КРИТИЧЕСКИМ (отклонение от нормы > 20%)!\n";
    }
}

void Menu::display_patient_card() const {
    if (patients.empty()) {
        throw NotFoundException("Список пациентов пуст.");
    }
    cout << "\n=== МЕДИЦИНСКИЕ КАРТЫ ПАЦИЕНТОВ ===\n";
    for (int i = 0; i < patients.size(); ++i) {
        cout << patients.get(i) << "\n";
    }
}

void Menu::add_analysis() {
    cout << "\nВыберите тип создаваемого анализа:\n"
        << "1. Анализ крови\n"
        << "2. Анализ мочи\n"
        << "3. Генетический / ПЦР анализ\n";
    int typeChoice = read_int("Ваш выбор: ", 1, 3);

    string name, category;
    cout << "Введите название анализа: ";
    getline(cin, name);
    cout << "Введите категорию: ";
    getline(cin, category);

    double baseCost = read_double("Введите баз. стоимость: ", 0.0);
    double minN = read_double("Мин. норма: ", 0.0);
    double maxN = read_double("Макс. норма: ", minN);

    Analysis* newAnalysis = nullptr;

    if (typeChoice == 1) {
        int fastingInt = read_int("Требуется сдача натощак (1 - Да, 0 - Нет): ", 0, 1);
        double reagentCost = read_double("Стоимость реагентов: ", 0.0);
        newAnalysis = new BloodAnalysis(name, category, baseCost, minN, maxN, fastingInt == 1, reagentCost);
    }
    else if (typeChoice == 2) {
        int sterileInt = read_int("Нужен контейнер (1 - Да, 0 - Нет): ", 0, 1);
        double containerCost = (sterileInt == 1) ? read_double("Стоимость контейнера: ", 0.0) : 0.0;
        newAnalysis = new UrineAnalysis(name, category, baseCost, minN, maxN, sterileInt == 1, containerCost);
    }
    else if (typeChoice == 3) {
        string gene;
        cout << "Введите ген-маркер: ";
        getline(cin, gene);
        double multiplier = read_double("Коэффициент сложности: ", 0.1);
        newAnalysis = new GeneticAnalysis(name, category, baseCost, minN, maxN, gene, multiplier);
    }

    if (newAnalysis) {
        availableAnalyses.add(newAnalysis);
        cout << "Новый вид анализа успешно добавлен в шаблонный контейнер!\n";
    }
}

void Menu::remove_analysis() {
    if (availableAnalyses.empty()) {
        throw NotFoundException("Список анализов пуст.");
    }
    display_analyses();
    int idx = read_int("Выберите номер анализа для удаления: ", 1, availableAnalyses.size()) - 1;

    Analysis* targetAnalysis = availableAnalyses.get(idx);

    for (int i = 0; i < patients.size(); ++i) {
        const auto& results = patients.get(i).get_results();
        for (const auto& res : results) {
            if (res.get_analysis() == targetAnalysis) {
                throw ConstraintViolationException("Ошибка: Этот анализ уже сдан пациентом! Удаление запрещено.");
            }
        }
    }

    delete availableAnalyses.get(idx);
    availableAnalyses.remove(idx);
    cout << "Вид анализа удален из базы.\n";
}

void Menu::remove_test_result() {
    if (patients.empty()) {
        throw NotFoundException("Список пациентов пуст!");
    }

    int p_idx = select_patient();
    const auto& results = patients.get(p_idx).get_results();
    if (results.empty()) {
        throw NotFoundException("У пациента нет результатов анализов.");
    }

    cout << "\nРезультаты анализов:\n";
    for (size_t i = 0; i < results.size(); ++i) {
        cout << i + 1 << ". " << results[i] << "\n";
    }

    int idx = read_int("Выберите номер результата: ", 1, results.size()) - 1;
    patients.get(p_idx) -= results[idx];
    cout << "Результат анализа удален у пациента.\n";
}

void Menu::compare_analyses() const {
    if (availableAnalyses.size() < 2) {
        throw ConstraintViolationException("Для сравнения нужно минимум 2 анализа в базе!");
    }
    display_analyses();
    int idx1 = read_int("Первый анализ: ", 1, availableAnalyses.size()) - 1;
    int idx2 = read_int("Второй анализ: ", 1, availableAnalyses.size()) - 1;

    if (idx1 == idx2) {
        throw InvalidDataException("Ошибка: Вы выбрали один и тот же анализ!");
    }

    const Analysis& a1 = *availableAnalyses.get(idx1);
    const Analysis& a2 = *availableAnalyses.get(idx2);

    cout << "\nРезультат сравнения стоимостей:\n";
    if (a1 > a2) {
        cout << "\"" << a1.get_name() << "\" дороже, чем \"" << a2.get_name() << "\".\n";
    }
    else if (a1 < a2) {
        cout << "\"" << a1.get_name() << "\" дешевле, чем \"" << a2.get_name() << "\".\n";
    }
    else {
        cout << "Стоимости равны.\n";
    }
}

int Menu::select_patient() const {
    if (patients.empty()) {
        throw NotFoundException("Список пациентов пуст.");
    }
    if (patients.size() == 1) {
        cout << "\nВыбран пациент: " << patients.get(0).get_full_name() << "\n";
        return 0;
    }
    cout << "\nВыберите пациента:\n";
    for (int i = 0; i < patients.size(); ++i) {
        cout << i + 1 << ". " << patients.get(i).get_full_name() << "\n";
    }
    return read_int("Ваш выбор: ", 1, patients.size()) - 1;
}

void Menu::demo_lab5_templates() {
    cout << "\n=== ДЕМОНСТРАЦИЯ ЛАБЫ №5 (Шаблоны) ===\n";
    cout << "1. Collection<Analysis*> содержит анализов: " << availableAnalyses.size() << "\n";
    cout << "2. Collection<Patient> содержит пациентов: " << patients.size() << "\n";
}

void Menu::demo_lab6_exceptions() {
    cout << "\n=== ДЕМОНСТРАЦИЯ ЛАБЫ №6 (Исключения) ===\n";
    try {
        cout << "Проверка перехвата выхода за границы контейнера...\n";
        availableAnalyses.get(999);
    }
    catch (const LabException& e) {
        cout << "[ПЕРЕХВАЧЕНО ИСКЛЮЧЕНИЕ]: " << e.what() << "\n";
    }
}

void Menu::run() {
    int choice = -1;
    while (choice != 0) {
        cout << "\n--- ГЛАВНОЕ МЕНЮ (Лабы 5 и 6) ---\n"
            << "1. Показать список доступных анализов\n"
            << "2. Изменить стоимость анализа\n"
            << "3. Сдать анализ пациенту\n"
            << "4. Показать медицинские карты пациентов\n"
            << "5. Добавить новый вид анализа\n"
            << "6. Удалить вид анализа из базы\n"
            << "7. Удалить результат анализа у пациента\n"
            << "8. Сравнить стоимость двух анализов\n"
            << "9. Добавить нового пациента\n"
            << "----------------------------------------\n"
            << "10. [Лаба №5] Демонстрация шаблонов\n"
            << "11. [Лаба №6] Демонстрация исключений\n"
            << "0. Выход\n";

        try {
            choice = read_int("Выберите действие: ", 0, 11);

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
            case 10: demo_lab5_templates(); break;
            case 11: demo_lab6_exceptions(); break;
            case 0: cout << "Завершение работы программы...\n"; break;
            }
        }
        catch (const LabException& e) {
            cerr << "\n[ОШИБКА В СИСТЕМЕ]: " << e.what() << "\n";
        }
        catch (const exception& e) {
            cerr << "\n[СТАНДАРТНАЯ ОШИБКА]: " << e.what() << "\n";
        }
    }
}