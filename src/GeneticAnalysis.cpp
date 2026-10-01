#include "GeneticAnalysis.h"

GeneticAnalysis::GeneticAnalysis()
    : GeneticAnalysis("", "", 0.0, 0.0, 0.0, "", 1.0) {
}

GeneticAnalysis::GeneticAnalysis(const string& name, const string& category, double baseCost,
    double minNormal, double maxNormal, const string& gene, double multiplier)
    : Analysis(name, category, baseCost, minNormal, maxNormal),
    targetGene(gene), techMultiplier(multiplier) {
}

string GeneticAnalysis::get_type() const {
    return "Генетический/ПЦР анализ";
}

double GeneticAnalysis::calculate_total_cost() const {
    return baseCost * techMultiplier; // Расчет с коэффициентом сложности
}

void GeneticAnalysis::print_info(ostream& os) const {
    Analysis::print_info(os); // Вызов базовой печати
    os << " \n\t Ген-маркер: " << targetGene
        << " \n\t Коэфф. сложности: x" << techMultiplier;
}

string GeneticAnalysis::get_target_gene() const { return targetGene; }
double GeneticAnalysis::get_tech_multiplier() const { return techMultiplier; }