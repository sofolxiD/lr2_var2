#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    std::string group;
    int* grades;
    int gradesCount;
    double average;

    void calculateAverage();

public:
    // Конструкторы
    Student();
    Student(std::string n, std::string g, int* gr, int count);
    Student(const Student& other);
    ~Student();

    // Операторы
    Student& operator=(const Student& other);
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);

    // Методы
    void setName(std::string n) { name = n; }
    void setGroup(std::string g) { group = g; }
    void setGrades(int* gr, int count);
    
    std::string getName() const { return name; }
    std::string getGroup() const { return group; }
    double getAverage() const { return average; }
    
    bool hasGoodGrades() const;
    void show() const;
    
    // Для файла
    void saveToFile(std::ofstream& file) const;
    void loadFromFile(std::ifstream& file);
};

#endif