#ifndef STUDENT_H  // Защита от повторного включения
#define STUDENT_H

#include <iostream>
#include <string>

class Student {
private:
    std::string name;       // Фамилия и инициалы
    std::string group;      // Номер группы
    int* grades;            // Указатель на массив оценок (динамический массив)
    int gradesCount;        // Количество оценок
    double average;         // Средний балл

    void calculateAverage(); // Вспомогательный метод для расчета среднего балла

public:
    // Конструкторы
    Student();  // Без параметров
    Student(std::string n, std::string g, int* gr, int count);  // С параметрами
    Student(const Student& other);  // Копирующий конструктор
    ~Student();  // Деструктор

    // Операторы
    Student& operator=(const Student& other);  // Оператор присваивания
    friend std::ostream& operator<<(std::ostream& os, const Student& s);  // Вывод
    friend std::istream& operator>>(std::istream& is, Student& s);  // Ввод

    // Простые методы установки значений (set)
    void setName(std::string n) { name = n; }
    void setGroup(std::string g) { group = g; }
    void setGrades(int* gr, int count);
    
    // Простые методы получения значений (get)
    std::string getName() const { return name; }
    std::string getGroup() const { return group; }
    double getAverage() const { return average; }
    
    // Дополнительные методы
    bool hasGoodGrades() const;  // Проверяет оценки 4 и 5
    void show() const;           // Показывает информацию
    
    // Методы для работы с файлами
    void saveToFile(std::ofstream& file) const;  // Сохраняет в файл
    void loadFromFile(std::ifstream& file);      // Загружает из файла
};

#endif