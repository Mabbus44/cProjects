#include "Day10.h"

Day10::Day10()
{
  //ctor
}

Day10::~Day10()
{
  //dtor
}

void Day10::part1(std::string filename){
  loadMap(filename);
  std::set<Point2D> paths;
  int pathSum = 0;
  for(int y=0; y<(int)typoMap.size(); y++){
    for(int x=0; x<(int)typoMap[0].size(); x++){
      if(typoMap[y][x] == 0){
        std::set<Point2D> newpaths = getPaths(x, y, 1);
        paths.insert(newpaths.begin(), newpaths.end());
        pathSum += newpaths.size();
      }
    }
  }
  std::cout << "part 1: " << pathSum << std::endl;
}

void Day10::part2(std::string filename){
  loadMap(filename);
  std::set<Point2D> paths;
  int pathSum = 0;
  for(int y=0; y<(int)typoMap.size(); y++){
    for(int x=0; x<(int)typoMap[0].size(); x++){
      if(typoMap[y][x] == 0){
        int newPaths = getPaths2(x, y, 1);
        pathSum += newPaths;
      }
    }
  }
  std::cout << "part 2: " << pathSum << std::endl;
}

void Day10::loadMap(std::string filename){
  InputLoader loader(filename);
  std::vector<std::vector<char>> input = loader.toVectorChar2d();
  typoMap.clear();
  for(int y=0; y<(int)input.size(); y++){
    typoMap.push_back(std::vector<int>());
    for(int x=0; x<(int)input[0].size(); x++){
      typoMap[y].push_back((int)(input[y][x]) - 48);
    }
  }
}

void Day10::outputMap(){
  for(int y=0; y<(int)typoMap.size(); y++){
    for(int x=0; x<(int)typoMap[0].size(); x++){
      std::cout << typoMap[y][x];
    }
    std::cout << std::endl;
  }
}

std::set<Point2D> Day10::getPaths(int x, int y, int findNum){
  std::set<Point2D> ret;
  for(int dy=-1; dy<2; dy++){
    for(int dx=-1; dx<2; dx++){
      if((dx == 0 && dy != 0) || (dx != 0 && dy == 0)){
        int checkX = x+dx;
        int checkY = y+dy;
        if(checkX >= 0 && checkY >= 0 && checkX < (int)typoMap[0].size() && checkY < (int)typoMap.size()){
          if(typoMap[checkY][checkX] == findNum){
            if(findNum == 9){
              ret.insert(Point2D(checkX, checkY));
            }else{
              std::set<Point2D> newPaths = getPaths(checkX, checkY, findNum+1);
              ret.insert(newPaths.begin(), newPaths.end());
            }
          }
        }
      }
    }
  }
  return ret;
}

int Day10::getPaths2(int x, int y, int findNum){
  int ret = 0;
  for(int dy=-1; dy<2; dy++){
    for(int dx=-1; dx<2; dx++){
      if((dx == 0 && dy != 0) || (dx != 0 && dy == 0)){
        int checkX = x+dx;
        int checkY = y+dy;
        if(checkX >= 0 && checkY >= 0 && checkX < (int)typoMap[0].size() && checkY < (int)typoMap.size()){
          if(typoMap[checkY][checkX] == findNum){
            if(findNum == 9){
              ret++;
            }else{
              ret+= getPaths2(checkX, checkY, findNum+1);
            }
          }
        }
      }
    }
  }
  return ret;
}
