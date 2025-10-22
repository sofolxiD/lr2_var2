#include <iostream>
#include <string>
#include "Keeper.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Bus.h"

void print_Menu() {
    std::cout << "\n--- Garage Menu ---\n";
    std::cout << "1. Add Car\n";
    std::cout << "2. Add Motorcycle\n";
    std::cout << "3. Add Bus\n";
    std::cout << "4. Remove by index\n";
    std::cout << "5. Show all\n";
    std::cout << "6. Save to file\n";
    std::cout << "7. Load from file\n";
    std::cout << "8. Edit item (replace)\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter choice: ";
}

int main() {
    Keeper k;
    std::string input;
    bool running = true;
    while (running) {
        try {
            print_Menu();
            std::getline(std::cin, input);
            int choice = atoi(input.c_str());
            switch (choice) {
                case 1: {
                    Car* c = new Car();
                    std::cout << "Adding new Car. Fill data:\n";
                    c->inputFromConsole();
                    k.add(c);
                    break;
                }
                case 2: {
                    Motorcycle* m = new Motorcycle();
                    std::cout << "Adding new Motorcycle. Fill data:\n";
                    m->inputFromConsole();
                    k.add(m);
                    break;
                }
                case 3: {
                    Bus* b = new Bus();
                    std::cout << "Adding new Bus. Fill data:\n";
                    b->inputFromConsole();
                    k.add(b);
                    break;
                }
                case 4: {
                    std::cout << "Enter index to remove: ";
                    std::getline(std::cin, input);
                    int idx = atoi(input.c_str());
                    k.removeAt(idx);
                    break;
                }
                case 5: {
                    k.showAll();
                    break;
                }
                case 6: {
                    std::cout << "Enter filename to save to: ";
                    std::getline(std::cin, input);
                    if (input.empty()) input = "garage.txt";
                    k.saveToFile(input);
                    break;
                }
                case 7: {
                    std::cout << "Enter filename to load from: ";
                    std::getline(std::cin, input);
                    if (input.empty()) input = "garage.txt";
                    k.loadFromFile(input);
                    break;
                }
                case 8: {
                    std::cout << "Enter index to replace/edit: ";
                    std::getline(std::cin, input);
                    int idx = atoi(input.c_str());
                    Base* old = k.getAt(idx);
                    if (!old) {
                        std::cout << "No item at that index.\n";
                        break;
                    }
                    std::cout << "Current item:\n" << *old;
                    std::cout << "Choose new type (1-Car,2-Motorcycle,3-Bus): ";
                    std::getline(std::cin, input);
                    int t = atoi(input.c_str());
                    Base* newObj = nullptr;
                    if (t == 1) {
                        Car* c = new Car();
                        c->inputFromConsole();
                        newObj = c;
                    } else if (t == 2) {
                        Motorcycle* m = new Motorcycle();
                        m->inputFromConsole();
                        newObj = m;
                    } else if (t == 3) {
                        Bus* b = new Bus();
                        b->inputFromConsole();
                        newObj = b;
                    } else {
                        std::cout << "Invalid type\n";
                        break;
                    }

                    k.removeAt(idx);

                    k.add(newObj);

                    int last = k.size() - 1;
                    if (idx != last) {

                        Base* a = k.getAt(idx);
                        Base* bptr = k.getAt(last);
                        //k.items[idx] = bptr;
                        Keeper temp = k; 
                        k.clear();
                        for (int i = 0; i < temp.size(); i++) {
                            if (i == idx) {
                                k.add(bptr);
                            } else if (i == last) {
                                k.add(a);
                            } else {
                                k.add(temp.getAt(i));
                            }
                        }
                        std::cout << "Note: item replaced (old removed) and new item added to the end of list.\n";
                    }
                    break;
                }
                case 9: {
                    running = false;
                    break;
                }
                default:
                    std::cout << "Unknown choice\n";
            }
        } catch (const GarageException& ge) {
            std::cout << "Error: " << ge.what() << "\n";
        } catch (const std::exception& ex) {
            std::cout << "Std exception: " << ex.what() << "\n";
        } catch (...) {
            std::cout << "Unknown error occurred\n";
        }
    }

    std::cout << "Exiting program. Goodbye!\n";
    return 0;
}
