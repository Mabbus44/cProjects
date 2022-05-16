#include "Day17.h"

Day17::Day17()
{
  //ctor
}

Day17::~Day17()
{
  //dtor
}

void Day17::part1(string filename){
  InputLoader loader(filename);
  vector<vector<char>> vvc = loader.toVectorChar2d();
  bool cubes[30][30][30];
  bool newCubes[30][30][30];
  for(int x=0; x<30; x++){
    for(int y=0; y<30; y++){
      for(int z=0; z<30; z++){
        cubes[x][y][z] = false;
      }
    }
  }
  for(int x=0; x<8; x++){
    for(int y=0; y<8; y++){
      if(vvc[y][x] == '#'){
        cubes[x+11][y+11][14] = true;
      }
    }
  }
  for(int i=0; i<6; i++){
    for(int x=1; x<29; x++){
      for(int y=1; y<29; y++){
        for(int z=1; z<29; z++){
          int neighbours = 0;
          for(int dx=-1; dx<2; dx++){
            for(int dy=-1; dy<2; dy++){
              for(int dz=-1; dz<2; dz++){
                if(!(dx==0 && dy==0 && dz==0) && cubes[x+dx][y+dy][z+dz]){
                  neighbours++;
                }
              }
            }
          }
          if(neighbours==3 || (neighbours==2 && cubes[x][y][z]))
            newCubes[x][y][z] = true;
          else
            newCubes[x][y][z] = false;
        }
      }
    }
    for(int x=1; x<29; x++){
      for(int y=1; y<29; y++){
        for(int z=1; z<29; z++){
          cubes[x][y][z] = newCubes[x][y][z];
        }
      }
    }
  }
  int activeCount=0;
  for(int x=1; x<29; x++){
    for(int y=1; y<29; y++){
      for(int z=1; z<29; z++){
        if(cubes[x][y][z])
          activeCount++;
      }
    }
  }
  cout << "part 1: " << activeCount << endl;
}

void Day17::part2(string filename){
  InputLoader loader(filename);
  vector<vector<char>> vvc = loader.toVectorChar2d();
  bool cubes[30][30][30][30];
  bool newCubes[30][30][30][30];
  for(int x=0; x<30; x++){
    for(int y=0; y<30; y++){
      for(int z=0; z<30; z++){
        for(int w=0; w<30; w++){
          cubes[x][y][z][w] = false;
        }
      }
    }
  }
  for(int x=0; x<8; x++){
    for(int y=0; y<8; y++){
      if(vvc[y][x] == '#'){
        cubes[x+11][y+11][14][14] = true;
      }
    }
  }
  for(int i=0; i<6; i++){
    for(int x=1; x<29; x++){
      for(int y=1; y<29; y++){
        for(int z=1; z<29; z++){
          for(int w=1; w<29; w++){
            int neighbours = 0;
            for(int dx=-1; dx<2; dx++){
              for(int dy=-1; dy<2; dy++){
                for(int dz=-1; dz<2; dz++){
                  for(int dw=-1; dw<2; dw++){
                    if(!(dx==0 && dy==0 && dz==0 && dw==0) && cubes[x+dx][y+dy][z+dz][w+dw]){
                      neighbours++;
                    }
                  }
                }
              }
            }
            if(neighbours==3 || (neighbours==2 && cubes[x][y][z][w]))
              newCubes[x][y][z][w] = true;
            else
              newCubes[x][y][z][w] = false;
          }
        }
      }
    }
    for(int x=1; x<29; x++){
      for(int y=1; y<29; y++){
        for(int z=1; z<29; z++){
          for(int w=1; w<29; w++){
            cubes[x][y][z][w] = newCubes[x][y][z][w];
          }
        }
      }
    }
  }
  int activeCount=0;
  for(int x=1; x<29; x++){
    for(int y=1; y<29; y++){
      for(int z=1; z<29; z++){
        for(int w=1; w<29; w++){
          if(cubes[x][y][z][w])
            activeCount++;
        }
      }
    }
  }
  cout << "part 2: " << activeCount << endl;
}
