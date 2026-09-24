#include "Analysis.h"

using namespace std;

Analysis::Analysis() : name(""), category(""), cost(0.0), minNormal(0.0), maxNormal(0.0) {}

Analysis::Analysis(const string& name, const string& category, double cost, double minNormal, double maxNormal)
    : name(name), category(category), cost(cost), minNormal(minNormal), maxNormal(maxNormal) {
}

string Analysis::get_name() const { return name; }
string Analysis::get_category() const { return category; }
double Analysis::get_cost() const { return cost; }
double Analysis::get_min_normal() const { return minNormal; }
double Analysis::get_max_normal() const { return maxNormal; }

void Analysis::set_cost(double newCost) {
    if (newCost >= 0) {
        cost = newCost;
    }
}

bool Analysis::operator>(const Analysis& other) const {
    return this->cost > other.cost;
}

bool Analysis::operator<(const Analysis& other) const {
    return this->cost < other.cost;
}

ostream& operator<<(ostream& os, const Analysis& obj) {
    os << "Анализ: " << obj.name << " | Категория: " << obj.category
        << " | Стоимость: " << obj.cost << " руб."
        << " | Норма: [" << obj.minNormal << " - " << obj.maxNormal << "]";
    return os;
}

istream& operator>>(istream& is, Analysis& obj) {
    cout << "Введите название анализа: ";
    getline(is >> ws, obj.name);
    cout << "Введите категорию анализа: ";
    getline(is, obj.category);
    cout << "Введите стоимость: ";
    is >> obj.cost;
    cout << "Введите минимальную норму: ";
    is >> obj.minNormal;
    cout << "Введите максимальную норму: ";
    is >> obj.maxNormal;
    return is;
}