#include <iostream>
#include "Fraction.h"

using namespace std;

Fraction::Fraction()
{
  p = new PrimeList(100);
  t = 0;
  n = 1;
}

Fraction::Fraction(PrimeList* p){
  this->p = p;
}

Fraction::Fraction(PrimeList* p, __int64 t){
  this->p = p;
  setInteger(t);
}

Fraction::Fraction(PrimeList* p, __int64 t, __int64 n){
  this->p = p;
  setFraction(t, n);
}

Fraction::~Fraction()
{

}

Fraction Fraction::operator+(const Fraction& other){
  Fraction f(this->p);
  f.t = this->t*other.n + other.t*this->n;
  f.n = this->n*other.n;
  return f;
}

Fraction Fraction::operator-(const Fraction& other){
  Fraction f;
  f.t = this->t*other.n - other.t*this->n;
  f.n = this->n*other.n;
  return f;
}

Fraction Fraction::operator*(const Fraction& other){
  Fraction f;
  f.t = this->t*other.t;
  f.n = this->n*other.n;
  return f;
}

Fraction Fraction::operator/(const Fraction& other){
  Fraction f;
  f.t = this->t*other.n;
  f.n = this->n*other.t;
  if(f.n == 0)
    f.n = 1/f.n;
  return f;
}

void Fraction::setInteger(__int64 t){
  this->t = t;
  this->n = 1;
}

bool Fraction::setFraction(__int64 t, __int64 n){
  if(!n)
    return false;
  this->t = t;
  this->n = n;
  return true;
}

void Fraction::invert(){
  __int64 temp = t;
  t = n;
  n=temp;
  if(n == 0)
    n = 1/n;
}

void Fraction::eliminate(){
  list<__int64> l1 = p->factorize(t);
  list<__int64> l2 = p->factorize(n);
  list<__int64>::iterator it1 = l1.begin();
  list<__int64>::iterator it2 = l2.begin();
  __int64 commonFactor = 1;
  while(it1 != l1.end() && it2 != l2.end()){
    if(*it1 == *it2){
      commonFactor*=*it1;
      it1++;
      it2++;
    }
    else{
      if(*it1<*it2)
        it1++;
      else
        it2++;
    }
  }
  t/=commonFactor;
  n/=commonFactor;
}

void Fraction::print(bool debug){
  if(debug)
    cout << "Primes adress: " << p << endl;
  cout << t << "/" << n << endl;
}
