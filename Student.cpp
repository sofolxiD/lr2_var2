#include "Student.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Конструктор по умолчанию - создает пустого студента
Student::Student() : name(""), group(""), grades(nullptr), gradesCount(0), average(0) {
    std::cout << "Конструктор Student()" << std::endl;
}

// Конструктор с параметрами
Student::Student(std::string n, std::string g, int* gr, int count) 
    : name(n), group(g), gradesCount(count), average(0) {
    
    std::cout << "Конструктор Student(" << n << ")" << std::endl;
    
    // Выделяем память для массива оценок
    grades = new int[count];
    // Копируем оценки
    for (int i = 0; i < count; i++) {
        grades[i] = gr[i];
    }
    calculateAverage();  // Считаем средний балл
}

// Конструктор копирования - создает копию другого студента
Student::Student(const Student& other) 
    : name(other.name), group(other.group), 
      gradesCount(other.gradesCount), average(other.average) {
    
    std::cout << "Конструктор копирования Student" << std::endl;
    
    // Выделяем память и копируем оценки
    grades = new int[gradesCount];
    for (int i = 0; i < gradesCount; i++) {
        grades[i] = other.grades[i];
    }
}

// Деструктор - освобождает память
Student::~Student() {
    std::cout << "Деструктор Student: " << name << std::endl;
    delete[] grades;  // Освобождаем память под оценки
}

// Оператор присваивания - копирует данные другого студента
Student& Student::operator=(const Student& other) {
    std::cout << "Оператор = Student" << std::endl;
    
    // Проверяем, не пытаемся ли скопировать самого себя
    if (this != &other) {
        delete[] grades;  // Освобождаем старую память
        
        // Копируем простые поля
        name = other.name;
        group = other.group;
        gradesCount = other.gradesCount;
        average = other.average;
        
        // Выделяем новую память и копируем оценки
        grades = new int[gradesCount];
        for (int i = 0; i < gradesCount; i++) {
            grades[i] = other.grades[i];
        }
    }
    return *this;  // Возвращаем себя
}

// Считает средний балл
void Student::calculateAverage() {
    if (gradesCount == 0) {
        average = 0;
        return;
    }
    
    double sum = 0;
    // Суммируем все оценки
    for (int i = 0; i < gradesCount; i++) {
        sum += grades[i];
    }
    // Делим сумму на количество
    average = sum / gradesCount;
}

// Устанавливает новые оценки
void Student::setGrades(int* gr, int count) {
    delete[] grades;        // Удаляем старые оценки
    gradesCount = count;    // Устанавливаем новое количество
    grades = new int[count]; // Выделяем память
    
    // Копируем новые оценки
    for (int i = 0; i < count; i++) {
        grades[i] = gr[i];
    }
    calculateAverage();  // Пересчитываем средний балл
}

// Проверяет, все ли оценки 4 и 5
bool Student::hasGoodGrades() const {
    for (int i = 0; i < gradesCount; i++) {
        if (grades[i] < 4) {  // Если найдена оценка меньше 4
            return false;      // Студент не "хороший"
        }
    }
    return true;  // Все оценки 4 и 5
}

// Выводит информацию о студенте на экран
void Student::show() const {
    std::cout << "Студент: " << name 
              << ", Группа: " << group 
              << ", Средний балл: " << average
              << ", Оценки: ";
    
    // Выводим все оценки
    for (int i = 0; i < gradesCount; i++) {
        std::cout << grades[i] << " ";
    }
    std::cout << std::endl;
}

// Оператор вывода - для записи в поток (например, в cout)
std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << s.name << " " << s.group << " " << s.gradesCount << " ";
    for (int i = 0; i < s.gradesCount; i++) {
        os << s.grades[i] << " ";
    }
    return os;
}

// Оператор ввода - для чтения из потока (например, из cin)
std::istream& operator>>(std::istream& is, Student& s) {
    std::cout << "Введите данные студента:" << std::endl;
    
    std::cout << "Фамилия и инициалы: ";
    std::getline(is, s.name);  // Читаем ФИО
    
    std::cout << "Номер группы: ";
    std::getline(is, s.group);  // Читаем группу
    
    std::cout << "Сколько оценок: ";
    is >> s.gradesCount;  // Читаем количество оценок
    
    // Освобождаем старую память и выделяем новую
    delete[] s.grades;
    s.grades = new int[s.gradesCount];
    
    std::cout << "Введите " << s.gradesCount << " оценок: ";
    // Читаем все оценки
    for (int i = 0; i < s.gradesCount; i++) {
        is >> s.grades[i];
    }
    is.ignore();  // Пропускаем перевод строки
    
    s.calculateAverage();  // Считаем средний балл
    return is;
}

// Сохраняет студента в файл
void Student::saveToFile(std::ofstream& file) const {
    if (!file.is_open()) return;
    
    // Записываем данные построчно
    file << name << std::endl;      // ФИО
    file << group << std::endl;     // Группа
    file << gradesCount << std::endl; // Количество оценок
    
    // Записываем все оценки в одну строку
    for (int i = 0; i < gradesCount; i++) {
        file << grades[i] << " ";
    }
    file << std::endl;
}

// Загружает студента из файла
void Student::loadFromFile(std::ifstream& file) {
    if (!file.is_open()) return;
    
    // Читаем данные построчно
    std::getline(file, name);   // ФИО
    std::getline(file, group);  // Группа
    file >> gradesCount;        // Количество оценок
    
    // Освобождаем старую память и выделяем новую
    delete[] grades;
    grades = new int[gradesCount];
    
    // Читаем все оценки
    for (int i = 0; i < gradesCount; i++) {
        file >> grades[i];
    }
    file.ignore();  // Пропускаем перевод строки
    
    calculateAverage();  // Считаем средний балл
    std::cout << "Загружен: " << name << std::endl;
}