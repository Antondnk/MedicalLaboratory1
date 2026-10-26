#include <iostream>
#include "Menu.h"
#include <windows.h>

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Menu menu;
    menu.run();
    return 0;
}