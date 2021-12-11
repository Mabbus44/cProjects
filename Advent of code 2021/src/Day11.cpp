#include "Day11.h"

Day11::Day11()
{
  //ctor
}

Day11::~Day11()
{
  //dtor
}

void Day11::part1(string filename){
  InputLoader loader(filename);
  vector<vector<char>> vvc = loader.toVectorChar2d();
  Dumbo dumbos[10][10];
  for(int row=0; row<10; row++){
    for(int col=0; col<10; col++){
      Dumbo d;
      d.energy = (int)vvc[row][col]-48;
      dumbos[row][col] = d;
    }
  }
  int totalFlashes = 0;
  for(int reps=0; reps<100; reps++){
    for(int row=0; row<10; row++){
      for(int col=0; col<10; col++){
        dumbos[row][col].energy++;
      }
    }
    bool oneFlash=true;
    while(oneFlash){
      oneFlash = false;
      for(int row=0; row<10; row++){
        for(int col=0; col<10; col++){
          if(dumbos[row][col].energy>9 && !dumbos[row][col].flashed){
            dumbos[row][col].flashed = true;
            dumbos[row][col].spreadEnergy = true;
            oneFlash = true;
            totalFlashes++;
          }
        }
      }
      for(int row=0; row<10; row++){
        for(int col=0; col<10; col++){
          if(dumbos[row][col].spreadEnergy){
            dumbos[row][col].spreadEnergy = false;
            for(int row2=row-1; row2<=row+1; row2++){
              for(int col2=col-1; col2<=col+1; col2++){
                if(row2>=0 && row2 <=9 && col2>=0 && col2 <= 9){
                  dumbos[row2][col2].energy++;
                }
              }
            }
          }
        }
      }
    }
    for(int row=0; row<10; row++){
      for(int col=0; col<10; col++){
        if(dumbos[row][col].flashed){
          dumbos[row][col].flashed = false;
          dumbos[row][col].energy = 0;
        }
      }
    }
  }
  cout << "Part 1: " << totalFlashes << endl;
}

void Day11::part2(string filename){
  InputLoader loader(filename);
  vector<vector<char>> vvc = loader.toVectorChar2d();
  Dumbo dumbos[10][10];
  for(int row=0; row<10; row++){
    for(int col=0; col<10; col++){
      Dumbo d;
      d.energy = (int)vvc[row][col]-48;
      dumbos[row][col] = d;
    }
  }
  int totalFlashes = 0;
  int step=0;
  while(totalFlashes!=100){
    step++;
    totalFlashes = 0;
    for(int row=0; row<10; row++){
      for(int col=0; col<10; col++){
        dumbos[row][col].energy++;
      }
    }
    bool oneFlash=true;
    while(oneFlash){
      oneFlash = false;
      for(int row=0; row<10; row++){
        for(int col=0; col<10; col++){
          if(dumbos[row][col].energy>9 && !dumbos[row][col].flashed){
            dumbos[row][col].flashed = true;
            dumbos[row][col].spreadEnergy = true;
            oneFlash = true;
            totalFlashes++;
          }
        }
      }
      for(int row=0; row<10; row++){
        for(int col=0; col<10; col++){
          if(dumbos[row][col].spreadEnergy){
            dumbos[row][col].spreadEnergy = false;
            for(int row2=row-1; row2<=row+1; row2++){
              for(int col2=col-1; col2<=col+1; col2++){
                if(row2>=0 && row2 <=9 && col2>=0 && col2 <= 9){
                  dumbos[row2][col2].energy++;
                }
              }
            }
          }
        }
      }
    }
    for(int row=0; row<10; row++){
      for(int col=0; col<10; col++){
        if(dumbos[row][col].flashed){
          dumbos[row][col].flashed = false;
          dumbos[row][col].energy = 0;
        }
      }
    }
  }
  cout << "Part 2: " << step << endl;
}
