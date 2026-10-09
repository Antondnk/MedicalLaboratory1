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
    return baseCost + reagentCost;
}

void BloodAnalysis::print_info(ostream& os) const {
    Analysis::print_info(os);
    os << " \n\t Натощак: " << (requiresFasting ? "Да" : "Нет")
        << " \n\t Реагенты: " << reagentCost << " руб."
        << " \n\t Требуемое голодание: " << (requiresFasting ? "мин. 8 часов" : "не требуется");
}

bool BloodAnalysis::get_requires_fasting() const { return requiresFasting; }
double BloodAnalysis::get_reagent_cost() const { return reagentCost; }

bool BloodAnalysis::verify_fasting_compliance(int hoursFasted) const {
    if (!requiresFasting) {
        return true;
    }
    return hoursFasted >= 8; 
}