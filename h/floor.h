#ifndef FLOOR_H
#define FLOOR_H

#include <iostream>
#include <string>
#include <iomanip>
#include <memory>
#include <stdarg.h>
#include "classroom.h"

class Floor
{
private:
    size_t nos{};                  // Number of all seats in the floor
    size_t no_of_classes{};        // Number of classes in the floor
    double avgtemperature{};       // Average temperature of all classes
    std::string name{};            // Name of the Floor
    std::shared_ptr<Classroom> pc; // pointer to one of the classes in the floor

public:
    Floor(const char *name, std::shared_ptr<Classroom> pc); // Constructor
    Floor(const char *name, size_t numOfInputs, ...);       // Constructor
    size_t noOfClasses();                                   // Number of classes in the floor
    void show() const;                                      // Show floor information for user
    std::shared_ptr<Classroom> operator[](int i) const;     // Defining [] operator functionality
    bool moveSeats(int source, int dest, size_t no);        // source and dest are indices of classrooms
    size_t noOfSeats(int i);                                // No of seats of the i-th class starting from pc
    size_t noOfSeats();                                     // No of seats of the whole floor
    double getTemperature();                                // Average of temperature of all the classes
    void setPointer(std::shared_ptr<Classroom> a) const;    // Sets the pc to another class in the floor
};

#endif