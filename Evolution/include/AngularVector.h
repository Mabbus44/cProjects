#ifndef ANGULARVECTOR_H
#define ANGULARVECTOR_H

#include <stdint.h>

#ifndef PI
#define PI 3.14159265
#endif

class AngularVector
{
    public:
        AngularVector();
        AngularVector(double angle, double length);
        AngularVector(uint64_t x, uint64_t y);
        virtual ~AngularVector();
        AngularVector operator+(const AngularVector& other);

        double angle;                 //Angle of vector
        double length;                //Length of vector

    protected:

    private:
};

#endif // ANGULARVECTOR_H
