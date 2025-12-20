#include "Student.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Student::Student() : name(""), group(""), grades(nullptr), gradesCount(0), average(0) {
    std::cout << "Конструктор Student()" << std::endl;
}

Student::Student(std::string n, std::string g, int* gr, int count) 
    : name(n), group(g), gradesCount(count), average(0) {
    
    std::cout << "Конструктор Student(" << n << ")" << std::endl;
    
    grades = new int[count];
    for (int i = 0; i < count; i++) {
        grades[i] = gr[i];
    }
    calculateAverage();
}

Student::Student(const Student& other) 
    : name(other.name), group(other.group), 
      gradesCount(other.gradesCount), average(other.average) {
    
    std::cout << "Конструктор копирования Student" << std::endl;
    
    grades = new int[gradesCount];
    for (int i = 0; i < gradesCount; i++) {
        grades[i] = other.grades[i];
    }
}

Student::~Student() {
    std::cout << "Деструктор Student: " << name << std::endl;
    delete[] grades;
}

Student& Student::operator=(const Student& other) {
    std::cout << "Оператор = Student" << std::endl;
    
    if (this != &other) {
        delete[] grades;
        
        name = other.name;
        group = other.group;
        gradesCount = other.gradesCount;
        average = other.average;
        
        grades = new int[gradesCount];
        for (int i = 0; i < gradesCount; i++) {
            grades[i] = other.grades[i];
        }
    }
    return *this;
}

void Student::calculateAverage() {
    if (gradesCount == 0) {
        average = 0;
        return;
    }
    
    double sum = 0;
    for (int i = 0; i < gradesCount; i++) {
        sum += grades[i];
    }
    average = sum / gradesCount;
}

void Student::setGrades(int* gr, int count) {
    delete[] grades;
    gradesCount = count;
    grades = new int[count];
    for (int i = 0; i < count; i++) {
        grades[i] = gr[i];
    }
    calculateAverage();
}

bool Student::hasGoodGrades() const {
    for (int i = 0; i < gradesCount; i++) {
        if (grades[i] < 4) {
            return false;
        }
    }
    return true;
}

void Student::show() const {
    std::cout << "Студент: " << name 
              << ", Группа: " << group 
              << ", Средний балл: " << average
              << ", Оценки: ";
    
    for (int i = 0; i < gradesCount; i++) {
        std::cout << grades[i] << " ";
    }
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << s.name << " " << s.group << " " << s.gradesCount << " ";
    for (int i = 0; i < s.gradesCount; i++) {
        os << s.grades[i] << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Student& s) {
    std::cout << "Введите данные студента:" << std::endl;
    
    std::cout << "Фамилия и инициалы: ";
    std::getline(is, s.name);
    
    std::cout << "Номер группы: ";
    std::getline(is, s.group);
    
    std::cout << "Сколько оценок: ";
    is >> s.gradesCount;
    
    delete[] s.grades;
    s.grades = new int[s.gradesCount];
    
    std::cout << "Введите " << s.gradesCount << " оценок: ";
    for (int i = 0; i < s.gradesCount; i++) {
        is >> s.grades[i];
    }
    is.ignore();
    
    s.calculateAverage();
    return is;
}

void Student::saveToFile(std::ofstream& file) const {
    if (!file.is_open()) return;
    
    file << name << std::endl;
    file << group << std::endl;
    file << gradesCount << std::endl;
    
    for (int i = 0; i < gradesCount; i++) {
        file << grades[i] << " ";
    }
    file << std::endl;
}

void Student::loadFromFile(std::ifstream& file) {
    if (!file.is_open()) return;
    
    std::getline(file, name);
    std::getline(file, group);
    file >> gradesCount;
    
    delete[] grades;
    grades = new int[gradesCount];
    
    for (int i = 0; i < gradesCount; i++) {
        file >> grades[i];
    }
    file.ignore();
    
    calculateAverage();
    std::cout << "Загружен: " << name << std::endl;
}