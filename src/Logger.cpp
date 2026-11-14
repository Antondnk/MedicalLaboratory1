#include "Logger.h"
#include "exceptions/Exceptions.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>

std::string Logger::timestamp() {
    std::time_t now = std::time(nullptr);
    std::tm local = std::tm();
#ifdef _WIN32
    localtime_s(&local, &now);
#else
    localtime_r(&now, &local);
#endif
    std::ostringstream os;
    os << std::put_time(&local, "%Y-%m-%d %H:%M:%S");
    return os.str();
}

void Logger::append(const std::string& path, const std::string& message) {
    std::ofstream out(path, std::ios::app);
    if (!out.is_open()) {
        throw FileOpenException("Не удалось открыть файл журнала \"" + path + "\" для записи.");
    }
    out << "[" << timestamp() << "] " << message << "\n";
    out.flush();
    if (!out) {
        throw FileWriteException("Ошибка записи в файл журнала \"" + path + "\".");
    }
}
