#include "Car.h"
#include <iostream>
#include <sstream>

Car::Car() : brand(""), model(""), engineVolume(0.0), color(""), transmission("") {
    std::cout << "Вызов конструктора по умолчанию [Car]\n";
}

Car::Car(const std::string& brand_, const std::string& model_, double engineVolume_,
         const std::string& color_, const std::string& transmission_)
    : brand(brand_), model(model_), engineVolume(engineVolume_),
      color(color_), transmission(transmission_) {
    std::cout << "Вызов параметризованного конструктора [Car] " << brand << " " << model << "\n";
}

Car::Car(const Car& other)
    : Base(other), brand(other.brand), model(other.model),
      engineVolume(other.engineVolume), color(other.color), transmission(other.transmission) {
    std::cout << "Вызов конструктора копирования [Car]\n";
}

Car& Car::operator=(const Car& other) {
    if (this != &other) {
        brand = other.brand;
        model = other.model;
        engineVolume = other.engineVolume;
        color = other.color;
        transmission = other.transmission;
    }
    std::cout << "Вызван оператор присваивания [Car]\n";
    return *this;
}

Car::~Car() {
    std::cout << "Вызван деструктор [Car] " << brand << " " << model << "\n";
}

Base* Car::clone() const {
    return new Car(*this);
}

void Car::inputFromConsole() {
    std::cout << "Введите марку: "; std::getline(std::cin, brand);
    std::cout << "Введите модель: "; std::getline(std::cin, model);
    std::cout << "Введите объем двигателя: "; std::string tmp; std::getline(std::cin, tmp); engineVolume = atof(tmp.c_str());
    std::cout << "Введите цвет: "; std::getline(std::cin, color);
    std::cout << "Введите тип КПП: "; std::getline(std::cin, transmission);
}

void Car::print(std::ostream& os) const {
    os << "[Car] Mарка: " << brand << ", Модель: " << model << ", Объем двигателя: " << engineVolume << "L" << ", Цвет: " << color << ", КПП: " << transmission << "\n";
}

std::string Car::serialize() const {
    std::stringstream ss;
    ss << "C|" << brand << "|" << model << "|" << engineVolume << "|" << color << "|" << transmission;
    return ss.str();
}

void Car::deserializeFromStream(std::stringstream& ss) {
    std::string token;
    // brand
    if (!std::getline(ss, brand, '|')) brand = "";
    // model
    if (!std::getline(ss, model, '|')) model = "";
    // engineVolume
    if (!std::getline(ss, token, '|')) token = "0";
    engineVolume = atof(token.c_str());
    // color
    if (!std::getline(ss, color, '|')) color = "";
    // transmission - remainder (no more '|')
    if (!std::getline(ss, transmission)) transmission = "";
}
