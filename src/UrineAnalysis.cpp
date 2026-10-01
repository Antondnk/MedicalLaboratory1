#include "UrineAnalysis.h"

UrineAnalysis::UrineAnalysis()
    : UrineAnalysis("", "", 0.0, 0.0, 0.0, false, 0.0) {
}

UrineAnalysis::UrineAnalysis(const string& name, const string& category, double baseCost,
    double minNormal, double maxNormal, bool sterile, double containerCost)
    : Analysis(name, category, baseCost, minNormal, maxNormal),
    isSterileContainer(sterile), containerCost(containerCost) {
}

string UrineAnalysis::get_type() const {
    return "Анализ мочи";
}

double UrineAnalysis::calculate_total_cost() const {
    return isSterileContainer ? (baseCost + containerCost) : baseCost;
}

void UrineAnalysis::print_info(ostream& os) const {
    Analysis::print_info(os); // Вызов базовой печати
    os << " \n\t Стерильный контейнер: " << (isSterileContainer ? "Да" : "Нет");
    if (isSterileContainer) {
        os << " (+" << containerCost << " руб.)";
    }
}

bool UrineAnalysis::get_is_sterile_container() const { return isSterileContainer; }
double UrineAnalysis::get_container_cost() const { return containerCost; }