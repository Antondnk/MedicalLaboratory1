#include <iostream>
#include "Analysis.h"
#include "TestResult.h"
#include "Patient.h"

using namespace std;

int main() {
    //поддержка русского языка в консоли Windows
    setlocale(LC_ALL, "Russian");

    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ МЕДИЦИНСКОЙ ЛАБОРАТОРИИ ===\n\n";

    //1.Создание объектов (виды анализов)
    cout << "--- 1. Доступные виды анализов ---\n";
    Analysis bloodTest("Общий анализ крови", "Гематология", 500.0, 4.0, 9.0);
    Analysis sugarTest("Уровень глюкозы", "Биохимия", 300.0, 3.3, 5.5);

    bloodTest.printInfo();
    sugarTest.printInfo();

    // 2.Изменение характеристик объекта
    cout << "\n--- 2. Изменение стоимости ---\n";
    cout << "Изменяем цену на глюкозу с 300 на 350 руб...\n";
    sugarTest.setCost(350.0);
    sugarTest.printInfo(); //Проверка, что цена изменилась

    // 3.Создание пациента и результатов
    cout << "\n--- 3. Обслуживание пациента ---\n";
    Patient patient1("Иванов Иван Иванович");

    //Пациент сдает кровь (результат 5.2 - норма)
    TestResult res1(bloodTest, "10.09.2023", 5.2);
    //Пациент сдает сахар (результат 6.1 - выше нормы)
    TestResult res2(sugarTest, "10.09.2023", 6.1);

    cout << "Добавляем результаты пациенту...\n";
    patient1.addTestResult(res1);
    patient1.addTestResult(res2);

    // 4.Проверка бизнес-ограничения (Пытаемся сдать кровь второй раз в тот же день)
    cout << "\n--- 4. Проверка ограничения (защита от дубликатов) ---\n";
    TestResult duplicateRes(bloodTest, "10.09.2023", 7.0);
    patient1.addTestResult(duplicateRes); //Тут должна выскочить красная ошибка

    //Но на следующий день сдавать можно
    cout << "\nПациент сдает кровь на следующий день...\n";
    TestResult res3(bloodTest, "11.09.2023", 4.1);
    patient1.addTestResult(res3);

    // 5.Вывод полной информации (медицинской карты)
    cout << "\n--- 5. Итоговая выписка ---\n";
    patient1.printMedicalRecord();

    cout << "\nПрограмма успешно завершена.\n";
    return 0;
}