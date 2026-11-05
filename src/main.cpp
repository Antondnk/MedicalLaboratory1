#include <iostream>
#include <windows.h>
#include "Menu.h"
#include "exceptions/Exceptions.h"
using namespace std;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Menu menu;
    bool running = true;

    while (running) {
        try {
            // Все действия меню вызываются здесь; исключения всплывают сюда из методов, где они брошены.
            running = menu.process_command();
        }
        // Порядок важен: сначала конкретные типы, потом общий базовый LabException, потом std::exception.
        catch (const InvalidDataException& e) {
            cerr << "\n[НЕКОРРЕКТНЫЕ ДАННЫЕ] " << e.what()
                 << "\n  Проверьте ввод и повторите действие.\n";
        }
        catch (const IndexOutOfBoundsException& e) {
            cerr << "\n[ВЫХОД ЗА ГРАНИЦЫ] " << e.what()
                 << "\n  Выбирайте номер из показанного списка.\n";
        }
        catch (const NotFoundException& e) {
            cerr << "\n[НЕ НАЙДЕНО] " << e.what()
                 << "\n  Сначала добавьте нужные данные через меню.\n";
        }
        catch (const DuplicateIdException& e) {
            cerr << "\n[ДУБЛИКАТ] " << e.what()
                 << "\n  Такая запись уже существует, измените дату или анализ.\n";
        }
        catch (const ConstraintViolationException& e) {
            cerr << "\n[НАРУШЕНО ОГРАНИЧЕНИЕ] " << e.what()
                 << "\n  Операция отменена, данные не изменены.\n";
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

        // Поток ввода закончился (Ctrl+Z / конец файла): продолжать нечего, иначе был бы бесконечный цикл.
        if (cin.eof()) {
            break;
        }
    }
    return 0;
}
