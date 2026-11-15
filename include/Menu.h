#pragma once
#include "Analytics.h"
#include "Collection.h"
#include "FileStorage.h"
#include "Patient.h"
#include "Analysis.h"
#include "BloodAnalysis.h"
#include "UrineAnalysis.h"
#include "GeneticAnalysis.h"
#include "Types.h"
#include <memory>
#include <string>

class Menu {
private:
    AnalysisMap catalog;
    Collection<Patient> patients;
    int nextAnalysisId;
    int nextPatientId;
    bool autosaveAllowed;

    void add_default_data();
    int register_analysis(std::unique_ptr<Analysis> analysis);
    int register_patient(Patient patient);
    bool analysis_name_exists(const std::string& name) const;
    Analysis* require_analysis(int id) const;
    void apply_state(LoadedState&& state);
    void journal(const std::string& message) const;
    void save_on_exit();

    void display_analyses() const;
    void print_analysis_list(const Analytics::AnalysisList& list) const;
    int select_patient() const;

    int read_int(const std::string& prompt) const;
    double read_double(const std::string& prompt) const;
    bool read_yes_no(const std::string& prompt) const;
    std::string read_line(const std::string& prompt) const;
    std::string read_path(const std::string& prompt, const std::string& defaultPath) const;

    static void check_analysis_not_used(const Analysis* analysis, const Collection<Patient>& patientList);

public:
    Menu();

    void load_on_startup();
    void save_state();
    void load_state();
    void show_journal() const;
    void write_report();

    void print_menu() const;
    bool process_command();

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

    void search_analyses_by_price() const;
    void search_specific_analysis() const;

    void search_analyses_by_criteria() const;
    void sort_analyses_menu() const;
    void group_analyses() const;
    void show_statistics() const;
    void show_patient_results_sorted() const;
};
