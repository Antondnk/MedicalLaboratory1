#include "Analysis.h"
#include "Validation.h"
#include "exceptions/Exceptions.h"

using namespace std;

void Analysis::validate_fields(const string& name, double baseCost, double minNormal, double maxNormal) {
    if (is_blank(name)) {
        throw InvalidDataException("Название анализа не может быть пустым.");
    }
    if (!(baseCost >= 0)) {
        throw InvalidDataException("Базовая стоимость не может быть отрицательной.");
    }
    if (!(minNormal >= 0)) {
        throw InvalidDataException("Нижняя граница нормы не может быть отрицательной.");
    }
    if (!(maxNormal >= minNormal)) {
        throw InvalidDataException("Верхняя граница нормы не может быть меньше нижней.");
    }
}

Analysis::Analysis()
    : name(""), category(""), baseCost(0.0), minNormal(0.0), maxNormal(0.0) {
}

Analysis::Analysis(const string& name, const string& category, double baseCost, double minNormal, double maxNormal) {
    validate_fields(name, baseCost, minNormal, maxNormal);
    this->name = name;
    this->category = category;
    this->baseCost = baseCost;
    this->minNormal = minNormal;
    this->maxNormal = maxNormal;
}

string Analysis::get_name() const { return name; }
string Analysis::get_category() const { return category; }
double Analysis::get_base_cost() const { return baseCost; }
double Analysis::get_min_normal() const { return minNormal; }
double Analysis::get_max_normal() const { return maxNormal; }

void Analysis::set_base_cost(double newCost) {
    if (!(newCost >= 0)) {
        throw InvalidDataException("Стоимость анализа не может быть отрицательной.");
    }
    baseCost = newCost;
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
    string name, category;
    double baseCost = 0, minNormal = 0, maxNormal = 0;

    cout << "Введите название анализа: ";
    getline(is, name);
    cout << "Введите категорию: ";
    getline(is, category);
    cout << "Введите базовую стоимость: ";
    is >> baseCost;
    cout << "Введите нижнюю границу нормы: ";
    is >> minNormal;
    cout << "Введите верхнюю границу нормы: ";
    is >> maxNormal;

    if (!is) {
        is.clear();
        is.ignore(10000, '\n');
        throw InvalidDataException("Не удалось прочитать анализ: ожидалось число.");
    }
    is.ignore(10000, '\n');

    Analysis::validate_fields(name, baseCost, minNormal, maxNormal);
    obj.name = name;
    obj.category = category;
    obj.baseCost = baseCost;
    obj.minNormal = minNormal;
    obj.maxNormal = maxNormal;
    return is;
}
