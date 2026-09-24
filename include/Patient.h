#pragma once
#include <string>
#include <vector>      
#include <iostream>
#include "TestResult.h" 

using namespace std;

class Patient
{
private:
    string fullName;
    vector<TestResult> results;

public:
    Patient(const string& fullName);

    Patient& operator+=(const TestResult& result);

    Patient& operator-=(const TestResult& result);

    friend ostream& operator<<(ostream& os, const Patient& obj);
};