#include "ReportWriter.h"
#include "Analytics.h"
#include "FileStorage.h"
#include "Logger.h"
#include <algorithm>
#include <iomanip>
#include <locale>
#include <sstream>

namespace {

const std::string LINE(60, '-');
const std::string DOUBLE_LINE(60, '=');

std::string money(double value) {
    std::ostringstream os;
    os << std::fixed << std::setprecision(2) << value;
    return os.str();
}

}

std::string ReportWriter::build(const AnalysisMap& catalog, const Collection<Patient>& patients) {
    std::ostringstream out;
    out.imbue(std::locale::classic());

    out << "ОТЧЁТ ЛАБОРАТОРНОЙ СИСТЕМЫ\n";
    out << "Сформирован: " << Logger::timestamp() << "\n";
    out << DOUBLE_LINE << "\n\n";

    out << "КАТАЛОГ АНАЛИЗОВ (" << catalog.size() << ")\n" << LINE << "\n";
    if (catalog.empty()) {
        out << "Каталог пуст.\n";
    }
    std::for_each(catalog.begin(), catalog.end(), [&out](const AnalysisMap::value_type& entry) {
        const Analysis& a = *entry.second;
        out << "#" << a.get_id() << " [" << a.get_type() << "] " << a.get_name()
            << " | категория: " << a.get_category()
            << " | итоговая стоимость: " << money(a.calculate_total_cost()) << " руб."
            << " | норма: " << money(a.get_min_normal()) << " - " << money(a.get_max_normal()) << "\n";
        });

    out << "\nАНАЛИЗЫ ПО ТИПАМ\n" << LINE << "\n";
    const auto groups = Analytics::group_by_type(catalog);
    for (const auto& group : groups) {
        out << group.first << ": " << group.second.size() << "\n";
    }

    out << "\nПАЦИЕНТЫ (" << patients.size() << ")\n" << LINE << "\n";
    if (patients.empty()) {
        out << "Пациентов нет.\n";
    }
    std::for_each(patients.begin(), patients.end(), [&out](const Patient& patient) {
        out << "#" << patient.get_id() << " " << patient.get_full_name()
            << " (результатов: " << patient.get_results().size() << ")\n";

        const auto results = Analytics::sorted_results(patient, false);
        int number = 1;
        std::for_each(results.begin(), results.end(), [&out, &number](const TestResult& result) {
            out << "    " << number++ << ") " << result.get_date()
                << " | " << result.get_analysis()->get_name()
                << " | результат: " << money(result.get_value())
                << " | статус: " << result.get_status()
                << (is_critical(result) ? " | КРИТИЧЕСКИЙ" : "") << "\n";
            });
        });

    out << "\nИТОГИ\n" << LINE << "\n";
    out << Analytics::statistics_text(catalog, patients);
    return out.str();
}

void ReportWriter::write(const std::string& path, const AnalysisMap& catalog, const Collection<Patient>& patients) {
    FileStorage::write_atomic(path, build(catalog, patients));
}
