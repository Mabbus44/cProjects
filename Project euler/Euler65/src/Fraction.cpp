#include <iostream>
#include "Fraction.h"

using namespace std;

Fraction::Fraction()
{
  p = new PrimeList(100);
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

Fraction Fraction::operator+(Fraction& other){
  //cout << "operator+()" << endl;
  Fraction f(this->p);
  list<__int64> l1, l2;
  l1.assign(this->t.begin(), this->t.end());
  for(list<__int64>::iterator it=other.n.begin(); it!=other.n.end(); it++)
    l1.push_back(*it);
  l2.assign(other.t.begin(), other.t.end());
  for(list<__int64>::iterator it=n.begin(); it!=n.end(); it++)
    l2.push_back(*it);
  /*cout << "l1= ";
  for(list<__int64>::iterator it=l1.begin(); it!=l1.end(); it++)
    cout << *it << ", ";
  cout << endl;
  cout << "l2= ";
  for(list<__int64>::iterator it=l2.begin(); it!=l2.end(); it++)
    cout << *it << ", ";
  cout << endl;*/
  f.t = addLists(l1, l2);
  f.n.assign(other.n.begin(), other.n.end());
  for(list<__int64>::iterator it=n.begin(); it!=n.end(); it++)
    f.n.push_back(*it);
  f.t.sort();
  f.n.sort();
  /*cout << "f.n= ";
  for(list<__int64>::iterator it=f.n.begin(); it!=f.n.end(); it++)
    cout << *it << ", ";
  cout << endl;*/
  f.eliminate();
  return f;
}

/*Fraction Fraction::operator-(const Fraction& other){
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
}*/

void Fraction::setInteger(__int64 t){
  this->t.clear();
  this->n.clear();
  this->t.push_back(t);
  this->n.push_back(1);
}

bool Fraction::setFraction(__int64 t, __int64 n){
  if(!n)
    return false;
  this->t.clear();
  this->n.clear();
  this->t.push_back(t);
  this->n.push_back(n);
  return true;
}

void Fraction::invert(){
  //cout << "invert()" << endl;
  list<__int64> temp = t;
  t = n;
  n=temp;
}

void Fraction::eliminate(){
  //cout << "eliminate()" << endl;
  list<__int64>::iterator it1 = t.begin();
  list<__int64>::iterator it2 = n.begin();
  /*cout << "n= ";
  for(list<__int64>::iterator it=n.begin(); it!=n.end(); it++)
    cout << *it << ", ";
  cout << endl;*/
  while(it1 != t.end() && *it1==1 && t.size() > 1)
    it1 = t.erase(it1);
  while(it2 != n.end() && *it2==1 && n.size() > 1)
    it2 = n.erase(it2);
  while(it1 != t.end() && it2 != n.end()){
    if(it1 != t.end() && it2 != n.end() && *it1 == *it2){
      if(*it1 == 1){
        it1++;
        it2++;
      }
      else{
        it1 = t.erase(it1);
        it2 = n.erase(it2);
      }
    }
    else{
      if(it2 == n.end() || (it1 != t.end() && *it1<*it2))
        it1++;
      else
        it2++;
    }
  }
}

void Fraction::print(bool debug){
  if(debug)
    cout << "Primes adress: " << p << endl;
  for(list<__int64>::iterator it = t.begin(); it!=t.end(); it++){
    cout << *it << " ";
  }
  cout << "/";
  for(list<__int64>::iterator it = n.begin(); it!=n.end(); it++){
    cout << *it << " ";
  }
  cout << endl;
}

list<__int64> Fraction::addLists(list<__int64>& l1, list<__int64>& l2){
  //cout << "AddLists()" << endl;
  l1.sort();
  l2.sort();
  list<__int64>::iterator it1 = l1.begin();
  list<__int64>::iterator it2 = l2.begin();
  list<__int64> lAns;
  __int64 restFactor1 = 1;
  __int64 restFactor2 = 1;
  while(it1 != l1.end() || it2 != l2.end()){
    /*if(it1 == l1.end())
      cout << "it1 end ";
    if(it2 == l2.end())
      cout << "it2 end ";
    cout << "*it1/*it2: " << *it1 << "/" << *it2 << endl;*/
    if(it1!=l1.end() && it2!=l2.end() && *it1 == *it2){
      /*if(*it1!=1)
        cout << "Common: " << *it1 << endl;*/
      if(*it1!=1)
        lAns.push_back(*it1);
      it1++;
      it2++;
    }
    else{
      if(it2==l2.end() || (it1!=l1.end() && *it1<*it2)){
        restFactor1*=*it1;
        //cout << "Restfactor1: " << restFactor1 << endl;
        it1++;
      }
      else{
        restFactor2*=*it2;
        //cout << "Restfactor2: " << restFactor2 << endl;
        it2++;
      }
    }
  }
  //cout << "restFactors: ";
  list<__int64> restFactorList = p->factorize(restFactor1+restFactor2);
  for(list<__int64>::iterator it=restFactorList.begin(); it!=restFactorList.end(); it++){
    //cout << *it << ", ";
    lAns.push_back(*it);
  }
  //cout << endl;
  return lAns;
}
