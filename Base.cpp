#include "Base.h"

Base::Base() {
    std::cout << "[Base] default constructor called\n";
}

Base::Base(const Base& other) {
    (void)other;
    std::cout << "[Base] copy constructor called\n";
}

Base::~Base() {
    std::cout << "[Base] destructor called\n";
}

void Base::inputFromConsole() {
    // default: nothing. Derived classes override.
}

#include "Car.h"
#include "Motorcycle.h"
#include "Bus.h"

// Factory: create derived object from a serialized line.
// Format (we choose): TYPE|field1|field2|...
// TYPE: C - car, M - motorcycle, B - bus
Base* Base::createFromSerialized(const std::string& line) {
    if (line.empty()) return nullptr;
    char type = line[0];
    std::string rest;
    if (line.size() >= 2 && line[1] == '|') rest = line.substr(2);
    else rest = line.substr(1);

    std::stringstream ss(rest);
    std::string token;

    try {
        if (type == 'C') {
            // Car: brand|model|engineVolume|color|transmission
            Car* c = new Car();
            c->deserializeFromStream(ss);
            return c;
        } else if (type == 'M') {
            // Motorcycle: brand|model|engineVolume|power|terrain
            Motorcycle* m = new Motorcycle();
            m->deserializeFromStream(ss);
            return m;
        } else if (type == 'B') {
            // Bus: brand|model|seated|totalSeats|destination
            Bus* b = new Bus();
            b->deserializeFromStream(ss);
            return b;
        } else {
            throw GarageException("Unknown type in serialized line");
        }
    } catch (std::bad_alloc&) {
        throw GarageException("Memory allocation failed while creating object");
    }
}
