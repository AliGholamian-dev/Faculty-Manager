#include "aphw2.h"

// Show classroom information for user
void show(Classroom showSingleClass)
{
    showSingleClass.show();
}

// Show floor information for user
void show(Floor showFloor)
{
    showFloor.show();
}

// Show class information for user(shared pointer version of class)
void show(std::shared_ptr<Classroom> showClass)
{
    showClass->show();
}