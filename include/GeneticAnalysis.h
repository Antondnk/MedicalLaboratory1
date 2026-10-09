#pragma once
#include "Analysis.h"

class GeneticAnalysis : public Analysis {
private:
    string targetGene;
    double techMultiplier;

public:
    GeneticAnalysis();
    GeneticAnalysis(const string& name, const string& category, double baseCost,
        double minNormal, double maxNormal, const string& gene, double multiplier);

    string get_type() const override;
    double calculate_total_cost() const override;

    void print_info(ostream& os) const override;

    string get_target_gene() const;
    double get_tech_multiplier() const;

    int estimate_processing_days() const;
};