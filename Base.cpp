#include "Base.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Bus.h"

Base::Base() {
    std::cout << "Вызван конструктор по умолчанию [Base]\n";
}

Base::Base(const Base& other) {
    (void)other;
    std::cout << "Вызван конструктор копирования [Base]\n";
}

Base::~Base() {
    std::cout << "Вызван деструктор [Base]\n";
}

void Base::inputFromConsole() {
    // default: nothing. Derived classes override.
}

Base* Base::createFromSerialized(const std::string& line) {
    if (line.empty()) return nullptr;
    char type = line[0];
    std::string rest;
    if (line.size() >= 2 && line[1] == ',') rest = line.substr(2);
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
            throw GarageException("Error");
        }
    } catch (std::bad_alloc&) {
        throw GarageException("Ошибка выделения памяти");
    }
}
