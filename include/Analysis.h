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
    Analysis(const string& name, const string& category, double cost, double minNormal, double maxNormal);

    string getName() const;
    string getCategory() const;
    double getCost() const;
    double getMinNormal() const;
    double getMaxNormal() const;

    void setCost(double newCost);

    void printInfo() const;
};