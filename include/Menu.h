#pragma once
#include "Collection.h"
#include "Patient.h"
#include "Analysis.h"
#include "BloodAnalysis.h"
#include "UrineAnalysis.h"
#include "GeneticAnalysis.h"
#include <string>

class Menu {
private:
    Collection<Analysis*> availableAnalyses;
    Collection<Patient> patients;

    void clear_memory();
    void display_analyses() const;
    int select_patient() const;

    int read_int(const std::string& prompt, int minVal, int maxVal) const;
    double read_double(const std::string& prompt, double minVal) const;
    bool is_valid_date(const std::string& date) const;
    std::string read_date(const std::string& prompt) const;

public:
    Menu();
    ~Menu();

    void change_analysis_cost();
    void add_patient();
    void take_test();
    void display_patient_card() const;
    void add_analysis();
    void remove_analysis();
    void remove_test_result();
    void compare_analyses() const;

    void demo_lab5_templates();
    void demo_lab6_exceptions();

    void run();

    void search_analyses_by_criteria() const;

    void search_specific_analysis() const;
};