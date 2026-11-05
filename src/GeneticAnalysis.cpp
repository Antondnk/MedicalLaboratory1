#include "GeneticAnalysis.h"
#include "Validation.h"
#include "exceptions/Exceptions.h"
#define COEFF 3

GeneticAnalysis::GeneticAnalysis()
    : Analysis(), targetGene(""), techMultiplier(1.0) {
}

GeneticAnalysis::GeneticAnalysis(const string& name, const string& category, double baseCost,
    double minNormal, double maxNormal, const string& gene, double multiplier)
    : Analysis(name, category, baseCost, minNormal, maxNormal),
    targetGene(gene), techMultiplier(multiplier) {
    if (is_blank(gene)) {
        throw InvalidDataException("Ген-маркер не может быть пустым.");
    }
    if (!(multiplier > 0)) {
        throw InvalidDataException("Коэффициент сложности должен быть больше нуля.");
    }
}

string GeneticAnalysis::get_type() const {
    return "Генетический/ПЦР анализ";
}

double GeneticAnalysis::calculate_total_cost() const {
    return baseCost * techMultiplier;
}

void GeneticAnalysis::print_info(ostream& os) const {
    Analysis::print_info(os);
    os << " \n\t Ген-маркер: " << targetGene
        << " \n\t Коэфф. сложности: x" << techMultiplier
        << " \n\t Срок выполнения: ~" << estimate_processing_days() << " дн.";
}

string GeneticAnalysis::get_target_gene() const { return targetGene; }
double GeneticAnalysis::get_tech_multiplier() const { return techMultiplier; }

int GeneticAnalysis::estimate_processing_days() const {
    return static_cast<int>(techMultiplier * COEFF);
}
