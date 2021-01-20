#include "classroom.h"

size_t Classroom::no{0}; //Static variable for counting number of objects created so far

/*
Classroom: Class Constructor
Input: name-> Class name , seats -> anumber of seats in the class
Output: Void
*/
Classroom::Classroom(const char *_name, size_t _seats) : name{_name}, seats{_seats} // Initialize class name and seast
{
    no++;                   //increase number of objects created so far
    this->getTemperature(); //update temperature for first time
}

/*
Classroom: Class Destructor
Input: void
Output: Void
*/
Classroom::~Classroom()
{
    no--; //decrease number of objects created so far
}

/*
getRight: returns a pointer to the class to the right of this class
Input: void
Output: right -> a pointer to the class to the right of this class
*/
std::shared_ptr<Classroom> Classroom::getRight()
{
    return right; // A smart pointer to the class to the right of this class
}

/*
getLeft: returns a pointer to the class to the left of this class
Input: void
Output: left -> a pointer to the class to the left of this class
*/
std::shared_ptr<Classroom> Classroom::getLeft()
{
    return left; // A smart pointer to the class to the left of this class
}

/*
setRight: sets a pointer to the class to the right of this class
Input: r -> a pointer to the class to the right of this class
Output: void
*/
void Classroom::setRight(std::shared_ptr<Classroom> r)
{
    this->right = r;
}

/*
setLeft: sets a pointer to the class to the left of this class
Input: l -> a pointer to the class to the left of this class
Output: void
*/
void Classroom::setLeft(std::shared_ptr<Classroom> l)
{
    this->left = l;
}

/*
getTemperature: returns temperature of the class(in this case randomly generated)
Input: void
Output: temperature -> a random number of Gaussian distribution with the mean of 27 and standard deviation of 3
*/
double Classroom::getTemperature()
{
    std::random_device rd{};
    std::mt19937 gen{rd()};                                   //random number for Gaussian distribution
    std::normal_distribution<double> distribution(27.0, 3.0); //Gaussian distribution
    this->temperature = distribution(gen);                    ///updating temperature
    return this->temperature;
}

/*
noOfSeats: returns number of seats in the class
Input: void
Output: seats -> number of seats in the class
*/
size_t Classroom::noOfSeats()
{
    return this->seats;
}

/*
setNoOfSeats: sets number of seats in the class
Input: seats -> number of seats in the class 
Output: void
*/
void Classroom::setNoOfSeats(size_t seats)
{
    this->seats = seats;
}

/*
show: show class information for user
Input: void 
Output: void
*/
void Classroom::show() const
{
    std::cout << std::right << "Class " << this->name << ", Seats: " << std::setw(3)
              << this->seats << ", Temperature: " << std::setprecision(4) << std::setw(6)
              << this->temperature << std::endl;
}