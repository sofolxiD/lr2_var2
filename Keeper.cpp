#include "Keeper.h"
#include <iostream>
#include <sstream>

Keeper::Keeper(int initialCapacity) : items(nullptr), count(0), capacity(initialCapacity) {
    if (capacity <= 0) capacity = 4;
    items = new Base*[capacity];
    for (int i = 0; i < capacity; ++i) items[i] = nullptr;
    std::cout << "[Keeper] created with capacity " << capacity << "\n";
}

Keeper::Keeper(const Keeper& other) : items(nullptr), count(other.count), capacity(other.capacity) {
    items = new Base*[capacity];
    for (int i = 0; i < count; ++i) {
        items[i] = other.items[i] ? other.items[i]->clone() : nullptr;
    }
    for (int i = count; i < capacity; ++i) items[i] = nullptr;
    std::cout << "[Keeper] copy constructor called\n";
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        clear();
        delete [] items;
        capacity = other.capacity;
        count = other.count;
        items = new Base*[capacity];
        for (int i = 0; i < count; ++i) {
            items[i] = other.items[i] ? other.items[i]->clone() : nullptr;
        }
        for (int i = count; i < capacity; ++i) items[i] = nullptr;
    }
    std::cout << "[Keeper] assignment operator called\n";
    return *this;
}

Keeper::~Keeper() {
    clear();
    delete [] items;
    std::cout << "[Keeper] destructor called\n";
}

void Keeper::resizeUp() {
    int newCap = capacity * 2;
    Base** newItems = new Base*[newCap];
    for (int i = 0; i < newCap; ++i) newItems[i] = nullptr;
    for (int i = 0; i < count; ++i) newItems[i] = items[i];
    delete [] items;
    items = newItems;
    capacity = newCap;
    std::cout << "[Keeper] resized to capacity " << capacity << "\n";
}

void Keeper::add(Base* obj) {
    if (!obj) throw GarageException("Null pointer passed to add()");
    if (count >= capacity) resizeUp();
    items[count++] = obj;
    std::cout << "[Keeper] object added. New size: " << count << "\n";
}

void Keeper::removeAt(int index) {
    if (index < 0 || index >= count) throw GarageException("Index out of range in removeAt");
    delete items[index];
    for (int i = index; i < count - 1; ++i) items[i] = items[i+1];
    items[count-1] = nullptr;
    --count;
    std::cout << "[Keeper] object removed at index " << index << ". New size: " << count << "\n";
}

void Keeper::showAll() const {
    std::cout << "Keeper contents (count = " << count << "):\n";
    for (int i = 0; i < count; ++i) {
        std::cout << i << ": " << *items[i];
    }
}

Base* Keeper::getAt(int index) const {
    if (index < 0 || index >= count) return nullptr;
    return items[index];
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename.c_str());
    if (!ofs) throw GarageException("Failed to open file for writing: " + filename);
    for (int i = 0; i < count; ++i) {
        std::string line = items[i]->serialize();
        ofs << line << "\n";
    }
    ofs.close();
    std::cout << "[Keeper] saved " << count << " items to file: " << filename << "\n";
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename.c_str());
    if (!ifs) throw GarageException("Failed to open file for reading: " + filename);
    clear();
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        Base* obj = Base::createFromSerialized(line);
        if (obj) add(obj);
    }
    ifs.close();
    std::cout << "[Keeper] loaded items from file: " << filename << "\n";
}

void Keeper::clear() {
    for (int i = 0; i < count; ++i) {
        delete items[i];
        items[i] = nullptr;
    }
    count = 0;
    std::cout << "[Keeper] cleared all items\n";
}
