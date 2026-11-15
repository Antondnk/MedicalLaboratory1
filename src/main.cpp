#include <iostream>
#include <windows.h>
#include "Menu.h"
#include "exceptions/Exceptions.h"
using namespace std;

namespace {

    template <typename Func>
    void run_and_report(const Func& action) {
        try {
            action();
        }
        catch (const InvalidDataException& e) {
            cerr << "\n[НЕКОРРЕКТНЫЕ ДАННЫЕ] " << e.what()
                << "\n  Проверьте данные и повторите действие.\n";
        }
        catch (const IndexOutOfBoundsException& e) {
            cerr << "\n[ВЫХОД ЗА ГРАНИЦЫ] " << e.what()
                << "\n  Выбирайте номер из показанного списка.\n";
        }
        catch (const NotFoundException& e) {
            cerr << "\n[НЕ НАЙДЕНО] " << e.what()
                << "\n  Проверьте, что нужные данные существуют.\n";
        }
        catch (const DuplicateIdException& e) {
            cerr << "\n[ДУБЛИКАТ] " << e.what()
                << "\n  Такая запись уже существует.\n";
        }
        catch (const ConstraintViolationException& e) {
            cerr << "\n[НАРУШЕНО ОГРАНИЧЕНИЕ] " << e.what()
                << "\n  Операция отменена, данные не изменены.\n";
        }
        catch (const FileOpenException& e) {
            cerr << "\n[ФАЙЛ НЕ ОТКРЫТ] " << e.what()
                << "\n  Проверьте путь к файлу и права доступа.\n";
        }
        catch (const FileReadException& e) {
            cerr << "\n[ОШИБКА ЧТЕНИЯ] " << e.what()
                << "\n  Текущее состояние программы не изменено.\n";
        }
        catch (const FileWriteException& e) {
            cerr << "\n[ОШИБКА ЗАПИСИ] " << e.what()
                << "\n  Проверьте свободное место и права на запись.\n";
        }
        catch (const LabException& e) {
            cerr << "\n[ОШИБКА СИСТЕМЫ: " << e.get_exception_category() << "] " << e.what() << "\n";
        }
        catch (const exception& e) {
            cerr << "\n[СТАНДАРТНАЯ ОШИБКА] " << e.what() << "\n";
        }
        catch (...) {
            cerr << "\n[НЕИЗВЕСТНАЯ ОШИБКА]\n";
        }
    }

}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Menu menu;

    run_and_report([&menu]() {
        menu.load_on_startup();
        });

    bool running = true;
    while (running) {
        run_and_report([&menu, &running]() {
            running = menu.process_command();
            });

        if (cin.eof()) {
            break;
        }
    }
    return 0;
}