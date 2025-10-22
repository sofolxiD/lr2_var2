#include "Motorcycle.h"
#include <iostream>
#include <sstream>

Motorcycle::Motorcycle() : brand(""), model(""), engineVolume(0.0), power(0.0), terrain("") {
    std::cout << "[Motorcycle] default constructor called\n";
}

Motorcycle::Motorcycle(const std::string& brand_, const std::string& model_, double engineVolume_,
                       double power_, const std::string& terrain_)
    : brand(brand_), model(model_), engineVolume(engineVolume_), power(power_), terrain(terrain_) {
    std::cout << "[Motorcycle] parameterized constructor called for " << brand << " " << model << "\n";
}

Motorcycle::Motorcycle(const Motorcycle& other)
    : Base(other), brand(other.brand), model(other.model),
      engineVolume(other.engineVolume), power(other.power), terrain(other.terrain) {
    std::cout << "[Motorcycle] copy constructor called\n";
}

Motorcycle& Motorcycle::operator=(const Motorcycle& other) {
    if (this != &other) {
        brand = other.brand;
        model = other.model;
        engineVolume = other.engineVolume;
        power = other.power;
        terrain = other.terrain;
    }
    std::cout << "[Motorcycle] assignment operator called\n";
    return *this;
}

Motorcycle::~Motorcycle() {
    std::cout << "[Motorcycle] destructor called for " << brand << " " << model << "\n";
}

Base* Motorcycle::clone() const {
    return new Motorcycle(*this);
}

void Motorcycle::inputFromConsole() {
    std::cout << "Enter brand: "; std::getline(std::cin, brand);
    std::cout << "Enter model: "; std::getline(std::cin, model);
    std::cout << "Enter engine volume (e.g. 0.6): "; std::string tmp; std::getline(std::cin, tmp); engineVolume = atof(tmp.c_str());
    std::cout << "Enter power (hp): "; std::getline(std::cin, tmp); power = atof(tmp.c_str());
    std::cout << "Enter terrain (on-road/off-road): "; std::getline(std::cin, terrain);
}

void Motorcycle::print(std::ostream& os) const {
    os << "[Motorcycle] Brand: " << brand << ", Model: " << model
       << ", Engine: " << engineVolume << "L, Power: " << power << "hp"
       << ", Terrain: " << terrain << "\n";
}

std::string Motorcycle::serialize() const {
    std::stringstream ss;
    ss << "M|" << brand << "|" << model << "|" << engineVolume << "|" << power << "|" << terrain;
    return ss.str();
}

void Motorcycle::deserializeFromStream(std::stringstream& ss) {
    std::string token;
    if (!std::getline(ss, brand, '|')) brand = "";
    if (!std::getline(ss, model, '|')) model = "";
    if (!std::getline(ss, token, '|')) token = "0";
    engineVolume = atof(token.c_str());
    if (!std::getline(ss, token, '|')) token = "0";
    power = atof(token.c_str());
    if (!std::getline(ss, terrain)) terrain = "";
}
