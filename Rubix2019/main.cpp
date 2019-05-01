#include <iostream>
#include <vector>
#include <set>
#include <time.h>
#include "RubixCube.h"

void generateCubesVector(int maxGenerations, bool outputProgress = false);
void generateCubesSet(int maxGenerations, bool outputProgress = false);

int main()
{
  generateCubesVector(6);
}

void generateCubesVector(int maxGenerations, bool outputProgress)
{
  time_t timeStart, timeFinish;
  double timePassed;
  time(&timeStart);
  RubixCube child, rotChild;
  RubixCube r;
  std::vector<RubixCube> rVector;
  std::vector<int> gVector;
  std::vector<double> tVector;
  bool unique;
  int parentIndex;
  int generation;
  int generationEnd;
  int showNext =0;

  __int8 arr[6][8] = {
           {0, 0, 0,
            0,    0,
            0, 0, 0},
                      {1, 1, 1,
                       1,    1,
                       1, 1, 1},
                                {2, 2, 2,
                                 2,    2,
                                 2, 2, 2},
                                          {3, 3, 3,
                                           3,    3,
                                           3, 3, 3},
                      {4, 4, 4,
                       4,    4,
                       4, 4, 4},

                      {5, 5, 5,
                       5,    5,
                       5, 5, 5}};


  for(int side = 0; side<6; side++)
    for(int square = 0; square<8; square++)
      r.colors[side][square] = arr[side][square];
  rVector.push_back(r);
  gVector.push_back(1);
  tVector.push_back(0);
  parentIndex = 0;
  generation = 1;
  generationEnd = 0;
  while(generation < maxGenerations)
  {
    for(int move=0; move<12; move++)
    {
      child = rVector[parentIndex].returnChild(move);
      unique = true;
      for(int rot=0; rot<24 && unique; rot++)
      {
        rotChild = child.returnRot(rot);
        int vectorSize = rVector.size();
        for(int i = 0; i<vectorSize && unique; i++)
          if(rotChild == rVector[i])
            unique = false;
      }
      if(unique)
        rVector.push_back(child);
    }
    parentIndex++;
    if(parentIndex>showNext)
    {
      if(outputProgress)
        std::cout << generation << ":" << parentIndex << "/" << generationEnd << std::endl;
      showNext += (gVector[generation-1]/20+1);
    }
    if(parentIndex > generationEnd)
    {
      if(outputProgress)
      {
        int genPop = gVector[generation-1];
        int newChildren = rVector.size() - generationEnd-1;
        double fertility = (newChildren) / ((double)genPop*12.0)*100.0;
        std::cout << std::endl << "Generation " << generation << std::endl;
        std::cout << "Total population " << generationEnd+1 << std::endl;
        std::cout << "Generation population " << genPop << std::endl;
        std::cout << "New children " << newChildren << " (" << fertility << "%)" << std::endl;
      }
      generation++;
      gVector.push_back(rVector.size() - generationEnd-1);
      time(&timeFinish);
      timePassed = difftime(timeFinish, timeStart);
      tVector.push_back(timePassed);
      generationEnd = rVector.size()-1;
    }
  }

  std::cout << std::endl << "generateCubes() done" << std::endl;
  for(unsigned int i=0; i<gVector.size(); i++)
    std::cout << "Generation " << i+1 << ": " << gVector[i] << " in " << tVector[i] << " seconds" << std::endl;
}


void generateCubesSet(int maxGenerations, bool outputProgress)
{
  time_t timeStart, timeFinish;
  double timePassed;
  time(&timeStart);
  RubixCube* child;
  RubixCube* rotChild;
  RubixCube* r;
  std::set<CubeContainer> rSet;
  std::vector<int> gVector;
  std::vector<double> tVector;
  bool unique;
  int parentIndex;
  int generation;
  int generationEnd;
  int showNext =0;

  __int8 arr[6][8] = {
           {0, 0, 0,
            0,    0,
            0, 0, 0},
                      {1, 1, 1,
                       1,    1,
                       1, 1, 1},
                                {2, 2, 2,
                                 2,    2,
                                 2, 2, 2},
                                          {3, 3, 3,
                                           3,    3,
                                           3, 3, 3},
                      {4, 4, 4,
                       4,    4,
                       4, 4, 4},

                      {5, 5, 5,
                       5,    5,
                       5, 5, 5}};


  for(int side = 0; side<6; side++)
    for(int square = 0; square<8; square++)
      r->colors[side][square] = arr[side][square];
  c.cube = r;
  rSet.insert(c);
  gVector.push_back(1);
  tVector.push_back(0);
  parentIndex = 0;
  generation = 1;
  generationEnd = 0;
  while(generation < maxGenerations)
  {
    for(int move=0; move<12; move++)
    {
      child = rSet[parentIndex].returnChild(move);
      unique = true;
      for(int rot=0; rot<24 && unique; rot++)
      {
        rotChild = child.returnRot(rot);
        int vectorSize = rSet.size();
        for(int i = 0; i<vectorSize && unique; i++)
          if(rotChild == rSet[i])
            unique = false;
      }
      if(unique)
        rSet.push_back(child);
    }
    parentIndex++;
    if(parentIndex>showNext)
    {
      if(outputProgress)
        std::cout << generation << ":" << parentIndex << "/" << generationEnd << std::endl;
      showNext += (gVector[generation-1]/20+1);
    }
    if(parentIndex > generationEnd)
    {
      if(outputProgress)
      {
        int genPop = gVector[generation-1];
        int newChildren = rSet.size() - generationEnd-1;
        double fertility = (newChildren) / ((double)genPop*12.0)*100.0;
        std::cout << std::endl << "Generation " << generation << std::endl;
        std::cout << "Total population " << generationEnd+1 << std::endl;
        std::cout << "Generation population " << genPop << std::endl;
        std::cout << "New children " << newChildren << " (" << fertility << "%)" << std::endl;
      }
      generation++;
      gVector.push_back(rSet.size() - generationEnd-1);
      time(&timeFinish);
      timePassed = difftime(timeFinish, timeStart);
      tVector.push_back(timePassed);
      generationEnd = rSet.size()-1;
    }
  }

  std::cout << std::endl << "generateCubes() done" << std::endl;
  for(unsigned int i=0; i<gVector.size(); i++)
    std::cout << "Generation " << i+1 << ": " << gVector[i] << " in " << tVector[i] << " seconds" << std::endl;
}
