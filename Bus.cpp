#include "Bus.h"
#include <iostream>
#include <sstream>
#include <conio.h>
#include <windows.h>

Bus::Bus() : brand(""), model(""), seated(0), totalSeats(0), destination("") {
    std::cout << "Вызван конструктор по умолчанию [Bus]\n";
}

Bus::Bus(const std::string& brand_, const std::string& model_,
         int seated_, int totalSeats_, const std::string& destination_)
    : brand(brand_), model(model_), seated(seated_),
      totalSeats(totalSeats_), destination(destination_) {
    std::cout << "Вызван параметризованный конструктор [Bus] " << brand << " " << model << "\n";
}

Bus::Bus(const Bus& other)
    : Base(other), brand(other.brand), model(other.model),
      seated(other.seated), totalSeats(other.totalSeats), destination(other.destination) {
    std::cout << "Вызван конструктор копирования [Bus]\n";
}

Bus& Bus::operator=(const Bus& other) {
    if (this != &other) {
        brand = other.brand;
        model = other.model;
        seated = other.seated;
        totalSeats = other.totalSeats;
        destination = other.destination;
    }
    std::cout << "Вызван оператор присваивания [Bus]\n";
    return *this;
}

Bus::~Bus() {
    std::cout << "Вызван деструктор [Bus] " << brand << " " << model << "\n";
}

Base* Bus::clone() const {
    return new Bus(*this);
}

void Bus::inputFromConsole() {
    std::cout << "Введите марку: ";
    std::getline(std::cin, brand);

    std::cout << "Введите модель: ";
    std::getline(std::cin, model);

    std::cout << "Введите количество сидячих мест: ";
    std::string tmp;
    std::getline(std::cin, tmp);
    seated = atoi(tmp.c_str());

    std::cout << "Введите общее количество мест: ";
    std::getline(std::cin, tmp);
    totalSeats = atoi(tmp.c_str());

    std::cout << "Введите конечный пункт назначения: ";
    std::getline(std::cin, destination);
}

void Bus::print(std::ostream& os) const {
    os << "(Bus) Марка: " << brand
       << ", Модель: " << model
       << ", Сидячих мест: " << seated
       << ", Всего мест: " << totalSeats
       << ", Конечный пункт: " << destination << "\n\n";
}

std::string Bus::serialize() const {
    std::stringstream ss;
    ss << "Bus," << brand << "," << model << "," << seated << "," << totalSeats << "," << destination;
    return ss.str();
}

void Bus::deserializeFromStream(std::stringstream& ss) {
    std::string token;
    if (!std::getline(ss, brand, ',')) brand = "";
    if (!std::getline(ss, model, ',')) model = "";
    if (!std::getline(ss, token, ',')) token = "0";
    seated = atoi(token.c_str());
    if (!std::getline(ss, token, ',')) token = "0";
    totalSeats = atoi(token.c_str());
    if (!std::getline(ss, destination)) destination = "";
}
