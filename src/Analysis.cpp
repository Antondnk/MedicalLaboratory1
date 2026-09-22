#include "Analysis.h"

using namespace std;

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

void Analysis::print_info() const {
    cout << "Анализ: " << name << " | Категория: " << category
        << " | Стоимость: " << cost << " руб."
        << " | Норма: [" << minNormal << " - " << maxNormal << "]" << endl;
}