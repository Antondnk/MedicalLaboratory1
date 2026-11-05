#include "Menu.h"
#include "exceptions/Exceptions.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Menu::Menu() {
    patients.add(Patient("Иванов Иван Иванович"));

    availableAnalyses.add(new BloodAnalysis("General blood test", "Гематология", 18.0, 4.0, 9.0, true, 6.0));
    availableAnalyses.add(new UrineAnalysis("Urinalysis according to Nechiporenko", "Клиника", 12.0, 0.0, 2000.0, true, 3.0));
    availableAnalyses.add(new GeneticAnalysis("PCR test for infections", "Генетика", 80.0, 0.0, 0.0, "BRCA1", 1.5));
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

int Menu::read_int(const string& prompt) const {
    cout << prompt;
    int value;
    if (cin >> value) {
        cin.ignore(10000, '\n');
        return value;
    }
    if (cin.eof()) {
        throw runtime_error("Ввод данных прекращён (конец потока ввода).");
    }
    cin.clear();
    cin.ignore(10000, '\n');
    throw InvalidDataException("Ожидалось целое число.");
}

double Menu::read_double(const string& prompt) const {
    cout << prompt;
    double value;
    if (cin >> value) {
        cin.ignore(10000, '\n');
        return value;
    }
    if (cin.eof()) {
        throw runtime_error("Ввод данных прекращён (конец потока ввода).");
    }
    cin.clear();
    cin.ignore(10000, '\n');
    throw InvalidDataException("Ожидалось число.");
}

bool Menu::read_yes_no(const string& prompt) const {
    int answer = read_int(prompt);
    if (answer != 0 && answer != 1) {
        throw InvalidDataException("Нужно ввести 1 (да) или 0 (нет), а введено: " + to_string(answer) + ".");
    }
    return answer == 1;
}

void Menu::check_analysis_not_used(const Analysis* analysis, const Collection<Patient>& patientList) {
    for (int i = 0; i < patientList.size(); ++i) {
        for (const auto& res : patientList.get(i).get_results()) {
            if (res.get_analysis() == analysis) {
                throw ConstraintViolationException(
                    "Анализ \"" + analysis->get_name() + "\" уже сдан пациентом \"" +
                    patientList.get(i).get_full_name() + "\". Удаление запрещено.");
            }
        }
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

void Menu::search_analyses_by_price() const {
    if (availableAnalyses.empty()) {
        throw NotFoundException("Список анализов пуст.");
    }

    double maxPrice = read_double("Введите максимальную базовую стоимость для поиска: ");
    if (!(maxPrice >= 0)) {
        throw InvalidDataException("Максимальная стоимость не может быть отрицательной.");
    }

    auto filteredAnalyses = availableAnalyses.find_by([maxPrice](Analysis* a) {
        return a->get_base_cost() <= maxPrice;
        });

    if (filteredAnalyses.empty()) {
        cout << "Не найдено анализов с базовой стоимостью до " << maxPrice << " руб.\n";
        return;
    }

    cout << "\n=== РЕЗУЛЬТАТЫ ПОИСКА ПО ЦЕНЕ (find_by) ===\n";
    for (size_t i = 0; i < filteredAnalyses.size(); ++i) {
        cout << i + 1 << ". " << *filteredAnalyses[i] << "\n";
    }
}

void Menu::change_analysis_cost() {
    display_analyses(); 
    int idx = read_int("Выберите номер анализа для изменения стоимости: ") - 1;
    Analysis* analysis = availableAnalyses.get(idx);
    double newCost = read_double("Введите новую базовую стоимость: ");

    analysis->set_base_cost(newCost); 
    cout << "Базовая стоимость анализа успешно изменена!\n";
}

void Menu::add_patient() {
    string name;
    cout << "Введите ФИО нового пациента: ";
    getline(cin, name);

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
    int a_idx = read_int("Введите номер анализа: ") - 1;
    Analysis* analysis = availableAnalyses.get(a_idx);

    string date;
    cout << "Введите дату сдачи (например, 10.09.2026): ";
    getline(cin, date);
    double val = read_double("Введите полученный результат (число): ");

    TestResult result(analysis, date, val); 

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
    int typeChoice = read_int("Ваш выбор: ");
    if (typeChoice < 1 || typeChoice > 3) {
        throw InvalidDataException("Неизвестный тип анализа: " + to_string(typeChoice) + " (допустимо 1-3).");
    }

    string name, category;
    cout << "Введите название анализа: ";
    getline(cin, name);
    cout << "Введите категорию: ";
    getline(cin, category);

    double baseCost = read_double("Введите баз. стоимость: ");
    double minN = read_double("Мин. норма: ");
    double maxN = read_double("Макс. норма: ");

    Analysis* newAnalysis = nullptr;

    if (typeChoice == 1) {
        bool fasting = read_yes_no("Требуется сдача натощак (1 - Да, 0 - Нет): ");
        double reagentCost = read_double("Стоимость реагентов: ");
        newAnalysis = new BloodAnalysis(name, category, baseCost, minN, maxN, fasting, reagentCost);
    }
    else if (typeChoice == 2) {
        bool sterile = read_yes_no("Нужен контейнер (1 - Да, 0 - Нет): ");
        double containerCost = sterile ? read_double("Стоимость контейнера: ") : 0.0;
        newAnalysis = new UrineAnalysis(name, category, baseCost, minN, maxN, sterile, containerCost);
    }
    else {
        string gene;
        cout << "Введите ген-маркер: ";
        getline(cin, gene);
        double multiplier = read_double("Коэффициент сложности: ");
        newAnalysis = new GeneticAnalysis(name, category, baseCost, minN, maxN, gene, multiplier);
    }

    availableAnalyses.add(newAnalysis);
    cout << "Новый вид анализа успешно добавлен в шаблонный контейнер!\n";
}

void Menu::remove_analysis() {
    display_analyses();
    int idx = read_int("Выберите номер анализа для удаления: ") - 1;
    Analysis* targetAnalysis = availableAnalyses.get(idx); 

    check_analysis_not_used(targetAnalysis, patients); 

    delete targetAnalysis;
    availableAnalyses.remove(idx);
    cout << "Вид анализа удален из базы.\n";
}

void Menu::remove_test_result() {
    int p_idx = select_patient();
    const auto& results = patients.get(p_idx).get_results();
    if (results.empty()) {
        throw NotFoundException("У пациента нет результатов анализов.");
    }

    cout << "\nРезультаты анализов:\n";
    for (size_t i = 0; i < results.size(); ++i) {
        cout << i + 1 << ". " << results[i] << "\n";
    }

    int idx = read_int("Выберите номер результата: ") - 1;
    if (idx < 0 || idx >= static_cast<int>(results.size())) {
        throw IndexOutOfBoundsException("Результата с номером " + to_string(idx + 1) +
            " нет (у пациента результатов: " + to_string(results.size()) + ").");
    }
    patients.get(p_idx) -= results[idx];
    cout << "Результат анализа удален у пациента.\n";
}

void Menu::compare_analyses() const {
    if (availableAnalyses.size() < 2) {
        throw ConstraintViolationException("Для сравнения нужно минимум 2 анализа в базе.");
    }
    display_analyses();
    int idx1 = read_int("Первый анализ: ") - 1;
    const Analysis& a1 = *availableAnalyses.get(idx1); 
    int idx2 = read_int("Второй анализ: ") - 1;
    const Analysis& a2 = *availableAnalyses.get(idx2); 

    if (idx1 == idx2) {
        throw InvalidDataException("Вы выбрали один и тот же анализ.");
    }

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
    int idx = read_int("Ваш выбор: ") - 1;
    patients.get(idx); 
    return idx;
}

void Menu::search_specific_analysis() const {
    if (availableAnalyses.empty()) {
        throw NotFoundException("Список анализов пуст.");
    }

    cout << "Введите название анализа для точного поиска: ";
    string targetName;

    getline(cin >> ws, targetName);

    int foundIndex = -1;
    for (int i = 0; i < availableAnalyses.size(); ++i) {
        if (availableAnalyses.get(i)->get_name() == targetName) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        cout << "\n[ОБЪЕКТ НАЙДЕН]: Элемент обнаружен в коллекции под индексом [" << foundIndex << "]:\n";
        cout << *availableAnalyses.get(foundIndex) << "\n";
    }
    else {
        cout << "\n[ПОИСК]: Объект с таким наименованием не найден в коллекции.\n";
    }
}

void Menu::demo_lab5_templates() {
    cout << "\n=== ДЕМОНСТРАЦИЯ ЛАБЫ №5 (Шаблоны) ===\n";
    cout << "1. Collection<Analysis*> содержит анализов: " << availableAnalyses.size() << "\n";
    cout << "2. Collection<Patient> содержит пациентов: " << patients.size() << "\n";
}

void Menu::demo_lab6_exceptions() {
    cout << "\n=== ДЕМОНСТРАЦИЯ ЛАБЫ №6 (Исключения) ===\n";

    BloodAnalysis demoAnalysis("Демо-анализ", "Демо", 10.0, 1.0, 5.0, false, 2.0);
    Patient demoPatient("Демо Пациент");

    try {
        cout << "1) Выход за границы контейнера: get(999)...\n";
        availableAnalyses.get(999);
    }
    catch (const IndexOutOfBoundsException& e) {
        cout << "   [IndexOutOfBoundsException / " << e.get_exception_category() << "]: " << e.what() << "\n";
    }

    try {
        cout << "2) Некорректные данные: анализ с отрицательной стоимостью...\n";
        BloodAnalysis bad("Плохой анализ", "Демо", -10.0, 1.0, 5.0, false, 2.0);
    }
    catch (const InvalidDataException& e) {
        cout << "   [InvalidDataException / " << e.get_exception_category() << "]: " << e.what() << "\n";
    }

    try {
        cout << "3) Некорректные данные: результат с несуществующей датой 31.02.2026...\n";
        TestResult badDate(&demoAnalysis, "31.02.2026", 3.0);
    }
    catch (const InvalidDataException& e) {
        cout << "   [InvalidDataException / " << e.get_exception_category() << "]: " << e.what() << "\n";
    }

    TestResult goodResult(&demoAnalysis, "01.01.2026", 3.0);
    demoPatient += goodResult;

    try {
        cout << "4) Дубликат: добавляем пациенту тот же результат второй раз...\n";
        demoPatient += goodResult;
    }
    catch (const DuplicateIdException& e) {
        cout << "   [DuplicateIdException / " << e.get_exception_category() << "]: " << e.what() << "\n";
    }

    try {
        cout << "5) Обращение к несуществующему объекту: удаляем результат, которого нет...\n";
        demoPatient -= TestResult(&demoAnalysis, "02.02.2026", 1.0);
    }
    catch (const NotFoundException& e) {
        cout << "   [NotFoundException / " << e.get_exception_category() << "]: " << e.what() << "\n";
    }

    try {
        cout << "6) Нарушение связи: удаляем анализ, который уже сдан пациентом...\n";
        Collection<Patient> demoPatients;
        demoPatients.add(demoPatient);
        check_analysis_not_used(&demoAnalysis, demoPatients);
    }
    catch (const ConstraintViolationException& e) {
        cout << "   [ConstraintViolationException / " << e.get_exception_category() << "]: " << e.what() << "\n";
    }

    cout << "\nВсе исключения перехвачены, программа продолжает работу.\n";
}

void Menu::print_menu() const {
    cout << "\n--- ГЛАВНОЕ МЕНЮ ---\n"
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
        << "12. [Лаба №5] Поиск анализов по цене (find_by)\n"
        << "13. [Лаба №5] Точный поиск объекта\n"
        << "0. Выход\n";
}

bool Menu::process_command() {
    print_menu();
    int choice = read_int("Выберите действие: ");

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
    case 12: search_analyses_by_price(); break;
    case 13: search_specific_analysis(); break;
    case 0:
        cout << "Завершение работы программы...\n";
        return false;
    default:
        throw InvalidDataException("Пункта меню №" + to_string(choice) + " не существует (допустимо 0-13).");
    }
    return true;
}
