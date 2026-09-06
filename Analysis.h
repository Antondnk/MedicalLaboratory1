#include <string>
#include <iostream>

class Analysis {
    // private - это Инкапсуляция. Эти переменные нельзя изменить напрямую из main, только через методы.
private:
    std::string name;       // Название анализа
    std::string category;   // Категория (например, "Гематология")
    double cost;            // Стоимость
    double minNormal;       // Минимальная граница нормы
    double maxNormal;       // Максимальная граница нормы

    // public - это то, что доступно "снаружи" класса (другим частям программы)
public:
    // Конструктор - вызывается при создании объекта
    Analysis(const std::string& name, const std::string& category, double cost, double minNormal, double maxNormal);

    // Геттеры - методы для получения значений (Они const, так как не меняют сам объект)
    std::string getName() const;
    std::string getCategory() const;
    double getCost() const;
    double getMinNormal() const;
    double getMaxNormal() const;

    // Сеттер - метод для изменения значения (по заданию нам нужно уметь менять характеристики)
    void setCost(double newCost);

    // Метод для вывода информации в консоль
    void printInfo() const;
};