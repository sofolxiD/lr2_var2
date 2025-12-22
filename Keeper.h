#ifndef KEEPER_H // для управления массивом студентов
#define KEEPER_H

#include "Student.h"

class Keeper {
private:
    Student** students;  // Массив указателей на студентов (двойной указатель)
    int size;            // Текущее количество студентов
    int capacity;        // Сколько студентов может вместить массив

    void resize();       // Увеличивает размер массива

public:
    Keeper();           // Конструктор
    ~Keeper();          // Деструктор
    
    // Основные операции
    void add(Student* s);           // Добавить в конец
    void insert(Student* s, int pos); // Вставить на позицию
    void remove(int index);         // Удалить по индексу
    void edit(int index);           // Редактировать по индексу
    
    // Вывод на экран
    void showAll() const;           // Показать всех
    void showGoodStudents() const;  // Показать хороших студентов
    
    // Геттеры (получить данные)
    int getSize() const { return size; }  // Получить количество студентов
    Student* getStudent(int index) const; // Получить студента по индексу
    
    // Работа с файлами
    void saveToFile();   // Сохранить в файл stud.txt
    void loadFromFile(); // Загрузить из файла stud.txt
    
    void sortByAverage(); // Сортировка по среднему баллу
};

#endif