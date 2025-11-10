#ifndef CAR_H
#define CAR_H

#include "Base.h"
#include <string>

class Car : public Base {
private:
    std::string brand;         // Марка автомобиля
    std::string model;         // Модель автомобиля
    double engineVolume;       // Объем двигателя
    std::string color;         // Цвет
    std::string transmission;  // Тип КПП (Механика, Автомат, Робот, Вариатор)

public:     //Конструкторы
    Car();  // Без параметров
    Car(const std::string& brand, const std::string& model, double engineVolume,
        const std::string& color, const std::string& transmission);
    Car(const Car& other);               // Копирующий конструктор
    Car& operator=(const Car& other);    // Оператор присваивания
    ~Car();                              // Деструктор

    // Переопределения виртуальных методов базового класса
    Base* clone() const override;        // Клонирование объекта
    void inputFromConsole() override;    // Ввод данных с клавиатуры (стрелочное меню КПП)
    void print(std::ostream& os) const override;  // Вывод на экран
    std::string serialize() const override;       // Сериализация (для записи в файл)
    void deserializeFromStream(std::stringstream& ss); // Десериализация из файла

    void setBrand(const std::string& b) { brand = b; }
    void setModel(const std::string& m) { model = m; }
    void setEngineVolume(double v) { engineVolume = v; }
    void setColor(const std::string& c) { color = c; }
    void setTransmission(const std::string& t) { transmission = t; }

    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    double getEngineVolume() const { return engineVolume; }
    std::string getColor() const { return color; }
    std::string getTransmission() const { return transmission; }
};

#endif