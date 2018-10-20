#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
using namespace std;

class Shape
{
protected:
    int centerX;
    int centerY;
    string  name;
public:
    Shape( int newCenterX, int newCenterY, string  newName)
        : centerX(newCenterX), centerY(newCenterY), name(newName)
    {
    }
    virtual double area() = 0;
    virtual void draw() = 0;
    virtual ~Shape()
    {
    }

};
#endif
