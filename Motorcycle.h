#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "Base.h"

class Motorcycle : public Base {
private:
    std::string brand;
    std::string model;
    double engineVolume;
    double power; // horsepower
    std::string terrain; // e.g., "on-road", "off-road"
public:
    Motorcycle();
    Motorcycle(const std::string& brand, const std::string& model, double engineVolume,
               double power, const std::string& terrain);
    Motorcycle(const Motorcycle& other);
    Motorcycle& operator=(const Motorcycle& other);
    ~Motorcycle();

    Base* clone() const override;
    void inputFromConsole() override;
    void print(std::ostream& os) const override;
    std::string serialize() const override;
    void deserializeFromStream(std::stringstream& ss);
};

#endif // MOTORCYCLE_H
