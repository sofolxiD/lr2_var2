#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

class Student {
private:
    std::string fullName;      // Фамилия и инициалы
    std::string groupNumber;   // Номер группы
    int* grades;               // Массив оценок (динамический)
    int gradesCount;           // Количество оценок
    double averageGrade;       // Средний балл

    void calculateAverage();   // Расчет среднего балла

public:
    // Конструкторы
    Student();
    Student(const std::string& name, const std::string& group, int* gradesArr, int count);
    Student(const Student& other); // Конструктор копирования
    ~Student();

    // Операторы
    Student& operator=(const Student& other);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    friend std::istream& operator>>(std::istream& is, Student& student);

    // Set и Get методы
    void setFullName(const std::string& name);
    void setGroupNumber(const std::string& group);
    void setGrades(int* gradesArr, int count);
    
    std::string getFullName() const;
    std::string getGroupNumber() const;
    double getAverageGrade() const;
    bool hasOnlyGoodGrades() const; // Проверка на оценки 4 и 5

    // Методы для работы с оценками
    void display() const;
};

#endif