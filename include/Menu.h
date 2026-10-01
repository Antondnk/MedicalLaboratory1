#pragma once
#include <vector>
#include "Analysis.h"
#include "BloodAnalysis.h"
#include "UrineAnalysis.h"
#include "GeneticAnalysis.h"
#include "Patient.h"
#include "TestResult.h"

using namespace std;

class Menu {
private:
    vector<Analysis*> availableAnalyses; // Полиморфный вектор указателей
    vector<Patient> patients;

    void clear_memory();
    void display_analyses() const;
    void add_analysis();
    void delete_analysis();                  // Удаление вида анализа (Очистка динамической памяти)
    void add_patient();
    void delete_patient();                    // Удаление пациента
    void add_test_result_to_patient();        // Добавление результата (Оператор +=)
    void remove_test_result_from_patient(); // Удаление результата (Оператор -=)
    void display_patients() const;

public:
    Menu();
    ~Menu(); // Деструктор для очистки памяти

    void run();
};