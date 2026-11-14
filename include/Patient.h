#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "TestResult.h"

using namespace std;

class Patient {
private:
    int id;
    string fullName;
    vector<TestResult> results;

public:
    Patient();
    explicit Patient(const string& fullName);

    int get_id() const;
    void set_id(int newId);
    string get_full_name() const;
    const vector<TestResult>& get_results() const;

    bool has_result(const TestResult& result) const;

    Patient& operator+=(const TestResult& result);
    Patient& operator-=(const TestResult& result);

    friend ostream& operator<<(ostream& os, const Patient& obj);
};