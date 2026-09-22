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

    string get_name() const;
    string get_category() const;
    double get_cost() const;
    double get_min_normal() const;
    double get_max_normal() const;

    void set_cost(double newCost);

    void print_info() const;
};