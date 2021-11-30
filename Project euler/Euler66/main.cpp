#include <iostream>
#include <list>
#include <math.h>

using namespace std;

int main(){
  __int64 maxk=100000;
  for(__int64 y=33; y<34; y++){
    __int64 k=y*y;
    if(y%2==0)
      k=k/2;
    cout << endl;
    cout << "y: " << y << endl;
    cout << "k: " << k << endl;

    for(__int64 x=2;x<maxk;x++){
      if((x*x-1)%(y*y)==0){
        if(!((x-1)%k==0 || (x+1)%k==0)){
          cout << x << endl;
          //x=maxk;
        }
      }
    }
  }
  return 0;
}
/*int main()
{
  __int64 maxX = 0;
  __int64 maxD = 0;
  list<int> dList;/* = {
    109,
    157,
    181,
    193,
    211,
    214,
    241,
    271,
    277,
    281,
    298,
    301,
    309,
    313,
    317,
    331,
    334,
    337,
    358,
    379,
    382,
    394,
    397,
    409,
    412,
    421,
    433,
    436,
    449,
    454,
    457,
    461,
    463,
    478,
    481,
    487,
    491,
    493,
    501,
    508,
    509,
    517,
    521,
    523,
    526,
    541,
    547,
    553,
    554,
    556,
    565,
    569,
    571,
    581,
    586,
    589,
    593,
    597,
    599,
    601,
    604,
    607,
    613,
    614,
    617,
    619,
    628,
    631,
    634,
    637,
    641,
    643,
    649,
    652,
    653,
    661,
    669,
    673,
    681,
    685,
    691,
    694,
    709,
    716,
    718,
    719,
    721,
    724,
    739,
    746,
    749,
    751,
    753,
    757,
    764,
    766,
    769,
    772,
    773,
    778,
    789,
    796,
    797,
    801,
    809,
    811,
    814,
    821,
    823,
    826,
    829,
    844,
    849,
    853,
    856,
    857,
    859,
    862,
    865,
    869,
    877,
    881,
    883,
    886,
    889,
    907,
    911,
    913,
    919,
    921,
    922,
    926,
    929,
    937,
    941,
    946,
    949,
    953,
    956,
    958,
    964,
    967,
    970,
    971,
    974,
    977,
    981,
    989,
    991};*/
/*  list<__int64> maxedD;
  for(int i=1; i<=1000; i++)
    dList.push_back(i);

  for(list<int>::iterator d=dList.begin(); d != dList.end(); d++){
    for(int i=1; i*i<=*d; i++){
      if(i*i == *d){
        cout << "Skipping d=" << *d << endl;
        d++;
      }
    }
    __int64 dx = 1;
    __int64 dy = (*d);
    __int64 dyJump = (*d)*2;
    __int64 diff = dx-dy;
    int n = (int)sqrt(*d);
    //int n2 = n*n;
    //int nx2 = n*2;
    while(diff != 1){
      if(diff<1){   //Big jump, i dont know why n=sqrt(d), but it turns out to be true on test.
        //sum=n*dx+((2n-2)/2+2)*n
        //sum=n*dx+n^2-n+2n = n*(dx+1)+n^2
        diff += (n*(dx+1)+n*n);
        dx += (n*2);
      }
      while(diff<1){
        dx += 2;
        diff += dx;
      }
      if(diff>1){
        dy += dyJump;
        diff -= dy;
      }
      if(dx>10000000000){
        diff = 1;
        maxedD.push_back(*d);
      }
    }
    if(dx>maxX){
      maxX = dx;
      maxD = *d;
    }
    cout << *d << ": " << (dx-1)/2+1 << ": " << (dy-1)/dyJump+1 << endl;
  }
  cout << "Maximum: " << maxD << ", " << maxX << endl;
  cout << "Maxed ds: " << endl;
  for(list<__int64>::iterator it=maxedD.begin(); it!=maxedD.end(); it++)
    cout << *it << endl;
  return 0;
}*/
