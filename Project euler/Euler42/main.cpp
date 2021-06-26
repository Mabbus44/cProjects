#include <iostream>
#include <fstream>
#include <string>

#ifndef TRINUMCOUNT
#define TRINUMCOUNT 25
#endif

int main(int argc, char **argv) {
  std::ifstream words;							//File
  int value;								//Value of letter
  int wordVal;								//Value of word
  int triNum[TRINUMCOUNT];						//Triangular numbers
  int biggestTriNum;							//Biggest triangular number in array
  int triWordCount;							//Number of triangilar words
  bool isTriWord;							//Keeps track of if a word is triangular
  char* letter = new char;						//Letter from file
  
 
  triNum[0]=1;
  for(int i=2; i<=TRINUMCOUNT; i++)
  {
    triNum[i-1]=triNum[i-2]+i;
    biggestTriNum=triNum[i-1];
  }
  
  words.open("p042_words.txt");  
  wordVal=0;
  triWordCount=0;
  
  while(words.read(letter,1))
  {
    value=((int)*letter)-64;
    if(value>0)
      wordVal+=value;
    else
    {
      if(wordVal>biggestTriNum)
      {
	std::cout << "More triangular numbers needed, wordval: " << wordVal;
	return 0;
      }
      isTriWord=false;
      for(int i=0; i<TRINUMCOUNT; i++)
      {
	if(wordVal==triNum[i])
	  isTriWord=true;
      }
      if(isTriWord)
	triWordCount++;
      wordVal=0;
    }
  }
  
  std::cout << "TriWordCount: " << triWordCount << std::endl;
  delete letter;
  words.close();
  return 0;
}
