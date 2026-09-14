#include "Analysis.h"

using namespace std;

//Реализация конструктора
Analysis::Analysis(const string& name, const string& category, double cost, double minNormal, double maxNormal)
    : name(name), category(category), cost(cost), minNormal(minNormal), maxNormal(maxNormal) {
}

//Реализация геттеров
string Analysis::getName() const { return name; }
string Analysis::getCategory() const { return category; }
double Analysis::getCost() const { return cost; }
double Analysis::getMinNormal() const { return minNormal; }
double Analysis::getMaxNormal() const { return maxNormal; }

//Реализация сеттера (например, цена на анализ изменилась)
void Analysis::setCost(double newCost) {
    if (newCost >= 0) { //Небольшая проверка, чтобы цена не стала отрицательной
        cost = newCost;
    }
}

//Реализация вывода информации
void Analysis::printInfo() const {
    cout << "Анализ: " << name << " | Категория: " << category
        << " | Стоимость: " << cost << " руб."
        << " | Норма: [" << minNormal << " - " << maxNormal << "]" << endl;
}