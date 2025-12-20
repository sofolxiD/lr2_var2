#ifndef KEEPER_H // для управления массивом студентов
#define KEEPER_H

#include "Student.h"

class Keeper {
private:
    Student** students;
    int size;
    int capacity;

    void resize();

public:
    Keeper();
    ~Keeper();
    
    void add(Student* s);
    void insert(Student* s, int pos);
    void remove(int index);
    void edit(int index);
    
    void showAll() const;
    void showGoodStudents() const;
    
    int getSize() const { return size; }
    Student* getStudent(int index) const;
    
    void saveToFile();
    void loadFromFile();
    
    void sortByAverage();
};

#endif