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
    void add_patient();
    void add_test_result_to_patient();
    void display_patients() const;

public:
    Menu();
    ~Menu(); // Деструктор очищает динамическую память

    void run();
};