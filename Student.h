#include "Student.h"
#include <iostream>
#include <stdexcept>

// Конструктор по умолчанию
Student::Student() : fullName(""), groupNumber(""), grades(nullptr), gradesCount(0), averageGrade(0.0) {
    std::cout << "Вызван конструктор по умолчанию [Student]" << std::endl;
}

// Параметризованный конструктор
Student::Student(const std::string& name, const std::string& group, int* gradesArr, int count) 
    : fullName(name), groupNumber(group), gradesCount(count), averageGrade(0.0) {
    
    std::cout << "Вызван параметризованный конструктор [Student] для " << name << std::endl;
    
    if (count <= 0) {
        throw std::invalid_argument("Количество оценок должно быть положительным");
    }
    
    grades = new int[count];
    for (int i = 0; i < count; i++) {
        if (gradesArr[i] < 2 || gradesArr[i] > 5) {
            delete[] grades;
            throw std::invalid_argument("Оценка должна быть в диапазоне 2-5");
        }
        grades[i] = gradesArr[i];
    }
    
    calculateAverage();
}

// Конструктор копирования
Student::Student(const Student& other) 
    : fullName(other.fullName), groupNumber(other.groupNumber), 
      gradesCount(other.gradesCount), averageGrade(other.averageGrade) {
    
    std::cout << "Вызван конструктор копирования [Student] для " << fullName << std::endl;
    
    grades = new int[gradesCount];
    for (int i = 0; i < gradesCount; i++) {
        grades[i] = other.grades[i];
    }
}

// Деструктор
Student::~Student() {
    std::cout << "Вызван деструктор [Student] для " << fullName << std::endl;
    delete[] grades;
}

// Оператор присваивания
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        std::cout << "Вызван оператор присваивания [Student]" << std::endl;
        
        delete[] grades;
        
        fullName = other.fullName;
        groupNumber = other.groupNumber;
        gradesCount = other.gradesCount;
        averageGrade = other.averageGrade;
        
        grades = new int[gradesCount];
        for (int i = 0; i < gradesCount; i++) {
            grades[i] = other.grades[i];
        }
    }
    return *this;
}

// Расчет среднего балла
void Student::calculateAverage() {
    if (gradesCount == 0) {
        averageGrade = 0.0;
        return;
    }
    
    double sum = 0;
    for (int i = 0; i < gradesCount; i++) {
        sum += grades[i];
    }
    averageGrade = sum / gradesCount;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "Студент: " << student.fullName 
       << ", Группа: " << student.groupNumber 
       << ", Средний балл: " << student.averageGrade
       << ", Оценки: ";
    
    for (int i = 0; i < student.gradesCount; i++) {
        os << student.grades[i] << " ";
    }
    
    return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, Student& student) {
    std::cout << "Введите фамилию и инициалы: ";
    std::getline(is, student.fullName);
    
    std::cout << "Введите номер группы: ";
    std::getline(is, student.groupNumber);
    
    std::cout << "Введите количество оценок: ";
    is >> student.gradesCount;
    is.ignore();
    
    delete[] student.grades;
    student.grades = new int[student.gradesCount];
    
    std::cout << "Введите " << student.gradesCount << " оценок (через пробел): ";
    for (int i = 0; i < student.gradesCount; i++) {
        is >> student.grades[i];
    }
    is.ignore();
    
    student.calculateAverage();
    return is;
}

// Set и Get методы
void Student::setFullName(const std::string& name) { fullName = name; }
void Student::setGroupNumber(const std::string& group) { groupNumber = group; }

void Student::setGrades(int* gradesArr, int count) {
    delete[] grades;
    gradesCount = count;
    grades = new int[count];
    for (int i = 0; i < count; i++) {
        grades[i] = gradesArr[i];
    }
    calculateAverage();
}

std::string Student::getFullName() const { return fullName; }
std::string Student::getGroupNumber() const { return groupNumber; }
double Student::getAverageGrade() const { return averageGrade; }

bool Student::hasOnlyGoodGrades() const {
    for (int i = 0; i < gradesCount; i++) {
        if (grades[i] < 4) {
            return false;
        }
    }
    return true;
}

void Student::display() const {
    std::cout << *this << std::endl;
}