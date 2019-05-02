#include <iostream>
#include <vector>
#include <set>
#include <time.h>
#include "RubixCube.h"

void generateCubesVector(int maxGenerations, bool outputProgress = false);
void generateCubesSet(int maxGenerations, bool outputProgress = false);

int main()
{
  int generations = 7;
  generateCubesVector(3);
  generateCubesSet(9);
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

  std::cout << std::endl << "generateCubesVector() done" << std::endl;
  for(unsigned int i=0; i<gVector.size(); i++)
    std::cout << "Generation " << i+1 << ": " << gVector[i] << " in " << tVector[i] << " seconds" << std::endl;
}


void generateCubesSet(int maxGenerations, bool outputProgress)
{
  time_t timeStart, timeFinish;
  double timePassed;
  time(&timeStart);
  CubeContainer child;
  CubeContainer rotChild;
  RubixCube* r;
  RubixCube* lastChild;
  CubeContainer c;
  std::set<CubeContainer> rSet;
  std::vector<int> gVector;
  std::vector<double> tVector;
  RubixCube* trackGenerations[50];
  bool unique;
  bool moveUp;
  int generation;
  int totalPopulation;

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


  r = new RubixCube;
  for(int side = 0; side<6; side++)
    for(int square = 0; square<8; square++)
      r->colors[side][square] = arr[side][square];
  c.cube = r;
  trackGenerations[0] = r;
  rSet.insert(c);
  gVector.push_back(1);
  totalPopulation = 1;
  tVector.push_back(0);
  generation = 1;
  while(generation < maxGenerations)
  {
    moveUp = false;
    int generationForTracking = 1;
    while(generationForTracking > 1 || !moveUp)
    {
      if(generation == generationForTracking)
      {
        lastChild = NULL;
        for(int move=0; move<12; move++)
        { //Create new children
          child.cube = new RubixCube;
          *(child.cube) = trackGenerations[generationForTracking-1]->returnChild(move);
          unique = true;
          for(int rot=0; rot<24 && unique; rot++)
          {
            rotChild = child.cube->returnRot(rot);
            if(rSet.find(rotChild) != rSet.end())
              unique = false;
          }
          if(unique)
          {
            child.cube->parent = trackGenerations[generationForTracking-1];
            if(lastChild)
              lastChild->sibling = child.cube;
            else
              trackGenerations[generationForTracking-1]->firstChild = child.cube;
            rSet.insert(child);
            lastChild = child.cube;
          }
          else
            delete child.cube;
        }
      }
      if(generation == generationForTracking)
      {
        if(trackGenerations[generationForTracking-1]->sibling)
        { //If in repopulating generation go to next sibling.
          trackGenerations[generationForTracking-1] = trackGenerations[generationForTracking-1]->sibling;
          moveUp = false;
        }
        else
        { //If in repopulating and no sibling, move one generation up.
          if(generationForTracking>1)
            generationForTracking--;
          moveUp = true;
        }
      }
      else
      {
        if(!moveUp && trackGenerations[generationForTracking-1]->firstChild)
        { //If not in repopulating generation and did not recently move up and has a child, go to that child
          trackGenerations[generationForTracking] = trackGenerations[generationForTracking-1]->firstChild;
          generationForTracking++;
          moveUp = false;
        }
        else if(trackGenerations[generationForTracking-1]->sibling)
        { //If just moved up or no child, go to next sibling
          trackGenerations[generationForTracking-1] = trackGenerations[generationForTracking-1]->sibling;
          moveUp = false;
        }
        else
        { //If just moved up or no child and no sibling, move one generation up
          if(generationForTracking>1)
            generationForTracking--;
          moveUp = true;
        }
      }
    }
    gVector.push_back(rSet.size() - totalPopulation);
    totalPopulation += gVector[generation];
    time(&timeFinish);
    timePassed = difftime(timeFinish, timeStart);
    tVector.push_back(timePassed);
    generation++;
  }

  std::cout << std::endl << "generateCubesSet() done" << std::endl;
  for(unsigned int i=0; i<gVector.size(); i++)
    std::cout << "Generation " << i+1 << ": " << gVector[i] << " in " << tVector[i] << " seconds" << std::endl;
  delete rotChild.cube;
}
