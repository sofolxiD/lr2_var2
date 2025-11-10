#include "Car.h"
#include <iostream>
#include <sstream>
#include <conio.h>
#include <windows.h>

Car::Car() : brand(""), model(""), engineVolume(0.0), color(""), transmission("") {
    std::cout << "Вызван конструктор по умолчанию [Car]\n";
}

Car::Car(const std::string& brand_, const std::string& model_, double engineVolume_,
    const std::string& color_, const std::string& transmission_)
    : brand(brand_), model(model_), engineVolume(engineVolume_),
    color(color_), transmission(transmission_) {
    std::cout << "Вызван параметризованный конструктор [Car] " << brand << " " << model << "\n";
}

Car::Car(const Car& other)
    : Base(other), brand(other.brand), model(other.model), engineVolume(other.engineVolume), color(other.color), transmission(other.transmission) {
    std::cout << "Вызван конструктор копирования [Car]\n";
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
    std::cout << "Введите марку: ";
    std::getline(std::cin, brand);

    std::cout << "Введите модель: ";
    std::getline(std::cin, model);

    std::cout << "Введите объем двигателя: ";
    std::string tmp;
    std::getline(std::cin, tmp);
    engineVolume = atof(tmp.c_str());

    std::cout << "Введите цвет: ";
    std::getline(std::cin, color);

    const char* KPP[] = {
        "Manual",
        "Automatic",
        "AMT",
        "CVT"
    };  //(Механика, Автомат, Робот, Вариатор)

    int KPP_index = 0;
    char key;

    while (true) {
        system("cls");
        std::cout << "--- Добавление автомобиля ---\n";
        std::cout << "Выберите тип КПП:\n";
        for (int i = 0; i < 4; i++) {
            if (i == KPP_index)
                std::cout << "-> " << KPP[i] << "\n";
            else
                std::cout << "   " << KPP[i] << "\n";
        }

        key = _getch();
        if (key == 72)
            KPP_index = (KPP_index == 0) ? 3 : KPP_index - 1;
        else if (key == 80)
            KPP_index = (KPP_index == 3) ? 0 : KPP_index + 1;
        else if (key == 13) break;
    }

    transmission = KPP[KPP_index];
    system("cls");

    std::cout << "--- Добавление автомобиля ---\n";
    std::cout << "Введите марку: " << brand << "\n";
    std::cout << "Введите модель: " << model << "\n";
    std::cout << "Введите объем двигателя: " << engineVolume << "\n";
    std::cout << "Введите цвет: " << color << "\n";
    std::cout << "Выбран тип КПП: " << transmission << "\n\n";
}

void Car::print(std::ostream& os) const {
    os << "(Car) Марка: " << brand
        << ", Модель: " << model
        << ", Объем двигателя: " << engineVolume
        << ", Цвет: " << color
        << ", КПП: " << transmission << "\n";
}

std::string Car::serialize() const {
    std::stringstream ss;
    ss << "Car," << brand << "," << model << "," << engineVolume << "," << color << "," << transmission;
    return ss.str();
}

void Car::deserializeFromStream(std::stringstream& ss) {
    std::string token;
    if (!std::getline(ss, brand, ',')) brand = "";
    if (!std::getline(ss, model, ',')) model = "";
    if (!std::getline(ss, token, ',')) token = "0";
    engineVolume = atof(token.c_str());
    if (!std::getline(ss, color, ',')) color = "";
    if (!std::getline(ss, transmission)) transmission = "";
}