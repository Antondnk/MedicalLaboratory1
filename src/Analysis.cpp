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
        << " \n\t Категория: " << category
        << " \n\t Итоговая стоимость: " << calculate_total_cost() << " руб."
        << " (Базовая: " << baseCost << " руб.)"
        << " \n\t Норма: [" << minNormal << " - " << maxNormal << "]";
}

bool Analysis::operator>(const Analysis& other) const {
    return this->calculate_total_cost() > other.calculate_total_cost();
}

bool Analysis::operator<(const Analysis& other) const {
    return this->calculate_total_cost() < other.calculate_total_cost();
}

ostream& operator<<(ostream& os, const Analysis& obj) {
    obj.print_info(os);
    return os;
}

istream& operator>>(istream& is, Analysis& obj) {
    cout << "Введите название анализа: ";
    getline(is, obj.name);
    cout << "Введите категорию: ";
    getline(is, obj.category);
    cout << "Введите базовую стоимость: ";
    is >> obj.baseCost;
    cout << "Введите нижнюю границу нормы: ";
    is >> obj.minNormal;
    cout << "Введите верхнюю границу нормы: ";
    is >> obj.maxNormal;
    is.ignore(10000, '\n');
    return is;
}