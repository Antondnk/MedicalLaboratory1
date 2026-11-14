#include "ReportWriter.h"
#include "FileStorage.h"
#include "Logger.h"
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

std::string ReportWriter::build(const Collection<Analysis*>& analyses, const Collection<Patient>& patients) {
    std::ostringstream out;
    out.imbue(std::locale::classic());

    out << "ОТЧЁТ ЛАБОРАТОРНОЙ СИСТЕМЫ\n";
    out << "Сформирован: " << Logger::timestamp() << "\n";
    out << DOUBLE_LINE << "\n\n";

    out << "КАТАЛОГ АНАЛИЗОВ (" << analyses.size() << ")\n" << LINE << "\n";
    if (analyses.empty()) {
        out << "Каталог пуст.\n";
    }
    for (int i = 0; i < analyses.size(); ++i) {
        const Analysis& a = *analyses.get(i);
        out << "#" << a.get_id() << " [" << a.get_type() << "] " << a.get_name()
            << " | категория: " << a.get_category()
            << " | итоговая стоимость: " << money(a.calculate_total_cost()) << " руб."
            << " | норма: " << money(a.get_min_normal()) << " - " << money(a.get_max_normal()) << "\n";
    }

    int totalResults = 0;
    int normal = 0;
    int below = 0;
    int above = 0;
    int critical = 0;
    double revenue = 0.0;

    out << "\nПАЦИЕНТЫ (" << patients.size() << ")\n" << LINE << "\n";
    if (patients.empty()) {
        out << "Пациентов нет.\n";
    }
    for (int i = 0; i < patients.size(); ++i) {
        const Patient& patient = patients.get(i);
        out << "#" << patient.get_id() << " " << patient.get_full_name()
            << " (результатов: " << patient.get_results().size() << ")\n";

        int number = 1;
        for (const auto& result : patient.get_results()) {
            const bool isCritical = is_critical(result);
            out << "    " << number++ << ") " << result.get_date()
                << " | " << result.get_analysis()->get_name()
                << " | результат: " << money(result.get_value())
                << " | статус: " << result.get_status()
                << (isCritical ? " | КРИТИЧЕСКИЙ" : "") << "\n";

            ++totalResults;
            revenue += result.get_analysis()->calculate_total_cost();
            if (isCritical) ++critical;
            if (result.get_status() == "Норма") ++normal;
            else if (result.get_status() == "Ниже нормы") ++below;
            else if (result.get_status() == "Выше нормы") ++above;
        }
    }

    out << "\nИТОГИ\n" << LINE << "\n";
    out << "Видов анализов в каталоге: " << analyses.size() << "\n";
    out << "Пациентов: " << patients.size() << "\n";
    out << "Результатов всего: " << totalResults << "\n";
    out << "  в норме: " << normal << ", ниже нормы: " << below << ", выше нормы: " << above << "\n";
    out << "Критических результатов: " << critical << "\n";
    out << "Суммарная стоимость сданных анализов: " << money(revenue) << " руб.\n";
    return out.str();
}

void ReportWriter::write(const std::string& path, const Collection<Analysis*>& analyses, const Collection<Patient>& patients) {
    FileStorage::write_atomic(path, build(analyses, patients));
}
