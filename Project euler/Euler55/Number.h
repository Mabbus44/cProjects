#include <stdint.h>

#ifndef NUMBERRAZ
#define NUMBERRAZ

class Number
{
private:
  int8_t* digits;				//DigitsInNumber
  int digitCount;				//DigitCount in number
  int size;					//Size of array

public:
  Number();					//Default constructor
  Number(const Number& number);			//Copy constructor
  Number(int size);				//Constructor that sets size
  ~Number();					//Default deconstructor
  Number& operator=(const int number);		//Number = Int
  Number& operator=(const Number number);		//Number = Number
  Number operator+(const Number& number);		//Number = Number+Number
  Number operator-(const Number& number);		//Number = Number-Number
  Number operator*(const Number& number);		//Number = Number*Number
  bool isPalindrom();				//Returns true if number is palindrom
  bool outputInfo();				//Outputs info about number
  bool outputNumber();				//Outputs number
  bool reverseDigits();				//Reverses the order of the digits  
};

#endif