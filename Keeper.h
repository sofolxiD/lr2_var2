#ifndef KEEPER_H // для управления массивом студентов
#define KEEPER_H

#include "Student.h"
#include <string>

class Keeper {
private:
    Student** students;    // Массив указателей на студентов
    int count;             // Текущее количество
    int capacity;          // Текущая вместимость
    
    void resize();         // Увеличение размера массива
    void sortByAverage();  // Сортировка по среднему баллу
    
public:
    Keeper(int initialCapacity = 2);
    Keeper(const Keeper& other);
    Keeper& operator=(const Keeper& other);
    ~Keeper();
    
    void add(Student* student);
    void insert(Student* student, int position);
    void remove(int index);
    void edit(int index);
    
    void displayAll() const;
    void displayGoodStudents() const;
    
    int size() const { return count; }
    Student* get(int index) const;
    
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif
