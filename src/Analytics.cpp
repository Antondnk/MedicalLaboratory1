#include "Analytics.h"
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <sstream>

namespace {

long date_key(const std::string& date) {
    return std::stol(date.substr(6, 4)) * 10000 + std::stol(date.substr(3, 2)) * 100 + std::stol(date.substr(0, 2));
}

double total_cost(const Analysis* a) {
    return a->calculate_total_cost();
}

}

Analytics::AnalysisList Analytics::list_all(const AnalysisMap& catalog) {
    AnalysisList result;
    result.reserve(catalog.size());
    std::transform(catalog.begin(), catalog.end(), std::back_inserter(result),
        [](const AnalysisMap::value_type& entry) { return entry.second.get(); });
    return result;
}

Analytics::AnalysisList Analytics::find_by_criteria(const AnalysisMap& catalog, const SearchCriteria& criteria) {
    const AnalysisList all = list_all(catalog);
    AnalysisList result;
    std::copy_if(all.begin(), all.end(), std::back_inserter(result), [&criteria](const Analysis* a) {
        if (!criteria.type.empty() && a->get_type() != criteria.type) {
            return false;
        }
        if (!criteria.category.empty() && a->get_category().find(criteria.category) == std::string::npos) {
            return false;
        }
        const double cost = a->calculate_total_cost();
        if (cost < criteria.minPrice) {
            return false;
        }
        if (criteria.maxPrice >= 0 && cost > criteria.maxPrice) {
            return false;
        }
        return true;
        });
    return result;
}

Analytics::AnalysisList Analytics::find_by_max_base_cost(const AnalysisMap& catalog, double maxCost) {
    const AnalysisList all = list_all(catalog);
    AnalysisList result;
    std::copy_if(all.begin(), all.end(), std::back_inserter(result),
        [maxCost](const Analysis* a) { return a->get_base_cost() <= maxCost; });
    return result;
}

const Analysis* Analytics::find_by_name(const AnalysisMap& catalog, const std::string& name) {
    auto it = std::find_if(catalog.begin(), catalog.end(),
        [&name](const AnalysisMap::value_type& entry) { return entry.second->get_name() == name; });
    return it == catalog.end() ? nullptr : it->second.get();
}

void Analytics::sort_analyses(AnalysisList& list, SortKey key, bool ascending) {
    auto before = [key](const Analysis* a, const Analysis* b) {
        if (key == SortKey::Price) {
            const double x = a->calculate_total_cost();
            const double y = b->calculate_total_cost();
            if (x != y) {
                return x < y;
            }
        }
        return a->get_name() < b->get_name();
    };
    std::sort(list.begin(), list.end(), [&before, ascending](const Analysis* a, const Analysis* b) {
        return ascending ? before(a, b) : before(b, a);
        });
}

const Analysis* Analytics::cheapest(const AnalysisList& list) {
    auto it = std::min_element(list.begin(), list.end(),
        [](const Analysis* a, const Analysis* b) { return total_cost(a) < total_cost(b); });
    return it == list.end() ? nullptr : *it;
}

const Analysis* Analytics::most_expensive(const AnalysisList& list) {
    auto it = std::max_element(list.begin(), list.end(),
        [](const Analysis* a, const Analysis* b) { return total_cost(a) < total_cost(b); });
    return it == list.end() ? nullptr : *it;
}

std::map<std::string, Analytics::AnalysisList> Analytics::group_by_type(const AnalysisMap& catalog) {
    std::map<std::string, AnalysisList> groups;
    std::for_each(catalog.begin(), catalog.end(), [&groups](const AnalysisMap::value_type& entry) {
        groups[entry.second->get_type()].push_back(entry.second.get());
        });
    return groups;
}

std::set<std::string> Analytics::categories(const AnalysisMap& catalog) {
    std::set<std::string> result;
    std::transform(catalog.begin(), catalog.end(), std::inserter(result, result.begin()),
        [](const AnalysisMap::value_type& entry) { return entry.second->get_category(); });
    return result;
}

double Analytics::average_cost(const AnalysisMap& catalog) {
    if (catalog.empty()) {
        return 0.0;
    }
    const double sum = std::accumulate(catalog.begin(), catalog.end(), 0.0,
        [](double acc, const AnalysisMap::value_type& entry) { return acc + entry.second->calculate_total_cost(); });
    return sum / static_cast<double>(catalog.size());
}

int Analytics::count_more_expensive_than(const AnalysisMap& catalog, double limit) {
    return static_cast<int>(std::count_if(catalog.begin(), catalog.end(),
        [limit](const AnalysisMap::value_type& entry) { return entry.second->calculate_total_cost() > limit; }));
}

int Analytics::count_all_results(const Collection<Patient>& patients) {
    return std::accumulate(patients.begin(), patients.end(), 0,
        [](int acc, const Patient& p) { return acc + static_cast<int>(p.get_results().size()); });
}

int Analytics::count_critical_results(const Collection<Patient>& patients) {
    return std::accumulate(patients.begin(), patients.end(), 0, [](int acc, const Patient& p) {
        const auto& results = p.get_results();
        return acc + static_cast<int>(std::count_if(results.begin(), results.end(),
            [](const TestResult& r) { return is_critical(r); }));
        });
}

double Analytics::results_cost_sum(const Collection<Patient>& patients) {
    return std::accumulate(patients.begin(), patients.end(), 0.0, [](double acc, const Patient& p) {
        const auto& results = p.get_results();
        return acc + std::accumulate(results.begin(), results.end(), 0.0,
            [](double inner, const TestResult& r) { return inner + r.get_analysis()->calculate_total_cost(); });
        });
}

std::unordered_map<std::string, int> Analytics::count_results_by_status(const Collection<Patient>& patients) {
    std::unordered_map<std::string, int> counts;
    std::for_each(patients.begin(), patients.end(), [&counts](const Patient& p) {
        const auto& results = p.get_results();
        std::for_each(results.begin(), results.end(), [&counts](const TestResult& r) { ++counts[r.get_status()]; });
        });
    return counts;
}

const Patient* Analytics::most_active_patient(const Collection<Patient>& patients) {
    auto it = std::max_element(patients.begin(), patients.end(), [](const Patient& a, const Patient& b) {
        return a.get_results().size() < b.get_results().size();
        });
    return it == patients.end() ? nullptr : &*it;
}

std::vector<TestResult> Analytics::sorted_results(const Patient& patient, bool newestFirst) {
    const auto& source = patient.get_results();
    std::vector<TestResult> copy;
    copy.reserve(source.size());
    std::copy(source.begin(), source.end(), std::back_inserter(copy));
    std::sort(copy.begin(), copy.end(), [newestFirst](const TestResult& a, const TestResult& b) {
        const long x = date_key(a.get_date());
        const long y = date_key(b.get_date());
        return newestFirst ? x > y : x < y;
        });
    return copy;
}

std::string Analytics::statistics_text(const AnalysisMap& catalog, const Collection<Patient>& patients) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(2);

    out << "Видов анализов в каталоге: " << catalog.size() << "\n";

    const std::set<std::string> cats = categories(catalog);
    out << "Категорий: " << cats.size();
    if (!cats.empty()) {
        out << " (";
        bool first = true;
        for (const auto& category : cats) {
            out << (first ? "" : ", ") << category;
            first = false;
        }
        out << ")";
    }
    out << "\n";

    const AnalysisList all = list_all(catalog);
    const Analysis* low = cheapest(all);
    const Analysis* high = most_expensive(all);
    if (low && high) {
        const double average = average_cost(catalog);
        out << "Самый дешёвый анализ: " << low->get_name() << " (" << low->calculate_total_cost() << " руб.)\n";
        out << "Самый дорогой анализ: " << high->get_name() << " (" << high->calculate_total_cost() << " руб.)\n";
        out << "Средняя итоговая стоимость: " << average << " руб.\n";
        out << "Анализов дороже средней стоимости: " << count_more_expensive_than(catalog, average) << "\n";
    }

    out << "Пациентов: " << patients.size() << "\n";
    out << "Результатов всего: " << count_all_results(patients) << "\n";

    auto byStatus = count_results_by_status(patients);
    out << "  в норме: " << byStatus["Норма"]
        << ", ниже нормы: " << byStatus["Ниже нормы"]
        << ", выше нормы: " << byStatus["Выше нормы"] << "\n";
    out << "Критических результатов: " << count_critical_results(patients) << "\n";

    const Patient* busiest = most_active_patient(patients);
    if (busiest && !busiest->get_results().empty()) {
        out << "Больше всего результатов у пациента: " << busiest->get_full_name()
            << " (" << busiest->get_results().size() << ")\n";
    }
    out << "Суммарная стоимость сданных анализов: " << results_cost_sum(patients) << " руб.\n";
    return out.str();
}
