#pragma once
#include <string>
#include "Collection.h"
#include "Patient.h"
#include "Types.h"

class ReportWriter {
public:
    static std::string build(const AnalysisMap& catalog, const Collection<Patient>& patients);
    static void write(const std::string& path, const AnalysisMap& catalog, const Collection<Patient>& patients);
};
