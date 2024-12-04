#include "Day04.h"

Day04::Day04()
{
  //ctor
}

Day04::~Day04()
{
  //dtor
}

void Day04::part1(std::string filename){
  InputLoader loader(filename);
  input = loader.toVectorChar2d();
  int xMasCount = 0;
  for(int x=0; x<(int)input[0].size(); x++){
    for(int y=0; y<(int)input.size(); y++){
      for(int dX=-1; dX <= 1; dX++){
        for(int dY=-1; dY <= 1; dY++){
          if(findXmas(x, y, dX, dY))
            xMasCount++;
        }
      }
    }
  }
  std::cout << "part 1: " << xMasCount << std::endl;
}

void Day04::part2(std::string filename){
  InputLoader loader(filename);
  input = loader.toVectorChar2d();
  int xMasCount = 0;
  for(int x=0; x<(int)input[0].size(); x++){
    for(int y=0; y<(int)input.size(); y++){
      if(findXdashMas(x, y))
        xMasCount++;
    }
  }
  std::cout << "part 2: " << xMasCount << std::endl;
}

bool Day04::findXmas(int x, int y, int dX, int dY){
  int wl=3;
  if(x+wl*dX<0 || x+wl*dX>=(int)input[0].size() || y+wl*dY<0 || y+wl*dY>=(int)input.size())
    return false;
  if(dX==0 && dY==0)
    return false;
  std::string word="XMAS";
  int pos=0;
  while(pos<(int)word.length()){
    if(input[y][x] != word[pos]){
      return false;
    }
    pos++;
    x+=dX;
    y+=dY;
  }
  return true;
}

bool Day04::findXdashMas(int x, int y){
  int wl=1;
  if(x-1<0 || x+1>=(int)input[0].size() || y-1<0 || y+1>=(int)input.size())
    return false;
  if(input[y][x] != 'A')
    return false;
  char tl=input[y-1][x-1];
  char tr=input[y-1][x+1];
  char bl=input[y+1][x-1];
  char br=input[y+1][x+1];

  if((tl == 'M' && br == 'S') || (tl == 'S' && br == 'M')){
    if((tr == 'M' && bl == 'S') || (tr == 'S' && bl == 'M')){
        return true;
    }
  }
  return false;
}
