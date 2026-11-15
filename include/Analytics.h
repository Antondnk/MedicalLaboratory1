#pragma once
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include "Collection.h"
#include "Patient.h"
#include "Types.h"

struct SearchCriteria {
    std::string type;
    std::string category;
    double minPrice;
    double maxPrice;

    SearchCriteria() : minPrice(0.0), maxPrice(-1.0) {}
};

enum class SortKey { Name, Price };

class Analytics {
public:
    using AnalysisList = std::vector<const Analysis*>;

    static AnalysisList list_all(const AnalysisMap& catalog);
    static AnalysisList find_by_criteria(const AnalysisMap& catalog, const SearchCriteria& criteria);
    static AnalysisList find_by_max_base_cost(const AnalysisMap& catalog, double maxCost);
    static const Analysis* find_by_name(const AnalysisMap& catalog, const std::string& name);

    static void sort_analyses(AnalysisList& list, SortKey key, bool ascending);
    static const Analysis* cheapest(const AnalysisList& list);
    static const Analysis* most_expensive(const AnalysisList& list);

    static std::map<std::string, AnalysisList> group_by_type(const AnalysisMap& catalog);
    static std::set<std::string> categories(const AnalysisMap& catalog);

    static double average_cost(const AnalysisMap& catalog);
    static int count_more_expensive_than(const AnalysisMap& catalog, double limit);

    static int count_all_results(const Collection<Patient>& patients);
    static int count_critical_results(const Collection<Patient>& patients);
    static double results_cost_sum(const Collection<Patient>& patients);
    static std::unordered_map<std::string, int> count_results_by_status(const Collection<Patient>& patients);
    static const Patient* most_active_patient(const Collection<Patient>& patients);

    static std::vector<TestResult> sorted_results(const Patient& patient, bool newestFirst);

    static std::string statistics_text(const AnalysisMap& catalog, const Collection<Patient>& patients);
};
