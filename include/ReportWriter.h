#pragma once
#include <string>
#include "Analysis.h"
#include "Collection.h"
#include "Patient.h"

class ReportWriter {
public:
    static std::string build(const Collection<Analysis*>& analyses, const Collection<Patient>& patients);
    static void write(const std::string& path, const Collection<Analysis*>& analyses, const Collection<Patient>& patients);
};
