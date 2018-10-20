#include "Shape.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Picture.h"
#include <iostream>
using namespace std;

int main()
{
    Picture p;
    p.add( new Triangle(0,0,"FirstString",5,5));
    p.add( new Triangle(0,0,"SecondTriangle",3,4));

    p.add( new Circle(0,0,"FirstCircle", 5));
    p.add( new Circle(0,0,"SecondCircle", 10));

    p.add( new Square(0,0,"FirstSquare",5));
    p.add( new Square(0,0,"SecondSquare",10));

    p.add( new Rectangle(0,0,"FirstRectangle",8,4));
    p.add( new Rectangle(0,0,"SecondRectangle",4,8));

    p.drawAll();
    cout<<"Total area = " << p.totalArea() <<endl;
    cout<<endl;

    return 0;
}
