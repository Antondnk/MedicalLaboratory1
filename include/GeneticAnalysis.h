#pragma once
#include "Analysis.h"

class GeneticAnalysis : public Analysis {
private:
    string targetGene;      // Исследуемый ген/маркер (например, BRCA1, COVID-19)
    double techMultiplier;  // Коэффициент сложности оборудования (например, 1.5)

public:
    GeneticAnalysis();
    GeneticAnalysis(const string& name, const string& category, double baseCost,
        double minNormal, double maxNormal, const string& gene, double multiplier);

    // Переопределение чисто виртуальных методов
    string get_type() const override;
    double calculate_total_cost() const override;

    // Переопределение метода вывода
    void print_info(ostream& os) const override;

    // Гетеры
    string get_target_gene() const;
    double get_tech_multiplier() const;
};