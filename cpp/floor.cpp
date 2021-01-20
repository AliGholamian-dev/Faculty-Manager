#include "floor.h"

/*
Floor: Class Constructor
Input: name-> Floor name , pc -> pointer to one of the classes in the floor
Output: Void
*/
Floor::Floor(const char *name, std::shared_ptr<Classroom> pc) : no_of_classes{1}
{
    this->name = name; // Updating name
    this->pc = pc;     // Updating pointer to one of the classes in the floor
    no_of_classes = 1; // Updating number of classes in the floor
    // Counting number of classes in the floor
    std::shared_ptr<Classroom> ithClass(this->pc->getRight()); // Start from class to the right
    while (this->pc != ithClass)                               // Count till reach first class again
    {
        ithClass = ithClass->getRight(); // Moving to right class
        no_of_classes++;                 // Increase number of classes in the floor
    }
    nos = this->noOfSeats(); // Updating number of all seats in the floor
    this->getTemperature();  // Updating average temperature of all classes in the floor
}

/*
Floor: Class Constructor(second form)
Input: name-> Floor name , numOfInputs -> number of classes in the input
... -> unknown number of classes
Output: Void
*/
Floor::Floor(const char *name, size_t numOfInputs, ...)
{
    this->name = name;           // Update Floor name
    no_of_classes = numOfInputs; // Number of classes is equal to input

    // An Array of smart pointers to input classes
    std::shared_ptr<Classroom> pc_multiple[numOfInputs];
    // Process of recieving unknown number of inputs
    va_list valist;
    va_start(valist, numOfInputs); // A list of inputs
    for (size_t i = 0; i < numOfInputs; i++)
        pc_multiple[i] = va_arg(valist, std::shared_ptr<Classroom>); // recieve all of inputs
    va_end(valist);

    // Process of defining of each class neighbors (Right an left classes)
    // First class is an exception
    pc_multiple[0]->setLeft(pc_multiple[numOfInputs - 1]);
    pc_multiple[numOfInputs - 1]->setRight(pc_multiple[0]);
    for (size_t i = 1; i < numOfInputs; i++)
    {
        pc_multiple[i]->setLeft(pc_multiple[i - 1]);
        pc_multiple[i - 1]->setRight(pc_multiple[i]);
    }

    this->pc = pc_multiple[0]; //  first class as main pointer
    nos = this->noOfSeats();   // Updating number of all seats in the floor
    this->getTemperature();    // Updating average temperature of all classes in the floor
}

/*
noOfClasses: returns number of classes in the floor
Input: void
Output: no_of_classes -> number of classes in the floor
*/
size_t Floor::noOfClasses()
{
    return no_of_classes;
}

/*
show: show floor information for user
Input: void
Output: void
*/
void Floor::show() const
{
    std::shared_ptr<Classroom> ithClass(this->pc);

    std::cout << "Floor: " << this->name << std::endl;
    std::cout << "         Average temperature: " << std::right << std::setprecision(4) << std::setw(6)
              << this->avgtemperature << std::endl;
    std::cout << "         No of seats: " << std::right << std::setw(3)
              << nos << std::endl;
    std::cout << "         No of classes: " << std::right << std::setw(3)
              << this->no_of_classes << std::endl;
    // Information of each class
    for (size_t opCount = 0; opCount < this->no_of_classes; opCount++)
    {
        std::cout << "         ";
        ithClass->show();
        ithClass = ithClass->getRight();
    }
}

/*
operator[]: defining [] operator functionality
Input: i -> i-th class of the floor, starting from the **pc**
Output: ithClass -> shared pointer to the i-th class of the floor, starting from the **pc**
*/
std::shared_ptr<Classroom> Floor::operator[](int i) const
{
    std::shared_ptr<Classroom> ithClass(this->pc); // Start from main class
    //Moving right or left till reach i
    for (size_t opCount = 0; opCount < std::abs(i); opCount++)
    {
        if (i < 0) // move left in case **i** is negetive
            ithClass = ithClass->getLeft();
        else // move right in case **i** is positive
            ithClass = ithClass->getRight();
    }
    return ithClass;
}

/*
moveSeats: move seats from one class to another
Input: source -> source class to trasnfer seats from
       dest -> destination class to trasnfer seats to
Output: returns true if it is possible to move seats 
        (if there is enough seats in the source), else, it returns false
*/
bool Floor::moveSeats(int source, int dest, size_t no)
{
    // A shared pointer to the source class
    std::shared_ptr<Classroom> sourceClass(this->pc);
    // A shared pointer to the destination class
    std::shared_ptr<Classroom> destClass(this->pc);

    // move till reach the source class
    for (size_t i = 0; i < std::abs(source); i++)
    {
        if (i < 0)
            sourceClass = sourceClass->getLeft();
        else
            sourceClass = sourceClass->getRight();
    }
    // move till reach the destination class
    for (size_t i = 0; i < std::abs(dest); i++)
    {
        if (i < 0)
            destClass = destClass->getLeft();
        else
            destClass = destClass->getRight();
    }

    // Checks if there is enough seats in the source
    if (sourceClass->noOfSeats() >= no)
    {
        // Move seats from source
        sourceClass->setNoOfSeats(sourceClass->noOfSeats() - no);
        // To destination
        destClass->setNoOfSeats(destClass->noOfSeats() + no);
        return true;
    }
    return false;
}

/*
noOfSeats(i): No of seats of the i-th class starting from pc
Input: i -> i-th class of the floor, starting from the **pc**
Output: No of seats of the i-th class starting from pc
*/
size_t Floor::noOfSeats(int i)
{
    std::shared_ptr<Classroom> ithClass(this->pc); // Start from main class

    // Move left or right till reach the desired class
    for (size_t opCount = 0; opCount < std::abs(i); opCount++)
    {
        if (i < 0) // Move left in case i is negative
            ithClass = ithClass->getLeft();
        else // move right in case i is positive
            ithClass = ithClass->getRight();
    }
    return ithClass->noOfSeats();
}

/*
noOfSeats: No of all seats in the floor
Input: void
Output: No of all seats in the floor
*/
size_t Floor::noOfSeats()
{
    size_t sumOfSeats{0};
    std::shared_ptr<Classroom> ithClass(this->pc); // Start from main class

    //sumation on all classes seats
    for (size_t opCount = 0; opCount < this->no_of_classes; opCount++)
    {
        sumOfSeats += ithClass->noOfSeats();
        ithClass = ithClass->getRight(); // Move to next class
    }
    return sumOfSeats;
}

/*
getTemperature: Updating average temperature of all classes in the floor
Input: void
Output: avgtemperature -> average temperature of all classes in the floor
*/
double Floor::getTemperature()
{
    this->avgtemperature = 0;
    std::shared_ptr<Classroom> ithClass(this->pc); // Start from main class
    //sumation on all classes temperatures
    for (size_t opCount = 0; opCount < this->no_of_classes; opCount++)
    {
        this->avgtemperature += ithClass->getTemperature();
        ithClass = ithClass->getRight(); // Move to next class
    }
    // Calculate mean temperature
    this->avgtemperature /= this->no_of_classes;
    return this->avgtemperature;
}

/*
setPointer: Sets the pc to another class in the floor
Input: a -> pointer to the desired class
Output: void
*/
void Floor::setPointer(std::shared_ptr<Classroom> a) const
{
    *pc = *a;
}