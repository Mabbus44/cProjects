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
    cout << "ERROR: Could not open or create file " << filename << endl;
    return false;
  }
  return true;
}

bool FileHandler::openCubeFile(string filename)
{
  cubeFile.open(filename, ios::in | ios::out | ios::binary);
  if(!cubeFile.is_open())
  {
    cout << "ERROR: Could not open or create file " << filename << endl;
    return false;
  }
  return true;
}
