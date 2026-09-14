#pragma once
#include <string>
#include <vector>      
#include "TestResult.h" 

using namespace std;

class Patient 
{
private:
    string fullName;            
    vector<TestResult> results;

public:
    
    Patient(const string& fullName);

    bool addTestResult(const TestResult& result);

    void printMedicalRecord() const;
};