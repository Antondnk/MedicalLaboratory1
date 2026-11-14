#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Analysis.h"
#include "Collection.h"
#include "Patient.h"

struct LoadedState {
    std::vector<std::unique_ptr<Analysis>> analyses;
    std::vector<Patient> patients;
};

class FileStorage {
public:
    static bool exists(const std::string& path);
    static void write_atomic(const std::string& path, const std::string& content);

    static void save(const std::string& path,
        const Collection<Analysis*>& analyses,
        const Collection<Patient>& patients);

    static LoadedState load(const std::string& path);
};
