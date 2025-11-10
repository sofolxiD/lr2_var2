#include "Motorcycle.h"
#include <iostream>
#include <sstream>
#include <conio.h>
#include <windows.h>

Motorcycle::Motorcycle() : brand(""), model(""), engineVolume(0.0), power(0), terrain("") {
    std::cout << "Вызван конструктор по умолчанию [Motorcycle]\n";
}

Motorcycle::Motorcycle(const std::string& brand_, const std::string& model_, double engineVolume_, int power_, const std::string& terrain_): 
        brand(brand_), model(model_), engineVolume(engineVolume_), power(power_), terrain(terrain_) {
    std::cout << "Вызван параметризованный конструктор [Motorcycle] " << brand << " " << model << "\n";
}

Motorcycle::Motorcycle(const Motorcycle& other)
    : Base(other), brand(other.brand), model(other.model),
      engineVolume(other.engineVolume), power(other.power), terrain(other.terrain) {
    std::cout << "Вызван конструктор копирования [Motorcycle]\n";
}

Motorcycle& Motorcycle::operator=(const Motorcycle& other) {
    if (this != &other) {
        brand = other.brand;
        model = other.model;
        engineVolume = other.engineVolume;
        power = other.power;
        terrain = other.terrain;
    }
    std::cout << "Вызван оператор присваивания [Motorcycle]\n";
    return *this;
}

Motorcycle::~Motorcycle() {
    std::cout << "Вызван деструктор [Motorcycle] " << brand << " " << model << "\n";
}

Base* Motorcycle::clone() const {
    return new Motorcycle(*this);
}

void Motorcycle::inputFromConsole() {
    std::cout << "Введите марку: ";
    std::getline(std::cin, brand);

    std::cout << "Введите модель: ";
    std::getline(std::cin, model);

    std::cout << "Введите объем двигателя: ";
    std::string tmp;
    std::getline(std::cin, tmp);
    engineVolume = atof(tmp.c_str());

    std::cout << "Введите мощность (л.с.): ";
    std::getline(std::cin, tmp);
    power = atoi(tmp.c_str());

    std::cout << "Для какой местности мотоцикл предназначен: ";
    std::getline(std::cin, terrain);
}    


void Motorcycle::print(std::ostream& os) const {
    os  << "(Motorcycle) Марка: " << brand 
        << ", Модель: " << model
        << ", Объем двигателя: " << engineVolume 
        << "L, Мощность: " << power << "hp"
        << "hp, Местность: " << terrain << "\n\n";
}

std::string Motorcycle::serialize() const {
    std::stringstream ss;
    ss << "Motorcycle," << brand << "," << model << "," << engineVolume << "," << power << "," << terrain;
    return ss.str();
}

void Motorcycle::deserializeFromStream(std::stringstream& ss) {
    std::string token;
    if (!std::getline(ss, brand, ',')) brand = "";
    if (!std::getline(ss, model, ',')) model = "";
    if (!std::getline(ss, token, ',')) token = "0";
    engineVolume = atof(token.c_str());
    if (!std::getline(ss, token, ',')) token = "0";
    power = atoi(token.c_str());
    if (!std::getline(ss, terrain)) terrain = "";
}
