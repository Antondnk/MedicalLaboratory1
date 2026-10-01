#include "Analysis.h"

using namespace std;

Analysis::Analysis()
    : name(""), category(""), baseCost(0.0), minNormal(0.0), maxNormal(0.0) {
}

Analysis::Analysis(const string& name, const string& category, double baseCost, double minNormal, double maxNormal)
    : name(name), category(category), baseCost(baseCost), minNormal(minNormal), maxNormal(maxNormal) {
}

string Analysis::get_name() const { return name; }
string Analysis::get_category() const { return category; }
double Analysis::get_base_cost() const { return baseCost; }
double Analysis::get_min_normal() const { return minNormal; }
double Analysis::get_max_normal() const { return maxNormal; }

void Analysis::set_base_cost(double newCost) {
    if (newCost >= 0) {
        baseCost = newCost;
    }
}

void Analysis::print_info(ostream& os) const {
    os << "[" << get_type() << "] " << name
        << " | Категория: " << category
        << " | Итоговая стоимость: " << calculate_total_cost() << " руб."
        << " (Базовая: " << baseCost << " руб.)"
        << " | Норма: [" << minNormal << " - " << maxNormal << "]";
}

bool Analysis::operator>(const Analysis& other) const {
    return this->calculate_total_cost() > other.calculate_total_cost();
}

bool Analysis::operator<(const Analysis& other) const {
    return this->calculate_total_cost() < other.calculate_total_cost();
}

ostream& operator<<(ostream& os, const Analysis& obj) {
    obj.print_info(os); // Полиморфный вызов через ссылку
    return os;
}