#ifndef BUS_H
#define BUS_H

#include "Base.h"
#include <string>

class Bus : public Base
{
public:
    std::string brand;       // Марка автобуса
    std::string model;       // Модель автобуса
    int seated;              // Сидячих мест
    int totalSeats;          // Всего мест
    std::string destination; // Тип маршрута (Городской, Междугородний и т.д.)

    Bus();   // Конструктор по умолчанию
    Bus(const std::string& brand_, const std::string& model_,
        int seated_, int totalSeats_, const std::string& destination_);
    Bus(const Bus& other);          // Конструктор копирования
    Bus& operator=(const Bus& other); // Оператор присваивания
    ~Bus();                         // Деструктор

    Base* clone() const override;        // Копирование объекта
    void inputFromConsole() override;    // Ввод данных с клавиатуры
    void print(std::ostream& os) const override; // Вывод информации
    std::string serialize() const override;      // Сериализация
    void deserializeFromStream(std::stringstream& ss); // Десериализация
};

#endif

