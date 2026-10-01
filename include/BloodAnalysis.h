#pragma once
#include "Analysis.h"

class BloodAnalysis : public Analysis {
private:
    bool requiresFasting; // Требуется ли сдавать натощак
    double reagentCost;   // Стоимость спец. реагентов

public:
    BloodAnalysis();
    BloodAnalysis(const string& name, const string& category, double baseCost,
        double minNormal, double maxNormal, bool fasting, double reagentCost);

    // Переопределение чисто виртуальных методов базового класса
    string get_type() const override;
    double calculate_total_cost() const override;

    // Переопределение метода вывода
    void print_info(ostream& os) const override;

    // Гетеры
    bool get_requires_fasting() const;
    double get_reagent_cost() const;
};