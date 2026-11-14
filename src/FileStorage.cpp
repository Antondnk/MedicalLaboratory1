#include "FileStorage.h"
#include "BloodAnalysis.h"
#include "UrineAnalysis.h"
#include "GeneticAnalysis.h"
#include "exceptions/Exceptions.h"
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <locale>
#include <map>
#include <set>
#include <sstream>

namespace {

const char* const MAGIC = "LABSTATE";
const int FORMAT_VERSION = 1;

std::string format_double(double value) {
    if (!std::isfinite(value)) {
        throw InvalidDataException("Нельзя сохранить нечисловое значение в файл.");
    }
    std::string text;
    for (int precision = 15; precision <= 17; ++precision) {
        std::ostringstream os;
        os.imbue(std::locale::classic());
        os.precision(precision);
        os << value;
        text = os.str();

        std::istringstream is(text);
        is.imbue(std::locale::classic());
        double back = 0;
        is >> back;
        if (back == value) {
            break;
        }
    }
    return text;
}

void write_text(std::ostream& os, const std::string& s) {
    os << '"';
    for (char c : s) {
        switch (c) {
        case '\\': os << "\\\\"; break;
        case '"':  os << "\\\""; break;
        case '\n': os << "\\n"; break;
        case '\r': os << "\\r"; break;
        default:   os << c; break;
        }
    }
    os << '"';
}

bool read_text(std::istream& is, std::string& out) {
    is >> std::ws;
    if (is.get() != '"') {
        return false;
    }
    out.clear();
    char c;
    while (is.get(c)) {
        if (c == '"') {
            return true;
        }
        if (c == '\\') {
            if (!is.get(c)) {
                return false;
            }
            switch (c) {
            case 'n': out += '\n'; break;
            case 'r': out += '\r'; break;
            case '\\': out += '\\'; break;
            case '"': out += '"'; break;
            default: return false;
            }
        }
        else {
            out += c;
        }
    }
    return false;
}

void write_common(std::ostream& os, const Analysis& a) {
    os << ' ' << a.get_id() << ' ';
    write_text(os, a.get_name());
    os << ' ';
    write_text(os, a.get_category());
    os << ' ' << format_double(a.get_base_cost())
       << ' ' << format_double(a.get_min_normal())
       << ' ' << format_double(a.get_max_normal());
}

void write_analysis(std::ostream& os, const Analysis& a) {
    os << "A ";
    if (const BloodAnalysis* blood = dynamic_cast<const BloodAnalysis*>(&a)) {
        os << "BLOOD";
        write_common(os, a);
        os << ' ' << (blood->get_requires_fasting() ? 1 : 0)
           << ' ' << format_double(blood->get_reagent_cost());
    }
    else if (const UrineAnalysis* urine = dynamic_cast<const UrineAnalysis*>(&a)) {
        os << "URINE";
        write_common(os, a);
        os << ' ' << (urine->get_is_sterile_container() ? 1 : 0)
           << ' ' << format_double(urine->get_container_cost());
    }
    else if (const GeneticAnalysis* genetic = dynamic_cast<const GeneticAnalysis*>(&a)) {
        os << "GENETIC";
        write_common(os, a);
        os << ' ';
        write_text(os, genetic->get_target_gene());
        os << ' ' << format_double(genetic->get_tech_multiplier());
    }
    else {
        throw InvalidDataException("Неизвестный тип анализа \"" + a.get_name() + "\": его нельзя сохранить.");
    }
    os << '\n';
}

bool is_valid_utf8(const std::string& s) {
    size_t i = 0;
    while (i < s.size()) {
        const unsigned char c = static_cast<unsigned char>(s[i]);
        size_t extra = 0;
        unsigned char low = 0x80;
        unsigned char high = 0xBF;
        if (c < 0x80) {
            extra = 0;
        }
        else if (c >= 0xC2 && c <= 0xDF) {
            extra = 1;
        }
        else if (c >= 0xE0 && c <= 0xEF) {
            extra = 2;
            if (c == 0xE0) low = 0xA0;
            if (c == 0xED) high = 0x9F;
        }
        else if (c >= 0xF0 && c <= 0xF4) {
            extra = 3;
            if (c == 0xF0) low = 0x90;
            if (c == 0xF4) high = 0x8F;
        }
        else {
            return false;
        }
        if (i + extra >= s.size()) {
            return false;
        }
        for (size_t j = 1; j <= extra; ++j) {
            const unsigned char next = static_cast<unsigned char>(s[i + j]);
            const unsigned char from = (j == 1) ? low : 0x80;
            const unsigned char to = (j == 1) ? high : 0xBF;
            if (next < from || next > to) {
                return false;
            }
        }
        i += extra + 1;
    }
    return true;
}

class Reader {
    std::istream& in;
    std::string path;
    int lineNo;

public:
    Reader(std::istream& stream, const std::string& filePath)
        : in(stream), path(filePath), lineNo(0) {
    }

    std::string where() const {
        return "Файл \"" + path + "\", строка " + std::to_string(lineNo) + ": ";
    }

    [[noreturn]] void fail(const std::string& message) const {
        throw FileReadException(where() + message);
    }

    bool next(std::string& line) {
        while (std::getline(in, line)) {
            ++lineNo;
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (lineNo == 1 && line.compare(0, 3, "\xEF\xBB\xBF") == 0) {
                line.erase(0, 3);
            }
            if (!is_valid_utf8(line)) {
                fail("файл не в кодировке UTF-8 (сохраните его как \"UTF-8\" без изменения кодировки на ANSI/Unicode).");
            }
            if (line.find_first_not_of(" \t") != std::string::npos) {
                return true;
            }
        }
        if (in.bad()) {
            throw FileReadException("Ошибка чтения файла \"" + path + "\" после строки " + std::to_string(lineNo) + ".");
        }
        return false;
    }

    std::string require() {
        std::string line;
        if (!next(line)) {
            if (lineNo == 0) {
                throw FileReadException("Файл \"" + path + "\" пуст.");
            }
            fail("неожиданный конец файла (файл повреждён или запись была прервана).");
        }
        return line;
    }
};

class Fields {
    std::istringstream ss;
    const Reader& reader;

    void require_separator(const std::string& what) {
        if (ss.eof()) {
            return;
        }
        const int next = ss.peek();
        if (next != std::char_traits<char>::eof() && !std::isspace(static_cast<unsigned char>(next))) {
            reader.fail("после поля (" + what + ") должен идти пробел: поля разделяются пробелами.");
        }
    }

public:
    Fields(const std::string& line, const Reader& r) : ss(line), reader(r) {
        ss.imbue(std::locale::classic());
    }

    std::string word() {
        std::string w;
        if (!(ss >> w)) {
            reader.fail("в строке не хватает данных.");
        }
        return w;
    }

    int integer(const std::string& what) {
        long long v = 0;
        if (!(ss >> v) || v < INT_MIN || v > INT_MAX) {
            reader.fail("ожидалось целое число (" + what + ").");
        }
        require_separator(what);
        return static_cast<int>(v);
    }

    double real(const std::string& what) {
        double v = 0;
        if (!(ss >> v)) {
            reader.fail("ожидалось число (" + what + ").");
        }
        require_separator(what);
        return v;
    }

    bool flag(const std::string& what) {
        int v = integer(what);
        if (v != 0 && v != 1) {
            reader.fail("ожидалось 0 или 1 (" + what + ").");
        }
        return v == 1;
    }

    std::string text(const std::string& what) {
        std::string s;
        if (!read_text(ss, s)) {
            reader.fail("ожидалась строка в кавычках (" + what + ").");
        }
        require_separator(what);
        return s;
    }

    void finish() {
        std::string extra;
        if (ss >> extra) {
            reader.fail("лишние данные в конце строки: \"" + extra + "\".");
        }
    }
};

int read_count(Reader& r, const std::string& keyword) {
    Fields f(r.require(), r);
    if (f.word() != keyword) {
        r.fail("ожидалась строка " + keyword + ".");
    }
    int n = f.integer("количество");
    f.finish();
    if (n < 0) {
        r.fail("количество не может быть отрицательным.");
    }
    return n;
}

std::unique_ptr<Analysis> parse_analysis(Reader& r) {
    Fields f(r.require(), r);
    if (f.word() != "A") {
        r.fail("ожидалась запись анализа (A).");
    }
    const std::string type = f.word();
    const int id = f.integer("ID анализа");
    const std::string name = f.text("название");
    const std::string category = f.text("категория");
    const double baseCost = f.real("базовая стоимость");
    const double minNormal = f.real("нижняя граница нормы");
    const double maxNormal = f.real("верхняя граница нормы");

    std::unique_ptr<Analysis> result;
    if (type == "BLOOD") {
        const bool fasting = f.flag("натощак");
        const double reagentCost = f.real("стоимость реагентов");
        f.finish();
        result = std::make_unique<BloodAnalysis>(name, category, baseCost, minNormal, maxNormal, fasting, reagentCost);
    }
    else if (type == "URINE") {
        const bool sterile = f.flag("стерильный контейнер");
        const double containerCost = f.real("стоимость контейнера");
        f.finish();
        result = std::make_unique<UrineAnalysis>(name, category, baseCost, minNormal, maxNormal, sterile, containerCost);
    }
    else if (type == "GENETIC") {
        const std::string gene = f.text("ген-маркер");
        const double multiplier = f.real("коэффициент сложности");
        f.finish();
        result = std::make_unique<GeneticAnalysis>(name, category, baseCost, minNormal, maxNormal, gene, multiplier);
    }
    else {
        r.fail("неизвестный тип анализа \"" + type + "\".");
    }
    result->set_id(id);
    return result;
}

Patient parse_patient(Reader& r, const std::map<int, const Analysis*>& analyses, std::set<int>& usedIds) {
    Fields f(r.require(), r);
    if (f.word() != "P") {
        r.fail("ожидалась запись пациента (P).");
    }
    const int id = f.integer("ID пациента");
    const std::string name = f.text("ФИО");
    const int resultCount = f.integer("число результатов");
    f.finish();
    if (resultCount < 0) {
        r.fail("число результатов не может быть отрицательным.");
    }
    if (!usedIds.insert(id).second) {
        throw DuplicateIdException("пациент с ID " + std::to_string(id) + " встречается в файле повторно.");
    }

    Patient patient(name);
    patient.set_id(id);

    for (int i = 0; i < resultCount; ++i) {
        Fields rf(r.require(), r);
        if (rf.word() != "R") {
            r.fail("ожидалась запись результата (R): у пациента \"" + name + "\" заявлено результатов: " +
                std::to_string(resultCount) + ".");
        }
        const int analysisId = rf.integer("ID анализа");
        const std::string date = rf.text("дата");
        const double value = rf.real("значение");
        rf.finish();

        auto it = analyses.find(analysisId);
        if (it == analyses.end()) {
            throw NotFoundException("результат ссылается на несуществующий анализ с ID " + std::to_string(analysisId) + ".");
        }
        patient += TestResult(it->second, date, value);
    }
    return patient;
}

LoadedState parse(Reader& r) {
    LoadedState state;

    {
        Fields f(r.require(), r);
        if (f.word() != MAGIC) {
            r.fail(std::string("это не файл состояния системы (нет заголовка ") + MAGIC + ").");
        }
        const int version = f.integer("версия формата");
        f.finish();
        if (version != FORMAT_VERSION) {
            r.fail("неподдерживаемая версия формата: " + std::to_string(version) + ".");
        }
    }

    const int analysisCount = read_count(r, "ANALYSES");
    std::map<int, const Analysis*> byId;
    std::set<std::string> names;
    for (int i = 0; i < analysisCount; ++i) {
        std::unique_ptr<Analysis> analysis = parse_analysis(r);
        if (!byId.emplace(analysis->get_id(), analysis.get()).second) {
            throw DuplicateIdException("анализ с ID " + std::to_string(analysis->get_id()) + " встречается в файле повторно.");
        }
        if (!names.insert(analysis->get_name()).second) {
            throw DuplicateIdException("название анализа \"" + analysis->get_name() + "\" встречается в файле повторно.");
        }
        state.analyses.push_back(std::move(analysis));
    }

    const int patientCount = read_count(r, "PATIENTS");
    std::set<int> patientIds;
    for (int i = 0; i < patientCount; ++i) {
        state.patients.push_back(parse_patient(r, byId, patientIds));
    }

    Fields end(r.require(), r);
    if (end.word() != "END") {
        r.fail("ожидалась метка END: данных больше, чем заявлено в заголовках.");
    }
    end.finish();

    std::string extra;
    if (r.next(extra)) {
        r.fail("после метки END есть лишние данные.");
    }
    return state;
}

}

bool FileStorage::exists(const std::string& path) {
    std::ifstream in(path);
    return in.is_open();
}

void FileStorage::write_atomic(const std::string& path, const std::string& content) {
    const std::string tmp = path + ".tmp";
    const std::string bak = path + ".bak";

    {
        std::ofstream out(tmp, std::ios::trunc);
        if (!out.is_open()) {
            throw FileOpenException("Не удалось открыть файл \"" + path + "\" для записи (проверьте путь и права доступа).");
        }
        out << content;
        out.flush();
        if (!out) {
            out.close();
            std::remove(tmp.c_str());
            throw FileWriteException("Ошибка записи в файл \"" + path + "\" (возможно, нет свободного места).");
        }
    }

    std::remove(bak.c_str());
    const bool hadOld = std::rename(path.c_str(), bak.c_str()) == 0;
    if (std::rename(tmp.c_str(), path.c_str()) != 0) {
        if (hadOld) {
            std::rename(bak.c_str(), path.c_str());
        }
        std::remove(tmp.c_str());
        throw FileWriteException("Не удалось заменить файл \"" + path + "\" новой версией.");
    }
    if (hadOld) {
        std::remove(bak.c_str());
    }
}

void FileStorage::save(const std::string& path,
    const Collection<Analysis*>& analyses,
    const Collection<Patient>& patients) {
    std::ostringstream buf;
    buf.imbue(std::locale::classic());

    buf << MAGIC << ' ' << FORMAT_VERSION << '\n';
    buf << "ANALYSES " << analyses.size() << '\n';
    for (int i = 0; i < analyses.size(); ++i) {
        write_analysis(buf, *analyses.get(i));
    }

    buf << "PATIENTS " << patients.size() << '\n';
    for (int i = 0; i < patients.size(); ++i) {
        const Patient& patient = patients.get(i);
        buf << "P " << patient.get_id() << ' ';
        write_text(buf, patient.get_full_name());
        buf << ' ' << patient.get_results().size() << '\n';
        for (const auto& result : patient.get_results()) {
            buf << "R " << result.get_analysis()->get_id() << ' ';
            write_text(buf, result.get_date());
            buf << ' ' << format_double(result.get_value()) << '\n';
        }
    }
    buf << "END\n";

    write_atomic(path, buf.str());
}

LoadedState FileStorage::load(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        throw FileOpenException("Не удалось открыть файл \"" + path + "\" для чтения (файл не существует или нет доступа).");
    }

    Reader reader(in, path);
    try {
        return parse(reader);
    }
    catch (const DuplicateIdException& e) {
        throw DuplicateIdException(reader.where() + e.what());
    }
    catch (const NotFoundException& e) {
        throw NotFoundException(reader.where() + e.what());
    }
    catch (const InvalidDataException& e) {
        throw InvalidDataException(reader.where() + e.what());
    }
}
