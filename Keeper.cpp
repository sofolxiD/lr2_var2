#include "Keeper.h"
#include <iostream>
#include <fstream>
#include <algorithm>

// Конструктор - создает пустой Keeper
Keeper::Keeper() : size(0), capacity(10) {
    // Выделяем память для массива указателей на студентов
    students = new Student*[capacity];
    for (int i = 0; i < capacity; i++) {
        students[i] = nullptr;  // Заполняем нулями
    }
    std::cout << "Создан Keeper" << std::endl;
}

// Деструктор - очищает память при удалении Keeper
Keeper::~Keeper() {
    // Удаляем всех студентов
    for (int i = 0; i < size; i++) {
        delete students[i];
    }
    // Удаляем сам массив
    delete[] students;
    std::cout << "Удален Keeper" << std::endl;
}

// Увеличивает размер массива если он заполнен
void Keeper::resize() {
    capacity *= 2;  // Удваиваем емкость
    Student** newStudents = new Student*[capacity];  // Новый массив большего размера
    
    // Заполняем новый массив нулями
    for (int i = 0; i < capacity; i++) {
        newStudents[i] = nullptr;
    }
    
    // Копируем старых студентов в новый массив
    for (int i = 0; i < size; i++) {
        newStudents[i] = students[i];
    }
    
    // Удаляем старый массив
    delete[] students;
    // Присваиваем новый массив
    students = newStudents;
    std::cout << "Keeper увеличен до " << capacity << std::endl;
}

// Добавляет студента в конец
void Keeper::add(Student* s) {
    // Проверяем, есть ли место
    if (size >= capacity) {
        resize();  // Если нет - увеличиваем массив
    }
    
    // Добавляем студента
    students[size] = s;
    size++;  // Увеличиваем счетчик
    
    sortByAverage();  // Сортируем по среднему баллу
    std::cout << "Добавлен студент. Всего: " << size << std::endl;
}

// Вставляет студента на определенную позицию
void Keeper::insert(Student* s, int pos) {
    // Проверка правильности позиции
    if (pos < 0 || pos > size) {
        std::cout << "Ошибка: неверная позиция" << std::endl;
        return;
    }
    
    // Проверяем, нужно ли увеличивать массив
    if (size >= capacity) {
        resize();
    }
    
    // Сдвигаем всех студентов справа от pos на одну позицию вправо
    for (int i = size; i > pos; i--) {
        students[i] = students[i - 1];
    }
    
    // Вставляем нового студента
    students[pos] = s;
    size++;  // Увеличиваем счетчик
    
    sortByAverage();  // Сортируем
}

// Удаляет студента по индексу
void Keeper::remove(int index) {
    // Проверка правильности индекса
    if (index < 0 || index >= size) {
        std::cout << "Ошибка: неверный индекс" << std::endl;
        return;
    }
    
    std::cout << "Удаляем студента: " << students[index]->getName() << std::endl;
    delete students[index];  // Удаляем студента из памяти
    
    // Сдвигаем всех студентов после удаленного на одну позицию влево
    for (int i = index; i < size - 1; i++) {
        students[i] = students[i + 1];
    }
    
    // Последний элемент обнуляем
    students[size - 1] = nullptr;
    size--;  // Уменьшаем счетчик
    
    std::cout << "Студент удален. Осталось: " << size << std::endl;
}

// Редактирует студента по индексу
void Keeper::edit(int index) {
    if (index < 0 || index >= size) {
        std::cout << "Ошибка: неверный индекс" << std::endl;
        return;
    }
    
    std::cout << "Редактирование студента:" << std::endl;
    students[index]->show();  // Показываем текущие данные
    
    // Перезаписываем данные студента
    std::cin >> *students[index];
    sortByAverage();  // Сортируем заново
}

// Показывает всех студентов
void Keeper::showAll() const {
    if (size == 0) {
        std::cout << "Список пуст" << std::endl;
        return;
    }
    
    std::cout << "\n=== Все студенты ===" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i << ") ";  // Выводим номер
        students[i]->show();     // Выводим информацию о студенте
    }
    std::cout << "====================" << std::endl;
}

// Показывает студентов у которых все оценки 4 и 5
void Keeper::showGoodStudents() const {
    bool found = false;  // Флаг - нашли ли таких студентов
    
    std::cout << "\n=== Студенты с 4 и 5 ===" << std::endl;
    for (int i = 0; i < size; i++) {
        // Проверяем у каждого студента оценки
        if (students[i]->hasGoodGrades()) {
            std::cout << students[i]->getName() 
                      << " группа " << students[i]->getGroup() << std::endl;
            found = true;  // Нашли хотя бы одного
        }
    }
    
    // Если никого не нашли
    if (!found) {
        std::cout << "Таких студентов нет" << std::endl;
    }
    std::cout << "=======================" << std::endl;
}

// Возвращает студента по индексу (для внешнего использования)
Student* Keeper::getStudent(int index) const {
    if (index < 0 || index >= size) {
        return nullptr;  // Если индекс неправильный - возвращаем nullptr
    }
    return students[index];
}

// Сохраняет всех студентов в файл stud.txt
void Keeper::saveToFile() {
    // Открываем файл для записи
    std::ofstream file("stud.txt");
    
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла" << std::endl;
        return;
    }
    
    // Сначала записываем количество студентов
    file << size << std::endl;
    
    // Затем записываем каждого студента
    for (int i = 0; i < size; i++) {
        students[i]->saveToFile(file);
    }
    
    file.close();  // Закрываем файл
    std::cout << "Сохранено в stud.txt" << std::endl;
}

// Загружает студентов из файла stud.txt
void Keeper::loadFromFile() {
    // Открываем файл для чтения
    std::ifstream file("stud.txt");
    
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла" << std::endl;
        return;
    }
    
    // Очищаем текущие данные (удаляем всех студентов)
    for (int i = 0; i < size; i++) {
        delete students[i];
    }
    size = 0;  // Сбрасываем счетчик
    
    // Читаем количество студентов из файла
    int fileSize;
    file >> fileSize;
    file.ignore();  // Пропускаем перевод строки
    
    // Читаем каждого студента
    for (int i = 0; i < fileSize; i++) {
        Student* s = new Student();  // Создаем нового студента
        s->loadFromFile(file);       // Загружаем данные из файла
        add(s);                      // Добавляем в базу
    }
    
    file.close();  // Закрываем файл
    std::cout << "Загружено из stud.txt" << std::endl;
}

// Сортирует студентов по среднему баллу (метод пузырька)
void Keeper::sortByAverage() {
    // Проходим по массиву много раз
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Если текущий студент имеет средний балл больше следующего
            if (students[j]->getAverage() > students[j + 1]->getAverage()) {
                // Меняем их местами
                Student* temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}