#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H
#include "Base.h"
#include <string>

class Motorcycle : public Base
{
public:
    std::string brand;
    std::string model;
    double engineVolume;
    int power;
    std::string terrain;

    Motorcycle();
    Motorcycle(const std::string& brand_, const std::string& model_, double engineVolume_, int power_, const std::string& terrain_);
    Motorcycle(const Motorcycle& other);
    Motorcycle& operator=(const Motorcycle& other);
    ~Motorcycle();

    Base* clone() const override;
    void inputFromConsole() override;
    void print(std::ostream& os) const override;
    std::string serialize() const override;
    void deserializeFromStream(std::stringstream& ss);
};

#endif
