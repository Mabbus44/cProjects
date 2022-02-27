#include <stdint.h>
#include "variable.h"
#include <vector>

#ifndef NUMBERRAZ
#define NUMBERRAZ


//Digit[0] is sign (1 or -1);
//Digit[1] is least significant digit;
class Number : public Variable
{
private:
  vector<int8_t> digits;
  int8_t sign;

public:
  Number();
  Number(const Number& number);
  Number(int64_t number);
  ~Number();
  Number& operator=(int64_t number);
  Number& operator=(const Number& number);
  Number operator+(const Number& number);
  Number operator-(const Number& number);
  Number operator*(const Number& number);
  int64_t operator% (const int64_t number);
  void operator/= (const int number);
  void operator+=(const Number& number);
  void operator-=(const Number& number);
  bool operator<(const Number& number) const;
  bool operator>(const Number& number) const;
  bool operator==(const Number& number) const;
  void trim(Number& number);
  Number sqrt();
  bool sqrtAble();
  int getDigitCount();
  int64_t getInt64();
  int digitalSum();
  bool isPalindrom();
  void outputInfo();
  void outputNumber();
  void reverseDigits();
};

void numberTester();

#endif
