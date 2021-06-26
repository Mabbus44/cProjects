#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
#include "number.h"

using namespace std;




Number::Number(){
  digitCount=1;
  size=2;
  digits = new int8_t[2];
  digits[0]=1;                                  //Positive number
  digits[1]=0;                                  //0
}





Number::Number(const Number& number){
  size = number.size;
  digitCount = number.digitCount;
  digits = new int8_t[size];
  for(int i=0; i<size; i++){                    //Set digits
    digits[i]=number.digits[i];
  }
}





Number::Number(int size){
  this->size = size;
  if(this->size<2)
    this->size = 2;
  digitCount = 1;
  digits = new int8_t[size];
  digits[0]=1;                                  //Positive number
  digits[1]=0;                                  //0
}





Number::~Number(){
  delete[] digits;                              //Delete old digits
}





Number& Number::operator=(const int number){
  int number2=number;
  digitCount = 0;                               //Count digits in "number"
  while(number2!=0){
    number2/=10;
    digitCount++;
  }
  if(number==0)                                 //If number = 0 the general code dont work
    digitCount = 1;
  if(size<digitCount+1){                        //Delete old digits
    delete[] digits;
    size=digitCount+1;
    digits = new int8_t[size];                  //Allocate memory for new digits
  }
  number2=number;
  if(number2>=0){                               //Set positive/negative tag
    digits[0] = 1;
  }else{
    digits[0] = -1;
  }
  for(int i=0; i<digitCount; i++){              //Set new digits to desired number
    this->digits[i+1] = abs(number2-(number2/10)*10);
    number2/=10;
  }
  return *this;
}





Number& Number::operator=(const Number number){
  if(number.digitCount+1>size){                 //If new number is bigger
    delete[] digits;                            //Delete old digits
    digits = new int8_t[number.digitCount+1];   //Allocate memory for new digits
  }
  digitCount = number.digitCount;               //Set size
  size = digitCount+1;
  for(int i=0; i<size; i++)                     //Set digits
    digits[i]=number.digits[i];
  return *this;
}





Number Number::operator+(const Number& number){
  int rest=0, sum, sign, size;
  size=std::max(digitCount, number.digitCount)+2;                    //Calculate new size
  if(digitCount>number.digitCount)                              //Check what sign result will be
    sign = digits[0];
  else if(digitCount<number.digitCount)
    sign = number.digits[0];
  else{                                                         //If digitCount is the same in the two numbers
    sign=0;
    int n=size-2;
    while(sign==0){                                             //Check for the first digit that is bigger in one of the numbers
      if(digits[n]>number.digits[n])
        sign = digits[0];
      else if(digits[n]<number.digits[n])
        sign = number.digits[0];
      n--;
      if(n==0){                                                 //If all digits are the same check signs of the two numbers
        if(digits[0]==number.digits[0])
          sign = digits[0];
        else
          sign = 1;
      }
    }
  }

  Number result(size);                                          //Allocate memory for new digits
  result.digits[0] = sign;                                      //Set sign of result
  result.digitCount = 0;                                        //Reset digitCount
  for(int i=1; i<result.size; i++){                             //Add all digits
    sum=rest;                                                   //Start with old rest
    rest = 0;
    if(i<digitCount+1)                                          //Add digit 1
      sum+=digits[i]*digits[0];
    if(i<number.digitCount+1)                                   //Add digit 2
      sum+=number.digits[i]*number.digits[0];
    if(result.digits[0]==1){                                    //If answer positive
      while(sum>9){                                             //0 <= sum <= 9
        sum-=10;
        rest+=1;
      }
      while(sum<0){
        sum+=10;
        rest-=1;
      }
    }
    if(result.digits[0]==-1){                                   //If answer negative
      while(sum>0){                                             //-9 <= sum <= 0
        sum-=10;
        rest+=1;
      }
      while(sum<-9){
        sum+=10;
        rest-=1;
      }
      sum = -sum;                                               //Make sum positive
    }
    result.digits[i] = sum;                                     //Set digit in result
    if(sum!=0)
      result.digitCount = i;                                    //Calculate digitCount
  }
  if(result.digitCount == 0)
    result.digitCount = 1;
  return result;
}





Number Number::operator-(const Number& number){
  int rest=0, sum, sign, size;
  size=std::max(digitCount, number.digitCount)+2;                    //Calculate new size
  if(digitCount>number.digitCount)                              //Check what sign result will be
    sign = digits[0];
  else if(digitCount<number.digitCount)
    sign = -number.digits[0];
  else{                                                         //If digitCount is the same in the two numbers
    sign=0;
    int n=size-2;
    while(sign==0){                                             //Check for the first digit that is bigger in one of the numbers
      if(digits[n]>number.digits[n])
        sign = digits[0];
      else if(digits[n]<number.digits[n])
        sign = -number.digits[0];
      n--;
      if(n==0){                                                 //If all digits are the same check signs of the two numbers
        if(digits[0]== -number.digits[0])
          sign = digits[0];
        else
          sign = 1;
      }
    }
  }

  Number result(size);                                          //Allocate memory for new digits
  result.digits[0] = sign;                                      //Set sign of result
  result.digitCount = 0;                                        //Reset digitCount
  for(int i=1; i<result.size; i++){                             //Add all digits
    sum=rest;                                                   //Start with old rest
    rest = 0;
    if(i<digitCount+1)                                          //Add digit 1
      sum+=digits[i]*digits[0];
    if(i<number.digitCount+1)                                   //Add digit 2
      sum+=number.digits[i] * -number.digits[0];
    if(result.digits[0]==1){                                    //If answer positive
      while(sum>9){                                             //0 <= sum <= 9
        sum-=10;
        rest+=1;
      }
      while(sum<0){
        sum+=10;
        rest-=1;
      }
    }
    if(result.digits[0]==-1){                                   //If answer negative
      while(sum>0){                                             //-9 <= sum <= 0
        sum-=10;
        rest+=1;
      }
      while(sum<-9){
        sum+=10;
        rest-=1;
      }
      sum = -sum;                                               //Make sum positive
    }
    result.digits[i] = sum;                                     //Set digit in result
    if(sum!=0)
      result.digitCount = i;                                    //Calculate digitCount
  }
  if(result.digitCount == 0)
    result.digitCount = 1;
  return result;
}





Number Number::operator*(const Number& number){
  int rest=0, size;
  size = digitCount + number.digitCount+1;                      //Calculate new size
  if((digits[1]==0 && digitCount==1) || (number.digits[1]==0 && number.digitCount==1))                          //If one product is 0 result is 0
    size = 2;

  Number result(size);                                          //Allocate memory for new digits
  if((digits[1]==0 && digitCount==1) || (number.digits[1]==0 && number.digitCount==1)){                         //If one product is 0 result is 0
    result.digits[0] = 1;
    result.digits[1] = 0;
    result.digitCount = 1;
    return result;
  }
  result.digits[0] = digits[0]*number.digits[0];                //Set sign of result
  result.digitCount = 0;                                        //Reset digitCount
  for(int i=1; i<result.size; i++)                              //Reset all digits in result
    result.digits[i] = 0;
  for(int i=1; i<digitCount+1; i++){                            //All digits of first number
    for(int i2=1; i2<number.digitCount+1; i2++){                //All digits of second number
      result.digits[i+i2-1] += digits[i] * number.digits[i2] + rest;    //Multiply 2 digits, add product + sum to result digit
      rest = 0;                                                 //Reset rest
      while(result.digits[i+i2-1] > 9){                         //0 <= Digit <= 9 and calculate rest
        result.digits[i+i2-1] -= 10;
        rest += 1;
      }
    }
    result.digits[i+number.digitCount] += rest;                         //Add rest if there still is rest
    rest = 0;                                                   //Reset rest
    while(result.digits[i+number.digitCount-1] > 9){                            //0 <= Digit <= 9 and calculate rest
      result.digits[i+number.digitCount-1] -= 10;
      rest += 1;
    }
  }
  if(result.digits[result.size-1]>0)                            //If biggest digit is > 0
    result.digitCount=result.size-1;                            //digitCount = digitCount of factors
  else
    result.digitCount=result.size-2;                            //else digitCount = digitCount of factors -1
  return result;
}





int Number::getDigitCount(){
    return digitCount;
}





int Number::digitalSum(){
  int result=0;
  for(int i=1; i<=digitCount; i++)
    result+=digits[i];
  return result;
}





bool Number::isPalindrom(){
  int pos=1;
  while(pos<=digitCount/2){
    if(digits[digitCount-pos+1] != digits[pos])
      return false;
    pos++;
  }
  return true;
}





bool Number::outputInfo(){
/*  cout << "Size:" << size << " DigitCount:" << digitCount << " adress:" << &digits << endl;
  cout << "Val:";
  if(digits[0]==-1){                                    //Output positive/negative tag
    cout << "-";
  }
  for(int i=digitCount-1; i>=0; i--){
    cout << (int)digits[i+1];
  }
  cout << endl;*/
  return true;
}





bool Number::outputNumber(){
/*  if(digits[0]==-1){                                    //Output positive/negative tag
    cout << "-";
  }
  for(int i=digitCount-1; i>=0; i--){
    cout << (int)digits[i+1];
  }*/
  return true;
}





bool Number::reverseDigits(){
  int x, pos=1;
  while(pos<=digitCount/2){
    x = digits[digitCount-pos+1];
    digits[digitCount-pos+1] = digits[pos];
    digits[pos] = x;
    pos++;
  }
  return true;
}

