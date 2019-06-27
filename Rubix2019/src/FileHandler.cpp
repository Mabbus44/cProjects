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
  nodeFile.open(filename, ios::in | ios::out | ios::binary);
  if(!nodeFile.is_open())
  {
    if(!createNodeFile(filename))
    {
      cout << "ERROR: Could not create file " << filename << endl;
      return false;
    }
    nodeFile.open(filename, ios::in | ios::out | ios::binary);
    if(!nodeFile.is_open())
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
    for(int i=0; i<20000000; i++)
    {
      node->adress = i+1;
      saveNode(node);
    }
    delete node;
    cout << "done" << endl;
  }
  return true;
}

bool FileHandler::openCubeFile(string filename)
{
  cubeFile.open(filename, ios::in | ios::out | ios::binary);
  if(!cubeFile.is_open())
  {
    if(!createCubeFile(filename))
    {
      cout << "ERROR: Could not create file " << filename << endl;
      return false;
    }
    cubeFile.open(filename, ios::in | ios::out | ios::binary);
    if(!cubeFile.is_open())
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
    for(int i=0; i<20000000; i++)
    {
      cube->adress = i+1;
      saveCube(cube);
    }
    delete cube;
    cout << "done" << endl;
  }
  return true;
}

bool FileHandler::openStatsFile(string filename)
{
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
  nodeFile.open(filename, ios::out | ios::binary);
  if(!nodeFile.is_open())
    return false;
  nodeFile.close();
  return true;
}

bool FileHandler::createCubeFile(string filename)
{
  cubeFile.open(filename, ios::out | ios::binary);
  if(!cubeFile.is_open())
    return false;
  cubeFile.close();
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
  cubeFile.seekp((cube->adress-1)*44);
  cubeFile.write(cube->corners, 8);
  cubeFile.write(cube->sides, 12);
  cubeFile.write((char*)(&(cube->parent)), 8);
  cubeFile.write((char*)(&(cube->firstChild)), 8);
  cubeFile.write((char*)(&(cube->sibling)), 8);
  return true;
}

bool FileHandler::saveCubeFirstChild(int adress, __int64 firstChild)
{
  cubeFile.seekp((adress-1)*44+28);
  cubeFile.write((char*)(&(firstChild)), 8);
  return true;
}

bool FileHandler::saveCubeSibling(int adress, __int64 sibling)
{
  cubeFile.seekp((adress-1)*44+36);
  cubeFile.write((char*)(&(sibling)), 8);
  return true;
}

RubixCube20BF* FileHandler::loadCube(int adress)
{
  RubixCube20BF* ret = new RubixCube20BF();
  ret->adress = adress;
  cubeFile.seekg((adress-1)*44);
  cubeFile.read(ret->corners, 8);
  cubeFile.read(ret->sides, 12);
  cubeFile.read((char*)(&(ret->parent)), 8);
  cubeFile.read((char*)(&(ret->firstChild)), 8);
  cubeFile.read((char*)(&(ret->sibling)), 8);
  return ret;
}

bool FileHandler::saveNode(BinaryNodeF* node)
{
  nodeFile.seekp((node->adress-1)*32);
  nodeFile.write((char*)(&(node->parent)), 8);
  nodeFile.write((char*)(&(node->smallerChild)), 8);
  nodeFile.write((char*)(&(node->biggerChild)), 8);
  nodeFile.write((char*)(&(node->height)), 8);
  return true;
}

BinaryNodeF* FileHandler::loadNode(int adress)
{
  BinaryNodeF* ret = new BinaryNodeF();
  ret->adress = adress;
  nodeFile.seekg((adress-1)*32);
  nodeFile.read((char*)(&(ret->parent)), 8);
  nodeFile.read((char*)(&(ret->smallerChild)), 8);
  nodeFile.read((char*)(&(ret->biggerChild)), 8);
  nodeFile.read((char*)(&(ret->height)), 8);
  return ret;
}

__int64 FileHandler::loadNodeParent(int adress)
{
  int ret;
  nodeFile.seekg((adress-1)*32);
  nodeFile.read((char*)(&ret), 8);
  return ret;
}

bool FileHandler::saveNodeParent(int adress, __int64 parent)
{
  nodeFile.seekp((adress-1)*32);
  nodeFile.write((char*)(&(parent)), 8);
  return true;
}

__int64 FileHandler::loadNodeSmallerChild(int adress)
{
  int ret;
  nodeFile.seekg((adress-1)*32+8);
  nodeFile.read((char*)(&ret), 8);
  return ret;
}

bool FileHandler::saveNodeSmallerChild(int adress, __int64 SmallerChild)
{
  nodeFile.seekp((adress-1)*32+8);
  nodeFile.write((char*)(&(SmallerChild)), 8);
  return true;
}

__int64 FileHandler::loadNodeBiggerChild(int adress)
{
  int ret;
  nodeFile.seekg((adress-1)*32+16);
  nodeFile.read((char*)(&ret), 8);
  return ret;
}

bool FileHandler::saveNodeBiggerChild(int adress, __int64 BiggerChild)
{
  nodeFile.seekp((adress-1)*32+16);
  nodeFile.write((char*)(&(BiggerChild)), 8);
  return true;
}

__int64 FileHandler::loadNodeHeight(int adress)
{
  int ret;
  nodeFile.seekg((adress-1)*32+24);
  nodeFile.read((char*)(&ret), 8);
  return ret;
}

bool FileHandler::saveNodeHeight(int adress, __int64 height)
{
  nodeFile.seekp((adress-1)*32+24);
  nodeFile.write((char*)(&(height)), 8);
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
