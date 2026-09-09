#pragma once
#include <string>
#include <iostream>

using namespace std;

class Analysis {

private:
    string name;       //Название анализа
    string category;   //Категория (например, "Гематология")
    double cost;            //Стоимость
    double minNormal;       //Минимальная граница нормы
    double maxNormal;       //Максимальная граница нормы

public:
    //Конструктор - вызывается при создании объекта
    Analysis(const string& name, const string& category, double cost, double minNormal, double maxNormal);

    //Геттеры - методы для получения значений (Они const, так как не меняют сам объект)
    string getName() const;
    string getCategory() const;
    double getCost() const;
    double getMinNormal() const;
    double getMaxNormal() const;

    //Сеттер - метод для изменения значения
    void setCost(double newCost);

    //Метод для вывода информации в консоль
    void printInfo() const;
};