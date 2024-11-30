#include "RubixCube.h"
#include <iostream>
#include <iomanip>

CubeSolver cubeSolver;

bool Cube::operator==(const Cube& other) const
{
  for(int a=0; a<12; a++)
  {
    if(a<8 && this->_corners[a] != other._corners[a])
      return false;
    if(this->_sides[a] != other._sides[a])
      return false;
  }
  return true;
}

bool Cube::operator<(const Cube& other)
{
  for(int a=0; a<12; a++)
  {
    if(a<8 && this->_corners[a] > other._corners[a])
      return false;
    if(a<8 && this->_corners[a] < other._corners[a])
      return true;
    if(this->_sides[a] > other._sides[a])
      return false;
    if(this->_sides[a] < other._sides[a])
      return true;
  }
  return false;
}

bool Cube::operator>(const Cube& other)
{
  for(int a=0; a<12; a++)
  {
    if(a<8 && this->_corners[a] < other._corners[a])
      return false;
    if(a<8 && this->_corners[a] > other._corners[a])
      return true;
    if(this->_sides[a] < other._sides[a])
      return false;
    if(this->_sides[a] > other._sides[a])
      return true;
  }
  return false;
}

int Cube::seb(Cube* other)
{
  for(int a=0; a<12; a++)
  {
    if(a<8 && this->_corners[a] > other->_corners[a])
      return SEB::BIGGER;
    if(a<8 && this->_corners[a] < other->_corners[a])
      return SEB::SMALLER;
    if(this->_sides[a] > other->_sides[a])
      return SEB::BIGGER;
    if(this->_sides[a] < other->_sides[a])
      return SEB::SMALLER;
  }
  return SEB::EQUALS;
}

void Cube::print()
{
/* c=corner, the others are _sides
    07
  04  06
    05
c 00  01  02  03
  00  01  02  03
c 04  05  06  07
    09
  08  10
    11

With centers
     07
   04 4 06
     05
c  00   01   02   03
 3 00 0 01 1 02 2 03
c  04   05   06   07
     09
   08 5 10
     11

*/
  std::cout << "                " << std::setw(3) << (int)(this->_sides[7]) << std::endl;
  std::cout << "            " << std::setw(3) << (int)(this->_sides[4]) << "     " << std::setw(3) << (int)(this->_sides[6]) << std::endl;
  std::cout << "                " << std::setw(3) << (int)(this->_sides[5]) << std::endl;
  std::cout << std::setw(3) << (int)(this->_corners[0]) << "         " << std::setw(3) << (int)(this->_corners[1]) << "         " << std::setw(3) << (int)(this->_corners[2]) << "         " << std::setw(3) << (int)(this->_corners[3]) << std::endl;
  std::cout << std::setw(3) << (int)(this->_sides[0])   << "         " << std::setw(3) << (int)(this->_sides[1])   << "         " << std::setw(3) << (int)(this->_sides[2])   << "         " << std::setw(3) << (int)(this->_sides[3])   << std::endl;
  std::cout << std::setw(3) << (int)(this->_corners[4]) << "         " << std::setw(3) << (int)(this->_corners[5]) << "         " << std::setw(3) << (int)(this->_corners[6]) << "         " << std::setw(3) << (int)(this->_corners[7]) << std::endl;
  std::cout << "                " << std::setw(3) << (int)(this->_sides[9]) << std::endl;
  std::cout << "            " << std::setw(3) << (int)(this->_sides[8]) << "     " << (int)(this->_sides[10]) << std::endl;
  std::cout << "                " << std::setw(3) << (int)(this->_sides[11]) << std::endl;
}

void Cube::setStartingCube(){
  for(int side = 0; side<12; side++)
      this->_sides[side] = side*2+1;
  for(int corner = 0; corner<8; corner++)
      this->_corners[corner] = corner*4+1;
}

void Cube::save(std::fstream* file){
  for(int side = 0; side<12; side++)
    file->write(reinterpret_cast<char*>(&(this->_sides[side])), 1);
  for(int corner = 0; corner<8; corner++)
    file->write(reinterpret_cast<char*>(&(this->_corners[corner])), 1);
}

void Cube::load(std::fstream* file){
  for(int side = 0; side<12; side++)
    file->read(reinterpret_cast<char*>(&(this->_sides[side])), 1);
  for(int corner = 0; corner<8; corner++)
    file->read(reinterpret_cast<char*>(&(this->_corners[corner])), 1);
}

Cube* Cube::returnChild(int move)
{
  Cube* child = new Cube();
  switch(move)
  {
  case 0:
    //Turn side 0 clockwise
    child->_corners[0] = this->_corners[4];
    child->_corners[1] = this->turnCornerRight(this->_corners[0]);
    child->_corners[2] = this->_corners[2];
    child->_corners[3] = this->_corners[3];
    child->_corners[4] = this->turnCornerRight(this->_corners[5]);
    child->_corners[5] = this->turnCornerRight(this->_corners[1]);
    child->_corners[6] = this->_corners[6];
    child->_corners[7] = this->_corners[7];
    child->_sides[0] = this->turnSide(this->_sides[8]);
    child->_sides[1] = this->_sides[4];
    child->_sides[2] = this->_sides[2];
    child->_sides[3] = this->_sides[3];
    child->_sides[4] = this->turnSide(this->_sides[0]);
    child->_sides[5] = this->_sides[5];
    child->_sides[6] = this->_sides[6];
    child->_sides[7] = this->_sides[7];
    child->_sides[8] = this->_sides[1];
    child->_sides[9] = this->_sides[9];
    child->_sides[10] = this->_sides[10];
    child->_sides[11] = this->_sides[11];
    break;
  case 1:
    //Turn side 1 clockwise
    child->_corners[0] = this->_corners[0];
    child->_corners[1] = this->_corners[5];
    child->_corners[2] = this->turnCornerRight(this->_corners[1]);
    child->_corners[3] = this->_corners[3];
    child->_corners[4] = this->_corners[4];
    child->_corners[5] = this->turnCornerRight(this->_corners[6]);
    child->_corners[6] = this->turnCornerRight(this->_corners[2]);
    child->_corners[7] = this->_corners[7];
    child->_sides[0] = this->_sides[0];
    child->_sides[1] = this->turnSide(this->_sides[9]);
    child->_sides[2] = this->_sides[5];
    child->_sides[3] = this->_sides[3];
    child->_sides[4] = this->_sides[4];
    child->_sides[5] = this->turnSide(this->_sides[1]);
    child->_sides[6] = this->_sides[6];
    child->_sides[7] = this->_sides[7];
    child->_sides[8] = this->_sides[8];
    child->_sides[9] = this->_sides[2];
    child->_sides[10] = this->_sides[10];
    child->_sides[11] = this->_sides[11];
    break;
  case 2:
    //Turn side 2 clockwise
    child->_corners[0] = this->_corners[0];
    child->_corners[1] = this->_corners[1];
    child->_corners[2] = this->_corners[6];
    child->_corners[3] = this->turnCornerRight(this->_corners[2]);
    child->_corners[4] = this->_corners[4];
    child->_corners[5] = this->_corners[5];
    child->_corners[6] = this->turnCornerRight(this->_corners[7]);
    child->_corners[7] = this->turnCornerRight(this->_corners[3]);
    child->_sides[0] = this->_sides[0];
    child->_sides[1] = this->_sides[1];
    child->_sides[2] = this->turnSide(this->_sides[10]);
    child->_sides[3] = this->_sides[6];
    child->_sides[4] = this->_sides[4];
    child->_sides[5] = this->_sides[5];
    child->_sides[6] = this->turnSide(this->_sides[2]);
    child->_sides[7] = this->_sides[7];
    child->_sides[8] = this->_sides[8];
    child->_sides[9] = this->_sides[9];
    child->_sides[10] = this->_sides[3];
    child->_sides[11] = this->_sides[11];
    break;
  case 3:
    //Turn side 3 clockwise
    child->_corners[0] = this->turnCornerRight(this->_corners[3]);
    child->_corners[1] = this->_corners[1];
    child->_corners[2] = this->_corners[2];
    child->_corners[3] = this->_corners[7];
    child->_corners[4] = this->turnCornerRight(this->_corners[0]);
    child->_corners[5] = this->_corners[5];
    child->_corners[6] = this->_corners[6];
    child->_corners[7] = this->turnCornerRight(this->_corners[4]);
    child->_sides[0] = this->_sides[7];
    child->_sides[1] = this->_sides[1];
    child->_sides[2] = this->_sides[2];
    child->_sides[3] = this->turnSide(this->_sides[11]);
    child->_sides[4] = this->_sides[4];
    child->_sides[5] = this->_sides[5];
    child->_sides[6] = this->_sides[6];
    child->_sides[7] = this->turnSide(this->_sides[3]);
    child->_sides[8] = this->_sides[8];
    child->_sides[9] = this->_sides[9];
    child->_sides[10] = this->_sides[10];
    child->_sides[11] = this->_sides[0];
    break;
  case 4:
    //Turn side 4 clockwise
    child->_corners[0] = this->_corners[1];
    child->_corners[1] = this->_corners[2];
    child->_corners[2] = this->_corners[3];
    child->_corners[3] = this->_corners[0];
    child->_corners[4] = this->_corners[4];
    child->_corners[5] = this->_corners[5];
    child->_corners[6] = this->_corners[6];
    child->_corners[7] = this->_corners[7];
    child->_sides[0] = this->_sides[0];
    child->_sides[1] = this->_sides[1];
    child->_sides[2] = this->_sides[2];
    child->_sides[3] = this->_sides[3];
    child->_sides[4] = this->_sides[5];
    child->_sides[5] = this->_sides[6];
    child->_sides[6] = this->_sides[7];
    child->_sides[7] = this->_sides[4];
    child->_sides[8] = this->_sides[8];
    child->_sides[9] = this->_sides[9];
    child->_sides[10] = this->_sides[10];
    child->_sides[11] = this->_sides[11];
    break;
  case 5:
    //Turn side 5 clockwise
    child->_corners[0] = this->_corners[0];
    child->_corners[1] = this->_corners[1];
    child->_corners[2] = this->_corners[2];
    child->_corners[3] = this->_corners[3];
    child->_corners[4] = this->_corners[7];
    child->_corners[5] = this->_corners[4];
    child->_corners[6] = this->_corners[5];
    child->_corners[7] = this->_corners[6];
    child->_sides[0] = this->_sides[0];
    child->_sides[1] = this->_sides[1];
    child->_sides[2] = this->_sides[2];
    child->_sides[3] = this->_sides[3];
    child->_sides[4] = this->_sides[4];
    child->_sides[5] = this->_sides[5];
    child->_sides[6] = this->_sides[6];
    child->_sides[7] = this->_sides[7];
    child->_sides[8] = this->_sides[11];
    child->_sides[9] = this->_sides[8];
    child->_sides[10] = this->_sides[9];
    child->_sides[11] = this->_sides[10];
    break;
  case 6:
    //Turn side 0 counter clockwise
    child->_corners[0] = this->turnCornerLeft(this->_corners[1]);
    child->_corners[1] = this->turnCornerLeft(this->_corners[5]);
    child->_corners[2] = this->_corners[2];
    child->_corners[3] = this->_corners[3];
    child->_corners[4] = this->_corners[0];
    child->_corners[5] = this->turnCornerLeft(this->_corners[4]);
    child->_corners[6] = this->_corners[6];
    child->_corners[7] = this->_corners[7];
    child->_sides[0] = this->turnSide(this->_sides[4]);
    child->_sides[1] = this->_sides[8];
    child->_sides[2] = this->_sides[2];
    child->_sides[3] = this->_sides[3];
    child->_sides[4] = this->_sides[1];
    child->_sides[5] = this->_sides[5];
    child->_sides[6] = this->_sides[6];
    child->_sides[7] = this->_sides[7];
    child->_sides[8] = this->turnSide(this->_sides[0]);
    child->_sides[9] = this->_sides[9];
    child->_sides[10] = this->_sides[10];
    child->_sides[11] = this->_sides[11];
    break;
  case 7:
    //Turn side 1 counter clockwise
    child->_corners[0] = this->_corners[0];
    child->_corners[1] = this->turnCornerLeft(this->_corners[2]);
    child->_corners[2] = this->turnCornerLeft(this->_corners[6]);
    child->_corners[3] = this->_corners[3];
    child->_corners[4] = this->_corners[4];
    child->_corners[5] = this->_corners[1];
    child->_corners[6] = this->turnCornerLeft(this->_corners[5]);
    child->_corners[7] = this->_corners[7];
    child->_sides[0] = this->_sides[0];
    child->_sides[1] = this->turnSide(this->_sides[5]);
    child->_sides[2] = this->_sides[9];
    child->_sides[3] = this->_sides[3];
    child->_sides[4] = this->_sides[4];
    child->_sides[5] = this->_sides[2];
    child->_sides[6] = this->_sides[6];
    child->_sides[7] = this->_sides[7];
    child->_sides[8] = this->_sides[8];
    child->_sides[9] = this->turnSide(this->_sides[1]);
    child->_sides[10] = this->_sides[10];
    child->_sides[11] = this->_sides[11];
    break;
  case 8:
    //Turn side 2 counter clockwise
    child->_corners[0] = this->_corners[0];
    child->_corners[1] = this->_corners[1];
    child->_corners[2] = this->turnCornerLeft(this->_corners[3]);
    child->_corners[3] = this->turnCornerLeft(this->_corners[7]);
    child->_corners[4] = this->_corners[4];
    child->_corners[5] = this->_corners[5];
    child->_corners[6] = this->_corners[2];
    child->_corners[7] = this->turnCornerLeft(this->_corners[6]);
    child->_sides[0] = this->_sides[0];
    child->_sides[1] = this->_sides[1];
    child->_sides[2] = this->turnSide(this->_sides[6]);
    child->_sides[3] = this->_sides[10];
    child->_sides[4] = this->_sides[4];
    child->_sides[5] = this->_sides[5];
    child->_sides[6] = this->_sides[3];
    child->_sides[7] = this->_sides[7];
    child->_sides[8] = this->_sides[8];
    child->_sides[9] = this->_sides[9];
    child->_sides[10] = this->turnSide(this->_sides[2]);
    child->_sides[11] = this->_sides[11];
    break;
  case 9:
    //Turn side 3 counter clockwise
    child->_corners[0] = this->turnCornerLeft(this->_corners[4]);
    child->_corners[1] = this->_corners[1];
    child->_corners[2] = this->_corners[2];
    child->_corners[3] = this->turnCornerLeft(this->_corners[0]);
    child->_corners[4] = this->turnCornerLeft(this->_corners[7]);
    child->_corners[5] = this->_corners[5];
    child->_corners[6] = this->_corners[6];
    child->_corners[7] = this->_corners[3];
    child->_sides[0] = this->_sides[11];
    child->_sides[1] = this->_sides[1];
    child->_sides[2] = this->_sides[2];
    child->_sides[3] = this->turnSide(this->_sides[7]);
    child->_sides[4] = this->_sides[4];
    child->_sides[5] = this->_sides[5];
    child->_sides[6] = this->_sides[6];
    child->_sides[7] = this->_sides[0];
    child->_sides[8] = this->_sides[8];
    child->_sides[9] = this->_sides[9];
    child->_sides[10] = this->_sides[10];
    child->_sides[11] = this->turnSide(this->_sides[3]);
    break;
  case 10:
    //Turn side 4 counter clockwise
    child->_corners[0] = this->_corners[3];
    child->_corners[1] = this->_corners[0];
    child->_corners[2] = this->_corners[1];
    child->_corners[3] = this->_corners[2];
    child->_corners[4] = this->_corners[4];
    child->_corners[5] = this->_corners[5];
    child->_corners[6] = this->_corners[6];
    child->_corners[7] = this->_corners[7];
    child->_sides[0] = this->_sides[0];
    child->_sides[1] = this->_sides[1];
    child->_sides[2] = this->_sides[2];
    child->_sides[3] = this->_sides[3];
    child->_sides[4] = this->_sides[7];
    child->_sides[5] = this->_sides[4];
    child->_sides[6] = this->_sides[5];
    child->_sides[7] = this->_sides[6];
    child->_sides[8] = this->_sides[8];
    child->_sides[9] = this->_sides[9];
    child->_sides[10] = this->_sides[10];
    child->_sides[11] = this->_sides[11];
    break;
  case 11:
    //Turn side 5 counter clockwise
    child->_corners[0] = this->_corners[0];
    child->_corners[1] = this->_corners[1];
    child->_corners[2] = this->_corners[2];
    child->_corners[3] = this->_corners[3];
    child->_corners[4] = this->_corners[5];
    child->_corners[5] = this->_corners[6];
    child->_corners[6] = this->_corners[7];
    child->_corners[7] = this->_corners[4];
    child->_sides[0] = this->_sides[0];
    child->_sides[1] = this->_sides[1];
    child->_sides[2] = this->_sides[2];
    child->_sides[3] = this->_sides[3];
    child->_sides[4] = this->_sides[4];
    child->_sides[5] = this->_sides[5];
    child->_sides[6] = this->_sides[6];
    child->_sides[7] = this->_sides[7];
    child->_sides[8] = this->_sides[9];
    child->_sides[9] = this->_sides[10];
    child->_sides[10] = this->_sides[11];
    child->_sides[11] = this->_sides[8];
    break;
  default:
    break;
  }
  return child;
}


Cube* Cube::returnRot(int rot)
{
  Cube* rotatedCube = new Cube();
  switch(rot)
  {
  case 0:
    //Side 0 forwards
    rotatedCube->_corners[0] = this->replaceCorner(this->_corners[3], rot);
    rotatedCube->_corners[1] = this->replaceCorner(this->_corners[0], rot);
    rotatedCube->_corners[2] = this->replaceCorner(this->_corners[1], rot);
    rotatedCube->_corners[3] = this->replaceCorner(this->_corners[2], rot);
    rotatedCube->_corners[4] = this->replaceCorner(this->_corners[7], rot);
    rotatedCube->_corners[5] = this->replaceCorner(this->_corners[4], rot);
    rotatedCube->_corners[6] = this->replaceCorner(this->_corners[5], rot);
    rotatedCube->_corners[7] = this->replaceCorner(this->_corners[6], rot);
    rotatedCube->_sides[0] = this->replaceSide(this->_sides[3], rot);
    rotatedCube->_sides[1] = this->replaceSide(this->_sides[0], rot);
    rotatedCube->_sides[2] = this->replaceSide(this->_sides[1], rot);
    rotatedCube->_sides[3] = this->replaceSide(this->_sides[2], rot);
    rotatedCube->_sides[4] = this->replaceSide(this->_sides[7], rot);
    rotatedCube->_sides[5] = this->replaceSide(this->_sides[4], rot);
    rotatedCube->_sides[6] = this->replaceSide(this->_sides[5], rot);
    rotatedCube->_sides[7] = this->replaceSide(this->_sides[6], rot);
    rotatedCube->_sides[8] = this->replaceSide(this->_sides[11], rot);
    rotatedCube->_sides[9] = this->replaceSide(this->_sides[8], rot);
    rotatedCube->_sides[10] = this->replaceSide(this->_sides[9], rot);
    rotatedCube->_sides[11] = this->replaceSide(this->_sides[10], rot);
    break;
  case 1:
    //Side 0 forwards rotate left
    rotatedCube->_corners[0] = this->turnCornerRight(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[1] = this->turnCornerLeft(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[2] = this->turnCornerLeft(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[3] = this->replaceCorner(this->_corners[6], rot);
    rotatedCube->_corners[4] = this->turnCornerRight(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[5] = this->replaceCorner(this->_corners[0], rot);
    rotatedCube->_corners[6] = this->turnCornerLeft(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[7] = this->turnCornerRight(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_sides[0] = this->replaceSide(this->_sides[6], rot);
    rotatedCube->_sides[1] = this->turnSide(this->replaceSide(this->_sides[4], rot));
    rotatedCube->_sides[2] = this->replaceSide(this->_sides[8], rot);
    rotatedCube->_sides[3] = this->turnSide(this->replaceSide(this->_sides[10], rot));
    rotatedCube->_sides[4] = this->turnSide(this->replaceSide(this->_sides[5], rot));
    rotatedCube->_sides[5] = this->replaceSide(this->_sides[1], rot);
    rotatedCube->_sides[6] = this->turnSide(this->replaceSide(this->_sides[9], rot));
    rotatedCube->_sides[7] = this->turnSide(this->replaceSide(this->_sides[2], rot));
    rotatedCube->_sides[8] = this->turnSide(this->replaceSide(this->_sides[7], rot));
    rotatedCube->_sides[9] = this->turnSide(this->replaceSide(this->_sides[0], rot));
    rotatedCube->_sides[10] = this->turnSide(this->replaceSide(this->_sides[11], rot));
    rotatedCube->_sides[11] = this->replaceSide(this->_sides[3], rot);
    break;
  case 2:
    //Side 0 forwards rotate 2x
    rotatedCube->_corners[0] = this->turnCornerRight(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[1] = this->turnCornerRight(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[2] = this->turnCornerRight(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[3] = this->turnCornerRight(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[4] = this->turnCornerLeft(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[5] = this->turnCornerLeft(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[6] = this->turnCornerLeft(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[7] = this->turnCornerLeft(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_sides[0] = this->turnSide(this->replaceSide(this->_sides[2], rot));
    rotatedCube->_sides[1] = this->turnSide(this->replaceSide(this->_sides[1], rot));
    rotatedCube->_sides[2] = this->turnSide(this->replaceSide(this->_sides[0], rot));
    rotatedCube->_sides[3] = this->turnSide(this->replaceSide(this->_sides[3], rot));
    rotatedCube->_sides[4] = this->replaceSide(this->_sides[9], rot);
    rotatedCube->_sides[5] = this->replaceSide(this->_sides[8], rot);
    rotatedCube->_sides[6] = this->replaceSide(this->_sides[11], rot);
    rotatedCube->_sides[7] = this->replaceSide(this->_sides[10], rot);
    rotatedCube->_sides[8] = this->replaceSide(this->_sides[5], rot);
    rotatedCube->_sides[9] = this->replaceSide(this->_sides[4], rot);
    rotatedCube->_sides[10] = this->replaceSide(this->_sides[7], rot);
    rotatedCube->_sides[11] = this->replaceSide(this->_sides[6], rot);
    break;
  case 3:
    //Side 0 forwards rotate right
    rotatedCube->_corners[0] = this->turnCornerLeft(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[1] = this->replaceCorner(this->_corners[4], rot);
    rotatedCube->_corners[2] = this->turnCornerRight(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[3] = this->turnCornerLeft(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[4] = this->turnCornerLeft(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[5] = this->turnCornerRight(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[6] = this->turnCornerRight(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[7] = this->replaceCorner(this->_corners[2], rot);
    rotatedCube->_sides[0] = this->replaceSide(this->_sides[10], rot);
    rotatedCube->_sides[1] = this->turnSide(this->replaceSide(this->_sides[8], rot));
    rotatedCube->_sides[2] = this->replaceSide(this->_sides[4], rot);
    rotatedCube->_sides[3] = this->turnSide(this->replaceSide(this->_sides[6], rot));
    rotatedCube->_sides[4] = this->turnSide(this->replaceSide(this->_sides[11], rot));
    rotatedCube->_sides[5] = this->turnSide(this->replaceSide(this->_sides[0], rot));
    rotatedCube->_sides[6] = this->turnSide(this->replaceSide(this->_sides[7], rot));
    rotatedCube->_sides[7] = this->replaceSide(this->_sides[3], rot);
    rotatedCube->_sides[8] = this->turnSide(this->replaceSide(this->_sides[9], rot));
    rotatedCube->_sides[9] = this->replaceSide(this->_sides[1], rot);
    rotatedCube->_sides[10] = this->turnSide(this->replaceSide(this->_sides[5], rot));
    rotatedCube->_sides[11] = this->turnSide(this->replaceSide(this->_sides[2], rot));
    break;
  case 4:
    //Side 1 forwards
    rotatedCube->_corners[0] = this->_corners[0];
    rotatedCube->_corners[1] = this->_corners[1];
    rotatedCube->_corners[2] = this->_corners[2];
    rotatedCube->_corners[3] = this->_corners[3];
    rotatedCube->_corners[4] = this->_corners[4];
    rotatedCube->_corners[5] = this->_corners[5];
    rotatedCube->_corners[6] = this->_corners[6];
    rotatedCube->_corners[7] = this->_corners[7];
    rotatedCube->_sides[0] = this->_sides[0];
    rotatedCube->_sides[1] = this->_sides[1];
    rotatedCube->_sides[2] = this->_sides[2];
    rotatedCube->_sides[3] = this->_sides[3];
    rotatedCube->_sides[4] = this->_sides[4];
    rotatedCube->_sides[5] = this->_sides[5];
    rotatedCube->_sides[6] = this->_sides[6];
    rotatedCube->_sides[7] = this->_sides[7];
    rotatedCube->_sides[8] = this->_sides[8];
    rotatedCube->_sides[9] = this->_sides[9];
    rotatedCube->_sides[10] = this->_sides[10];
    rotatedCube->_sides[11] = this->_sides[11];
    break;
  case 5:
    //Side 1 forwards rotate left
    rotatedCube->_corners[0] = this->turnCornerRight(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[1] = this->turnCornerLeft(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[2] = this->turnCornerLeft(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[3] = this->replaceCorner(this->_corners[7], rot);
    rotatedCube->_corners[4] = this->turnCornerRight(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[5] = this->replaceCorner(this->_corners[1], rot);
    rotatedCube->_corners[6] = this->turnCornerLeft(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[7] = this->turnCornerRight(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_sides[0] = this->replaceSide(this->_sides[7], rot);
    rotatedCube->_sides[1] = this->turnSide(this->replaceSide(this->_sides[5], rot));
    rotatedCube->_sides[2] = this->replaceSide(this->_sides[9], rot);
    rotatedCube->_sides[3] = this->turnSide(this->replaceSide(this->_sides[11], rot));
    rotatedCube->_sides[4] = this->turnSide(this->replaceSide(this->_sides[6], rot));
    rotatedCube->_sides[5] = this->replaceSide(this->_sides[2], rot);
    rotatedCube->_sides[6] = this->turnSide(this->replaceSide(this->_sides[10], rot));
    rotatedCube->_sides[7] = this->turnSide(this->replaceSide(this->_sides[3], rot));
    rotatedCube->_sides[8] = this->turnSide(this->replaceSide(this->_sides[4], rot));
    rotatedCube->_sides[9] = this->turnSide(this->replaceSide(this->_sides[1], rot));
    rotatedCube->_sides[10] = this->turnSide(this->replaceSide(this->_sides[8], rot));
    rotatedCube->_sides[11] = this->replaceSide(this->_sides[0], rot);
    break;
  case 6:
    //Side 1 forwards rotate 2x
    rotatedCube->_corners[0] = this->turnCornerRight(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[1] = this->turnCornerRight(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[2] = this->turnCornerRight(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[3] = this->turnCornerRight(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[4] = this->turnCornerLeft(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[5] = this->turnCornerLeft(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[6] = this->turnCornerLeft(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[7] = this->turnCornerLeft(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_sides[0] = this->turnSide(this->replaceSide(this->_sides[3], rot));
    rotatedCube->_sides[1] = this->turnSide(this->replaceSide(this->_sides[2], rot));
    rotatedCube->_sides[2] = this->turnSide(this->replaceSide(this->_sides[1], rot));
    rotatedCube->_sides[3] = this->turnSide(this->replaceSide(this->_sides[0], rot));
    rotatedCube->_sides[4] = this->replaceSide(this->_sides[10], rot);
    rotatedCube->_sides[5] = this->replaceSide(this->_sides[9], rot);
    rotatedCube->_sides[6] = this->replaceSide(this->_sides[8], rot);
    rotatedCube->_sides[7] = this->replaceSide(this->_sides[11], rot);
    rotatedCube->_sides[8] = this->replaceSide(this->_sides[6], rot);
    rotatedCube->_sides[9] = this->replaceSide(this->_sides[5], rot);
    rotatedCube->_sides[10] = this->replaceSide(this->_sides[4], rot);
    rotatedCube->_sides[11] = this->replaceSide(this->_sides[7], rot);
    break;
  case 7:
    //Side 1 forwards rotate right
    rotatedCube->_corners[0] = this->turnCornerLeft(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[1] = this->replaceCorner(this->_corners[5], rot);
    rotatedCube->_corners[2] = this->turnCornerRight(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[3] = this->turnCornerLeft(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[4] = this->turnCornerLeft(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[5] = this->turnCornerRight(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[6] = this->turnCornerRight(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[7] = this->replaceCorner(this->_corners[3], rot);
    rotatedCube->_sides[0] = this->replaceSide(this->_sides[11], rot);
    rotatedCube->_sides[1] = this->turnSide(this->replaceSide(this->_sides[9], rot));
    rotatedCube->_sides[2] = this->replaceSide(this->_sides[5], rot);
    rotatedCube->_sides[3] = this->turnSide(this->replaceSide(this->_sides[7], rot));
    rotatedCube->_sides[4] = this->turnSide(this->replaceSide(this->_sides[8], rot));
    rotatedCube->_sides[5] = this->turnSide(this->replaceSide(this->_sides[1], rot));
    rotatedCube->_sides[6] = this->turnSide(this->replaceSide(this->_sides[4], rot));
    rotatedCube->_sides[7] = this->replaceSide(this->_sides[0], rot);
    rotatedCube->_sides[8] = this->turnSide(this->replaceSide(this->_sides[10], rot));
    rotatedCube->_sides[9] = this->replaceSide(this->_sides[2], rot);
    rotatedCube->_sides[10] = this->turnSide(this->replaceSide(this->_sides[6], rot));
    rotatedCube->_sides[11] = this->turnSide(this->replaceSide(this->_sides[3], rot));
    break;
  case 8:
    //Side 2 forwards
    rotatedCube->_corners[0] = this->replaceCorner(this->_corners[1], rot);
    rotatedCube->_corners[1] = this->replaceCorner(this->_corners[2], rot);
    rotatedCube->_corners[2] = this->replaceCorner(this->_corners[3], rot);
    rotatedCube->_corners[3] = this->replaceCorner(this->_corners[0], rot);
    rotatedCube->_corners[4] = this->replaceCorner(this->_corners[5], rot);
    rotatedCube->_corners[5] = this->replaceCorner(this->_corners[6], rot);
    rotatedCube->_corners[6] = this->replaceCorner(this->_corners[7], rot);
    rotatedCube->_corners[7] = this->replaceCorner(this->_corners[4], rot);
    rotatedCube->_sides[0] = this->replaceSide(this->_sides[1], rot);
    rotatedCube->_sides[1] = this->replaceSide(this->_sides[2], rot);
    rotatedCube->_sides[2] = this->replaceSide(this->_sides[3], rot);
    rotatedCube->_sides[3] = this->replaceSide(this->_sides[0], rot);
    rotatedCube->_sides[4] = this->replaceSide(this->_sides[5], rot);
    rotatedCube->_sides[5] = this->replaceSide(this->_sides[6], rot);
    rotatedCube->_sides[6] = this->replaceSide(this->_sides[7], rot);
    rotatedCube->_sides[7] = this->replaceSide(this->_sides[4], rot);
    rotatedCube->_sides[8] = this->replaceSide(this->_sides[9], rot);
    rotatedCube->_sides[9] = this->replaceSide(this->_sides[10], rot);
    rotatedCube->_sides[10] = this->replaceSide(this->_sides[11], rot);
    rotatedCube->_sides[11] = this->replaceSide(this->_sides[8], rot);
    break;
  case 9:
    //Side 2 forwards rotate left
    rotatedCube->_corners[0] = this->turnCornerRight(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[1] = this->turnCornerLeft(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[2] = this->turnCornerLeft(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[3] = this->replaceCorner(this->_corners[4], rot);
    rotatedCube->_corners[4] = this->turnCornerRight(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[5] = this->replaceCorner(this->_corners[2], rot);
    rotatedCube->_corners[6] = this->turnCornerLeft(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[7] = this->turnCornerRight(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_sides[0] = this->replaceSide(this->_sides[4], rot);
    rotatedCube->_sides[1] = this->turnSide(this->replaceSide(this->_sides[6], rot));
    rotatedCube->_sides[2] = this->replaceSide(this->_sides[10], rot);
    rotatedCube->_sides[3] = this->turnSide(this->replaceSide(this->_sides[8], rot));
    rotatedCube->_sides[4] = this->turnSide(this->replaceSide(this->_sides[7], rot));
    rotatedCube->_sides[5] = this->replaceSide(this->_sides[3], rot);
    rotatedCube->_sides[6] = this->turnSide(this->replaceSide(this->_sides[11], rot));
    rotatedCube->_sides[7] = this->turnSide(this->replaceSide(this->_sides[0], rot));
    rotatedCube->_sides[8] = this->turnSide(this->replaceSide(this->_sides[5], rot));
    rotatedCube->_sides[9] = this->turnSide(this->replaceSide(this->_sides[2], rot));
    rotatedCube->_sides[10] = this->turnSide(this->replaceSide(this->_sides[9], rot));
    rotatedCube->_sides[11] = this->replaceSide(this->_sides[1], rot);
    break;
  case 10:
    //Side 2 forwards rotate 2x
    rotatedCube->_corners[0] = this->turnCornerRight(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[1] = this->turnCornerRight(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[2] = this->turnCornerRight(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[3] = this->turnCornerRight(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[4] = this->turnCornerLeft(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[5] = this->turnCornerLeft(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[6] = this->turnCornerLeft(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[7] = this->turnCornerLeft(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_sides[0] = this->turnSide(this->replaceSide(this->_sides[0], rot));
    rotatedCube->_sides[1] = this->turnSide(this->replaceSide(this->_sides[3], rot));
    rotatedCube->_sides[2] = this->turnSide(this->replaceSide(this->_sides[2], rot));
    rotatedCube->_sides[3] = this->turnSide(this->replaceSide(this->_sides[1], rot));
    rotatedCube->_sides[4] = this->replaceSide(this->_sides[11], rot);
    rotatedCube->_sides[5] = this->replaceSide(this->_sides[10], rot);
    rotatedCube->_sides[6] = this->replaceSide(this->_sides[9], rot);
    rotatedCube->_sides[7] = this->replaceSide(this->_sides[8], rot);
    rotatedCube->_sides[8] = this->replaceSide(this->_sides[7], rot);
    rotatedCube->_sides[9] = this->replaceSide(this->_sides[6], rot);
    rotatedCube->_sides[10] = this->replaceSide(this->_sides[5], rot);
    rotatedCube->_sides[11] = this->replaceSide(this->_sides[4], rot);
    break;
  case 11:
    //Side 2 forwards rotate right
    rotatedCube->_corners[0] = this->turnCornerLeft(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[1] = this->replaceCorner(this->_corners[6], rot);
    rotatedCube->_corners[2] = this->turnCornerRight(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[3] = this->turnCornerLeft(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[4] = this->turnCornerLeft(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[5] = this->turnCornerRight(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[6] = this->turnCornerRight(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[7] = this->replaceCorner(this->_corners[0], rot);
    rotatedCube->_sides[0] = this->replaceSide(this->_sides[8], rot);
    rotatedCube->_sides[1] = this->turnSide(this->replaceSide(this->_sides[10], rot));
    rotatedCube->_sides[2] = this->replaceSide(this->_sides[6], rot);
    rotatedCube->_sides[3] = this->turnSide(this->replaceSide(this->_sides[4], rot));
    rotatedCube->_sides[4] = this->turnSide(this->replaceSide(this->_sides[9], rot));
    rotatedCube->_sides[5] = this->turnSide(this->replaceSide(this->_sides[2], rot));
    rotatedCube->_sides[6] = this->turnSide(this->replaceSide(this->_sides[5], rot));
    rotatedCube->_sides[7] = this->replaceSide(this->_sides[1], rot);
    rotatedCube->_sides[8] = this->turnSide(this->replaceSide(this->_sides[11], rot));
    rotatedCube->_sides[9] = this->replaceSide(this->_sides[3], rot);
    rotatedCube->_sides[10] = this->turnSide(this->replaceSide(this->_sides[7], rot));
    rotatedCube->_sides[11] = this->turnSide(this->replaceSide(this->_sides[0], rot));
    break;
  case 12:
    //Side 3 forwards
    rotatedCube->_corners[0] = this->replaceCorner(this->_corners[2], rot);
    rotatedCube->_corners[1] = this->replaceCorner(this->_corners[3], rot);
    rotatedCube->_corners[2] = this->replaceCorner(this->_corners[0], rot);
    rotatedCube->_corners[3] = this->replaceCorner(this->_corners[1], rot);
    rotatedCube->_corners[4] = this->replaceCorner(this->_corners[6], rot);
    rotatedCube->_corners[5] = this->replaceCorner(this->_corners[7], rot);
    rotatedCube->_corners[6] = this->replaceCorner(this->_corners[4], rot);
    rotatedCube->_corners[7] = this->replaceCorner(this->_corners[5], rot);
    rotatedCube->_sides[0] = this->replaceSide(this->_sides[2], rot);
    rotatedCube->_sides[1] = this->replaceSide(this->_sides[3], rot);
    rotatedCube->_sides[2] = this->replaceSide(this->_sides[0], rot);
    rotatedCube->_sides[3] = this->replaceSide(this->_sides[1], rot);
    rotatedCube->_sides[4] = this->replaceSide(this->_sides[6], rot);
    rotatedCube->_sides[5] = this->replaceSide(this->_sides[7], rot);
    rotatedCube->_sides[6] = this->replaceSide(this->_sides[4], rot);
    rotatedCube->_sides[7] = this->replaceSide(this->_sides[5], rot);
    rotatedCube->_sides[8] = this->replaceSide(this->_sides[10], rot);
    rotatedCube->_sides[9] = this->replaceSide(this->_sides[11], rot);
    rotatedCube->_sides[10] = this->replaceSide(this->_sides[8], rot);
    rotatedCube->_sides[11] = this->replaceSide(this->_sides[9], rot);
    break;
  case 13:
    //Side 3 forwards rotate left
    rotatedCube->_corners[0] = this->turnCornerRight(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[1] = this->turnCornerLeft(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[2] = this->turnCornerLeft(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[3] = this->replaceCorner(this->_corners[5], rot);
    rotatedCube->_corners[4] = this->turnCornerRight(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[5] = this->replaceCorner(this->_corners[3], rot);
    rotatedCube->_corners[6] = this->turnCornerLeft(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[7] = this->turnCornerRight(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_sides[0] = this->replaceSide(this->_sides[5], rot);
    rotatedCube->_sides[1] = this->turnSide(this->replaceSide(this->_sides[7], rot));
    rotatedCube->_sides[2] = this->replaceSide(this->_sides[11], rot);
    rotatedCube->_sides[3] = this->turnSide(this->replaceSide(this->_sides[9], rot));
    rotatedCube->_sides[4] = this->turnSide(this->replaceSide(this->_sides[4], rot));
    rotatedCube->_sides[5] = this->replaceSide(this->_sides[0], rot);
    rotatedCube->_sides[6] = this->turnSide(this->replaceSide(this->_sides[8], rot));
    rotatedCube->_sides[7] = this->turnSide(this->replaceSide(this->_sides[1], rot));
    rotatedCube->_sides[8] = this->turnSide(this->replaceSide(this->_sides[6], rot));
    rotatedCube->_sides[9] = this->turnSide(this->replaceSide(this->_sides[3], rot));
    rotatedCube->_sides[10] = this->turnSide(this->replaceSide(this->_sides[10], rot));
    rotatedCube->_sides[11] = this->replaceSide(this->_sides[2], rot);
    break;
  case 14:
    //Side 3 forwards rotate 2x
    rotatedCube->_corners[0] = this->turnCornerRight(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[1] = this->turnCornerRight(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[2] = this->turnCornerRight(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[3] = this->turnCornerRight(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[4] = this->turnCornerLeft(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[5] = this->turnCornerLeft(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[6] = this->turnCornerLeft(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[7] = this->turnCornerLeft(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_sides[0] = this->turnSide(this->replaceSide(this->_sides[1], rot));
    rotatedCube->_sides[1] = this->turnSide(this->replaceSide(this->_sides[0], rot));
    rotatedCube->_sides[2] = this->turnSide(this->replaceSide(this->_sides[3], rot));
    rotatedCube->_sides[3] = this->turnSide(this->replaceSide(this->_sides[2], rot));
    rotatedCube->_sides[4] = this->replaceSide(this->_sides[8], rot);
    rotatedCube->_sides[5] = this->replaceSide(this->_sides[11], rot);
    rotatedCube->_sides[6] = this->replaceSide(this->_sides[10], rot);
    rotatedCube->_sides[7] = this->replaceSide(this->_sides[9], rot);
    rotatedCube->_sides[8] = this->replaceSide(this->_sides[4], rot);
    rotatedCube->_sides[9] = this->replaceSide(this->_sides[7], rot);
    rotatedCube->_sides[10] = this->replaceSide(this->_sides[6], rot);
    rotatedCube->_sides[11] = this->replaceSide(this->_sides[5], rot);
    break;
  case 15:
    //Side 3 forwards rotate right
    rotatedCube->_corners[0] = this->turnCornerLeft(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[1] = this->replaceCorner(this->_corners[7], rot);
    rotatedCube->_corners[2] = this->turnCornerRight(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[3] = this->turnCornerLeft(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[4] = this->turnCornerLeft(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[5] = this->turnCornerRight(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[6] = this->turnCornerRight(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[7] = this->replaceCorner(this->_corners[1], rot);
    rotatedCube->_sides[0] = this->replaceSide(this->_sides[9], rot);
    rotatedCube->_sides[1] = this->turnSide(this->replaceSide(this->_sides[11], rot));
    rotatedCube->_sides[2] = this->replaceSide(this->_sides[7], rot);
    rotatedCube->_sides[3] = this->turnSide(this->replaceSide(this->_sides[5], rot));
    rotatedCube->_sides[4] = this->turnSide(this->replaceSide(this->_sides[10], rot));
    rotatedCube->_sides[5] = this->turnSide(this->replaceSide(this->_sides[3], rot));
    rotatedCube->_sides[6] = this->turnSide(this->replaceSide(this->_sides[6], rot));
    rotatedCube->_sides[7] = this->replaceSide(this->_sides[2], rot);
    rotatedCube->_sides[8] = this->turnSide(this->replaceSide(this->_sides[8], rot));
    rotatedCube->_sides[9] = this->replaceSide(this->_sides[0], rot);
    rotatedCube->_sides[10] = this->turnSide(this->replaceSide(this->_sides[4], rot));
    rotatedCube->_sides[11] = this->turnSide(this->replaceSide(this->_sides[1], rot));
    break;
  case 16:
    //Side 4 forwards
    rotatedCube->_corners[0] = this->replaceCorner(this->_corners[4], rot);
    rotatedCube->_corners[1] = this->turnCornerRight(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[2] = this->turnCornerLeft(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[3] = this->turnCornerLeft(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[4] = this->turnCornerRight(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[5] = this->turnCornerRight(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[6] = this->replaceCorner(this->_corners[2], rot);
    rotatedCube->_corners[7] = this->turnCornerLeft(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_sides[0] = this->turnSide(this->replaceSide(this->_sides[8], rot));
    rotatedCube->_sides[1] = this->replaceSide(this->_sides[4], rot);
    rotatedCube->_sides[2] = this->turnSide(this->replaceSide(this->_sides[6], rot));
    rotatedCube->_sides[3] = this->replaceSide(this->_sides[10], rot);
    rotatedCube->_sides[4] = this->turnSide(this->replaceSide(this->_sides[0], rot));
    rotatedCube->_sides[5] = this->turnSide(this->replaceSide(this->_sides[7], rot));
    rotatedCube->_sides[6] = this->replaceSide(this->_sides[3], rot);
    rotatedCube->_sides[7] = this->turnSide(this->replaceSide(this->_sides[11], rot));
    rotatedCube->_sides[8] = this->replaceSide(this->_sides[1], rot);
    rotatedCube->_sides[9] = this->turnSide(this->replaceSide(this->_sides[5], rot));
    rotatedCube->_sides[10] = this->turnSide(this->replaceSide(this->_sides[2], rot));
    rotatedCube->_sides[11] = this->turnSide(this->replaceSide(this->_sides[9], rot));
    break;
  case 17:
    //Side 4 forwards rotate left
    rotatedCube->_corners[0] = this->replaceCorner(this->_corners[7], rot);
    rotatedCube->_corners[1] = this->turnCornerRight(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[2] = this->turnCornerLeft(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[3] = this->turnCornerLeft(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[4] = this->turnCornerRight(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[5] = this->turnCornerRight(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[6] = this->replaceCorner(this->_corners[1], rot);
    rotatedCube->_corners[7] = this->turnCornerLeft(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_sides[0] = this->turnSide(this->replaceSide(this->_sides[11], rot));
    rotatedCube->_sides[1] = this->replaceSide(this->_sides[7], rot);
    rotatedCube->_sides[2] = this->turnSide(this->replaceSide(this->_sides[5], rot));
    rotatedCube->_sides[3] = this->replaceSide(this->_sides[9], rot);
    rotatedCube->_sides[4] = this->turnSide(this->replaceSide(this->_sides[3], rot));
    rotatedCube->_sides[5] = this->turnSide(this->replaceSide(this->_sides[6], rot));
    rotatedCube->_sides[6] = this->replaceSide(this->_sides[2], rot);
    rotatedCube->_sides[7] = this->turnSide(this->replaceSide(this->_sides[10], rot));
    rotatedCube->_sides[8] = this->replaceSide(this->_sides[0], rot);
    rotatedCube->_sides[9] = this->turnSide(this->replaceSide(this->_sides[4], rot));
    rotatedCube->_sides[10] = this->turnSide(this->replaceSide(this->_sides[1], rot));
    rotatedCube->_sides[11] = this->turnSide(this->replaceSide(this->_sides[8], rot));
    break;
  case 18:
    //Side 4 forwards rotate 2x
    rotatedCube->_corners[0] = this->replaceCorner(this->_corners[6], rot);
    rotatedCube->_corners[1] = this->turnCornerRight(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[2] = this->turnCornerLeft(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[3] = this->turnCornerLeft(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[4] = this->turnCornerRight(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[5] = this->turnCornerRight(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[6] = this->replaceCorner(this->_corners[0], rot);
    rotatedCube->_corners[7] = this->turnCornerLeft(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_sides[0] = this->turnSide(this->replaceSide(this->_sides[10], rot));
    rotatedCube->_sides[1] = this->replaceSide(this->_sides[6], rot);
    rotatedCube->_sides[2] = this->turnSide(this->replaceSide(this->_sides[4], rot));
    rotatedCube->_sides[3] = this->replaceSide(this->_sides[8], rot);
    rotatedCube->_sides[4] = this->turnSide(this->replaceSide(this->_sides[2], rot));
    rotatedCube->_sides[5] = this->turnSide(this->replaceSide(this->_sides[5], rot));
    rotatedCube->_sides[6] = this->replaceSide(this->_sides[1], rot);
    rotatedCube->_sides[7] = this->turnSide(this->replaceSide(this->_sides[9], rot));
    rotatedCube->_sides[8] = this->replaceSide(this->_sides[3], rot);
    rotatedCube->_sides[9] = this->turnSide(this->replaceSide(this->_sides[7], rot));
    rotatedCube->_sides[10] = this->turnSide(this->replaceSide(this->_sides[0], rot));
    rotatedCube->_sides[11] = this->turnSide(this->replaceSide(this->_sides[11], rot));
    break;
  case 19:
    //Side 4 forwards rotate right
    rotatedCube->_corners[0] = this->replaceCorner(this->_corners[5], rot);
    rotatedCube->_corners[1] = this->turnCornerRight(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[2] = this->turnCornerLeft(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[3] = this->turnCornerLeft(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[4] = this->turnCornerRight(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[5] = this->turnCornerRight(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[6] = this->replaceCorner(this->_corners[3], rot);
    rotatedCube->_corners[7] = this->turnCornerLeft(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_sides[0] = this->turnSide(this->replaceSide(this->_sides[9], rot));
    rotatedCube->_sides[1] = this->replaceSide(this->_sides[5], rot);
    rotatedCube->_sides[2] = this->turnSide(this->replaceSide(this->_sides[7], rot));
    rotatedCube->_sides[3] = this->replaceSide(this->_sides[11], rot);
    rotatedCube->_sides[4] = this->turnSide(this->replaceSide(this->_sides[1], rot));
    rotatedCube->_sides[5] = this->turnSide(this->replaceSide(this->_sides[4], rot));
    rotatedCube->_sides[6] = this->replaceSide(this->_sides[0], rot);
    rotatedCube->_sides[7] = this->turnSide(this->replaceSide(this->_sides[8], rot));
    rotatedCube->_sides[8] = this->replaceSide(this->_sides[2], rot);
    rotatedCube->_sides[9] = this->turnSide(this->replaceSide(this->_sides[6], rot));
    rotatedCube->_sides[10] = this->turnSide(this->replaceSide(this->_sides[3], rot));
    rotatedCube->_sides[11] = this->turnSide(this->replaceSide(this->_sides[10], rot));
    break;
  case 20:
    //Side 5 forwards
    rotatedCube->_corners[0] = this->turnCornerLeft(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[1] = this->turnCornerLeft(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[2] = this->replaceCorner(this->_corners[6], rot);
    rotatedCube->_corners[3] = this->turnCornerRight(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[4] = this->replaceCorner(this->_corners[0], rot);
    rotatedCube->_corners[5] = this->turnCornerLeft(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[6] = this->turnCornerRight(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[7] = this->turnCornerRight(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_sides[0] = this->turnSide(this->replaceSide(this->_sides[4], rot));
    rotatedCube->_sides[1] = this->replaceSide(this->_sides[8], rot);
    rotatedCube->_sides[2] = this->turnSide(this->replaceSide(this->_sides[10], rot));
    rotatedCube->_sides[3] = this->replaceSide(this->_sides[6], rot);
    rotatedCube->_sides[4] = this->replaceSide(this->_sides[1], rot);
    rotatedCube->_sides[5] = this->turnSide(this->replaceSide(this->_sides[9], rot));
    rotatedCube->_sides[6] = this->turnSide(this->replaceSide(this->_sides[2], rot));
    rotatedCube->_sides[7] = this->turnSide(this->replaceSide(this->_sides[5], rot));
    rotatedCube->_sides[8] = this->turnSide(this->replaceSide(this->_sides[0], rot));
    rotatedCube->_sides[9] = this->turnSide(this->replaceSide(this->_sides[11], rot));
    rotatedCube->_sides[10] = this->replaceSide(this->_sides[3], rot);
    rotatedCube->_sides[11] = this->turnSide(this->replaceSide(this->_sides[7], rot));
    break;
  case 21:
    //Side 5 forwards rotate left
    rotatedCube->_corners[0] = this->turnCornerLeft(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_corners[1] = this->turnCornerLeft(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[2] = this->replaceCorner(this->_corners[7], rot);
    rotatedCube->_corners[3] = this->turnCornerRight(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[4] = this->replaceCorner(this->_corners[1], rot);
    rotatedCube->_corners[5] = this->turnCornerLeft(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[6] = this->turnCornerRight(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[7] = this->turnCornerRight(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_sides[0] = this->turnSide(this->replaceSide(this->_sides[5], rot));
    rotatedCube->_sides[1] = this->replaceSide(this->_sides[9], rot);
    rotatedCube->_sides[2] = this->turnSide(this->replaceSide(this->_sides[11], rot));
    rotatedCube->_sides[3] = this->replaceSide(this->_sides[7], rot);
    rotatedCube->_sides[4] = this->replaceSide(this->_sides[2], rot);
    rotatedCube->_sides[5] = this->turnSide(this->replaceSide(this->_sides[10], rot));
    rotatedCube->_sides[6] = this->turnSide(this->replaceSide(this->_sides[3], rot));
    rotatedCube->_sides[7] = this->turnSide(this->replaceSide(this->_sides[6], rot));
    rotatedCube->_sides[8] = this->turnSide(this->replaceSide(this->_sides[1], rot));
    rotatedCube->_sides[9] = this->turnSide(this->replaceSide(this->_sides[8], rot));
    rotatedCube->_sides[10] = this->replaceSide(this->_sides[0], rot);
    rotatedCube->_sides[11] = this->turnSide(this->replaceSide(this->_sides[4], rot));
    break;
  case 22:
    //Side 5 forwards rotate 2x
    rotatedCube->_corners[0] = this->turnCornerLeft(this->replaceCorner(this->_corners[3], rot));
    rotatedCube->_corners[1] = this->turnCornerLeft(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[2] = this->replaceCorner(this->_corners[4], rot);
    rotatedCube->_corners[3] = this->turnCornerRight(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[4] = this->replaceCorner(this->_corners[2], rot);
    rotatedCube->_corners[5] = this->turnCornerLeft(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[6] = this->turnCornerRight(this->replaceCorner(this->_corners[5], rot));
    rotatedCube->_corners[7] = this->turnCornerRight(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_sides[0] = this->turnSide(this->replaceSide(this->_sides[6], rot));
    rotatedCube->_sides[1] = this->replaceSide(this->_sides[10], rot);
    rotatedCube->_sides[2] = this->turnSide(this->replaceSide(this->_sides[8], rot));
    rotatedCube->_sides[3] = this->replaceSide(this->_sides[4], rot);
    rotatedCube->_sides[4] = this->replaceSide(this->_sides[3], rot);
    rotatedCube->_sides[5] = this->turnSide(this->replaceSide(this->_sides[11], rot));
    rotatedCube->_sides[6] = this->turnSide(this->replaceSide(this->_sides[0], rot));
    rotatedCube->_sides[7] = this->turnSide(this->replaceSide(this->_sides[7], rot));
    rotatedCube->_sides[8] = this->turnSide(this->replaceSide(this->_sides[2], rot));
    rotatedCube->_sides[9] = this->turnSide(this->replaceSide(this->_sides[9], rot));
    rotatedCube->_sides[10] = this->replaceSide(this->_sides[1], rot);
    rotatedCube->_sides[11] = this->turnSide(this->replaceSide(this->_sides[5], rot));
    break;
  case 23:
    //Side 5 forwards rotate right
    rotatedCube->_corners[0] = this->turnCornerLeft(this->replaceCorner(this->_corners[0], rot));
    rotatedCube->_corners[1] = this->turnCornerLeft(this->replaceCorner(this->_corners[4], rot));
    rotatedCube->_corners[2] = this->replaceCorner(this->_corners[5], rot);
    rotatedCube->_corners[3] = this->turnCornerRight(this->replaceCorner(this->_corners[1], rot));
    rotatedCube->_corners[4] = this->replaceCorner(this->_corners[3], rot);
    rotatedCube->_corners[5] = this->turnCornerLeft(this->replaceCorner(this->_corners[7], rot));
    rotatedCube->_corners[6] = this->turnCornerRight(this->replaceCorner(this->_corners[6], rot));
    rotatedCube->_corners[7] = this->turnCornerRight(this->replaceCorner(this->_corners[2], rot));
    rotatedCube->_sides[0] = this->turnSide(this->replaceSide(this->_sides[7], rot));
    rotatedCube->_sides[1] = this->replaceSide(this->_sides[11], rot);
    rotatedCube->_sides[2] = this->turnSide(this->replaceSide(this->_sides[9], rot));
    rotatedCube->_sides[3] = this->replaceSide(this->_sides[5], rot);
    rotatedCube->_sides[4] = this->replaceSide(this->_sides[0], rot);
    rotatedCube->_sides[5] = this->turnSide(this->replaceSide(this->_sides[8], rot));
    rotatedCube->_sides[6] = this->turnSide(this->replaceSide(this->_sides[1], rot));
    rotatedCube->_sides[7] = this->turnSide(this->replaceSide(this->_sides[4], rot));
    rotatedCube->_sides[8] = this->turnSide(this->replaceSide(this->_sides[3], rot));
    rotatedCube->_sides[9] = this->turnSide(this->replaceSide(this->_sides[10], rot));
    rotatedCube->_sides[10] = this->replaceSide(this->_sides[2], rot);
    rotatedCube->_sides[11] = this->turnSide(this->replaceSide(this->_sides[6], rot));
    break;
  default:
    break;
  }
  return rotatedCube;
}


__int8 Cube::replaceSide(__int8 side, int rot)
{
  __int8 color = side&254;
  __int8 turn = side&1;
  switch(rot)
  {
  case 0:
    //Side 0 forwards
    if(color == 6)
			return 0 + turn;
    if(color == 0)
			return 2 + turn;
    if(color == 2)
			return 4 + turn;
    if(color == 4)
			return 6 + turn;
    if(color == 14)
			return 8 + turn;
    if(color == 8)
			return 10 + turn;
    if(color == 10)
			return 12 + turn;
    if(color == 12)
			return 14 + turn;
    if(color == 22)
			return 16 + turn;
    if(color == 16)
			return 18 + turn;
    if(color == 18)
			return 20 + turn;
    if(color == 20)
			return 22 + turn;
    break;
  case 1:
    //Side 0 forwards rotate left
    if(color == 12)
			return 0 + turn;
    if(color == 8)
			return 2 + !turn;
    if(color == 16)
			return 4 + turn;
    if(color == 20)
			return 6 + !turn;
    if(color == 10)
			return 8 + !turn;
    if(color == 2)
			return 10 + turn;
    if(color == 18)
			return 12 + !turn;
    if(color == 4)
			return 14 + !turn;
    if(color == 14)
			return 16 + !turn;
    if(color == 0)
			return 18 + !turn;
    if(color == 22)
			return 20 + !turn;
    if(color == 6)
			return 22 + turn;
    break;
  case 2:
    //Side 0 forwards rotate 2x
    if(color == 4)
			return 0 + !turn;
    if(color == 2)
			return 2 + !turn;
    if(color == 0)
			return 4 + !turn;
    if(color == 6)
			return 6 + !turn;
    if(color == 18)
			return 8 + turn;
    if(color == 16)
			return 10 + turn;
    if(color == 22)
			return 12 + turn;
    if(color == 20)
			return 14 + turn;
    if(color == 10)
			return 16 + turn;
    if(color == 8)
			return 18 + turn;
    if(color == 14)
			return 20 + turn;
    if(color == 12)
			return 22 + turn;
    break;
  case 3:
    //Side 0 forwards rotate right
    if(color == 20)
			return 0 + turn;
    if(color == 16)
			return 2 + !turn;
    if(color == 8)
			return 4 + turn;
    if(color == 12)
			return 6 + !turn;
    if(color == 22)
			return 8 + !turn;
    if(color == 0)
			return 10 + !turn;
    if(color == 14)
			return 12 + !turn;
    if(color == 6)
			return 14 + turn;
    if(color == 18)
			return 16 + !turn;
    if(color == 2)
			return 18 + turn;
    if(color == 10)
			return 20 + !turn;
    if(color == 4)
			return 22 + !turn;
    break;
  case 4:
    //Side 1 forwards
    break;
  case 5:
    //Side 1 forwards rotate left
    if(color == 14)
			return 0 + turn;
    if(color == 10)
			return 2 + !turn;
    if(color == 18)
			return 4 + turn;
    if(color == 22)
			return 6 + !turn;
    if(color == 12)
			return 8 + !turn;
    if(color == 4)
			return 10 + turn;
    if(color == 20)
			return 12 + !turn;
    if(color == 6)
			return 14 + !turn;
    if(color == 8)
			return 16 + !turn;
    if(color == 2)
			return 18 + !turn;
    if(color == 16)
			return 20 + !turn;
    if(color == 0)
			return 22 + turn;
    break;
  case 6:
    //Side 1 forwards rotate 2x
    if(color == 6)
			return 0 + !turn;
    if(color == 4)
			return 2 + !turn;
    if(color == 2)
			return 4 + !turn;
    if(color == 0)
			return 6 + !turn;
    if(color == 20)
			return 8 + turn;
    if(color == 18)
			return 10 + turn;
    if(color == 16)
			return 12 + turn;
    if(color == 22)
			return 14 + turn;
    if(color == 12)
			return 16 + turn;
    if(color == 10)
			return 18 + turn;
    if(color == 8)
			return 20 + turn;
    if(color == 14)
			return 22 + turn;
    break;
  case 7:
    //Side 1 forwards rotate right
    if(color == 22)
			return 0 + turn;
    if(color == 18)
			return 2 + !turn;
    if(color == 10)
			return 4 + turn;
    if(color == 14)
			return 6 + !turn;
    if(color == 16)
			return 8 + !turn;
    if(color == 2)
			return 10 + !turn;
    if(color == 8)
			return 12 + !turn;
    if(color == 0)
			return 14 + turn;
    if(color == 20)
			return 16 + !turn;
    if(color == 4)
			return 18 + turn;
    if(color == 12)
			return 20 + !turn;
    if(color == 6)
			return 22 + !turn;
    break;
  case 8:
    //Side 2 forwards
    if(color == 2)
			return 0 + turn;
    if(color == 4)
			return 2 + turn;
    if(color == 6)
			return 4 + turn;
    if(color == 0)
			return 6 + turn;
    if(color == 10)
			return 8 + turn;
    if(color == 12)
			return 10 + turn;
    if(color == 14)
			return 12 + turn;
    if(color == 8)
			return 14 + turn;
    if(color == 18)
			return 16 + turn;
    if(color == 20)
			return 18 + turn;
    if(color == 22)
			return 20 + turn;
    if(color == 16)
			return 22 + turn;
    break;
  case 9:
    //Side 2 forwards rotate left
    if(color == 8)
			return 0 + turn;
    if(color == 12)
			return 2 + !turn;
    if(color == 20)
			return 4 + turn;
    if(color == 16)
			return 6 + !turn;
    if(color == 14)
			return 8 + !turn;
    if(color == 6)
			return 10 + turn;
    if(color == 22)
			return 12 + !turn;
    if(color == 0)
			return 14 + !turn;
    if(color == 10)
			return 16 + !turn;
    if(color == 4)
			return 18 + !turn;
    if(color == 18)
			return 20 + !turn;
    if(color == 2)
			return 22 + turn;
    break;
  case 10:
    //Side 2 forwards rotate 2x
    if(color == 0)
			return 0 + !turn;
    if(color == 6)
			return 2 + !turn;
    if(color == 4)
			return 4 + !turn;
    if(color == 2)
			return 6 + !turn;
    if(color == 22)
			return 8 + turn;
    if(color == 20)
			return 10 + turn;
    if(color == 18)
			return 12 + turn;
    if(color == 16)
			return 14 + turn;
    if(color == 14)
			return 16 + turn;
    if(color == 12)
			return 18 + turn;
    if(color == 10)
			return 20 + turn;
    if(color == 8)
			return 22 + turn;
    break;
  case 11:
    //Side 2 forwards rotate right
    if(color == 16)
			return 0 + turn;
    if(color == 20)
			return 2 + !turn;
    if(color == 12)
			return 4 + turn;
    if(color == 8)
			return 6 + !turn;
    if(color == 18)
			return 8 + !turn;
    if(color == 4)
			return 10 + !turn;
    if(color == 10)
			return 12 + !turn;
    if(color == 2)
			return 14 + turn;
    if(color == 22)
			return 16 + !turn;
    if(color == 6)
			return 18 + turn;
    if(color == 14)
			return 20 + !turn;
    if(color == 0)
			return 22 + !turn;
    break;
  case 12:
    //Side 3 forwards
    if(color == 4)
			return 0 + turn;
    if(color == 6)
			return 2 + turn;
    if(color == 0)
			return 4 + turn;
    if(color == 2)
			return 6 + turn;
    if(color == 12)
			return 8 + turn;
    if(color == 14)
			return 10 + turn;
    if(color == 8)
			return 12 + turn;
    if(color == 10)
			return 14 + turn;
    if(color == 20)
			return 16 + turn;
    if(color == 22)
			return 18 + turn;
    if(color == 16)
			return 20 + turn;
    if(color == 18)
			return 22 + turn;
    break;
  case 13:
    //Side 3 forwards rotate left
    if(color == 10)
			return 0 + turn;
    if(color == 14)
			return 2 + !turn;
    if(color == 22)
			return 4 + turn;
    if(color == 18)
			return 6 + !turn;
    if(color == 8)
			return 8 + !turn;
    if(color == 0)
			return 10 + turn;
    if(color == 16)
			return 12 + !turn;
    if(color == 2)
			return 14 + !turn;
    if(color == 12)
			return 16 + !turn;
    if(color == 6)
			return 18 + !turn;
    if(color == 20)
			return 20 + !turn;
    if(color == 4)
			return 22 + turn;
    break;
  case 14:
    //Side 3 forwards rotate 2x
    if(color == 2)
			return 0 + !turn;
    if(color == 0)
			return 2 + !turn;
    if(color == 6)
			return 4 + !turn;
    if(color == 4)
			return 6 + !turn;
    if(color == 16)
			return 8 + turn;
    if(color == 22)
			return 10 + turn;
    if(color == 20)
			return 12 + turn;
    if(color == 18)
			return 14 + turn;
    if(color == 8)
			return 16 + turn;
    if(color == 14)
			return 18 + turn;
    if(color == 12)
			return 20 + turn;
    if(color == 10)
			return 22 + turn;
    break;
  case 15:
    //Side 3 forwards rotate right
    if(color == 18)
			return 0 + turn;
    if(color == 22)
			return 2 + !turn;
    if(color == 14)
			return 4 + turn;
    if(color == 10)
			return 6 + !turn;
    if(color == 20)
			return 8 + !turn;
    if(color == 6)
			return 10 + !turn;
    if(color == 12)
			return 12 + !turn;
    if(color == 4)
			return 14 + turn;
    if(color == 16)
			return 16 + !turn;
    if(color == 0)
			return 18 + turn;
    if(color == 8)
			return 20 + !turn;
    if(color == 2)
			return 22 + !turn;
    break;
  case 16:
    //Side 4 forwards
    if(color == 16)
			return 0 + !turn;
    if(color == 8)
			return 2 + turn;
    if(color == 12)
			return 4 + !turn;
    if(color == 20)
			return 6 + turn;
    if(color == 0)
			return 8 + !turn;
    if(color == 14)
			return 10 + !turn;
    if(color == 6)
			return 12 + turn;
    if(color == 22)
			return 14 + !turn;
    if(color == 2)
			return 16 + turn;
    if(color == 10)
			return 18 + !turn;
    if(color == 4)
			return 20 + !turn;
    if(color == 18)
			return 22 + !turn;
    break;
  case 17:
    //Side 4 forwards rotate left
    if(color == 22)
			return 0 + !turn;
    if(color == 14)
			return 2 + turn;
    if(color == 10)
			return 4 + !turn;
    if(color == 18)
			return 6 + turn;
    if(color == 6)
			return 8 + !turn;
    if(color == 12)
			return 10 + !turn;
    if(color == 4)
			return 12 + turn;
    if(color == 20)
			return 14 + !turn;
    if(color == 0)
			return 16 + turn;
    if(color == 8)
			return 18 + !turn;
    if(color == 2)
			return 20 + !turn;
    if(color == 16)
			return 22 + !turn;
    break;
  case 18:
    //Side 4 forwards rotate 2x
    if(color == 20)
			return 0 + !turn;
    if(color == 12)
			return 2 + turn;
    if(color == 8)
			return 4 + !turn;
    if(color == 16)
			return 6 + turn;
    if(color == 4)
			return 8 + !turn;
    if(color == 10)
			return 10 + !turn;
    if(color == 2)
			return 12 + turn;
    if(color == 18)
			return 14 + !turn;
    if(color == 6)
			return 16 + turn;
    if(color == 14)
			return 18 + !turn;
    if(color == 0)
			return 20 + !turn;
    if(color == 22)
			return 22 + !turn;
    break;
  case 19:
    //Side 4 forwards rotate right
    if(color == 18)
			return 0 + !turn;
    if(color == 10)
			return 2 + turn;
    if(color == 14)
			return 4 + !turn;
    if(color == 22)
			return 6 + turn;
    if(color == 2)
			return 8 + !turn;
    if(color == 8)
			return 10 + !turn;
    if(color == 0)
			return 12 + turn;
    if(color == 16)
			return 14 + !turn;
    if(color == 4)
			return 16 + turn;
    if(color == 12)
			return 18 + !turn;
    if(color == 6)
			return 20 + !turn;
    if(color == 20)
			return 22 + !turn;
    break;
  case 20:
    //Side 5 forwards
    if(color == 8)
			return 0 + !turn;
    if(color == 16)
			return 2 + turn;
    if(color == 20)
			return 4 + !turn;
    if(color == 12)
			return 6 + turn;
    if(color == 2)
			return 8 + turn;
    if(color == 18)
			return 10 + !turn;
    if(color == 4)
			return 12 + !turn;
    if(color == 10)
			return 14 + !turn;
    if(color == 0)
			return 16 + !turn;
    if(color == 22)
			return 18 + !turn;
    if(color == 6)
			return 20 + turn;
    if(color == 14)
			return 22 + !turn;
    break;
  case 21:
    //Side 5 forwards rotate left
    if(color == 10)
			return 0 + !turn;
    if(color == 18)
			return 2 + turn;
    if(color == 22)
			return 4 + !turn;
    if(color == 14)
			return 6 + turn;
    if(color == 4)
			return 8 + turn;
    if(color == 20)
			return 10 + !turn;
    if(color == 6)
			return 12 + !turn;
    if(color == 12)
			return 14 + !turn;
    if(color == 2)
			return 16 + !turn;
    if(color == 16)
			return 18 + !turn;
    if(color == 0)
			return 20 + turn;
    if(color == 8)
			return 22 + !turn;
    break;
  case 22:
    //Side 5 forwards rotate 2x
    if(color == 12)
			return 0 + !turn;
    if(color == 20)
			return 2 + turn;
    if(color == 16)
			return 4 + !turn;
    if(color == 8)
			return 6 + turn;
    if(color == 6)
			return 8 + turn;
    if(color == 22)
			return 10 + !turn;
    if(color == 0)
			return 12 + !turn;
    if(color == 14)
			return 14 + !turn;
    if(color == 4)
			return 16 + !turn;
    if(color == 18)
			return 18 + !turn;
    if(color == 2)
			return 20 + turn;
    if(color == 10)
			return 22 + !turn;
    break;
  case 23:
    //Side 5 forwards rotate right
    if(color == 14)
			return 0 + !turn;
    if(color == 22)
			return 2 + turn;
    if(color == 18)
			return 4 + !turn;
    if(color == 10)
			return 6 + turn;
    if(color == 0)
			return 8 + turn;
    if(color == 16)
			return 10 + !turn;
    if(color == 2)
			return 12 + !turn;
    if(color == 8)
			return 14 + !turn;
    if(color == 6)
			return 16 + !turn;
    if(color == 20)
			return 18 + !turn;
    if(color == 4)
			return 20 + turn;
    if(color == 12)
			return 22 + !turn;
    break;
  default:
    break;
  }
  return 0;
}


__int8 Cube::replaceCorner(__int8 corner, int rot)
{
  __int8 color = corner&252;
  __int8 turn = corner&3;
  switch(rot)
  {
  case 0:
    //Side 0 forwards
    if(color == 12)
			return 0 + turn;
    if(color == 0)
			return 4 + turn;
    if(color == 4)
			return 8 + turn;
    if(color == 8)
			return 12 + turn;
    if(color == 28)
			return 16 + turn;
    if(color == 16)
			return 20 + turn;
    if(color == 20)
			return 24 + turn;
    if(color == 24)
			return 28 + turn;
    break;
  case 1:
    //Side 0 forwards rotate left
    if(color == 8)
			return 0 + this->turnCornerLeft(turn);
    if(color == 4)
			return 4 + this->turnCornerRight(turn);
    if(color == 20)
			return 8 + this->turnCornerRight(turn);
    if(color == 24)
			return 12 + turn;
    if(color == 12)
			return 16 + this->turnCornerLeft(turn);
    if(color == 0)
			return 20 + turn;
    if(color == 16)
			return 24 + this->turnCornerRight(turn);
    if(color == 28)
			return 28 + this->turnCornerLeft(turn);
    break;
  case 2:
    //Side 0 forwards rotate 2x
    if(color == 24)
			return 0 + this->turnCornerLeft(turn);
    if(color == 20)
			return 4 + this->turnCornerLeft(turn);
    if(color == 16)
			return 8 + this->turnCornerLeft(turn);
    if(color == 28)
			return 12 + this->turnCornerLeft(turn);
    if(color == 8)
			return 16 + this->turnCornerRight(turn);
    if(color == 4)
			return 20 + this->turnCornerRight(turn);
    if(color == 0)
			return 24 + this->turnCornerRight(turn);
    if(color == 12)
			return 28 + this->turnCornerRight(turn);
    break;
  case 3:
    //Side 0 forwards rotate right
    if(color == 28)
			return 0 + this->turnCornerRight(turn);
    if(color == 16)
			return 4 + turn;
    if(color == 0)
			return 8 + this->turnCornerLeft(turn);
    if(color == 12)
			return 12 + this->turnCornerRight(turn);
    if(color == 24)
			return 16 + this->turnCornerRight(turn);
    if(color == 20)
			return 20 + this->turnCornerLeft(turn);
    if(color == 4)
			return 24 + this->turnCornerLeft(turn);
    if(color == 8)
			return 28 + turn;
    break;
  case 4:
    //Side 1 forwards
    break;
  case 5:
    //Side 1 forwards rotate left
    if(color == 12)
			return 0 + this->turnCornerLeft(turn);
    if(color == 8)
			return 4 + this->turnCornerRight(turn);
    if(color == 24)
			return 8 + this->turnCornerRight(turn);
    if(color == 28)
			return 12 + turn;
    if(color == 0)
			return 16 + this->turnCornerLeft(turn);
    if(color == 4)
			return 20 + turn;
    if(color == 20)
			return 24 + this->turnCornerRight(turn);
    if(color == 16)
			return 28 + this->turnCornerLeft(turn);
    break;
  case 6:
    //Side 1 forwards rotate 2x
    if(color == 28)
			return 0 + this->turnCornerLeft(turn);
    if(color == 24)
			return 4 + this->turnCornerLeft(turn);
    if(color == 20)
			return 8 + this->turnCornerLeft(turn);
    if(color == 16)
			return 12 + this->turnCornerLeft(turn);
    if(color == 12)
			return 16 + this->turnCornerRight(turn);
    if(color == 8)
			return 20 + this->turnCornerRight(turn);
    if(color == 4)
			return 24 + this->turnCornerRight(turn);
    if(color == 0)
			return 28 + this->turnCornerRight(turn);
    break;
  case 7:
    //Side 1 forwards rotate right
    if(color == 16)
			return 0 + this->turnCornerRight(turn);
    if(color == 20)
			return 4 + turn;
    if(color == 4)
			return 8 + this->turnCornerLeft(turn);
    if(color == 0)
			return 12 + this->turnCornerRight(turn);
    if(color == 28)
			return 16 + this->turnCornerRight(turn);
    if(color == 24)
			return 20 + this->turnCornerLeft(turn);
    if(color == 8)
			return 24 + this->turnCornerLeft(turn);
    if(color == 12)
			return 28 + turn;
    break;
  case 8:
    //Side 2 forwards
    if(color == 4)
			return 0 + turn;
    if(color == 8)
			return 4 + turn;
    if(color == 12)
			return 8 + turn;
    if(color == 0)
			return 12 + turn;
    if(color == 20)
			return 16 + turn;
    if(color == 24)
			return 20 + turn;
    if(color == 28)
			return 24 + turn;
    if(color == 16)
			return 28 + turn;
    break;
  case 9:
    //Side 2 forwards rotate left
    if(color == 0)
			return 0 + this->turnCornerLeft(turn);
    if(color == 12)
			return 4 + this->turnCornerRight(turn);
    if(color == 28)
			return 8 + this->turnCornerRight(turn);
    if(color == 16)
			return 12 + turn;
    if(color == 4)
			return 16 + this->turnCornerLeft(turn);
    if(color == 8)
			return 20 + turn;
    if(color == 24)
			return 24 + this->turnCornerRight(turn);
    if(color == 20)
			return 28 + this->turnCornerLeft(turn);
    break;
  case 10:
    //Side 2 forwards rotate 2x
    if(color == 16)
			return 0 + this->turnCornerLeft(turn);
    if(color == 28)
			return 4 + this->turnCornerLeft(turn);
    if(color == 24)
			return 8 + this->turnCornerLeft(turn);
    if(color == 20)
			return 12 + this->turnCornerLeft(turn);
    if(color == 0)
			return 16 + this->turnCornerRight(turn);
    if(color == 12)
			return 20 + this->turnCornerRight(turn);
    if(color == 8)
			return 24 + this->turnCornerRight(turn);
    if(color == 4)
			return 28 + this->turnCornerRight(turn);
    break;
  case 11:
    //Side 2 forwards rotate right
    if(color == 20)
			return 0 + this->turnCornerRight(turn);
    if(color == 24)
			return 4 + turn;
    if(color == 8)
			return 8 + this->turnCornerLeft(turn);
    if(color == 4)
			return 12 + this->turnCornerRight(turn);
    if(color == 16)
			return 16 + this->turnCornerRight(turn);
    if(color == 28)
			return 20 + this->turnCornerLeft(turn);
    if(color == 12)
			return 24 + this->turnCornerLeft(turn);
    if(color == 0)
			return 28 + turn;
    break;
  case 12:
    //Side 3 forwards
    if(color == 8)
			return 0 + turn;
    if(color == 12)
			return 4 + turn;
    if(color == 0)
			return 8 + turn;
    if(color == 4)
			return 12 + turn;
    if(color == 24)
			return 16 + turn;
    if(color == 28)
			return 20 + turn;
    if(color == 16)
			return 24 + turn;
    if(color == 20)
			return 28 + turn;
    break;
  case 13:
    //Side 3 forwards rotate left
    if(color == 4)
			return 0 + this->turnCornerLeft(turn);
    if(color == 0)
			return 4 + this->turnCornerRight(turn);
    if(color == 16)
			return 8 + this->turnCornerRight(turn);
    if(color == 20)
			return 12 + turn;
    if(color == 8)
			return 16 + this->turnCornerLeft(turn);
    if(color == 12)
			return 20 + turn;
    if(color == 28)
			return 24 + this->turnCornerRight(turn);
    if(color == 24)
			return 28 + this->turnCornerLeft(turn);
    break;
  case 14:
    //Side 3 forwards rotate 2x
    if(color == 20)
			return 0 + this->turnCornerLeft(turn);
    if(color == 16)
			return 4 + this->turnCornerLeft(turn);
    if(color == 28)
			return 8 + this->turnCornerLeft(turn);
    if(color == 24)
			return 12 + this->turnCornerLeft(turn);
    if(color == 4)
			return 16 + this->turnCornerRight(turn);
    if(color == 0)
			return 20 + this->turnCornerRight(turn);
    if(color == 12)
			return 24 + this->turnCornerRight(turn);
    if(color == 8)
			return 28 + this->turnCornerRight(turn);
    break;
  case 15:
    //Side 3 forwards rotate right
    if(color == 24)
			return 0 + this->turnCornerRight(turn);
    if(color == 28)
			return 4 + turn;
    if(color == 12)
			return 8 + this->turnCornerLeft(turn);
    if(color == 8)
			return 12 + this->turnCornerRight(turn);
    if(color == 20)
			return 16 + this->turnCornerRight(turn);
    if(color == 16)
			return 20 + this->turnCornerLeft(turn);
    if(color == 0)
			return 24 + this->turnCornerLeft(turn);
    if(color == 4)
			return 28 + turn;
    break;
  case 16:
    //Side 4 forwards
    if(color == 16)
			return 0 + turn;
    if(color == 0)
			return 4 + this->turnCornerLeft(turn);
    if(color == 12)
			return 8 + this->turnCornerRight(turn);
    if(color == 28)
			return 12 + this->turnCornerRight(turn);
    if(color == 20)
			return 16 + this->turnCornerLeft(turn);
    if(color == 4)
			return 20 + this->turnCornerLeft(turn);
    if(color == 8)
			return 24 + turn;
    if(color == 24)
			return 28 + this->turnCornerRight(turn);
    break;
  case 17:
    //Side 4 forwards rotate left
    if(color == 28)
			return 0 + turn;
    if(color == 12)
			return 4 + this->turnCornerLeft(turn);
    if(color == 8)
			return 8 + this->turnCornerRight(turn);
    if(color == 24)
			return 12 + this->turnCornerRight(turn);
    if(color == 16)
			return 16 + this->turnCornerLeft(turn);
    if(color == 0)
			return 20 + this->turnCornerLeft(turn);
    if(color == 4)
			return 24 + turn;
    if(color == 20)
			return 28 + this->turnCornerRight(turn);
    break;
  case 18:
    //Side 4 forwards rotate 2x
    if(color == 24)
			return 0 + turn;
    if(color == 8)
			return 4 + this->turnCornerLeft(turn);
    if(color == 4)
			return 8 + this->turnCornerRight(turn);
    if(color == 20)
			return 12 + this->turnCornerRight(turn);
    if(color == 28)
			return 16 + this->turnCornerLeft(turn);
    if(color == 12)
			return 20 + this->turnCornerLeft(turn);
    if(color == 0)
			return 24 + turn;
    if(color == 16)
			return 28 + this->turnCornerRight(turn);
    break;
  case 19:
    //Side 4 forwards rotate right
    if(color == 20)
			return 0 + turn;
    if(color == 4)
			return 4 + this->turnCornerLeft(turn);
    if(color == 0)
			return 8 + this->turnCornerRight(turn);
    if(color == 16)
			return 12 + this->turnCornerRight(turn);
    if(color == 24)
			return 16 + this->turnCornerLeft(turn);
    if(color == 8)
			return 20 + this->turnCornerLeft(turn);
    if(color == 12)
			return 24 + turn;
    if(color == 28)
			return 28 + this->turnCornerRight(turn);
    break;
  case 20:
    //Side 5 forwards
    if(color == 4)
			return 0 + this->turnCornerRight(turn);
    if(color == 20)
			return 4 + this->turnCornerRight(turn);
    if(color == 24)
			return 8 + turn;
    if(color == 8)
			return 12 + this->turnCornerLeft(turn);
    if(color == 0)
			return 16 + turn;
    if(color == 16)
			return 20 + this->turnCornerRight(turn);
    if(color == 28)
			return 24 + this->turnCornerLeft(turn);
    if(color == 12)
			return 28 + this->turnCornerLeft(turn);
    break;
  case 21:
    //Side 5 forwards rotate left
    if(color == 8)
			return 0 + this->turnCornerRight(turn);
    if(color == 24)
			return 4 + this->turnCornerRight(turn);
    if(color == 28)
			return 8 + turn;
    if(color == 12)
			return 12 + this->turnCornerLeft(turn);
    if(color == 4)
			return 16 + turn;
    if(color == 20)
			return 20 + this->turnCornerRight(turn);
    if(color == 16)
			return 24 + this->turnCornerLeft(turn);
    if(color == 0)
			return 28 + this->turnCornerLeft(turn);
    break;
  case 22:
    //Side 5 forwards rotate 2x
    if(color == 12)
			return 0 + this->turnCornerRight(turn);
    if(color == 28)
			return 4 + this->turnCornerRight(turn);
    if(color == 16)
			return 8 + turn;
    if(color == 0)
			return 12 + this->turnCornerLeft(turn);
    if(color == 8)
			return 16 + turn;
    if(color == 24)
			return 20 + this->turnCornerRight(turn);
    if(color == 20)
			return 24 + this->turnCornerLeft(turn);
    if(color == 4)
			return 28 + this->turnCornerLeft(turn);
    break;
  case 23:
    //Side 5 forwards rotate right
    if(color == 0)
			return 0 + this->turnCornerRight(turn);
    if(color == 16)
			return 4 + this->turnCornerRight(turn);
    if(color == 20)
			return 8 + turn;
    if(color == 4)
			return 12 + this->turnCornerLeft(turn);
    if(color == 12)
			return 16 + turn;
    if(color == 28)
			return 20 + this->turnCornerRight(turn);
    if(color == 24)
			return 24 + this->turnCornerLeft(turn);
    if(color == 8)
			return 28 + this->turnCornerLeft(turn);
    break;
  default:
    break;
  }
  return 0;

}

__int8 Cube::turnSide(__int8 side)
{
  if((side&1) == 1)
    return side-1;
  else
    return side+1;
}

__int8 Cube::turnCornerRight(__int8 corner)
{
  if((corner&3) < 2)
    return corner+1;
  else
    return corner-2;
}

__int8 Cube::turnCornerLeft(__int8 corner)
{
  if((corner&3) > 0)
    return corner-1;
  else
    return corner+2;
}

void BinaryNodeRef::nodeRef(BinaryNode* b){
  _nodeRef = b;
  _id = _nodeRef->id();
}

void BinaryNodeRef::createNode(BinaryNode* parent, BinaryNode* smaller, BinaryNode* bigger, Cube* cube){
  if(_id != NONE){
    std::cout << "Error: Trying to create node on already valid noderef" << std::endl;
    return;
  }
  BinaryNode* testingNode = cubeSolver.testingNode();
  if(!testingNode){
    std::cout << "Error: No testingNode in BinaryNodeRef::createNode()" << std::endl;
    return;
  }
  _id = cubeSolver.useId();
  _nodeRef = new BinaryNode(_id, testingNode, parent, smaller, bigger, cube);
}

BinaryNode* BinaryNodeRef::nodeRef(){
  if(!_nodeRef && _id != NONE)
    _nodeRef = new BinaryNode(_id);
  return _nodeRef;
}

BinaryNode::BinaryNode(__int64 id, BinaryNode* solveParent, BinaryNode* parent, BinaryNode* smaller, BinaryNode* bigger, Cube* cube){
  std::cout << "Creating BinaryNode: " << id << std::endl;
  this->id(id);
  if(solveParent)
    _solveParent.id(solveParent->id());
  if(parent)
    _parent.id(parent->id());
  if(smaller)
    _smaller.id(smaller->id());
  if(bigger)
    _bigger.id(bigger->id());
  _cube = cube;
}

bool BinaryNode::operator==(const BinaryNode& other)
{
  return *(this->_cube) == *(other._cube);
}


bool BinaryNode::operator<(const BinaryNode& other)
{
  return *(this->_cube) < *(other._cube);
}


bool BinaryNode::operator>(const BinaryNode& other)
{
  return *(this->_cube) > *(other._cube);
}

void BinaryNode::save(){
  std::fstream* file = cubeSolver.getFileInPos(_id);
  __int64 solveParentId = _solveParent.id();
  __int64 parentId = _parent.id();
  __int64 smallerId = _smaller.id();
  __int64 biggerId = _bigger.id();
  file->write(reinterpret_cast<char*>(&solveParentId), sizeof(solveParentId));
  file->write(reinterpret_cast<char*>(&parentId), sizeof(parentId));
  file->write(reinterpret_cast<char*>(&smallerId), sizeof(smallerId));
  file->write(reinterpret_cast<char*>(&biggerId), sizeof(biggerId));
  if(_cube)
    _cube->save(file);
  std::cout << "Saved node " << _id << " (" << solveParentId << ", " << parentId << ", " << smallerId << ", " << biggerId << ")" << std::endl;
  _cube->print();

}

void BinaryNode::generateChildren(){
  if(!_cube){
    std::cout << "Error: No _cube in generateChildren()" << std::endl;
  }
  for(int rot=0; rot<12; rot++){
    std::cout << "Rot: " << rot << std::endl;
    Cube* child = _cube->returnChild(rot);
    child->print();
    std::cout << "Inserting smallest rot: " << std::endl;
    child = cubeSolver.getSmallestRotation(child);
    child->print();
    int depth = cubeSolver.insertIntoTree(child);
  }
}

int BinaryNode::insertIntoTree(Cube* cube){
  if(!_cube){
    std::cout << "Error: No _cube in BinaryNode::insertIntoTree()" << std::endl;
    return NO_ACTION;
  }
  int seb = cube->seb(_cube);
  if(seb == SEB::SMALLER){
    if(_smaller.id() == NONE){
      std::cout << "Cube smaller than " << _id << ". Creating new node" << std::endl;
      _smaller.createNode(this, nullptr, nullptr, new Cube(cube));
      _smaller.nodeRef()->save();
      save();
      return 1;
    }else{
      std::cout << "Cube smaller than " << _id << ". Continuing..." << std::endl;
      return _smaller.nodeRef()->insertIntoTree(cube);
    }
  }else if(seb == SEB::BIGGER){
    if(_bigger.id() == NONE){
      std::cout << "Cube bigger than " << _id << ". Creating new node" << std::endl;
      _bigger.createNode(this, nullptr, nullptr, new Cube(cube));
      _bigger.nodeRef()->save();
      save();
      return 1;
    }else{
      std::cout << "Cube bigger than " << _id << ". Continuing..." << std::endl;
      return _bigger.nodeRef()->insertIntoTree(cube);
    }
  }else{
    std::cout << "Cube equal to " << _id << ". ending..." << std::endl;
    return NO_ACTION;
  }
}

void BinaryNode::load(__int64 id){
  std::fstream* file = cubeSolver.getFileInPos(id);
  __int64 smallerId;
  __int64 biggerId;
  __int64 parentId;
  __int64 solveParentId;
  file->read(reinterpret_cast<char*>(&smallerId), sizeof(smallerId));
  file->read(reinterpret_cast<char*>(&biggerId), sizeof(biggerId));
  file->read(reinterpret_cast<char*>(&parentId), sizeof(parentId));
  file->read(reinterpret_cast<char*>(&solveParentId), sizeof(solveParentId));
  _smaller.id(smallerId);
  _bigger.id(biggerId);
  _parent.id(parentId);
  _solveParent.id(solveParentId);
  this->id(id);
  _cube = new Cube(file);
}

CubeSolver::CubeSolver(){
  //If file exist, load top node and testingCube from it
  if(fileExist(_fileName)){
    _topNode = new BinaryNode(0);
    while(_topNode->parentId() != NONE){
      __int64 parentId = _topNode->parentId();
      delete _topNode;
      _topNode = new BinaryNode(parentId);
    }
    BinaryNode* lastNode = new BinaryNode(-1);
    _testingNode = new BinaryNode(lastNode->solveParentId());
    delete lastNode;
  }
  //If file does not exist, start from a solved cube.
  else{
    //Create starting cube
    Cube* startingCube = new Cube();
    startingCube->setStartingCube();
    startingCube = getSmallestRotation(startingCube);
    //Create top node with cube above
    _topNode = new BinaryNode(0, nullptr, nullptr, nullptr, nullptr, startingCube);
    //Set tesing node to copy of node above
    _testingNode = new BinaryNode(0, nullptr, nullptr, nullptr, nullptr, new Cube(startingCube));
    _topNode->save();
    _nextId=1;
  }
}

void CubeSolver::run(){
  if(!_testingNode){
    std::cout << "error: no _testingNode in CubeSolver::Run()" << std::endl;
    return;
  }
  std::string ans = "";
  while(ans != "q"){
    std::cout << "Tested " << _testingNode->id() << "/" << _nextId << " cubes."
    std::cout << "How many cubes should we test? (q for quit): " << std::endl;
    std::cin >> ans;
    int runGenerations = 0;
    try{
      runGenerations = std::stoi(ans);
    }
    catch(...)
    {
    }
    for(int i=0; i<runGenerations; i++){
      _testingNode->generateChildren();
      __int64 testId = _testingNode->id()+1;
      delete _testingNode;
      _testingNode = new BinaryNode(testId);
    }
  }
}

std::fstream* CubeSolver::getFileInPos(__int64 id){
  if(!_file.is_open())
    openFile();
  if(id<0)
    _file.seekg(NODE_SIZE*id, std::ios::end);
  else
    _file.seekg(NODE_SIZE*id);
  return &_file;
}

Cube* CubeSolver::getSmallestRotation(Cube* cube){
  Cube* smallestCube = cube;
  for(int rot=0; rot<24; rot++){
    if(rot == 4)
    rot++;
    Cube* rotatedCube = cube->returnRot(rot);
    if((*rotatedCube) < (*smallestCube)){
      if(smallestCube != cube)
        delete smallestCube;  //Dont delete cube until we are done
      smallestCube = rotatedCube;
    }
  }
  if(smallestCube != cube)    //Now delete cube unless it is being returned
    delete cube;
  return smallestCube;
}

int CubeSolver::insertIntoTree(Cube* cube){
  if(!_topNode){
    std::cout << "Error: No _topNode in CubeSolver::insertIntoTree" << std::endl;
    return NO_ACTION;
  }
  return _topNode->insertIntoTree(cube);
}

void CubeSolver::openFile(){
  if(_file.is_open()){
    std::cout << "Warning: File already open" << std::endl;
    return;
  }
  _file.open(_fileName, std::ios::in | std::ios::out | std::ios::binary);
  if(!_file.is_open()){
    //Try to create file (apperantly it does not try to create when you have ios::in)
    _file.open(_fileName, std::ios::out | std::ios::binary);
    if(!_file.is_open()){
      std::cout << "Error: Could not open or create file" << std::endl;
      return;
    }
    _file.close();
    _file.open(_fileName, std::ios::in | std::ios::out | std::ios::binary);
    if(!_file.is_open()){
      std::cout << "Error: Could create but not open file" << std::endl;
    }
  }
}

bool CubeSolver::fileExist(const std::string& name) {
  return ( access( name.c_str(), F_OK ) != -1 );
}
