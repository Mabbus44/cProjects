#include "Day08.h"

Day08::Day08()
{
  //ctor
}

Day08::~Day08()
{
  //dtor
}

void Day08::part1(std::string filename){
  InputLoader loader(filename);
  std::vector<std::vector<char>> input = loader.toVectorChar2d();
  int mapSizeX = (int)input[0].size();
  int mapSizeY = (int)input.size();
  std::vector<AntennaFamily> families;
  for(int y=0; y<mapSizeY; y++){
    for(int x=0; x<mapSizeX; x++){
      if(input[y][x] != '.'){
        bool familyExist = false;
        for(AntennaFamily& family: families){
          if(family.family == input[y][x]){
            familyExist = true;
            family.antennas.insert(Point2D(x, y));
          }
        }
        if(!familyExist)
          families.push_back(AntennaFamily(input[y][x], Point2D(x, y)));
      }
    }
  }
  std::set<Point2D> antiNodes;
  for(AntennaFamily& family: families){
    family.addAntiNodes(antiNodes, mapSizeX, mapSizeY);
  }
  std::cout << "part 1: " << antiNodes.size() << std::endl;
}

void Day08::part2(std::string filename){
  InputLoader loader(filename);
  std::vector<std::vector<char>> input = loader.toVectorChar2d();
  int mapSizeX = (int)input[0].size();
  int mapSizeY = (int)input.size();
  std::vector<AntennaFamily> families;
  for(int y=0; y<mapSizeY; y++){
    for(int x=0; x<mapSizeX; x++){
      if(input[y][x] != '.'){
        bool familyExist = false;
        for(AntennaFamily& family: families){
          if(family.family == input[y][x]){
            familyExist = true;
            family.antennas.insert(Point2D(x, y));
          }
        }
        if(!familyExist)
          families.push_back(AntennaFamily(input[y][x], Point2D(x, y)));
      }
    }
  }
  std::set<Point2D> antiNodes;
  for(AntennaFamily& family: families){
    family.addAntiNodes2(antiNodes, mapSizeX, mapSizeY);
  }
  std::cout << "part 2: " << antiNodes.size() << std::endl;
}

void AntennaFamily::addAntiNodes(std::set<Point2D>& antiNodes, int mapSizeX, int mapSizeY){
  std::vector<Point2D> antennasCopy;
  std::copy(antennas.begin(), antennas.end(), std::back_inserter(antennasCopy));
  for(int idA=0; idA<(int)antennasCopy.size(); idA++){
    for(int idB=idA+1; idB<(int)antennasCopy.size(); idB++){
      Point2D diff = antennasCopy[idB] - antennasCopy[idA];
      Point2D antiNode1 = antennasCopy[idB] + diff;
      Point2D antiNode2 = antennasCopy[idA] - diff;
      if(antiNode1.x >= 0 && antiNode1.y >= 0 && antiNode1.x < mapSizeX && antiNode1.y < mapSizeY)
        antiNodes.insert(antiNode1);
      if(antiNode2.x >= 0 && antiNode2.y >= 0 && antiNode2.x < mapSizeX && antiNode2.y < mapSizeY)
        antiNodes.insert(antiNode2);
    }
  }
}

void AntennaFamily::addAntiNodes2(std::set<Point2D>& antiNodes, int mapSizeX, int mapSizeY){
  std::vector<Point2D> antennasCopy;
  std::copy(antennas.begin(), antennas.end(), std::back_inserter(antennasCopy));
  for(int idA=0; idA<(int)antennasCopy.size(); idA++){
    for(int idB=idA+1; idB<(int)antennasCopy.size(); idB++){
      Point2D diff = antennasCopy[idB] - antennasCopy[idA];
      Point2D antiNode1 = antennasCopy[idB];
      Point2D antiNode2 = antennasCopy[idA];
      while(antiNode1.x >= 0 && antiNode1.y >= 0 && antiNode1.x < mapSizeX && antiNode1.y < mapSizeY){
        antiNodes.insert(antiNode1);
        antiNode1 = antiNode1 + diff;
      }
      while(antiNode2.x >= 0 && antiNode2.y >= 0 && antiNode2.x < mapSizeX && antiNode2.y < mapSizeY){
        antiNodes.insert(antiNode2);
        antiNode2 = antiNode2 - diff;
      }
    }
  }
}
