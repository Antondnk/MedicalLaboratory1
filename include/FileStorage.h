#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Analysis.h"
#include "Collection.h"
#include "Patient.h"
#include "Types.h"
#include <utility>

struct LoadedState {
    AnalysisMap analyses;
    std::vector<Patient> patients;

    LoadedState() = default;

    LoadedState(LoadedState&& other) noexcept
        : analyses(std::move(other.analyses)), patients(std::move(other.patients)) {
    }

    LoadedState& operator=(LoadedState&& other) noexcept {
        analyses = std::move(other.analyses);
        patients = std::move(other.patients);
        return *this;
    }
};

class FileStorage {
public:
    static bool exists(const std::string& path);
    static void write_atomic(const std::string& path, const std::string& content);

    static void save(const std::string& path,
        const AnalysisMap& analyses,
        const Collection<Patient>& patients);

    static LoadedState load(const std::string& path);
};
