#include <iostream>
#include <vector>
#include <set>
#include <time.h>
#include <chrono>
#include "RubixCube.h"
#include "RubixCube20B.h"
#include "BinaryNode.h"
#include "FileHandler.h"
#include "RubixCube20BF.h"

using namespace std;

void generateCubesVector(int maxGenerations);
void generateCubesSet(int maxGenerations);
void generateCubes20BSet(int maxGenerations);
RubixCube20B* generateCubes20BBinaryNode(int maxGenerations);
void generateCubes20BF();
void compareCubesToFiles(RubixCube20B* cube);
void printCubes(RubixCube20B* cube);
void printCubesF();

int main()
{
  generateCubesVector(6);
  generateCubesSet(7);
  generateCubes20BSet(8);
  generateCubes20BBinaryNode(8);
  generateCubes20BF();
  //compareCubesToFiles(generateCubes20BBinaryNode(7));
  //printCubes(generateCubes20BBinaryNode(3));
  //printCubesF();
}

void generateCubesVector(int maxGenerations)
{
  auto chronoTimeStart = std::chrono::steady_clock::now();
  auto chronoTimeFinish = std::chrono::steady_clock::now();
  double timePassed;
  RubixCube child, rotChild;
  RubixCube r;
  std::vector<RubixCube> rVector;
  std::vector<int> gVector;
  std::vector<double> tVector;
  bool unique;
  int parentIndex;
  int generation;
  int generationEnd;

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
    if(parentIndex > generationEnd)
    {
      generation++;
      gVector.push_back(rVector.size() - generationEnd-1);

      chronoTimeFinish = std::chrono::steady_clock::now();
      timePassed = (std::chrono::duration_cast<std::chrono::microseconds>(chronoTimeFinish - chronoTimeStart).count())/1000000.0;
      tVector.push_back(timePassed);
      generationEnd = rVector.size()-1;
    }
  }

  std::cout << "generateCubesVector() done" << std::endl;
  for(unsigned int i=0; i<gVector.size(); i++)
    std::cout << "Generation " << i+1 << ": " << gVector[i] << " in " << tVector[i] << " seconds" << std::endl;
  std::cout << std::endl;
}


void generateCubesSet(int maxGenerations)
{
  auto chronoTimeStart = std::chrono::steady_clock::now();
  auto chronoTimeFinish = std::chrono::steady_clock::now();
  double timePassed;
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

    chronoTimeFinish = std::chrono::steady_clock::now();
    timePassed = (std::chrono::duration_cast<std::chrono::microseconds>(chronoTimeFinish - chronoTimeStart).count())/1000000.0;
    std::cout << "Generation " << generation+1 << "/" << maxGenerations << ": " << gVector[generation] << " in " << timePassed << " seconds" << std::endl;

    tVector.push_back(timePassed);
    generation++;
  }

  std::cout << "generateCubesSet() done" << std::endl;
  for(unsigned int i=0; i<gVector.size(); i++)
    std::cout << "Generation " << i+1 << ": " << gVector[i] << " in " << tVector[i] << " seconds" << std::endl;
  std::cout << std::endl;
  delete rotChild.cube;
}


void generateCubes20BSet(int maxGenerations)
{
  auto chronoTimeStart = std::chrono::steady_clock::now();
  auto chronoTimeFinish = std::chrono::steady_clock::now();
  double timePassed;
  CubeContainer20B child;
  CubeContainer20B rotChild;
  RubixCube20B* r;
  RubixCube20B* lastChild;
  CubeContainer20B c;
  std::set<CubeContainer20B> rSet;
  std::vector<int> gVector;
  std::vector<double> tVector;
  RubixCube20B* trackGenerations[50];
  bool unique;
  bool moveUp;
  int generation;
  int totalPopulation;

  r = new RubixCube20B;
  for(int side = 0; side<12; side++)
      r->sides[side] = side*2+1;
  for(int corner = 0; corner<8; corner++)
      r->corners[corner] = corner*4+1;
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
          child.cube = new RubixCube20B;
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

    chronoTimeFinish = std::chrono::steady_clock::now();
    timePassed = (std::chrono::duration_cast<std::chrono::microseconds>(chronoTimeFinish - chronoTimeStart).count())/1000000.0;
    std::cout << "Generation " << generation+1 << "/" << maxGenerations << ": " << gVector[generation] << " in " << timePassed << " seconds" << std::endl;

    tVector.push_back(timePassed);
    generation++;
  }

  std::cout << "generateCubes20BSet() done" << std::endl;
  for(unsigned int i=0; i<gVector.size(); i++)
    std::cout << "Generation " << i+1 << ": " << gVector[i] << " in " << tVector[i] << " seconds" << std::endl;
  delete rotChild.cube;
  std::cout << std::endl;
}


RubixCube20B* generateCubes20BBinaryNode(int maxGenerations)
{
  auto chronoTimeStart = std::chrono::steady_clock::now();
  auto chronoTimeFinish = std::chrono::steady_clock::now();
  double timePassed;
  RubixCube20B* child;
  RubixCube20B rotChild;
  RubixCube20B* r;
  RubixCube20B* lastChild;
  BinaryNode<RubixCube20B>* rSet = new BinaryNode<RubixCube20B>;
  std::vector<int> gVector;
  std::vector<double> tVector;
  RubixCube20B* trackGenerations[50];
  bool unique;
  bool moveUp;
  int generation;
  int populationUpuntilLastGeneration;
  int totalPopulation;

  r = new RubixCube20B;
  for(int side = 0; side<12; side++)
      r->sides[side] = side*2+1;
  for(int corner = 0; corner<8; corner++)
      r->corners[corner] = corner*4+1;
  trackGenerations[0] = r;
  rSet->cubePointer = r;
  gVector.push_back(1);
  populationUpuntilLastGeneration = 1;
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
          child = new RubixCube20B;
          *(child) = trackGenerations[generationForTracking-1]->returnChild(move);
          unique = true;
          for(int rot=0; rot<24 && unique; rot++)
          {
            rotChild = child->returnRot(rot);
            if(rSet->find(&rotChild))
              unique = false;
          }
          if(unique)
          {
            child->parent = trackGenerations[generationForTracking-1];
            if(lastChild)
              lastChild->sibling = child;
            else
              trackGenerations[generationForTracking-1]->firstChild = child;
            rSet->insert(child);
            lastChild = child;
            totalPopulation++;
            while(rSet->parent)
              rSet = rSet->parent;
            if(false)
            {
              std::cout << std::endl << std::endl << "Printing binary tree (move " << move << ")" << std::endl;
              rSet->print();
            }
          }
          else
            delete child;
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
    gVector.push_back(totalPopulation - populationUpuntilLastGeneration);
    populationUpuntilLastGeneration += gVector[generation];

    chronoTimeFinish = std::chrono::steady_clock::now();
    timePassed = (std::chrono::duration_cast<std::chrono::microseconds>(chronoTimeFinish - chronoTimeStart).count())/1000000.0;
    std::cout << "Generation " << generation+1 << "/" << maxGenerations << ": " << gVector[generation] << " in " << timePassed << " seconds" << std::endl;

    tVector.push_back(timePassed);
    generation++;
  }

  std::cout << "generateCubes20BBinaryNode() done" << std::endl;
  for(unsigned int i=0; i<gVector.size(); i++)
    std::cout << "Generation " << i+1 << ": " << gVector[i] << " in " << tVector[i] << " seconds" << std::endl;
  std::cout << std::endl;
  return trackGenerations[0];
}


void compareCubesToFiles(RubixCube20B* cube)
{
  RubixCube20B* trackGenerations[50];
  RubixCube20BF* trackGenerationsF[50];
  bool moveUp;
  bool comparedCube = true;
  int compareGenration = 1;
  FileHandler* fh = new FileHandler();
  __int64 generation;
  __int64 populationUpuntilLastGeneration;
  __int64 totalPopulation;
  __int64 checkingCube;

  if(!fh->openStatsFile("C:\\cubes\\stats"))
    return;
  fh->loadStats(&checkingCube, &totalPopulation, &populationUpuntilLastGeneration, &generation, true);
  __int64 nextFileAt = CUBES_PER_FILE + 1;
  __int64 tempCubeCount = totalPopulation;
  int fileCount = 1;
  while(tempCubeCount>CUBES_PER_FILE)
  {
    tempCubeCount-=CUBES_PER_FILE;
    nextFileAt+=nextFileAt;
    fileCount++;
  }
  for(int i=0; i<fileCount; i++)
  {
    if(!fh->openCubeFile("C:\\cubes\\cube"))
      return;
    if(!fh->openNodeFile("C:\\cubes\\node"))
      return;
  }

  if(checkingCube == 1)
  {
    std::cout << "No cubes to print, exiting compareCubesToFiles()" << std::endl;
    return;
  }

  trackGenerations[0] = cube;
  trackGenerationsF[0] = fh->loadCube(1);
  for(int i=1; i<50; i++)
  {
    trackGenerations[i] = NULL;
    trackGenerationsF[i] = NULL;
  }
  while(comparedCube)
  {
    comparedCube = false;
    moveUp = false;
    int generationForTracking = 1;
    while(generationForTracking > 1 || !moveUp)
    {
      if(compareGenration == generationForTracking)
      {//Compare cubes
        if(!comparedCube)
        {
          std::cout << std::endl << "Generation " << compareGenration << std::endl;
          comparedCube = true;
        }
        if(!(*(trackGenerations[generationForTracking-1]) == *(trackGenerations[generationForTracking-1])))
        {
          std::cout << "Cubes does not match!!" << std::endl;
          std::cout << "FileCube:" << std::endl;
          trackGenerationsF[generationForTracking-1]->print(true);
          std::cout << "RawCube:" << std::endl;
          trackGenerations[generationForTracking-1]->print();
          return;
        }
      }
      if(compareGenration == generationForTracking)
      {
        if(trackGenerationsF[generationForTracking-1]->sibling)
        { //If in comparing generation go to next sibling.
          if(!trackGenerations[generationForTracking-1]->sibling)
          {
            std::cout << "Cube does not have sibling while cubeF does" << std::endl;
          }
          __int64 sibling = trackGenerationsF[generationForTracking-1]->sibling;
          delete trackGenerationsF[generationForTracking-1];
          trackGenerationsF[generationForTracking-1] = fh->loadCube(sibling);
          trackGenerations[generationForTracking-1] = trackGenerations[generationForTracking-1]->sibling;
          moveUp = false;
        }
        else
        { //If in comparing and no sibling, move one generation up.
          if(trackGenerations[generationForTracking-1]->sibling)
          {
            std::cout << "CubeF does not have sibling while cube does" << std::endl;
          }
          if(generationForTracking>1)
            generationForTracking--;
          moveUp = true;
        }
      }
      else
      {
        if(!moveUp && trackGenerationsF[generationForTracking-1]->firstChild)
        { //If not in comparing generation and did not recently move up and has a child, go to that child
          if(!trackGenerations[generationForTracking-1]->firstChild)
          {
            std::cout << "Cube does not have child while cubeF does" << std::endl;
          }
          __int64 firstChild = trackGenerationsF[generationForTracking-1]->firstChild;
          delete trackGenerationsF[generationForTracking];
          trackGenerationsF[generationForTracking] = fh->loadCube(firstChild);
          trackGenerations[generationForTracking] = trackGenerations[generationForTracking-1]->firstChild;
          generationForTracking++;
          moveUp = false;
        }
        else if(trackGenerationsF[generationForTracking-1]->sibling)
        { //If just moved up or no child, go to next sibling
          if(!trackGenerations[generationForTracking-1]->sibling)
          {
            std::cout << "Cube does not have sibling while cubeF does" << std::endl;
          }
          __int64 sibling = trackGenerationsF[generationForTracking-1]->sibling;
          delete trackGenerationsF[generationForTracking-1];
          trackGenerationsF[generationForTracking-1] = fh->loadCube(sibling);
          trackGenerations[generationForTracking-1] = trackGenerations[generationForTracking-1]->sibling;
          moveUp = false;
        }
        else
        { //If just moved up or no child and no sibling, move one generation up
          if(trackGenerations[generationForTracking-1]->sibling || (!moveUp && trackGenerations[generationForTracking-1]->firstChild))
          {
            std::cout << "CubeF does not have sibling or child while cube does" << std::endl;
          }
          if(generationForTracking>1)
            generationForTracking--;
          moveUp = true;
        }
      }
    }
    compareGenration++;
  }

  std::cout << "compareCubesToFiles() done" << std::endl;
}


void generateCubes20BF()
{
  auto chronoTimeStart = std::chrono::steady_clock::now();
  auto chronoTimeFinish = std::chrono::steady_clock::now();
  double timePassed;
  __int64 statsInterval = 1;
  __int64 nextStats = 0;
  __int64 lastStats;

  RubixCube20BF* child;
  RubixCube20BF rotChild;
  RubixCube20BF* r;
  BinaryNodeF* topNode;
  __int64 lastChild;
  bool unique;
  __int64 aditionalChecks;
  __int64 checkLimit;
  __int64 generation;
  __int64 populationUpuntilLastGeneration;
  __int64 totalPopulation;
  __int64 checkingCube;

  FileHandler* fh = new FileHandler();
  if(!fh->openStatsFile("C:\\cubes\\stats"))
    return;
  fh->loadStats(&checkingCube, &totalPopulation, &populationUpuntilLastGeneration, &generation, true);
  __int64 nextFileAt = CUBES_PER_FILE + 1;
  __int64 tempCubeCount = totalPopulation;
  int fileCount = 1;
  while(tempCubeCount>CUBES_PER_FILE)
  {
    tempCubeCount-=CUBES_PER_FILE;
    nextFileAt+=nextFileAt;
    fileCount++;
  }
  for(int i=0; i<fileCount; i++)
  {
    if(!fh->openCubeFile("C:\\cubes\\cube"))
      return;
    if(!fh->openNodeFile("C:\\cubes\\node"))
      return;
  }

  if(checkingCube == 1)
  {
    r = new RubixCube20BF;
    for(int side = 0; side<12; side++)
      r->sides[side] = side*2+1;
    for(int corner = 0; corner<8; corner++)
      r->corners[corner] = corner*4+1;
    r->adress = 1;
    topNode = new BinaryNodeF();
    topNode->adress = 1;
    fh->saveCube(r);
    fh->saveNode(topNode);
    delete r;
  }
  else
  {
    __int64 topNodeAdress = 1;
    while(fh->loadNodeParent(topNodeAdress))
      topNodeAdress = fh->loadNodeParent(topNodeAdress);
    topNode = new BinaryNodeF();
    topNode = fh->loadNode(topNodeAdress);
  }
  checkLimit = checkingCube-1;
  cout << "How many cubes to check?: ";
  cin >> aditionalChecks;
  cout << endl;
  checkLimit += aditionalChecks;
  chronoTimeStart = std::chrono::steady_clock::now();
  lastStats = checkingCube;
  while(checkingCube <= checkLimit)
  {
    RubixCube20BF* cube = fh->loadCube(checkingCube);
    lastChild = 0;
    for(int move=0; move<12; move++)
    { //Create new children
      child = new RubixCube20BF;
      *(child) = cube->returnChild(move);
      unique = true;
      for(int rot=0; rot<24 && unique; rot++)
      {
        rotChild = child->returnRot(rot);
        if(topNode->find(&rotChild, fh))
          unique = false;
      }
      if(unique)
      {
        totalPopulation++;
        if(totalPopulation == nextFileAt)
        {
          nextFileAt += CUBES_PER_FILE;
          if(!fh->openCubeFile("C:\\cubes\\cube"))
            return;
          if(!fh->openNodeFile("C:\\cubes\\node"))
            return;
        }
        child->parent = checkingCube;
        child->adress = totalPopulation;
        if(lastChild)
          fh->saveCubeSibling(lastChild, totalPopulation);
        else
          fh->saveCubeFirstChild(cube->adress, totalPopulation);
        topNode->insert(child, fh);
        lastChild = child->adress;
        fh->saveCube(child);
        delete child;
        __int64 newTop = fh->loadNodeParent(topNode->adress);
        if(!newTop)
          newTop = topNode->adress;
       delete topNode;
        topNode = fh->loadNode(newTop);
      }
      else
        delete child;
    }
    delete cube;
    if(true || checkingCube >= nextStats)
    {
      /*chronoTimeFinish = std::chrono::steady_clock::now();
      timePassed = (std::chrono::duration_cast<std::chrono::seconds>(chronoTimeFinish - chronoTimeStart).count())/1.0;

      if(timePassed < 5.0)
        statsInterval*=2;
      else if(timePassed < 10.0)
        statsInterval++;
      else
        statsInterval--;
      nextStats = checkingCube+statsInterval;*/
      cout << "Cubes checked: " << checkingCube << "/" << populationUpuntilLastGeneration << " (" << totalPopulation << ")"<<endl;//(" << timePassed/((double)(checkingCube-lastStats)) << " c/s)" << endl;
/*      lastStats = checkingCube;
      chronoTimeStart = std::chrono::steady_clock::now();*/
    }
    if(checkingCube >= populationUpuntilLastGeneration)
    {
      cout << "Making offspring for generation " << generation << " done" << endl;
      cout << "Cubes checked: " << checkingCube << endl;
      cout << "New cubes in this generation: " << totalPopulation-populationUpuntilLastGeneration << endl;
      cout << "Total cubes: " << totalPopulation << endl << endl;
      populationUpuntilLastGeneration = totalPopulation;
      generation++;
    }
    checkingCube++;
  }
  cout << "Run ended at generation " << generation << endl;
  cout << "Cubes checked: " << checkingCube-1 << endl;
  cout << "New cubes in this generation: " << totalPopulation-populationUpuntilLastGeneration << endl;
  cout << "Total cubes: " << totalPopulation << endl << endl;

  fh->saveStats(checkingCube, totalPopulation, populationUpuntilLastGeneration, generation);

  std::cout << "generateCubes20BF() done" << std::endl;

  //printCubes(8, fh);

  for(unsigned int i=0; i<fh->cubeFile.size(); i++)
    fh->cubeFile[i]->close();
  for(unsigned int i=0; i<fh->nodeFile.size(); i++)
    fh->nodeFile[i]->close();
  fh->statsFile.close();
  delete fh;
}


void printCubes(RubixCube20B* cube)
{
  RubixCube20B* trackGenerations[50];
  bool moveUp;
  bool printedCube = true;
  int printGenration = 1;
  trackGenerations[0] = cube;
  while(trackGenerations[0]->parent)
  {
    trackGenerations[0] = trackGenerations[0]->parent;
  }

  while(printedCube)
  {
    printedCube = false;
    moveUp = false;
    int generationForTracking = 1;
    while(generationForTracking > 1 || !moveUp)
    {
      if(printGenration == generationForTracking)
      {//Print cube
        if(!printedCube)
        {
          std::cout << "Generation " << printGenration << std::endl;
          printedCube = true;
        }
        trackGenerations[generationForTracking-1]->print();
      }
      if(printGenration == generationForTracking)
      {
        if(trackGenerations[generationForTracking-1]->sibling)
        { //If in printing generation go to next sibling.
          trackGenerations[generationForTracking-1] = trackGenerations[generationForTracking-1]->sibling;
          moveUp = false;
        }
        else
        { //If in printing and no sibling, move one generation up.
          if(generationForTracking>1)
            generationForTracking--;
          moveUp = true;
        }
      }
      else
      {
        if(!moveUp && trackGenerations[generationForTracking-1]->firstChild)
        { //If not in printing generation and did not recently move up and has a child, go to that child
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
    printGenration++;
  }

  std::cout << "printCubes() done" << std::endl;
}


void printCubesF()
{
  RubixCube20BF* trackGenerations[50];
  bool moveUp;
  bool printedCube = true;
  int printGenration = 1;
  FileHandler* fh = new FileHandler();
  __int64 generation;
  __int64 populationUpuntilLastGeneration;
  __int64 totalPopulation;
  __int64 checkingCube;

  if(!fh->openStatsFile("C:\\cubes\\stats"))
    return;
  fh->loadStats(&checkingCube, &totalPopulation, &populationUpuntilLastGeneration, &generation, true);
  __int64 nextFileAt = CUBES_PER_FILE + 1;
  __int64 tempCubeCount = totalPopulation;
  int fileCount = 1;
  while(tempCubeCount>CUBES_PER_FILE)
  {
    tempCubeCount-=CUBES_PER_FILE;
    nextFileAt+=nextFileAt;
    fileCount++;
  }
  for(int i=0; i<fileCount; i++)
  {
    if(!fh->openCubeFile("C:\\cubes\\cube"))
      return;
    if(!fh->openNodeFile("C:\\cubes\\node"))
      return;
  }

  if(checkingCube == 1)
  {
    std::cout << "No cubes to print, exiting printCubesF()" << std::endl;
  }

  trackGenerations[0] = fh->loadCube(1);
  for(int i=1; i<50; i++)
  {
    trackGenerations[i] = NULL;
  }
  while(printedCube)
  {
    printedCube = false;
    moveUp = false;
    int generationForTracking = 1;
    while(generationForTracking > 1 || !moveUp)
    {
      if(printGenration == generationForTracking)
      {//Print cube
        if(!printedCube)
        {
          std::cout << std::endl << "Generation " << printGenration << std::endl;
          printedCube = true;
        }
        trackGenerations[generationForTracking-1]->print(true);
        std::cout << std::endl;
      }
      if(printGenration == generationForTracking)
      {
        if(trackGenerations[generationForTracking-1]->sibling)
        { //If in printing generation go to next sibling.
          __int64 sibling = trackGenerations[generationForTracking-1]->sibling;
          delete trackGenerations[generationForTracking-1];
          trackGenerations[generationForTracking-1] = fh->loadCube(sibling);
          moveUp = false;
        }
        else
        { //If in printing and no sibling, move one generation up.
          if(generationForTracking>1)
            generationForTracking--;
          moveUp = true;
        }
      }
      else
      {
        if(!moveUp && trackGenerations[generationForTracking-1]->firstChild)
        { //If not in printing generation and did not recently move up and has a child, go to that child
          __int64 firstChild = trackGenerations[generationForTracking-1]->firstChild;
          delete trackGenerations[generationForTracking];
          trackGenerations[generationForTracking] = fh->loadCube(firstChild);
          generationForTracking++;
          moveUp = false;
        }
        else if(trackGenerations[generationForTracking-1]->sibling)
        { //If just moved up or no child, go to next sibling
          __int64 sibling = trackGenerations[generationForTracking-1]->sibling;
          delete trackGenerations[generationForTracking-1];
          trackGenerations[generationForTracking-1] = fh->loadCube(sibling);
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
    printGenration++;
  }

  std::cout << "printCubesF() done" << std::endl;
}
