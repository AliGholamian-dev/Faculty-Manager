#ifndef CLASSROOM_H
#define CLASSROOM_H

#include <iostream>
#include <string>
#include <iomanip>
#include <memory>
#include <random>

class Classroom
{
private:
    std::string name{};               //Name of the class
    size_t seats{20};                 //  No of seats of the class
    std::shared_ptr<Classroom> left;  // A smart pointer to the class to the left of this class
    std::shared_ptr<Classroom> right; // A smart pointer to the class to the right of this class
    double temperature{27};

public:
    static size_t no;

    Classroom(const char *_name, size_t _seats);
    ~Classroom();
    std::shared_ptr<Classroom> getRight();
    std::shared_ptr<Classroom> getLeft();
    void setRight(std::shared_ptr<Classroom> r);
    void setLeft(std::shared_ptr<Classroom> l);
    double getTemperature();
    size_t noOfSeats();
    void setNoOfSeats(size_t seats);
    void show() const;
};

#endif