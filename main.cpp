#include <iostream>
#include <conio.h>
#include <windows.h>
#include <limits>
#include "Keeper.h"
#include "TextProcessor.h"

using namespace std;

void showMenu() {
    system("cls");
    cout << "=================================" << endl;
    cout << "         УПРАВЛЕНИЕ СТУДЕНТАМИ" << endl;
    cout << "=================================" << endl;
    cout << "1. Добавить студента" << endl;
    cout << "2. Добавить на позицию" << endl;
    cout << "3. Редактировать студента" << endl;
    cout << "4. Удалить студента" << endl;
    cout << "5. Показать всех" << endl;
    cout << "6. Показать отличников (4 и 5)" << endl;
    cout << "7. СОХРАНИТЬ в stud.txt" << endl;
    cout << "8. ЗАГРУЗИТЬ из stud.txt" << endl;
    cout << "9. Найти слово в text.txt" << endl;
    cout << "0. ВЫХОД" << endl;
    cout << "=================================" << endl;
    cout << "Выбор: ";
}

void pressEnter() {
    cout << "\nНажмите Enter...";
    cin.get();
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    
    Keeper keeper;
    int choice;
    
    do {
        showMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                Student* s = new Student();
                cin >> *s;
                keeper.add(s);
                cout << "Добавлено!" << endl;
                pressEnter();
                break;
            }
            case 2: {
                int pos;
                cout << "Позиция (0-" << keeper.getSize() << "): ";
                cin >> pos;
                cin.ignore();
                
                if (pos < 0 || pos > keeper.getSize()) {
                    cout << "Неверная позиция!" << endl;
                } else {
                    Student* s = new Student();
                    cin >> *s;
                    keeper.insert(s, pos);
                    cout << "Вставлено!" << endl;
                }
                pressEnter();
                break;
            }
            case 3: {
                if (keeper.getSize() == 0) {
                    cout << "Список пуст!" << endl;
                } else {
                    int idx;
                    cout << "Индекс (0-" << keeper.getSize()-1 << "): ";
                    cin >> idx;
                    cin.ignore();
                    
                    if (idx < 0 || idx >= keeper.getSize()) {
                        cout << "Неверный индекс!" << endl;
                    } else {
                        keeper.edit(idx);
                        cout << "Отредактировано!" << endl;
                    }
                }
                pressEnter();
                break;
            }
            case 4: {
                if (keeper.getSize() == 0) {
                    cout << "Список пуст!" << endl;
                } else {
                    int idx;
                    cout << "Индекс для удаления (0-" << keeper.getSize()-1 << "): ";
                    cin >> idx;
                    cin.ignore();
                    
                    if (idx < 0 || idx >= keeper.getSize()) {
                        cout << "Неверный индекс!" << endl;
                    } else {
                        keeper.remove(idx);
                        cout << "Удалено!" << endl;
                    }
                }
                pressEnter();
                break;
            }
            case 5: {
                keeper.showAll();
                pressEnter();
                break;
            }
            case 6: {
                keeper.showGoodStudents();
                pressEnter();
                break;
            }
            case 7: {
                keeper.saveToFile();
                pressEnter();
                break;
            }
            case 8: {
                keeper.loadFromFile();
                pressEnter();
                break;
            }
            case 9: {
                string word;
                cout << "Введите слово для поиска: ";
                getline(cin, word);
                TextProcessor::findSentencesWithWord(word);
                pressEnter();
                break;
            }
            case 0: {
                cout << "Выход из программы..." << endl;
                break;
            }
            default: {
                cout << "Неверный выбор!" << endl;
                pressEnter();
            }
        }
        
    } while (choice != 0);
    
    return 0;
}