#include "Keeper.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Keeper::Keeper() : size(0), capacity(10) {
    students = new Student*[capacity];
    for (int i = 0; i < capacity; i++) {
        students[i] = nullptr;
    }
    std::cout << "Создан Keeper" << std::endl;
}

Keeper::~Keeper() {
    for (int i = 0; i < size; i++) {
        delete students[i];
    }
    delete[] students;
    std::cout << "Удален Keeper" << std::endl;
}

void Keeper::resize() {
    capacity *= 2;
    Student** newStudents = new Student*[capacity];
    
    for (int i = 0; i < capacity; i++) {
        newStudents[i] = nullptr;
    }
    
    for (int i = 0; i < size; i++) {
        newStudents[i] = students[i];
    }
    
    delete[] students;
    students = newStudents;
    std::cout << "Keeper увеличен до " << capacity << std::endl;
}

void Keeper::add(Student* s) {
    if (size >= capacity) {
        resize();
    }
    
    students[size] = s;
    size++;
    
    sortByAverage();
    std::cout << "Добавлен студент. Всего: " << size << std::endl;
}

void Keeper::insert(Student* s, int pos) {
    if (pos < 0 || pos > size) {
        std::cout << "Ошибка: неверная позиция" << std::endl;
        return;
    }
    
    if (size >= capacity) {
        resize();
    }
    
    for (int i = size; i > pos; i--) {
        students[i] = students[i - 1];
    }
    
    students[pos] = s;
    size++;
    
    sortByAverage();
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        std::cout << "Ошибка: неверный индекс" << std::endl;
        return;
    }
    
    std::cout << "Удаляем студента: " << students[index]->getName() << std::endl;
    delete students[index];
    
    for (int i = index; i < size - 1; i++) {
        students[i] = students[i + 1];
    }
    
    students[size - 1] = nullptr;
    size--;
    
    std::cout << "Студент удален. Осталось: " << size << std::endl;
}

void Keeper::edit(int index) {
    if (index < 0 || index >= size) {
        std::cout << "Ошибка: неверный индекс" << std::endl;
        return;
    }
    
    std::cout << "Редактирование студента:" << std::endl;
    students[index]->show();
    
    std::cin >> *students[index];
    sortByAverage();
}

void Keeper::showAll() const {
    if (size == 0) {
        std::cout << "Список пуст" << std::endl;
        return;
    }
    
    std::cout << "\n=== Все студенты ===" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i << ") ";
        students[i]->show();
    }
    std::cout << "====================" << std::endl;
}

void Keeper::showGoodStudents() const {
    bool found = false;
    
    std::cout << "\n=== Студенты с 4 и 5 ===" << std::endl;
    for (int i = 0; i < size; i++) {
        if (students[i]->hasGoodGrades()) {
            std::cout << students[i]->getName() 
                      << " группа " << students[i]->getGroup() << std::endl;
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "Таких студентов нет" << std::endl;
    }
    std::cout << "=======================" << std::endl;
}

Student* Keeper::getStudent(int index) const {
    if (index < 0 || index >= size) {
        return nullptr;
    }
    return students[index];
}

void Keeper::saveToFile() {
    std::ofstream file("stud.txt");
    
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла" << std::endl;
        return;
    }
    
    file << size << std::endl;
    
    for (int i = 0; i < size; i++) {
        students[i]->saveToFile(file);
    }
    
    file.close();
    std::cout << "Сохранено в stud.txt" << std::endl;
}

void Keeper::loadFromFile() {
    std::ifstream file("stud.txt");
    
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла" << std::endl;
        return;
    }
    
    // Очищает
    for (int i = 0; i < size; i++) {
        delete students[i];
    }
    size = 0;
    
    int fileSize;
    file >> fileSize;
    file.ignore();
    
    for (int i = 0; i < fileSize; i++) {
        Student* s = new Student();
        s->loadFromFile(file);
        add(s);
    }
    
    file.close();
    std::cout << "Загружено из stud.txt" << std::endl;
}

void Keeper::sortByAverage() {
    // сортировка пузырьком
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (students[j]->getAverage() > students[j + 1]->getAverage()) {
                Student* temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}