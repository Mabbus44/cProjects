#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char **argv) {
  fstream mesFile;                                      //File with encrypted message
  fstream wordFile;                                     //File with english words
  string ascii;                                         //Ascii code read from file
  string word;                                          //Word consising of the latest decrypted letters
  string wordList[1100];                                //List of english words
  char letter;                                          //Latest decrypted letter
  char pass[3];                                         //Password to decrypt with
  char bestPass[3];                                     //Best password
  char mesFileCopy[4000];                               //Copy of mesFile
  int passPos=0;                                        //Current position in password to decrypt with
  int num;                                              //Ascii code of letter
  int wordCount=0;                                      //Number of words in list of english words (should be 106902 due to a few words like don't)
  int foundWordCount=0;                                 //Number of words found in decrypted message
  int foundSegmentCount=0;                              //Number of segments (groups of letters without non letter characters inbetween them)
  int mesFileLength=0;                                  //Number of characters in message file
  int asciiVal=0;                                       //Sum of all ASCII values
  double percentWords;                                  //Percent words in decrypted message
  double bestPercentWords=0;                            //Best percent words in decrypted message
  bool letterPresent = false;                           //If word contains at least 1 letter

  wordFile.open("words.txt",ios_base::in);              //Open file with english words
  pass[0]='a';
  pass[1]='a';
  pass[2]='a';
  while(wordFile.read(&letter,1)){                      //Read from list of english words
    if((int)letter >= 97 && (int)letter <= 122){        //If it is a letter
      word += letter;                                   //Add it to current word
      letterPresent = true;                             //At least one letter is now present
    }
    else if(letterPresent){                             //If char was not a letter and word contains at least one letter, end the word
      wordList[wordCount] = word;                       //Add the word to the list
      wordCount++;
      word.clear();
      letterPresent = false;
    }
  }
  word.clear();
  letterPresent = false;
  cout << endl << "WordCount: " << wordCount << endl << endl;
  wordFile.close();                                     //Close file with encrypted message
  
  mesFile.open("text.txt",ios_base::in);                //Open file with encrypted message
  while(mesFile.read(&letter,1)){                       //Copy file to ram
    mesFileCopy[mesFileLength] = letter;
    mesFileLength++;
  }
  mesFile.close();                                      //Close file with encrypted message
  
  /*for(pass[0] = 97; pass[0] <= 122; pass[0]++){                       //Go through all passwords
    for(pass[1] = 97; pass[1] <= 122; pass[1]++){
      for(pass[2] = 97; pass[2] <= 122; pass[2]++){
        passPos = 0;                                            //Start to encrypt with first letter in password
        foundWordCount = 0;                                     //Reset wordcounts
        foundSegmentCount = 0;
        for(int i2 = 0; i2<mesFileLength; i2++){                //Go through message
          letter=mesFileCopy[i2];                               
          if(letter!=','){                                      //If char is not "'"
            ascii += letter;                                    //Add digit to current number
          }
          else{                                         
            istringstream (ascii) >> num;                       //Else number string to int
            letter = pass[passPos] ^num;                        //Decrypt ascii code
            ascii.clear();                                      //Clear number
            passPos++;                                          //Decrypt with next letter in passpos next time
            if(passPos>2)
              passPos=0;
            if((int)letter >= 65 && (int)letter <= 90)          //If capital letter then make it not capital
              letter+=32;
            if((int)letter >= 97 && (int)letter <= 122){        //If it is a letter
              word += letter;                                   //Add it to current word
              letterPresent = true;                             //At least one letter is now present
            }
            else if(letterPresent){                             //If char was not a letter and word contains at least one letter, end the word
              for(int i=0; i<wordCount; i++){                   //Check if the word is in the wordlist
                if(word == wordList[i]){
                  foundWordCount++;
                  i = wordCount;
                }
              }
              foundSegmentCount++;
              word.clear();
              letterPresent = false;
            }
          }
        }
        for(int i=0; i<wordCount; i++){                         //Check if the last word is in the wordlist                     
          if(word == wordList[i]){
            foundWordCount++;
            i = wordCount;
          }
        }
        foundSegmentCount++;
        word.clear();
        letterPresent = false;
        percentWords = (double)foundWordCount/(double)foundSegmentCount;        //Calculate what percent of letter segments is actual words
        if(percentWords > bestPercentWords){                                    //Save best percentage
          bestPass[0] = pass[0];
          bestPass[1] = pass[1];
          bestPass[2] = pass[2];
          bestPercentWords = percentWords;
          cout << pass[0] << pass[1] << pass[2] << endl;
          cout << foundWordCount << "/" << foundSegmentCount << "=" << (double)foundWordCount/(double)foundSegmentCount << endl << endl;
        }
      }
    }
  }*/
  
  pass[0] = 'd
