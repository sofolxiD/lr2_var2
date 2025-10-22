#ifndef BUS_H
#define BUS_H

#include "Base.h"

class Bus : public Base {
private:
    std::string brand;
    std::string model;
    int seated;
    int totalSeats;
    std::string destination;
public:
    Bus();
    Bus(const std::string& brand, const std::string& model, int seated,
        int totalSeats, const std::string& destination);
    Bus(const Bus& other);
    Bus& operator=(const Bus& other);
    ~Bus();

    Base* clone() const override;
    void inputFromConsole() override;
    void print(std::ostream& os) const override;
    std::string serialize() const override;
    void deserializeFromStream(std::stringstream& ss);
};

#endif // BUS_H
