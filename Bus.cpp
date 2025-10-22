#include "Bus.h"
#include <iostream>
#include <sstream>

Bus::Bus() : brand(""), model(""), seated(0), totalSeats(0), destination("") {
    std::cout << "[Bus] default constructor called\n";
}

Bus::Bus(const std::string& brand_, const std::string& model_, int seated_,
         int totalSeats_, const std::string& destination_)
    : brand(brand_), model(model_), seated(seated_), totalSeats(totalSeats_), destination(destination_) {
    std::cout << "[Bus] parameterized constructor called for " << brand << " " << model << "\n";
}

Bus::Bus(const Bus& other)
    : Base(other), brand(other.brand), model(other.model),
      seated(other.seated), totalSeats(other.totalSeats), destination(other.destination) {
    std::cout << "[Bus] copy constructor called\n";
}

Bus& Bus::operator=(const Bus& other) {
    if (this != &other) {
        brand = other.brand;
        model = other.model;
        seated = other.seated;
        totalSeats = other.totalSeats;
        destination = other.destination;
    }
    std::cout << "[Bus] assignment operator called\n";
    return *this;
}

Bus::~Bus() {
    std::cout << "[Bus] destructor called for " << brand << " " << model << "\n";
}

Base* Bus::clone() const {
    return new Bus(*this);
}

void Bus::inputFromConsole() {
    std::cout << "Enter brand: "; std::getline(std::cin, brand);
    std::cout << "Enter model: "; std::getline(std::cin, model);
    std::cout << "Enter number of seated passengers: "; std::string tmp; std::getline(std::cin, tmp); seated = atoi(tmp.c_str());
    std::cout << "Enter total passenger capacity: "; std::getline(std::cin, tmp); totalSeats = atoi(tmp.c_str());
    std::cout << "Enter destination: "; std::getline(std::cin, destination);
}

void Bus::print(std::ostream& os) const {
    os << "[Bus] Brand: " << brand << ", Model: " << model
       << ", Seated: " << seated << ", Total seats: " << totalSeats
       << ", Destination: " << destination << "\n";
}

std::string Bus::serialize() const {
    std::stringstream ss;
    ss << "B|" << brand << "|" << model << "|" << seated << "|" << totalSeats << "|" << destination;
    return ss.str();
}

void Bus::deserializeFromStream(std::stringstream& ss) {
    std::string token;
    if (!std::getline(ss, brand, '|')) brand = "";
    if (!std::getline(ss, model, '|')) model = "";
    if (!std::getline(ss, token, '|')) token = "0";
    seated = atoi(token.c_str());
    if (!std::getline(ss, token, '|')) token = "0";
    totalSeats = atoi(token.c_str());
    if (!std::getline(ss, destination)) destination = "";
}
