#pragma once
#include <vector>
#include <string>
#include "Analysis.h"
#include "BloodAnalysis.h"
#include "UrineAnalysis.h"
#include "GeneticAnalysis.h"
#include "Patient.h"
#include "TestResult.h"

using namespace std;

class Menu {
private:
    vector<Analysis*> availableAnalyses;
    vector<Patient> patients;

    int read_int(const string& prompt, int minVal, int maxVal) const;
    double read_double(const string& prompt, double minVal = 0.0) const;
    string read_date(const string& prompt) const;
    bool is_valid_date(const string& date) const;

    void clear_memory();
    void display_analyses() const;
    void change_analysis_cost();
    void take_test();
    void display_patient_card() const;
    void add_analysis();
    void remove_analysis();
    void remove_test_result();
    void compare_analyses() const;
    void add_patient();
    int select_patient() const;
public:
    Menu();
    ~Menu();

    void run();
};