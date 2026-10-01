#pragma once
#include "Analysis.h"

class UrineAnalysis : public Analysis {
private:
    bool isSterileContainer; // Требуется ли стерильный контейнер
    double containerCost;    // Стоимость контейнера

public:
    UrineAnalysis();
    UrineAnalysis(const string& name, const string& category, double baseCost,
        double minNormal, double maxNormal, bool sterile, double containerCost);

    // Переопределение чисто виртуальных методов базового класса
    string get_type() const override;
    double calculate_total_cost() const override;

    // Переопределение метода вывода
    void print_info(ostream& os) const override;

    // Гетеры
    bool get_is_sterile_container() const;
    double get_container_cost() const;
};