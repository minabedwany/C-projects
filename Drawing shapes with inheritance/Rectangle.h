#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
#include <iostream>
using namespace std; 

class Rectangle : public Shape
{
protected:
    double length;
    double height;

public:
    Rectangle( int newCenterX, int newCenterY, string newName,double newLength, 
    double newHeight)
        : Shape(newCenterX, newCenterY, newName), length(newLength), height(newHeight)
    {
    }

    double area()
    {
        return length*height;
    }

    void draw()
    {
        for(int top=1; top<=length; ++top)
            cout << "* ";
        cout << endl;

        for(int middle=1; middle<=height-2; ++middle)
        {
            cout<<"* ";
            for(int space=1; space<=length-2; ++space)
                cout<<"  ";
            cout << "*" << endl;
        }
        
        for(int bottom=1; bottom<=length; ++bottom)
            cout<<"* ";
        cout<<"\n"<<endl;
    }

};
#endif
