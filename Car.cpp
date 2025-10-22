#include "Car.h"
#include <iostream>
#include <sstream>

Car::Car() : brand(""), model(""), engineVolume(0.0), color(""), transmission("") {
    std::cout << "[Car] default constructor called\n";
}

Car::Car(const std::string& brand_, const std::string& model_, double engineVolume_,
         const std::string& color_, const std::string& transmission_)
    : brand(brand_), model(model_), engineVolume(engineVolume_),
      color(color_), transmission(transmission_) {
    std::cout << "[Car] parameterized constructor called for " << brand << " " << model << "\n";
}

Car::Car(const Car& other)
    : Base(other), brand(other.brand), model(other.model),
      engineVolume(other.engineVolume), color(other.color), transmission(other.transmission) {
    std::cout << "[Car] copy constructor called\n";
}

Car& Car::operator=(const Car& other) {
    if (this != &other) {
        brand = other.brand;
        model = other.model;
        engineVolume = other.engineVolume;
        color = other.color;
        transmission = other.transmission;
    }
    std::cout << "[Car] assignment operator called\n";
    return *this;
}

Car::~Car() {
    std::cout << "[Car] destructor called for " << brand << " " << model << "\n";
}

Base* Car::clone() const {
    return new Car(*this);
}

void Car::inputFromConsole() {
    std::cout << "Enter brand: "; std::getline(std::cin, brand);
    std::cout << "Enter model: "; std::getline(std::cin, model);
    std::cout << "Enter engine volume (e.g. 1.6): "; std::string tmp; std::getline(std::cin, tmp); engineVolume = atof(tmp.c_str());
    std::cout << "Enter color: "; std::getline(std::cin, color);
    std::cout << "Enter transmission (manual/automatic): "; std::getline(std::cin, transmission);
}

void Car::print(std::ostream& os) const {
    os << "[Car] Brand: " << brand << ", Model: " << model
       << ", Engine: " << engineVolume << "L"
       << ", Color: " << color << ", Transmission: " << transmission << "\n";
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
