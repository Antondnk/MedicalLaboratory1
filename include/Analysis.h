#pragma once
#include <string>
#include <iostream>

using namespace std;

class Analysis {

private:
    string name;
    string category;
    double cost;
    double minNormal;
    double maxNormal;

public:
    // 1. Добавляем пустой конструктор (нужен для ввода через cin >>)
    Analysis();
    Analysis(const string& name, const string& category, double cost, double minNormal, double maxNormal);

    string get_name() const;
    string get_category() const;
    double get_cost() const;
    double get_min_normal() const;
    double get_max_normal() const;

    void set_cost(double newCost);

    // 2. Перегрузка операторов отношения (сравнение по стоимости)
    bool operator>(const Analysis& other) const;
    bool operator<(const Analysis& other) const;

    // 3. Дружественные функции для удобного вывода и ввода
    // Обрати внимание: мы удалили print_info(), теперь вместо нее будет оператор <<
    friend ostream& operator<<(ostream& os, const Analysis& obj);
    friend istream& operator>>(istream& is, Analysis& obj);
};