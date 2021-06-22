#include "RootFraction.h"
#include <iostream>
#include <math.h>

Abc::Abc(){
}

Abc::Abc(int a, int b, int c){
  this->a = a;
  this->b = b;
  this->c = c;
}

bool Abc::operator==(const Abc& other){
  if(this->a == other.a && this->b == other.b && this->c == other.c)
    return true;
  return false;
}

RootFraction::RootFraction(){
}

RootFraction::RootFraction(int n){
  setN(n);
}

RootFraction::~RootFraction(){
}

void RootFraction::setN(int n){
  fList.clear();
  this->n = n;
  m = (int)std::sqrt(n);
  a = m;
  c = m;
  b = 1;
  fList.push_back(Abc(a, b, c));
}

void RootFraction::nextFraction(){
  b = (n - c*c)/b;
  a = (int)((c+m)/b);
  c = a*b-c;
  fList.push_back(Abc(a, b, c));
}

void RootFraction::printFraction(){
  std::cout << "A: " << a;
  std::cout << "  B: " << b;
  std::cout << "  C: " << c;
  std::cout << "  M: " << m;
  std::cout << "  N: " << n << std::endl;
}

int RootFraction::getPeriod(int n){
  bool done = false;
  list<Abc>::iterator last;
  int len = 0;
  setN(n);
  if(m*m == n)
    return 0;
  while(!done){
    nextFraction();
    last = fList.end();
    last--;
    for(list<Abc>::iterator it=fList.begin(); it!=last; it++){
      if(len>0)
        len++;
      if(*last == *it){
        done = true;
        len = 1;
      }
    }
  }
  return len;
}
