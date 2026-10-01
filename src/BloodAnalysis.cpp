#include "BloodAnalysis.h"

BloodAnalysis::BloodAnalysis()
    : BloodAnalysis("", "", 0.0, 0.0, 0.0, false, 0.0) {
}

BloodAnalysis::BloodAnalysis(const string& name, const string& category, double baseCost,
    double minNormal, double maxNormal, bool fasting, double reagentCost)
    : Analysis(name, category, baseCost, minNormal, maxNormal),
    requiresFasting(fasting), reagentCost(reagentCost) {
}

string BloodAnalysis::get_type() const {
    return "Анализ крови";
}

double BloodAnalysis::calculate_total_cost() const {
    return baseCost + reagentCost; // Реализация специфического расчета
}

void BloodAnalysis::print_info(ostream& os) const {
    Analysis::print_info(os); // Вызов базовой печати
    os << " \n\t Натощак: " << (requiresFasting ? "Да" : "Нет")
        << " \n\t Реагенты: " << reagentCost << " руб.";
}

bool BloodAnalysis::get_requires_fasting() const { return requiresFasting; }
double BloodAnalysis::get_reagent_cost() const { return reagentCost; }