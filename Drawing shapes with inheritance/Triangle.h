#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"
#include<cmath>
#include <iostream>
using namespace std;

class Triangle: public Shape
{
protected:
    double base;
    double height;

public:
    Triangle(int newCenterX, int newCenterY, string  newName, double newBase, 
    double newHeight)
        : Shape(newCenterX, newCenterY, newName), base(newBase), height(newHeight)
    {
    }

    double area()
    {
        return base * height / 2.0;
    }

    void draw()
    {  
        for (double row=1; row<=height; ++row)
        {
            for (double column=1; column<base*(row/height); ++column)
                cout<<"* ";
            cout<<endl;
        }
        if (base<=height)
        {
            for (int bottom=1; bottom<=base; ++bottom)
                cout<<"* ";
        cout<<"\n"<<endl;
        }
    }
};
#endif
