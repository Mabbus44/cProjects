#include <iostream>
#include <stdint.h>
#include <math.h>

#ifndef PRIMECOUNT
#define PRIMECOUNT 100000
#endif

int pow(int num, int power);




class PrimeList
{
private:
  int error;					//holds last error code
  int primeCount;				//number of primes
  int primes[PRIMECOUNT];			//array of primes
public:
  PrimeList();					//creates list with "PRIMECOUNT" primes at creation
  bool isPrime(int num);			//tests if num is prime
  int outputError();				//outputs and returns last error
  void outputPrimes();				//outputs all primes in list to terminal
  int returnPrime(int num);			//return prime with index "num"
};




class Number
{
private:
  int bestMask;					//Mask that generated most primes
  bool debug;
  int digitCount;					//DigitCount in number
  int8_t* digits;					//DigitsInNumber
  int mask;					//Mask for replacing digits in number
  int number;					//The number being tested
  int numberIndex;				//Index in the primelist of "number"
  PrimeList primes;				//List of "PRIMECOUNT" primes

  int countPrimes();				//Count primes with current number and mask
  int digit2Num();				//Converts digit to a intiger
  bool incrementNumber();				//Increments number to next prime
  bool num2Digit();				//Converts number to digits
  bool replaceDigits(int digit);			//Replaces digits acording to "Mask" with "digit"
  bool setNumber(int number);			//Sets number

public:

  Number();					//Default
  int search(int primeCount);			//Search for lowest number that generates primeCount
};





int pow(int num, int power)
{
  int ans=1;
  for(int i=0; i<power; i++)
    ans*=num;
  return ans;
}





PrimeList::PrimeList()
{
  primes[0]=2;					//first prime
  primeCount=1;					//1 prime so far
  for(int i=3; primeCount<PRIMECOUNT; i++)			//test if numbers up to "PRIMECOUNT" is primes
  {
    if(isPrime(i))					//if i is prime, add it to list
    {
      primes[primeCount]=i;
      primeCount++;
    }
  }						//end for
}





bool PrimeList::isPrime(int num)
{
  bool isPrime=true;				//number is prime until shown otherwise
  int i;					//for iterations
  
  if(num<2)					//2 is smallest prime
    return false;
  for(i=0; primes[i]*primes[i]<=num && isPrime && i<primeCount; i++)	//cycle through all primes < sqrt(i) or until i is not prime or until list of primes run out
  {
    if(num%primes[i]==0)			//if devisible by prime i2 then i is not prime
      isPrime=false;
  }
  if(i==primeCount)
  {
    std::cout << std::endl << "Error, prime list of " << primeCount << " primes is to small for testing number: " << num << std::endl << std::endl;
    error=1;
  }
  return isPrime;					//return if num is prime
}





void PrimeList::outputPrimes()
{
  std::cout << "Prime count: " << primeCount << std::endl;
  for(int i=0; i<primeCount; i++)
    std::cout << primes[i] << std::endl;
}





int PrimeList::outputError()
{
  int lastError=error;
  switch(error)
  {
    case 0:
      std::cout << std::endl << "No new errors" << std::endl << std::endl;
      break;
    case 1:
      std::cout << std::endl << "Error, prime list to small for testing if number is prime" << std::endl << std::endl;
      break;
    case 2:
      std::cout << std::endl << "Error, index outside range" << std::endl << std::endl;
      break;
    default:
      std::cout << std::endl << "Unknown error" << std::endl << std::endl;
      break;
  }
  return lastError;
}





int PrimeList::returnPrime(int num)
{
  if(num>=primeCount || num<0)
  {
    error=2;
    std::cout << std::endl << "Error, index: " << num << " outside range" << std::endl << std::endl;
    return 0;
  }
  return primes[num];
}





Number::Number()
{
  debug=false;
  digitCount=0;
  number=0;
}





int Number::countPrimes()
{
  if(this->debug)
  {
    std::cout << "countPrimes()" << std::endl;
  }
  int primeCount;
  int maxPrimeCount=0;
  for(this->mask=1; this->mask < pow(2, this->digitCount-1); this->mask++)	//Test for all masks
  {
    if(this->debug)
    {
      std::cout << "Mask: " << this->mask << std::endl;
    }
    primeCount=0;
    for(int i=0; i<10; i++)			//Replace masked digits with 0-9
    {
      if(this->mask >= pow(2, this->digitCount-1)/2 && i==0)	//Dont replace first digit with 0
	i++;
      if(!this->replaceDigits(i))
	return 0;
      if(this->primes.isPrime(this->digit2Num()))	//Count primes
      {
	primeCount++;
	if(this->debug)
	  {
	    std::cout << "Is prime" << std::endl;
	  }
      }
    }
    if(primeCount>maxPrimeCount)			//Save best mask
    {
      maxPrimeCount=primeCount;
      this->bestMask=mask;
    }
    this->num2Digit();				//Set digits again
  }
  if(this->debug)
  {
    std::cout << "maxPrimeCount " << maxPrimeCount << std::endl;
  }
  return maxPrimeCount;
}





int Number::digit2Num()
{
/*  if(this->debug)
  {
    std::cout << "digit2Num()" << std::endl;
  }*/
  int number=0;
  int factor=1;
  for(int i=0; i<this->digitCount; i++)		//Converts digits to number
  {
    number+=this->digits[i]*factor;
    factor*=10;
/*    if(this->debug)
    {
      std::cout << (int)(this->digits[i]);
    }*/
  }
  if(this->debug)
  {
    std::cout << "Number: " << number << std::endl;
  }
  return number;
}





bool Number::incrementNumber()
{
  if(this->debug)
  {
    std::cout << std::endl << "incrementNumber()" << std::endl;
  }
  this->numberIndex++;				//Increment index
  if(!this->setNumber(primes.returnPrime(this->numberIndex)))	//Set number to prime no index
    return false;
  return true;
}





bool Number::num2Digit()
{
/*  if(this->debug)
  {
    std::cout << "num2Digit()" << std::endl;
    std::cout << "number: " << this->number << std::endl;
    std::cout << "digitCount: " << this->digitCount << std::endl;
  }*/
  int number = this->number;
  for(int i=0; i<this->digitCount; i++)		//Set new digits to desider number
  {
    this->digits[i] = number-(number/10)*10;
    number/=10;
/*    if(this->debug)
    {
      std::cout << (int)(this->digits[i]);
    }*/
  }
  /*if(this->debug)
  {
    std::cout << std::endl;
  }*/
  return true;
}





bool Number::replaceDigits(int digit)
{
  if(this->debug)
  {
    std::cout << "repalceDigits(" << digit << ")" << std::endl;
  }
  for(int i=1; i<this->digitCount; i++)
  {
/*    if(this->debug)
    {
      std::cout << "if(" << mask << " & " << pow(2,i-1) << ")" << std::endl;
    }*/
    if(mask & pow(2,i-1))
      this->digits[i]=digit;
  }
  return true;
}





bool Number::setNumber(int number)
{
  if(this->debug)
  {
    std::cout << "setNumber(" << number << ")" << std::endl;
  }
  int digitCount;				//Digitcount in new number
  if(number<1)					//Give error if digitCount is outside bounds
  {
    std::cout << std::endl << std::endl << "Error: Number outside bounds: " << number << std::endl << std::endl;
    return false;
  }
  this->number = number;			//Set number to desired number
  digitCount = 0;				//Count digits in "number"
  while(number>0)				//
  {
    number/=10;
    digitCount++;
  }
  if(digitCount!=this->digitCount && digits)					//Delete old digits
  {
    if(this->debug)
    {
      std::cout << "Old digits deleted" << std::endl;
    }
    delete[] digits;
  }
  if(digitCount!=this->digitCount)		//Allocate memory for new digits
  {
    digits = new int8_t[digitCount];		
    if(this->debug)
      if(digits)
	std::cout << "New digits created" << std::endl;
      else
	std::cout << "New digits could not be created" << std::endl;
  }
  this->digitCount = digitCount;		//Set digitCount to desired number
  this->num2Digit();				//Set digits
  return true;
}





int Number::search(int primeCount)
{
  if(this->debug)
  {
    std::cout << "search()" << std::endl;
  }
  int currentCount;
  if(primeCount>10 || primeCount<1)
  {
    std::cout << std::endl << "Error: Illigal primeCount: " << primeCount << std::endl << std::endl;
    return 0;
  }
  this->numberIndex = 4;				//Index to prime no 1
  if(!this->setNumber(primes.returnPrime(this->numberIndex)))	//Set number to prime no 1
    return false;
  
  while(this->numberIndex<PRIMECOUNT)			//Go through all primes
  {
    currentCount = this->countPrimes();			//Count primes from current number
    if(currentCount==0)					//If count failed, quit
    {
      std::cout << std::endl << "Error when counting primes" << std::endl;
      return 0;
    }
    if(currentCount >= primeCount)			//If number is found, return it
    {
      std::cout << std::endl << "Lowest number with " << primeCount << " primes is " << this->number << ", with mask: " << this->bestMask << std::endl;
      return this->number;
    }
    this->incrementNumber();				//Go to next prime
  }
  std::cout << std::endl << "Could not find number with " << primeCount << " primes among the first " << PRIMECOUNT << " primes" << std::endl;
  return 0;
}





int main(int argc, char **argv) {
  
  Number num;
  std::cout << "Start" << std::endl;
  num.search(8);
  std::cout << "Stopp" << std::endl;
  return 0;
}
