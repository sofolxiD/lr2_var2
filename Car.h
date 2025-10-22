#ifndef CAR_H
#define CAR_H

#include "Base.h"

class Car : public Base {
private:
    std::string brand;
    std::string model;
    double engineVolume;
    std::string color;
    std::string transmission; // e.g., manual, automatic
public:
    Car();
    Car(const std::string& brand, const std::string& model, double engineVolume,
        const std::string& color, const std::string& transmission);
    Car(const Car& other);
    Car& operator=(const Car& other);
    ~Car();

    Base* clone() const override;
    void inputFromConsole() override;
    void print(std::ostream& os) const override;
    std::string serialize() const override;

    // For factory: read from stream tokens separated by '|'
    void deserializeFromStream(std::stringstream& ss);
};

#endif // CAR_H
