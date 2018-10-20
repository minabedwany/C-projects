#ifndef SQUARE_H
#define SQUARE_H
#include "Rectangle.h"
#include <iostream>
using namespace std;

class Square : public Rectangle
{
public:
    Square( int newCenterX, int newCenterY, string newName, double newSide)
        : Rectangle(newCenterX, newCenterY, newName, newSide, newSide)
    {
    }

};
#endif
