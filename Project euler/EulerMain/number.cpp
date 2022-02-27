#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
#include "number.h"
#include <iostream>
#include <math.h>

using namespace std;

Number::Number(){
  digits.push_back(0);
  sign = 1;
}

Number::Number(const Number& number){
  digits = number.digits;
  sign = number.sign;
}

Number::Number(int64_t number){
  digits.clear();
  sign = 1;
  if(number<0){
    number = 0-number;
    sign = -1;
  }
  while(number>0){
    digits.push_back(number%10);
    number/=10;
  }
  if(digits.size() == 0)
    digits.push_back(0);
}

Number::~Number(){}

Number& Number::operator=(int64_t number){
  digits.clear();
  sign = 1;
  if(number<0){
    number = 0-number;
    sign = -1;
  }
  while(number>0){
    digits.push_back(number%10);
    number/=10;
  }
  if(digits.size() == 0)
    digits.push_back(0);
  return *this;
}

Number& Number::operator=(const Number& number){
  digits = number.digits;
  sign = number.sign;
  return *this;
}

Number Number::operator+(const Number& number){
  Number result;
  result.digits.clear();
  int maxSize = max(digits.size(), number.digits.size());
  int8_t carry=0;
  for(int i=0; i<maxSize; i++){
    result.digits.push_back(0);
    if(i<(int)digits.size()){
      if(sign==1)
        result.digits.back() += digits[i];
      else
        result.digits.back() -= digits[i];
    }
    if(i<(int)number.digits.size()){
      if(number.sign==1)
        result.digits.back() += number.digits[i];
      else
        result.digits.back() -= number.digits[i];
    }
    result.digits.back() += carry;
    carry = 0;
    if(result.digits.back()>9){
      result.digits.back() -= 10;
      carry = 1;
    }
    if(result.digits.back()<0){
      result.digits.back() += 10;
      carry = -1;
    }
  }
  if(carry==1)
    result.digits.push_back(1);
  if(carry==-1){
    result.sign = -1;
    result.digits.push_back(-1);
    carry = 0;
    for(int i=0; i<(int)result.digits.size(); i++){
      result.digits[i] = 0-result.digits[i]+carry;
      carry = 0;
      if(result.digits[i]<0){
        result.digits[i] += 10;
        carry = -1;
      }
    }
  }
  trim(result);
  return result;
}

Number Number::operator-(const Number& number){
  Number result;
  result.digits.clear();
  int maxSize = max(digits.size(), number.digits.size());
  int8_t carry=0;
  for(int i=0; i<maxSize; i++){
    result.digits.push_back(0);
    if(i<(int)digits.size()){
      if(sign==1)
        result.digits.back() += digits[i];
      else
        result.digits.back() -= digits[i];
    }
    if(i<(int)number.digits.size()){
      if(number.sign==1)
        result.digits.back() -= number.digits[i];
      else
        result.digits.back() += number.digits[i];
    }
    result.digits.back() += carry;
    carry=0;
    if(result.digits.back()>9){
      result.digits.back() -= 10;
      carry = 1;
    }
    if(result.digits.back()<0){
      result.digits.back() += 10;
      carry = -1;
    }
  }
  if(carry==1)
    result.digits.push_back(1);
  if(carry==-1){
    result.sign = -1;
    result.digits.push_back(-1);
    carry = 0;
    for(int i=0; i<(int)result.digits.size(); i++){
      result.digits[i] = 0-result.digits[i]+carry;
      carry = 0;
      if(result.digits[i]<0){
        result.digits[i] += 10;
        carry = -1;
      }
    }
  }
  trim(result);
  return result;
}

Number Number::operator*(const Number& number){
  int maxDigits = digits.size() + number.digits.size();
  Number result;
  result.digits.reserve(maxDigits);
  for(int i=0; i<maxDigits; i++)
    result.digits.push_back(0);
  for(int i1=0; i1<(int)digits.size(); i1++){
    for(int i2=0; i2<(int)number.digits.size(); i2++){
      result.digits[i1+i2] += digits[i1]*number.digits[i2];
      if(result.digits[i1+i2]>9){
        result.digits[i1+i2+1] += result.digits[i1+i2]/10;
        result.digits[i1+i2] = result.digits[i1+i2]%10;
      }
    }
  }
  result.sign = sign*number.sign;
  trim(result);
  return result;
}

int64_t Number::operator% (const int64_t number){
  int rest=0;
  for(int i=digits.size()-1; i>=0; i--){
    rest *= 10;
    rest = (rest+digits[i])%number;
  }
  return rest;
}

void Number::operator/= (const int number){
  int rest=0;
  int oldRest=0;
  for(int i=digits.size()-1; i>=0; i--){
    rest = (oldRest+digits[i])%number;
    digits[i] = (oldRest+digits[i])/number;
    oldRest=10*rest;
  }
  trim(*this);
}

void Number::operator+=(const Number& number){
  int maxSize = max(digits.size(), number.digits.size());
  for(int i=(int)digits.size(); i<(int)number.digits.size(); i++)
    digits.push_back(0);
  digits.push_back(0);
  int8_t carry=0;
  for(int i=0; i<maxSize; i++){
    if(i<(int)number.digits.size()){
      if(number.sign*sign==1)
        digits[i] += number.digits[i];
      else
        digits[i] -= number.digits[i];
    }
    digits[i] += carry;
    carry = 0;
    if(digits[i]>9){
      digits[i] -= 10;
      carry = 1;
    }
    if(digits[i]<0){
      digits[i] += 10;
      carry = -1;
    }
  }
  if(carry==1)
    digits.back()=1;
  if(carry==-1){
    sign = sign*-1;
    digits.back()=-1;
    carry = 0;
    for(int i=0; i<(int)digits.size(); i++){
      digits[i] = 0-digits[i]+carry;
      carry = 0;
      if(digits[i]<0){
        digits[i] += 10;
        carry = -1;
      }
    }
  }
  trim(*this);
}

void Number::operator-=(const Number& number){
  int maxSize = max(digits.size(), number.digits.size());
  for(int i=(int)digits.size(); i<(int)number.digits.size(); i++)
    digits.push_back(0);
  digits.push_back(0);
  int8_t carry=0;
  for(int i=0; i<maxSize; i++){
    if(i<(int)number.digits.size()){
      if(number.sign*sign==1)
        digits[i] -= number.digits[i];
      else
        digits[i] += number.digits[i];
    }
    digits[i] += carry;
    carry = 0;
    if(digits[i]>9){
      digits[i] -= 10;
      carry = 1;
    }
    if(digits[i]<0){
      digits[i] += 10;
      carry = -1;
    }
  }
  if(carry==1)
    digits.back()=1;
  if(carry==-1){
    sign = sign*-1;
    digits.back()=-1;
    carry = 0;
    for(int i=0; i<(int)digits.size(); i++){
      digits[i] = 0-digits[i]+carry;
      carry = 0;
      if(digits[i]<0){
        digits[i] += 10;
        carry = -1;
      }
    }
  }
  trim(*this);
}

bool Number::operator<(const Number& number) const{
  if(sign==1 && number.sign==1){
    if(digits.size()>number.digits.size())
      return false;
    if(digits.size()<number.digits.size())
      return true;
    for(int i=digits.size()-1; i>=0; i--){
      if(digits[i]>number.digits[i])
        return false;
      if(digits[i]<number.digits[i])
        return true;
    }
  }else if(sign==-1 && number.sign==1){
    return true;
  }else if(sign==1 && number.sign==-1){
    return false;
  }else{
    if(digits.size()<number.digits.size())
      return false;
    if(digits.size()>number.digits.size())
      return true;
    for(int i=digits.size()-1; i>=0; i--){
      if(digits[i]<number.digits[i])
        return false;
      if(digits[i]>number.digits[i])
        return true;
    }
  }
  return false;
}

bool Number::operator>(const Number& number) const{
  if(sign==1 && number.sign==1){
    if(digits.size()>number.digits.size())
      return true;
    if(digits.size()<number.digits.size())
      return false;
    for(int i=digits.size()-1; i>=0; i--){
      if(digits[i]>number.digits[i])
        return true;
      if(digits[i]<number.digits[i])
        return false;
    }
  }else if(sign==-1 && number.sign==1){
    return false;
  }else if(sign==1 && number.sign==-1){
    return true;
  }else{
    if(digits.size()<number.digits.size())
      return true;
    if(digits.size()>number.digits.size())
      return false;
    for(int i=digits.size()-1; i>=0; i--){
      if(digits[i]<number.digits[i])
        return true;
      if(digits[i]>number.digits[i])
        return false;
    }
  }
  return false;
}

bool Number::operator==(const Number& number) const{
  if(digits.size() != number.digits.size() || sign != number.sign)
    return false;
  for(int i=0; i<(int)digits.size(); i++)
    if(digits[i] != number.digits[i])
      return false;
  return true;
}

void Number::trim(Number& number){
  for(int i=number.digits.size()-1; i>=0; i--){
    if(number.digits[i] == 0)
      number.digits.pop_back();
    else
      break;
  }
  if(number.digits.size()==0){
    number.digits.push_back(0);
    number.sign = 1;
  }
}

Number Number::sqrt(){
  if(digits.size() == 1 && (digits[0] == 1 || digits[0] == 0))
    return *this;
  Number adjust=(*this);
  if(!(digits.size()==1 && (digits[0] == 2 || digits[0] == 3)))
    adjust /=2;
  Number result=adjust;
  int finalDir=0;
  while(true){
    Number square = result*result;
    if(square==(*this))
      return result;
    if(finalDir==0)
      adjust /=2;
    if(square>(*this)){
      if((int)adjust.digits.size() == 1 && adjust.digits[0] == 1 && finalDir==0){
        finalDir = -1;
      }
      result -= adjust;
      if(finalDir==1)
        return result;
    }else{
      if((int)adjust.digits.size() == 1 && adjust.digits[0] == 1 && finalDir==0){
        finalDir = 1;
      }
      if(finalDir == -1)
        return result;
      result += adjust;
    }
  }
}

bool Number::sqrtAble(){
  int newSize = (digits.size()+1)/2;
  vector<int8_t> digitsCopy;
  vector<int8_t> digitsCopyMinusDecided=digits;
  vector<int8_t> newDigits(newSize);
  int product;
  bool tryAgain;
  for(int primaryDigitId=newSize-1; primaryDigitId>=0; primaryDigitId--){
    newDigits[primaryDigitId] = 9;
    tryAgain = false;
    do{
      digitsCopy = digitsCopyMinusDecided;
      tryAgain = false;
      for(int secondaryDigitId=primaryDigitId; secondaryDigitId<newSize && !tryAgain; secondaryDigitId++){
        if(primaryDigitId==secondaryDigitId)
          product = newDigits[primaryDigitId]*newDigits[secondaryDigitId];
        else
          product = newDigits[primaryDigitId]*newDigits[secondaryDigitId]*2;
        digitsCopy[primaryDigitId+secondaryDigitId]-=product%10;
        product /= 10;
        if(product>0 && primaryDigitId+secondaryDigitId+1>=(int)digitsCopy.size())
          tryAgain=true;
        else if(product>0){
          digitsCopy[primaryDigitId+secondaryDigitId+1]-=product%10;
          product /= 10;
          if(product>0 && primaryDigitId+secondaryDigitId+2>=(int)digitsCopy.size())
            tryAgain=true;
          else if(product>0){
            digitsCopy[primaryDigitId+secondaryDigitId+2]-=product;
          }
        }
        while(digitsCopy[primaryDigitId+secondaryDigitId]<0){
          digitsCopy[primaryDigitId+secondaryDigitId]+=10;
          if(primaryDigitId+secondaryDigitId+1<(int)digitsCopy.size())
            digitsCopy[primaryDigitId+secondaryDigitId+1]--;
          else
            tryAgain=true;
        }
      }
      for(int secondaryDigitId=primaryDigitId+newSize; secondaryDigitId<(int)digitsCopy.size()-1; secondaryDigitId++){
        while(digitsCopy[secondaryDigitId]<0){
          digitsCopy[secondaryDigitId]+=10;
          digitsCopy[secondaryDigitId+1]--;
        }
      }
      if(digitsCopy.back()<0)
        tryAgain=true;
      if(tryAgain)
        newDigits[primaryDigitId]--;
    }while(tryAgain && newDigits[primaryDigitId]!=0);
    if(newDigits[primaryDigitId]!=0)
      digitsCopyMinusDecided = digitsCopy;
  }
  for(int8_t i: digitsCopyMinusDecided)
    if(i!=0)
      return false;
  return true;
}

int Number::getDigitCount(){
    return digits.size();
}

int64_t Number::getInt64(){
  int64_t ans=0;
  int64_t pow=1;
  for(int i:digits){
    ans+=i*pow;
    pow*=10;
  }
  int64_t sign64t = sign;
  return ans*sign64t;
}

int Number::digitalSum(){
  int result=0;
  for(int i=0; i<(int)digits.size(); i++)
    result+=digits[i];
  return result;
}

bool Number::isPalindrom(){
  int pos=0;
  while(pos<(int)digits.size()/2){
    if(digits[digits.size()-pos-1] != digits[pos])
      return false;
    pos++;
  }
  return true;
}

void Number::outputInfo(){
  outputNumber();
  cout << endl;
}

void Number::outputNumber(){
  if(sign==-1)
    cout << "-";
  for(int i=(int)digits.size()-1; i>=0; i--){
    cout << (int)digits[i];
    if(i>0 && i%3==0)
      cout << ",";
  }
}

void Number::reverseDigits(){
  int x, pos=0;
  while(pos<(int)digits.size()/2){
    x = digits[digits.size()-pos-1];
    digits[digits.size()-pos-1] = digits[pos];
    digits[pos] = x;
    pos++;
  }
}

void numberTester(){
  vector<int> values = {783,5,1,-1,0,1,0,-1,-493821,-432,5842123,432,0,483921,4883921,-1,-1,-234922,0,9499212,0,-432,-432,133,133,133};
  int64_t a,b,c;
  Number x,y,z;
  bool fail=false;
  for(int i=0; i<(int)values.size()-1; i++){
    cout << "Testing value " << values[i] << " and " << values[i+1] << endl;

    a = values[i];
    x = values[i];
    cout << "=" << values[i] << ", " << a << ", ";
    x.outputNumber();
    if(a!=x.getInt64()){
      cout << " FAIL!!!!!!!";
      fail=true;
    }
    cout << endl;

    a = values[i];
    b = a;
    x = values[i];
    y = x;
    cout << "=(Number)" << values[i] << ", " << b << ", ";
    y.outputNumber();
    if(b!=y.getInt64()){
      cout << " FAIL!!!!!!!";
      fail=true;
    }
    cout << endl;

    a = values[i];
    b = values[i+1];
    c = a+b;
    x = values[i];
    y = values[i+1];
    z = x+y;
    cout << values[i] << "+" << values[i+1] << ", " << c << ", ";
    z.outputNumber();
    if(c!=z.getInt64()){
      cout << " FAIL!!!!!!!";
      fail=true;
    }
    cout << endl;

    c = a-b;
    z = x-y;
    cout << values[i] << "-" << values[i+1] << ", " << c << ", ";
    z.outputNumber();
    if(c!=z.getInt64()){
      cout << " FAIL!!!!!!!";
      fail=true;
    }
    cout << endl;

    c = a*b;
    z = x*y;
    cout << values[i] << "*" << values[i+1] << ", " << c << ", ";
    z.outputNumber();
    if(c!=z.getInt64()){
      cout << " FAIL!!!!!!!";
      fail=true;
    }
    cout << endl;

    if(values[i+1] != 0){
      a/=b;
      x/=b;
      cout << values[i] << "/=" << values[i+1] << ", " << a << ", ";
      x.outputNumber();
      if(a!=x.getInt64()){
        cout << " FAIL!!!!!!!";
        fail=true;
      }
      cout << endl;
    }

    a = values[i];
    x = values[i];
    a+=b;
    x+=y;
    cout << values[i] << "+=" << values[i+1] << ", " << a << ", ";
    x.outputNumber();
    if(a!=x.getInt64()){
      cout << " FAIL!!!!!!!";
      fail=true;
    }
    cout << endl;

    a = values[i];
    x = values[i];
    a-=b;
    x-=y;
    cout << values[i] << "-=" << values[i+1] << ", " << a << ", ";
    x.outputNumber();
    if(a!=x.getInt64()){
      cout << " FAIL!!!!!!!";
      fail=true;
    }
    cout << endl;

    a = values[i];
    x = values[i];
    cout << values[i] << "<" << values[i+1] << ", " << (a<b) << ", " << (x<y);
    if((a<b)!=(x<y)){
      cout << " FAIL!!!!!!!";
      fail=true;
    }
    cout << endl;

    cout << values[i] << ">" << values[i+1] << ", " << (a>b) << ", " << (x>y);
    if((a>b)!=(x>y)){
      cout << " FAIL!!!!!!!";
      fail=true;
    }
    cout << endl;

    cout << values[i] << "==" << values[i+1] << ", " << (a==b) << ", " << (x==y);
    if((a==b)!=(x==y)){
      cout << " FAIL!!!!!!!";
      fail=true;
    }
    cout << endl;

    if(values[i] >= 0){
      c = sqrt(a);
      z = x.sqrt();
      cout << "sqrt(" << values[i] << "), " << c << ", ";
      z.outputNumber();
      if(c!=z.getInt64()){
        cout << " FAIL!!!!!!!";
        fail=true;
      }
      cout << endl;
    }

    cout << endl;
  }
  if(fail)
    cout << "At least one test failed!!!!!!!!!!" << endl;
  else
    cout << "All tests passed!" << endl;
}
