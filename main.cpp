#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Keeper.h"
#include "TextProcessor.h"

using namespace std;

void printMenu(int selected) {
    const char* menu[] = {
        "1) Добавить нового студента",
        "2) Добавить студента на позицию",
        "3) Редактировать студента",
        "4) Удалить студента",
        "5) Показать всех студентов",
        "6) Показать успевающих студентов (4 и 5)",
        "7) Сохранить в файл",
        "8) Загрузить из файла",
        "9) Обработать текст (задание 2)",
        "10) Выход"
    };
    
    const int menuSize = 10;
    
    system("cls");
    cout << "=== Управление студентами ===" << endl;
    cout << "==============================" << endl;
    
    for (int i = 0; i < menuSize; i++) {
        if (i == selected) {
            cout << "-> " << menu[i] << endl;
        } else {
            cout << "   " << menu[i] << endl;
        }
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    
    Keeper keeper;
    int menuIndex = 0;
    char key;
    
    while (true) {
        printMenu(menuIndex);
        key = _getch();
        
        if (key == 72) { // Стрелка вверх
            menuIndex = (menuIndex == 0) ? 9 : menuIndex - 1;
        } else if (key == 80) { // Стрелка вниз
            menuIndex = (menuIndex == 9) ? 0 : menuIndex + 1;
        } else if (key == 13) { // Enter
            system("cls");
            
            try {
                switch (menuIndex) {
                    case 0: { // Добавить студента
                        Student* s = new Student();
                        cout << "=== Добавление студента ===" << endl;
                        cin >> *s;
                        keeper.add(s);
                        cout << "Студент добавлен!" << endl;
                        system("pause");
                        break;
                    }
                    case 4: { // Удалить студента
                        int index;
                        cout << "Введите индекс для удаления: ";
                        cin >> index;
                        cin.ignore();
                        keeper.remove(index);
                        cout << "Студент удален!" << endl;
                        system("pause");
                        break;
                    }
                    case 5: { // Показать успевающих
                        keeper.displayGoodStudents();
                        system("pause");
                        break;
                    }
                    case 9: { // Выход
                        cout << "Выход из программы..." << endl;
                        return 0;
                    }
                }
            } catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
                system("pause");
            }
        }
    }
    
    return 0;
}