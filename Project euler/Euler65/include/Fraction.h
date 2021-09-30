#ifndef FRACTION_H
#define FRACTION_H
#include "PrimeList.h"

class Fraction
{
  public:
    Fraction();
    Fraction(PrimeList* p);
    Fraction(PrimeList* p, __int64 t);
    Fraction(PrimeList* p, __int64 t, __int64 n);
    ~Fraction();

    Fraction operator+(Fraction& other);
    /*Fraction operator-(const Fraction& other);
    Fraction operator*(const Fraction& other);
    Fraction operator/(const Fraction& other);*/

    void setInteger(__int64 t);
    bool setFraction(__int64 t, __int64 n);
    void invert();
    void eliminate();
    void print(bool debug=false);
    list<__int64> addLists(list<__int64>& l1, list<__int64>& l2);

  protected:

  private:
    list<__int64> t, n;
    PrimeList* p;
};

#endif // FRACTION_H
