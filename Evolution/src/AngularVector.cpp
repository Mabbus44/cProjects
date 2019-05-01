#include "AngularVector.h"
#include <math.h>

AngularVector::AngularVector()
{
    //ctor
}

AngularVector::AngularVector(double angle, double length)
{
    this->angle = angle;
    this->length = length;
}

AngularVector::AngularVector(uint64_t x, uint64_t y)
{
    length = sqrt(x*x+y*y);
    if(length != 0)
    {
        angle = acos(x/length);
        if(y<0)
            angle = 2*PI - angle;
    }
}

AngularVector::~AngularVector()
{
    //dtor
}

AngularVector AngularVector::operator+(const AngularVector& other)
{
    AngularVector newVector;
    double y = this->length * sin(this->angle) + other.length * sin(other.angle);
    double x = this->length * cos(this->angle) + other.length * cos(other.angle);
    newVector.length = sqrt(x*x+y*y);
    if(newVector.length != 0)
    {
        newVector.angle = acos(x/newVector.length);
        if(y<0)
            newVector.angle = 2*PI - newVector.angle;
    }
    else
        newVector.angle = 0;
    return newVector;
}
