#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
#include <iostream>
using namespace std;

class Circle : public Shape
{
private:
    const double PI = 3.14159;
protected:
    double radius;
public:
    Circle( int newCenterX, int newCenterY, string newName, double newRadius)
        : Shape(newCenterX, newCenterY, newName), radius(newRadius)
    {
    }

    double area()
    {
        return PI * radius * radius;
    }

    void draw()
    {
        double inner_radius = radius-0.2;
        double outer_radius = radius+0.2;

        for (double y=radius; y>= -radius; --y)
        {
          for (double x= -radius; x<outer_radius; x+=0.5)
          {
            double squared = x*x + y*y;
            if (squared >= inner_radius*inner_radius && squared <= outer_radius*outer_radius)
                cout << "*";
            else
                cout << " ";
          }
          cout<<endl;
        }
        cout<<endl;
    }


};
#endif
