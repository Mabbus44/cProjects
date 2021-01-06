#include <iostream>
#include <fstream>
#include <string>
#include "FileHandler.h"

using namespace std;

FileHandler::FileHandler()
{
  //ctor
}

FileHandler::~FileHandler()
{
  //dtor
}


bool FileHandler::openNodeFile(string filename)
{
  filename = filename + to_string(nodeFile.size()+1) + ".dat";
  fstream* file = new fstream();
  nodeFile.push_back(file);
  nodeFile[nodeFile.size()-1]->open(filename, ios::in | ios::out | ios::binary);
  if(!nodeFile[nodeFile.size()-1]->is_open())
  {
    if(!createNodeFile(filename))
    {
      cout << "ERROR: Could not create file " << filename << endl;
      return false;
    }
    nodeFile[nodeFile.size()-1]->open(filename, ios::in | ios::out | ios::binary);
    if(!nodeFile[nodeFile.size()-1]->is_open())
    {
      cout << "ERROR: Could not open file " << filename << endl;
      return false;
    }
    cout << "Creating node file...";
    BinaryNodeF* node = new BinaryNodeF();
    node->parent = 0;
    node->smallerChild = 0;
    node->biggerChild = 0;
    node->height = 0;
    for(int i=0; i<CUBES_PER_FILE; i++)
    {
      node->adress = i+1 + (nodeFile.size()-1) * CUBES_PER_FILE;
      saveNode(node);
    }
    delete node;
    cout << "done" << endl;
  }
  return true;
}

bool FileHandler::openCubeFile(string filename)
{
  filename = filename + to_string(cubeFile.size()+1) + ".dat";
  fstream* file = new fstream;
  cubeFile.push_back(file);
  cubeFile[cubeFile.size()-1]->open(filename, ios::in | ios::out | ios::binary);
  if(!cubeFile[cubeFile.size()-1]->is_open())
  {
    if(!createCubeFile(filename))
    {
      cout << "ERROR: Could not create file " << filename << endl;
      return false;
    }
    cubeFile[cubeFile.size()-1]->open(filename, ios::in | ios::out | ios::binary);
    if(!cubeFile[cubeFile.size()-1]->is_open())
    {
      cout << "ERROR: Could not open file " << filename << endl;
      return false;
    }
    cout << "Creating cube file...";
    RubixCube20BF* cube = new RubixCube20BF();
    cube->parent = 0;
    cube->firstChild = 0;
    cube->sibling = 0;
    for(int side = 0; side<12; side++)
        cube->sides[side] = 0;
    for(int corner = 0; corner<8; corner++)
        cube->corners[corner] = 0;
    for(int i=0; i<CUBES_PER_FILE; i++)
    {
      cube->adress = i+1 + (cubeFile.size()-1) * CUBES_PER_FILE;
      saveCube(cube);
    }
    delete cube;
    cout << "done" << endl;
  }
  return true;
}

bool FileHandler::openStatsFile(string filename)
{
  filename = filename + ".dat";
  statsFile.open(filename, ios::in | ios::out | ios::binary);
  if(!statsFile.is_open())
  {
    if(!createStatsFile(filename))
    {
      cout << "ERROR: Could not create file " << filename << endl;
      return false;
    }
    statsFile.open(filename, ios::in | ios::out | ios::binary);
    if(!statsFile.is_open())
    {
      cout << "ERROR: Could not open file " << filename << endl;
      return false;
    }
    cout << "Creating stats file...";
    __int64 setting = 1;
    statsFile.seekp(0);
    statsFile.write((char*)(&setting), 8);
    statsFile.write((char*)(&setting), 8);
    statsFile.write((char*)(&setting), 8);
    statsFile.write((char*)(&setting), 8);
    cout << "done" << endl;
  }
  return true;
}

bool FileHandler::createNodeFile(string filename)
{
  nodeFile[nodeFile.size()-1]->open(filename, ios::out | ios::binary);
  if(!nodeFile[nodeFile.size()-1]->is_open())
    return false;
  nodeFile[nodeFile.size()-1]->close();
  return true;
}

bool FileHandler::createCubeFile(string filename)
{
  cubeFile[cubeFile.size()-1]->open(filename, ios::out | ios::binary);
  if(!cubeFile[cubeFile.size()-1]->is_open())
    return false;
  cubeFile[cubeFile.size()-1]->close();
  return true;
}

bool FileHandler::createStatsFile(string filename)
{
  statsFile.open(filename, ios::out | ios::binary);
  if(!statsFile.is_open())
    return false;
  statsFile.close();
  return true;
}

bool FileHandler::saveCube(RubixCube20BF* cube)
{
  int fileIndex = 0;
  __int64 adress = cube->adress;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  cubeFile[fileIndex]->seekp((adress-1)*44);
  cubeFile[fileIndex]->write(cube->corners, 8);
  cubeFile[fileIndex]->write(cube->sides, 12);
  cubeFile[fileIndex]->write((char*)(&(cube->parent)), 8);
  cubeFile[fileIndex]->write((char*)(&(cube->firstChild)), 8);
  cubeFile[fileIndex]->write((char*)(&(cube->sibling)), 8);
  return true;
}

bool FileHandler::saveCubeFirstChild(__int64 adress, __int64 firstChild)
{
  int fileIndex = 0;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  cubeFile[fileIndex]->seekp((adress-1)*44+28);
  cubeFile[fileIndex]->write((char*)(&(firstChild)), 8);
  return true;
}

bool FileHandler::saveCubeSibling(__int64 adress, __int64 sibling)
{
  int fileIndex = 0;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  cubeFile[fileIndex]->seekp((adress-1)*44+36);
  cubeFile[fileIndex]->write((char*)(&(sibling)), 8);
  return true;
}

RubixCube20BF* FileHandler::loadCube(__int64 adress)
{
  RubixCube20BF* ret = new RubixCube20BF();
  ret->adress = adress;
  int fileIndex = 0;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  cubeFile[fileIndex]->seekg((adress-1)*44);
  cubeFile[fileIndex]->read(ret->corners, 8);
  cubeFile[fileIndex]->read(ret->sides, 12);
  cubeFile[fileIndex]->read((char*)(&(ret->parent)), 8);
  cubeFile[fileIndex]->read((char*)(&(ret->firstChild)), 8);
  cubeFile[fileIndex]->read((char*)(&(ret->sibling)), 8);
  return ret;
}

bool FileHandler::saveNode(BinaryNodeF* node)
{
  int fileIndex = 0;
  __int64 adress = node->adress;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  nodeFile[fileIndex]->seekp((adress-1)*32);
  nodeFile[fileIndex]->write((char*)(&(node->parent)), 8);
  nodeFile[fileIndex]->write((char*)(&(node->smallerChild)), 8);
  nodeFile[fileIndex]->write((char*)(&(node->biggerChild)), 8);
  nodeFile[fileIndex]->write((char*)(&(node->height)), 8);
  return true;
}

BinaryNodeF* FileHandler::loadNode(__int64 adress)
{
  BinaryNodeF* ret = new BinaryNodeF();
  ret->adress = adress;
  int fileIndex = 0;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  nodeFile[fileIndex]->seekg((adress-1)*32);
  nodeFile[fileIndex]->read((char*)(&(ret->parent)), 8);
  nodeFile[fileIndex]->read((char*)(&(ret->smallerChild)), 8);
  nodeFile[fileIndex]->read((char*)(&(ret->biggerChild)), 8);
  nodeFile[fileIndex]->read((char*)(&(ret->height)), 8);
  return ret;
}

__int64 FileHandler::loadNodeParent(__int64 adress)
{
  int fileIndex = 0;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  int ret;
  nodeFile[fileIndex]->seekg((adress-1)*32);
  nodeFile[fileIndex]->read((char*)(&ret), 8);
  return ret;
}

bool FileHandler::saveNodeParent(__int64 adress, __int64 parent)
{
  int fileIndex = 0;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  nodeFile[fileIndex]->seekp((adress-1)*32);
  nodeFile[fileIndex]->write((char*)(&(parent)), 8);
  return true;
}

__int64 FileHandler::loadNodeSmallerChild(__int64 adress)
{
  int fileIndex = 0;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  int ret;
  nodeFile[fileIndex]->seekg((adress-1)*32+8);
  nodeFile[fileIndex]->read((char*)(&ret), 8);
  return ret;
}

bool FileHandler::saveNodeSmallerChild(__int64 adress, __int64 SmallerChild)
{
  int fileIndex = 0;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  nodeFile[fileIndex]->seekp((adress-1)*32+8);
  nodeFile[fileIndex]->write((char*)(&(SmallerChild)), 8);
  return true;
}

__int64 FileHandler::loadNodeBiggerChild(__int64 adress)
{
  int fileIndex = 0;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  int ret;
  nodeFile[fileIndex]->seekg((adress-1)*32+16);
  nodeFile[fileIndex]->read((char*)(&ret), 8);
  return ret;
}

bool FileHandler::saveNodeBiggerChild(__int64 adress, __int64 BiggerChild)
{
  int fileIndex = 0;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  nodeFile[fileIndex]->seekp((adress-1)*32+16);
  nodeFile[fileIndex]->write((char*)(&(BiggerChild)), 8);
  return true;
}

__int64 FileHandler::loadNodeHeight(__int64 adress)
{
  int fileIndex = 0;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  int ret;
  nodeFile[fileIndex]->seekg((adress-1)*32+24);
  nodeFile[fileIndex]->read((char*)(&ret), 8);
  return ret;
}

bool FileHandler::saveNodeHeight(__int64 adress, __int64 height)
{
  int fileIndex = 0;
  while(adress>CUBES_PER_FILE)
  {
    fileIndex++;
    adress-=CUBES_PER_FILE;
  }
  nodeFile[fileIndex]->seekp((adress-1)*32+24);
  nodeFile[fileIndex]->write((char*)(&(height)), 8);
  return true;
}

bool FileHandler::saveStats(__int64 checkingCube, __int64 totalPopulation, __int64 populationUpuntilLastGeneration, __int64 generation)
{
  statsFile.seekp(0);
  statsFile.write((char*)(&checkingCube), 8);
  statsFile.write((char*)(&totalPopulation), 8);
  statsFile.write((char*)(&populationUpuntilLastGeneration), 8);
  statsFile.write((char*)(&generation), 8);
  return true;
}

void FileHandler::loadStats(__int64* checkingCube, __int64* totalPopulation, __int64* populationUpuntilLastGeneration, __int64* generation, bool print)
{
  statsFile.seekg(0);
  statsFile.read((char*)checkingCube, 8);
  statsFile.read((char*)totalPopulation, 8);
  statsFile.read((char*)populationUpuntilLastGeneration, 8);
  statsFile.read((char*)generation, 8);
  if(print)
  {
    cout << "Stats loaded" << endl;
    cout << "CheckingCube: " << *checkingCube << endl;
    cout << "Total population: " << *totalPopulation << endl;
    cout << "Population upuntil last generation: " << *populationUpuntilLastGeneration << endl;
    cout << "Generation: " << *generation << endl;
  }
}
