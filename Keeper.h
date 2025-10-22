#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include <fstream>

class Keeper {
private:
    Base** items;
    int count;
    int capacity;

    void resizeUp();
public:
    Keeper(int initialCapacity = 4);
    Keeper(const Keeper& other);
    Keeper& operator=(const Keeper& other);
    ~Keeper();

    void add(Base* obj); // takes ownership
    void removeAt(int index); // delete object at index
    void showAll() const;
    int size() const { return count; }
    Base* getAt(int index) const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    // helper to clear all
    void clear();
};

#endif // KEEPER_H
