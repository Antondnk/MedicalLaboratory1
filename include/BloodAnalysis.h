#pragma once
#include "Analysis.h"

class BloodAnalysis : public Analysis {
private:
    bool requiresFasting;
    double reagentCost;

public:
    BloodAnalysis();
    BloodAnalysis(const string& name, const string& category, double baseCost,
        double minNormal, double maxNormal, bool fasting, double reagentCost);

    string get_type() const override;
    double calculate_total_cost() const override;

    void print_info(ostream& os) const override;

    bool get_requires_fasting() const;
    double get_reagent_cost() const;

    double calculate_express_cost() const;
};