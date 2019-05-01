#include <iostream>
#include "Creature.h"
#include "AngularVector.h"

using namespace std;

int main()
{
    AngularVector a(0.0, 100.0);
    AngularVector b(PI/2, 100.0);
    AngularVector c = a+b;
    cout << "Angle: " << c.angle << endl << "Length: " << c.length;
    return 0;
}
