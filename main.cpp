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
    // Настраиваем консоль для русского языка
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    
    Keeper keeper;  // Создаем объект Keeper - это наша "база данных" студентов
    int choice;     // Переменная для выбора пункта меню
    
    // Основной цикл программы - работает пока не выберем "0"
    do {
        showMenu();          // Показываем меню
        cin >> choice;       // Читаем выбор пользователя
        cin.ignore();        // Очищаем буфер ввода
        
        // switch - это как много if'ов в одном
        switch (choice) {
            case 1: {  // Добавить студента
                Student* s = new Student();  // Создаем нового студента в памяти
                cin >> *s;                   // Вводим данные студента
                keeper.add(s);               // Добавляем студента в базу
                cout << "Добавлено!" << endl;
                pressEnter();  // Ждем нажатия Enter
                break;
            }
            case 2: {  // Добавить студента на конкретную позицию
                int pos;  // Позиция куда вставить
                cout << "Позиция (0-" << keeper.getSize() << "): ";
                cin >> pos;
                cin.ignore();
                
                if (pos < 0 || pos > keeper.getSize()) {
                    cout << "Неверная позиция!" << endl;
                } else {
                    Student* s = new Student();  // Новый студент
                    cin >> *s;                   // Ввод данных
                    keeper.insert(s, pos);       // Вставляем на позицию
                    cout << "Вставлено!" << endl;
                }
                pressEnter();
                break;
            }
            case 3: {  // Редактировать существующего студента
                if (keeper.getSize() == 0) {  // Проверяем, есть ли студенты
                    cout << "Список пуст!" << endl;
                } else {
                    int idx;  // Индекс студента для редактирования
                    cout << "Индекс (0-" << keeper.getSize()-1 << "): ";
                    cin >> idx;
                    cin.ignore();
                    
                    if (idx < 0 || idx >= keeper.getSize()) {
                        cout << "Неверный индекс!" << endl;
                    } else {
                        keeper.edit(idx);  // Редактируем студента
                        cout << "Отредактировано!" << endl;
                    }
                }
                pressEnter();
                break;
            }
            case 4: {  // Удалить студента
                if (keeper.getSize() == 0) {
                    cout << "Список пуст!" << endl;
                } else {
                    int idx;  // Индекс студента для удаления
                    cout << "Индекс для удаления (0-" << keeper.getSize()-1 << "): ";
                    cin >> idx;
                    cin.ignore();
                    
                    if (idx < 0 || idx >= keeper.getSize()) {
                        cout << "Неверный индекс!" << endl;
                    } else {
                        keeper.remove(idx);  // Удаляем студента
                        cout << "Удалено!" << endl;
                    }
                }
                pressEnter();
                break;
            }
            case 5: {  // Показать всех студентов
                keeper.showAll();  // Выводим всех студентов
                pressEnter();
                break;
            }
            case 6: {  // Показать только хороших студентов (оценки 4 и 5)
                keeper.showGoodStudents();
                pressEnter();
                break;
            }
            case 7: {  // Сохранить в файл
                keeper.saveToFile();  // Сохраняем в файл stud.txt
                pressEnter();
                break;
            }
            case 8: {  // Загрузить из файла
                keeper.loadFromFile();  // Загружаем из файла stud.txt
                pressEnter();
                break;
            }
            case 9: {  // Вторая часть задания - поиск слова в тексте
                string word;  // Слово для поиска
                cout << "Введите слово для поиска: ";
                getline(cin, word);  // Читаем слово
                TextProcessor::findSentencesWithWord(word);  // Ищем слово в text.txt
                pressEnter();
                break;
            }
            case 0: {  // Выход из программы
                cout << "Выход из программы..." << endl;
                break;
            }
            default: {  // Если выбрали несуществующий пункт
                cout << "Неверный выбор!" << endl;
                pressEnter();
            }
        }
        
    } while (choice != 0);  // Повторяем пока не выберут 0
    
    return 0; 
}