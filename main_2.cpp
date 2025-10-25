#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "Keeper.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Bus.h"

using namespace std;

void print_menu(int selected)
{
    const char* menu[] = {
        "1) Добавить автомобиль",
        "2) Добавить мотоцикл",
        "3) Добавить автобус",
        "4) Удалить элемент по индексу",
        "5) Показать все",
        "6) Сохранить в файл",
        "7) Загрузить из файла",
        "8) Выход"
    };
    const int menuSize = 8;

    system("cls");
    cout << "=== Гараж ===\n\n";
    for (int i = 0; i < menuSize; i++) {
        if (i == selected)
            cout << "-> " << menu[i] << endl;
        else
            cout << "   " << menu[i] << endl;
    }
}

int main()
{
    SetConsoleOutputCP(1251); // русский
    SetConsoleCP(1251);

    Keeper keeper;
    int menu_index = 0;
    char key;

    while (true) {
        print_menu(menu_index);
        key = _getch();

        if (key == 72) // стрелка вверх
            menu_index = (menu_index == 0) ? 7 : menu_index - 1;
        else if (key == 80) // стрелка вниз
            menu_index = (menu_index == 7) ? 0 : menu_index + 1;
        else if (key == 13) { // Enter
            system("cls");
            try {
                switch (menu_index) {
                case 0: { // добавить автомобиль
                    Car* c = new Car();
                    cout << "Добавление автомобиля:\n";
                    cin.ignore(); // очищаем '\n' после предыдущего ввода
                    c->inputFromConsole();
                    keeper.add(c);
                    cout << "Автомобиль добавлен.\n";
                    system("pause");
                    break;
                }
                case 1: { // добавить мотоцикл
                    Motorcycle* m = new Motorcycle();
                    cout << "Добавление мотоцикла:\n";
                    cin.ignore();
                    m->inputFromConsole();
                    keeper.add(m);
                    cout << "Мотоцикл добавлен.\n";
                    system("pause");
                    break;
                }
                case 2: { // добавить автобус
                    Bus* b = new Bus();
                    cout << "Добавление автобуса:\n";
                    cin.ignore();
                    b->inputFromConsole();
                    keeper.add(b);
                    cout << "Автобус добавлен.\n";
                    system("pause");
                    break;
                }
                case 3: { // удалить элемент
                    int idx;
                    cout << "Введите индекс для удаления: ";
                    cin >> idx;
                    keeper.removeAt(idx);
                    cout << "Элемент удалён.\n";
                    system("pause");
                    break;
                }
                case 4: { // показать все
                    keeper.showAll();
                    system("pause");
                    break;
                }
                case 5: { // сохранить в файл
                    string filename;
                    cout << "Введите имя файла (по умолчанию garage.txt): ";
                    cin.ignore();
                    getline(cin, filename);
                    if (filename.empty()) filename = "garage.txt";
                    keeper.saveToFile(filename);
                    cout << "Данные сохранены в " << filename << endl;
                    system("pause");
                    break;
                }
                case 6: { // загрузить из файла
                    string filename;
                    cout << "Введите имя файла (по умолчанию garage.txt): ";
                    cin.ignore();
                    getline(cin, filename);
                    if (filename.empty()) filename = "garage.txt";
                    keeper.loadFromFile(filename);
                    cout << "Данные загружены из " << filename << endl;
                    system("pause");
                    break;
                }
                case 7: { // выход
                    cout << "Выход из программы...\n";
                    system("pause");
                    return 0;
                }
                }
            }
            catch (const GarageException& ge) {
                cout << "Ошибка: " << ge.what() << endl;
                system("pause");
            }
            catch (const exception& ex) {
                cout << "Стандартное исключение: " << ex.what() << endl;
                system("pause");
            }
        }
    }
}