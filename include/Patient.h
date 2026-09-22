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

    bool add_test_result(const TestResult& result);

    void print_medical_record() const;
};