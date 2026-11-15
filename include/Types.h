#pragma once
#include <map>
#include <memory>
#include "Analysis.h"

using AnalysisMap = std::map<int, std::unique_ptr<Analysis>>;
