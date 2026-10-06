#pragma once
#include "Analysis.h"

class UrineAnalysis : public Analysis {
private:
    bool isSterileContainer;
    double containerCost;

public:
    UrineAnalysis();
    UrineAnalysis(const string& name, const string& category, double baseCost,
        double minNormal, double maxNormal, bool sterile, double containerCost);

    string get_type() const override;
    double calculate_total_cost() const override;

    void print_info(ostream& os) const override;

    bool get_is_sterile_container() const;
    double get_container_cost() const;
};