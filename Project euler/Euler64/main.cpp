#include <iostream>
#include "RootFraction.h"

using namespace std;

int main()
{
    RootFraction r;
    int count = 0;
    for(int i=2; i<10000; i++)
      if(r.getPeriod(i)%2 == 1)
        count++;
    cout << "Count: " << count;
    return 0;
}
