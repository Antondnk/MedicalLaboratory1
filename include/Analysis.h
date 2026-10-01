#pragma once
#include <string>
#include <iostream>

using namespace std;

class Analysis {
protected:
    string name;
    string category;
    double baseCost;
    double minNormal;
    double maxNormal;

public:
    Analysis();
    Analysis(const string& name, const string& category, double baseCost, double minNormal, double maxNormal);

    // Виртуальный деструктор (защита от утечек памяти при полиморфизме)
    virtual ~Analysis() = default;

    // Гетеры и сеттеры
    string get_name() const;
    string get_category() const;
    double get_base_cost() const;
    double get_min_normal() const;
    double get_max_normal() const;
    void set_base_cost(double newCost);

    // ЧИСТО ВИРТУАЛЬНЫЕ МЕТОДЫ (делают класс абстрактным)
    virtual string get_type() const = 0;
    virtual double calculate_total_cost() const = 0;

    // Виртуальный метод вывода информации
    virtual void print_info(ostream& os) const;

    // Перегрузка операторов сравнения по ИТОГОВОЙ стоимости
    bool operator>(const Analysis& other) const;
    bool operator<(const Analysis& other) const;

    // Дружественный оператор вывода
    friend ostream& operator<<(ostream& os, const Analysis& obj);

    friend istream& operator>>(istream& is, Analysis& obj);
};