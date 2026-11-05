#include "BloodAnalysis.h"
#include "exceptions/Exceptions.h"
#define NUM  2
#define MORE 15
#define LESS 5

// Конструктор по умолчанию не валидирует: пустой объект-заготовка допустим.
BloodAnalysis::BloodAnalysis()
    : Analysis(), requiresFasting(false), reagentCost(0.0) {
}

BloodAnalysis::BloodAnalysis(const string& name, const string& category, double baseCost,
    double minNormal, double maxNormal, bool fasting, double reagentCost)
    : Analysis(name, category, baseCost, minNormal, maxNormal),
    requiresFasting(fasting), reagentCost(reagentCost) {
    if (!(reagentCost >= 0)) {
        throw InvalidDataException("Стоимость реагентов не может быть отрицательной.");
    }
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
        << " \n\t Срочное выполнение (CITO): " << calculate_express_cost() << " руб.";
}

bool BloodAnalysis::get_requires_fasting() const { return requiresFasting; }
double BloodAnalysis::get_reagent_cost() const { return reagentCost; }

double BloodAnalysis::calculate_express_cost() const {
    double expressReagent = reagentCost * NUM;
    double expressSurcharge = requiresFasting ? MORE : LESS;
    return baseCost + expressReagent + expressSurcharge;
}
