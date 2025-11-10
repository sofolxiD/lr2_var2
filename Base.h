#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <string>
#include <sstream>
#include <exception>

class Base {
public:
    Base();
    Base(const Base& other);
    virtual ~Base();

    virtual Base* clone() const = 0;
    virtual void inputFromConsole();
    virtual void print(std::ostream& os) const = 0;
    virtual std::string serialize() const = 0;
    static Base* createFromSerialized(const std::string& line);

    friend std::ostream& operator<<(std::ostream& os, const Base& b) {
        b.print(os);
        return os;
    }
};

class GarageException : public std::exception {
    std::string msg;
public:
    GarageException(const std::string& m): msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

#endif
