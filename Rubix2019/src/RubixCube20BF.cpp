#include <iostream>
#include <iomanip>
#include "RubixCube20BF.h"

RubixCube20BF::RubixCube20BF()
{
  adress = 0;
  parent = 0;
  firstChild = 0;
  sibling = 0;
  //ctor
}

RubixCube20BF& RubixCube20BF::operator=(const RubixCube20BF& other)
{
  for(int a=0; a<12; a++)
  {
    if(a<8)
      this->corners[a] = other.corners[a];
    this->sides[a] = other.sides[a];
  }
  return *this;
}


bool RubixCube20BF::operator==(const RubixCube20BF& other)
{
  for(int a=0; a<12; a++)
  {
    if(a<8 && this->corners[a] != other.corners[a])
      return false;
    if(this->sides[a] != other.sides[a])
      return false;
  }
  return true;
}

bool RubixCube20BF::operator==(const RubixCube20B& other)
{
  for(int a=0; a<12; a++)
  {
    if(a<8 && this->corners[a] != other.corners[a])
      return false;
    if(this->sides[a] != other.sides[a])
      return false;
  }
  return true;
}

bool RubixCube20BF::operator<(const RubixCube20BF& other)
{
  for(int a=0; a<12; a++)
  {
    if(a<8 && this->corners[a] > other.corners[a])
      return false;
    if(a<8 && this->corners[a] < other.corners[a])
      return true;
    if(this->sides[a] > other.sides[a])
      return false;
    if(this->sides[a] < other.sides[a])
      return true;
  }
  return false;
}

bool RubixCube20BF::operator>(const RubixCube20BF& other)
{
  for(int a=0; a<12; a++)
  {
    if(a<8 && this->corners[a] < other.corners[a])
      return false;
    if(a<8 && this->corners[a] > other.corners[a])
      return true;
    if(this->sides[a] < other.sides[a])
      return false;
    if(this->sides[a] > other.sides[a])
      return true;
  }
  return false;
}

int RubixCube20BF::seb(RubixCube20BF* other)
{
  for(int a=0; a<12; a++)
  {
    if(a<8 && this->corners[a] > other->corners[a])
      return BIGGER;
    if(a<8 && this->corners[a] < other->corners[a])
      return SMALLER;
    if(this->sides[a] > other->sides[a])
      return BIGGER;
    if(this->sides[a] < other->sides[a])
      return SMALLER;
  }
  return EQUALS;
}

void RubixCube20BF::print(bool verbose)
{
  std::cout << "Cube adress: " << adress << std::endl;
  std::cout << "Parent: " << parent << std::endl;
  std::cout << "FirstChild: " << firstChild << std::endl;
  std::cout << "Sibling: " << sibling << std::endl;
  if(verbose)
  {
    std::cout << "                " << std::setw(3) << (int)(this->sides[7]) << std::endl;
    std::cout << "            " << std::setw(3) << (int)(this->sides[4]) << "     " << std::setw(3) << (int)(this->sides[6]) << std::endl;
    std::cout << "                " << std::setw(3) << (int)(this->sides[5]) << std::endl;
    std::cout << std::setw(3) << (int)(this->corners[0]) << "         " << std::setw(3) << (int)(this->corners[1]) << "         " << std::setw(3) << (int)(this->corners[2]) << "         " << std::setw(3) << (int)(this->corners[3]) << std::endl;
    std::cout << std::setw(3) << (int)(this->sides[0])   << "         " << std::setw(3) << (int)(this->sides[1])   << "         " << std::setw(3) << (int)(this->sides[2])   << "         " << std::setw(3) << (int)(this->sides[3])   << std::endl;
    std::cout << std::setw(3) << (int)(this->corners[4]) << "         " << std::setw(3) << (int)(this->corners[5]) << "         " << std::setw(3) << (int)(this->corners[6]) << "         " << std::setw(3) << (int)(this->corners[7]) << std::endl;
    std::cout << "                " << std::setw(3) << (int)(this->sides[9]) << std::endl;
    std::cout << "            " << std::setw(3) << (int)(this->sides[8]) << "     " << (int)(this->sides[10]) << std::endl;
    std::cout << "                " << std::setw(3) << (int)(this->sides[11]) << std::endl;
  }
}


RubixCube20BF RubixCube20BF::returnChild(int move)
{
  RubixCube20BF child = *this;
  child.parent = adress;
  switch(move)
  {
  case 0:
    //Turn side 0 clockwise
    child.corners[0] = this->corners[4];
    child.corners[1] = this->turnCornerRight(this->corners[0]);
    child.corners[2] = this->corners[2];
    child.corners[3] = this->corners[3];
    child.corners[4] = this->turnCornerRight(this->corners[5]);
    child.corners[5] = this->turnCornerRight(this->corners[1]);
    child.corners[6] = this->corners[6];
    child.corners[7] = this->corners[7];
    child.sides[0] = this->turnSide(this->sides[8]);
    child.sides[1] = this->sides[4];
    child.sides[2] = this->sides[2];
    child.sides[3] = this->sides[3];
    child.sides[4] = this->turnSide(this->sides[0]);
    child.sides[5] = this->sides[5];
    child.sides[6] = this->sides[6];
    child.sides[7] = this->sides[7];
    child.sides[8] = this->sides[1];
    child.sides[9] = this->sides[9];
    child.sides[10] = this->sides[10];
    child.sides[11] = this->sides[11];
    break;
  case 1:
    //Turn side 1 clockwise
    child.corners[0] = this->corners[0];
    child.corners[1] = this->corners[5];
    child.corners[2] = this->turnCornerRight(this->corners[1]);
    child.corners[3] = this->corners[3];
    child.corners[4] = this->corners[4];
    child.corners[5] = this->turnCornerRight(this->corners[6]);
    child.corners[6] = this->turnCornerRight(this->corners[2]);
    child.corners[7] = this->corners[7];
    child.sides[0] = this->sides[0];
    child.sides[1] = this->turnSide(this->sides[9]);
    child.sides[2] = this->sides[5];
    child.sides[3] = this->sides[3];
    child.sides[4] = this->sides[4];
    child.sides[5] = this->turnSide(this->sides[1]);
    child.sides[6] = this->sides[6];
    child.sides[7] = this->sides[7];
    child.sides[8] = this->sides[8];
    child.sides[9] = this->sides[2];
    child.sides[10] = this->sides[10];
    child.sides[11] = this->sides[11];
    break;
  case 2:
    //Turn side 2 clockwise
    child.corners[0] = this->corners[0];
    child.corners[1] = this->corners[1];
    child.corners[2] = this->corners[6];
    child.corners[3] = this->turnCornerRight(this->corners[2]);
    child.corners[4] = this->corners[4];
    child.corners[5] = this->corners[5];
    child.corners[6] = this->turnCornerRight(this->corners[7]);
    child.corners[7] = this->turnCornerRight(this->corners[3]);
    child.sides[0] = this->sides[0];
    child.sides[1] = this->sides[1];
    child.sides[2] = this->turnSide(this->sides[10]);
    child.sides[3] = this->sides[6];
    child.sides[4] = this->sides[4];
    child.sides[5] = this->sides[5];
    child.sides[6] = this->turnSide(this->sides[2]);
    child.sides[7] = this->sides[7];
    child.sides[8] = this->sides[8];
    child.sides[9] = this->sides[9];
    child.sides[10] = this->sides[3];
    child.sides[11] = this->sides[11];
    break;
  case 3:
    //Turn side 3 clockwise
    child.corners[0] = this->turnCornerRight(this->corners[3]);
    child.corners[1] = this->corners[1];
    child.corners[2] = this->corners[2];
    child.corners[3] = this->corners[7];
    child.corners[4] = this->turnCornerRight(this->corners[0]);
    child.corners[5] = this->corners[5];
    child.corners[6] = this->corners[6];
    child.corners[7] = this->turnCornerRight(this->corners[4]);
    child.sides[0] = this->sides[7];
    child.sides[1] = this->sides[1];
    child.sides[2] = this->sides[2];
    child.sides[3] = this->turnSide(this->sides[11]);
    child.sides[4] = this->sides[4];
    child.sides[5] = this->sides[5];
    child.sides[6] = this->sides[6];
    child.sides[7] = this->turnSide(this->sides[3]);
    child.sides[8] = this->sides[8];
    child.sides[9] = this->sides[9];
    child.sides[10] = this->sides[10];
    child.sides[11] = this->sides[0];
    break;
  case 4:
    //Turn side 4 clockwise
    child.corners[0] = this->corners[1];
    child.corners[1] = this->corners[2];
    child.corners[2] = this->corners[3];
    child.corners[3] = this->corners[0];
    child.corners[4] = this->corners[4];
    child.corners[5] = this->corners[5];
    child.corners[6] = this->corners[6];
    child.corners[7] = this->corners[7];
    child.sides[0] = this->sides[0];
    child.sides[1] = this->sides[1];
    child.sides[2] = this->sides[2];
    child.sides[3] = this->sides[3];
    child.sides[4] = this->sides[5];
    child.sides[5] = this->sides[6];
    child.sides[6] = this->sides[7];
    child.sides[7] = this->sides[4];
    child.sides[8] = this->sides[8];
    child.sides[9] = this->sides[9];
    child.sides[10] = this->sides[10];
    child.sides[11] = this->sides[11];
    break;
  case 5:
    //Turn side 5 clockwise
    child.corners[0] = this->corners[0];
    child.corners[1] = this->corners[1];
    child.corners[2] = this->corners[2];
    child.corners[3] = this->corners[3];
    child.corners[4] = this->corners[7];
    child.corners[5] = this->corners[4];
    child.corners[6] = this->corners[5];
    child.corners[7] = this->corners[6];
    child.sides[0] = this->sides[0];
    child.sides[1] = this->sides[1];
    child.sides[2] = this->sides[2];
    child.sides[3] = this->sides[3];
    child.sides[4] = this->sides[4];
    child.sides[5] = this->sides[5];
    child.sides[6] = this->sides[6];
    child.sides[7] = this->sides[7];
    child.sides[8] = this->sides[11];
    child.sides[9] = this->sides[8];
    child.sides[10] = this->sides[9];
    child.sides[11] = this->sides[10];
    break;
  case 6:
    //Turn side 0 counter clockwise
    child.corners[0] = this->turnCornerLeft(this->corners[1]);
    child.corners[1] = this->turnCornerLeft(this->corners[5]);
    child.corners[2] = this->corners[2];
    child.corners[3] = this->corners[3];
    child.corners[4] = this->corners[0];
    child.corners[5] = this->turnCornerLeft(this->corners[4]);
    child.corners[6] = this->corners[6];
    child.corners[7] = this->corners[7];
    child.sides[0] = this->turnSide(this->sides[4]);
    child.sides[1] = this->sides[8];
    child.sides[2] = this->sides[2];
    child.sides[3] = this->sides[3];
    child.sides[4] = this->sides[1];
    child.sides[5] = this->sides[5];
    child.sides[6] = this->sides[6];
    child.sides[7] = this->sides[7];
    child.sides[8] = this->turnSide(this->sides[0]);
    child.sides[9] = this->sides[9];
    child.sides[10] = this->sides[10];
    child.sides[11] = this->sides[11];
    break;
  case 7:
    //Turn side 1 counter clockwise
    child.corners[0] = this->corners[0];
    child.corners[1] = this->turnCornerLeft(this->corners[2]);
    child.corners[2] = this->turnCornerLeft(this->corners[6]);
    child.corners[3] = this->corners[3];
    child.corners[4] = this->corners[4];
    child.corners[5] = this->corners[1];
    child.corners[6] = this->turnCornerLeft(this->corners[5]);
    child.corners[7] = this->corners[7];
    child.sides[0] = this->sides[0];
    child.sides[1] = this->turnSide(this->sides[5]);
    child.sides[2] = this->sides[9];
    child.sides[3] = this->sides[3];
    child.sides[4] = this->sides[4];
    child.sides[5] = this->sides[2];
    child.sides[6] = this->sides[6];
    child.sides[7] = this->sides[7];
    child.sides[8] = this->sides[8];
    child.sides[9] = this->turnSide(this->sides[1]);
    child.sides[10] = this->sides[10];
    child.sides[11] = this->sides[11];
    break;
  case 8:
    //Turn side 2 counter clockwise
    child.corners[0] = this->corners[0];
    child.corners[1] = this->corners[1];
    child.corners[2] = this->turnCornerLeft(this->corners[3]);
    child.corners[3] = this->turnCornerLeft(this->corners[7]);
    child.corners[4] = this->corners[4];
    child.corners[5] = this->corners[5];
    child.corners[6] = this->corners[2];
    child.corners[7] = this->turnCornerLeft(this->corners[6]);
    child.sides[0] = this->sides[0];
    child.sides[1] = this->sides[1];
    child.sides[2] = this->turnSide(this->sides[6]);
    child.sides[3] = this->sides[10];
    child.sides[4] = this->sides[4];
    child.sides[5] = this->sides[5];
    child.sides[6] = this->sides[3];
    child.sides[7] = this->sides[7];
    child.sides[8] = this->sides[8];
    child.sides[9] = this->sides[9];
    child.sides[10] = this->turnSide(this->sides[2]);
    child.sides[11] = this->sides[11];
    break;
  case 9:
    //Turn side 3 counter clockwise
    child.corners[0] = this->turnCornerLeft(this->corners[4]);
    child.corners[1] = this->corners[1];
    child.corners[2] = this->corners[2];
    child.corners[3] = this->turnCornerLeft(this->corners[0]);
    child.corners[4] = this->turnCornerLeft(this->corners[7]);
    child.corners[5] = this->corners[5];
    child.corners[6] = this->corners[6];
    child.corners[7] = this->corners[3];
    child.sides[0] = this->sides[11];
    child.sides[1] = this->sides[1];
    child.sides[2] = this->sides[2];
    child.sides[3] = this->turnSide(this->sides[7]);
    child.sides[4] = this->sides[4];
    child.sides[5] = this->sides[5];
    child.sides[6] = this->sides[6];
    child.sides[7] = this->sides[0];
    child.sides[8] = this->sides[8];
    child.sides[9] = this->sides[9];
    child.sides[10] = this->sides[10];
    child.sides[11] = this->turnSide(this->sides[3]);
    break;
  case 10:
    //Turn side 4 counter clockwise
    child.corners[0] = this->corners[3];
    child.corners[1] = this->corners[0];
    child.corners[2] = this->corners[1];
    child.corners[3] = this->corners[2];
    child.corners[4] = this->corners[4];
    child.corners[5] = this->corners[5];
    child.corners[6] = this->corners[6];
    child.corners[7] = this->corners[7];
    child.sides[0] = this->sides[0];
    child.sides[1] = this->sides[1];
    child.sides[2] = this->sides[2];
    child.sides[3] = this->sides[3];
    child.sides[4] = this->sides[7];
    child.sides[5] = this->sides[4];
    child.sides[6] = this->sides[5];
    child.sides[7] = this->sides[6];
    child.sides[8] = this->sides[8];
    child.sides[9] = this->sides[9];
    child.sides[10] = this->sides[10];
    child.sides[11] = this->sides[11];
    break;
  case 11:
    //Turn side 5 counter clockwise
    child.corners[0] = this->corners[0];
    child.corners[1] = this->corners[1];
    child.corners[2] = this->corners[2];
    child.corners[3] = this->corners[3];
    child.corners[4] = this->corners[5];
    child.corners[5] = this->corners[6];
    child.corners[6] = this->corners[7];
    child.corners[7] = this->corners[4];
    child.sides[0] = this->sides[0];
    child.sides[1] = this->sides[1];
    child.sides[2] = this->sides[2];
    child.sides[3] = this->sides[3];
    child.sides[4] = this->sides[4];
    child.sides[5] = this->sides[5];
    child.sides[6] = this->sides[6];
    child.sides[7] = this->sides[7];
    child.sides[8] = this->sides[9];
    child.sides[9] = this->sides[10];
    child.sides[10] = this->sides[11];
    child.sides[11] = this->sides[8];
    break;
  default:
    break;
  }
  return child;
}


RubixCube20BF RubixCube20BF::returnRot(int rot)
{
  RubixCube20BF rotatedCube;
  switch(rot)
  {
  case 0:
    //Side 0 forwards
    rotatedCube.corners[0] = this->replaceCorner(this->corners[3], rot);
    rotatedCube.corners[1] = this->replaceCorner(this->corners[0], rot);
    rotatedCube.corners[2] = this->replaceCorner(this->corners[1], rot);
    rotatedCube.corners[3] = this->replaceCorner(this->corners[2], rot);
    rotatedCube.corners[4] = this->replaceCorner(this->corners[7], rot);
    rotatedCube.corners[5] = this->replaceCorner(this->corners[4], rot);
    rotatedCube.corners[6] = this->replaceCorner(this->corners[5], rot);
    rotatedCube.corners[7] = this->replaceCorner(this->corners[6], rot);
    rotatedCube.sides[0] = this->replaceSide(this->sides[3], rot);
    rotatedCube.sides[1] = this->replaceSide(this->sides[0], rot);
    rotatedCube.sides[2] = this->replaceSide(this->sides[1], rot);
    rotatedCube.sides[3] = this->replaceSide(this->sides[2], rot);
    rotatedCube.sides[4] = this->replaceSide(this->sides[7], rot);
    rotatedCube.sides[5] = this->replaceSide(this->sides[4], rot);
    rotatedCube.sides[6] = this->replaceSide(this->sides[5], rot);
    rotatedCube.sides[7] = this->replaceSide(this->sides[6], rot);
    rotatedCube.sides[8] = this->replaceSide(this->sides[11], rot);
    rotatedCube.sides[9] = this->replaceSide(this->sides[8], rot);
    rotatedCube.sides[10] = this->replaceSide(this->sides[9], rot);
    rotatedCube.sides[11] = this->replaceSide(this->sides[10], rot);
    break;
  case 1:
    //Side 0 forwards rotate left
    rotatedCube.corners[0] = this->turnCornerRight(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[1] = this->turnCornerLeft(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[2] = this->turnCornerLeft(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[3] = this->replaceCorner(this->corners[6], rot);
    rotatedCube.corners[4] = this->turnCornerRight(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[5] = this->replaceCorner(this->corners[0], rot);
    rotatedCube.corners[6] = this->turnCornerLeft(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[7] = this->turnCornerRight(this->replaceCorner(this->corners[7], rot));
    rotatedCube.sides[0] = this->replaceSide(this->sides[6], rot);
    rotatedCube.sides[1] = this->turnSide(this->replaceSide(this->sides[4], rot));
    rotatedCube.sides[2] = this->replaceSide(this->sides[8], rot);
    rotatedCube.sides[3] = this->turnSide(this->replaceSide(this->sides[10], rot));
    rotatedCube.sides[4] = this->turnSide(this->replaceSide(this->sides[5], rot));
    rotatedCube.sides[5] = this->replaceSide(this->sides[1], rot);
    rotatedCube.sides[6] = this->turnSide(this->replaceSide(this->sides[9], rot));
    rotatedCube.sides[7] = this->turnSide(this->replaceSide(this->sides[2], rot));
    rotatedCube.sides[8] = this->turnSide(this->replaceSide(this->sides[7], rot));
    rotatedCube.sides[9] = this->turnSide(this->replaceSide(this->sides[0], rot));
    rotatedCube.sides[10] = this->turnSide(this->replaceSide(this->sides[11], rot));
    rotatedCube.sides[11] = this->replaceSide(this->sides[3], rot);
    break;
  case 2:
    //Side 0 forwards rotate 2x
    rotatedCube.corners[0] = this->turnCornerRight(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[1] = this->turnCornerRight(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[2] = this->turnCornerRight(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[3] = this->turnCornerRight(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[4] = this->turnCornerLeft(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[5] = this->turnCornerLeft(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[6] = this->turnCornerLeft(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[7] = this->turnCornerLeft(this->replaceCorner(this->corners[3], rot));
    rotatedCube.sides[0] = this->turnSide(this->replaceSide(this->sides[2], rot));
    rotatedCube.sides[1] = this->turnSide(this->replaceSide(this->sides[1], rot));
    rotatedCube.sides[2] = this->turnSide(this->replaceSide(this->sides[0], rot));
    rotatedCube.sides[3] = this->turnSide(this->replaceSide(this->sides[3], rot));
    rotatedCube.sides[4] = this->replaceSide(this->sides[9], rot);
    rotatedCube.sides[5] = this->replaceSide(this->sides[8], rot);
    rotatedCube.sides[6] = this->replaceSide(this->sides[11], rot);
    rotatedCube.sides[7] = this->replaceSide(this->sides[10], rot);
    rotatedCube.sides[8] = this->replaceSide(this->sides[5], rot);
    rotatedCube.sides[9] = this->replaceSide(this->sides[4], rot);
    rotatedCube.sides[10] = this->replaceSide(this->sides[7], rot);
    rotatedCube.sides[11] = this->replaceSide(this->sides[6], rot);
    break;
  case 3:
    //Side 0 forwards rotate right
    rotatedCube.corners[0] = this->turnCornerLeft(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[1] = this->replaceCorner(this->corners[4], rot);
    rotatedCube.corners[2] = this->turnCornerRight(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[3] = this->turnCornerLeft(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[4] = this->turnCornerLeft(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[5] = this->turnCornerRight(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[6] = this->turnCornerRight(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[7] = this->replaceCorner(this->corners[2], rot);
    rotatedCube.sides[0] = this->replaceSide(this->sides[10], rot);
    rotatedCube.sides[1] = this->turnSide(this->replaceSide(this->sides[8], rot));
    rotatedCube.sides[2] = this->replaceSide(this->sides[4], rot);
    rotatedCube.sides[3] = this->turnSide(this->replaceSide(this->sides[6], rot));
    rotatedCube.sides[4] = this->turnSide(this->replaceSide(this->sides[11], rot));
    rotatedCube.sides[5] = this->turnSide(this->replaceSide(this->sides[0], rot));
    rotatedCube.sides[6] = this->turnSide(this->replaceSide(this->sides[7], rot));
    rotatedCube.sides[7] = this->replaceSide(this->sides[3], rot);
    rotatedCube.sides[8] = this->turnSide(this->replaceSide(this->sides[9], rot));
    rotatedCube.sides[9] = this->replaceSide(this->sides[1], rot);
    rotatedCube.sides[10] = this->turnSide(this->replaceSide(this->sides[5], rot));
    rotatedCube.sides[11] = this->turnSide(this->replaceSide(this->sides[2], rot));
    break;
  case 4:
    //Side 1 forwards
    rotatedCube.corners[0] = this->corners[0];
    rotatedCube.corners[1] = this->corners[1];
    rotatedCube.corners[2] = this->corners[2];
    rotatedCube.corners[3] = this->corners[3];
    rotatedCube.corners[4] = this->corners[4];
    rotatedCube.corners[5] = this->corners[5];
    rotatedCube.corners[6] = this->corners[6];
    rotatedCube.corners[7] = this->corners[7];
    rotatedCube.sides[0] = this->sides[0];
    rotatedCube.sides[1] = this->sides[1];
    rotatedCube.sides[2] = this->sides[2];
    rotatedCube.sides[3] = this->sides[3];
    rotatedCube.sides[4] = this->sides[4];
    rotatedCube.sides[5] = this->sides[5];
    rotatedCube.sides[6] = this->sides[6];
    rotatedCube.sides[7] = this->sides[7];
    rotatedCube.sides[8] = this->sides[8];
    rotatedCube.sides[9] = this->sides[9];
    rotatedCube.sides[10] = this->sides[10];
    rotatedCube.sides[11] = this->sides[11];
    break;
  case 5:
    //Side 1 forwards rotate left
    rotatedCube.corners[0] = this->turnCornerRight(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[1] = this->turnCornerLeft(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[2] = this->turnCornerLeft(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[3] = this->replaceCorner(this->corners[7], rot);
    rotatedCube.corners[4] = this->turnCornerRight(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[5] = this->replaceCorner(this->corners[1], rot);
    rotatedCube.corners[6] = this->turnCornerLeft(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[7] = this->turnCornerRight(this->replaceCorner(this->corners[4], rot));
    rotatedCube.sides[0] = this->replaceSide(this->sides[7], rot);
    rotatedCube.sides[1] = this->turnSide(this->replaceSide(this->sides[5], rot));
    rotatedCube.sides[2] = this->replaceSide(this->sides[9], rot);
    rotatedCube.sides[3] = this->turnSide(this->replaceSide(this->sides[11], rot));
    rotatedCube.sides[4] = this->turnSide(this->replaceSide(this->sides[6], rot));
    rotatedCube.sides[5] = this->replaceSide(this->sides[2], rot);
    rotatedCube.sides[6] = this->turnSide(this->replaceSide(this->sides[10], rot));
    rotatedCube.sides[7] = this->turnSide(this->replaceSide(this->sides[3], rot));
    rotatedCube.sides[8] = this->turnSide(this->replaceSide(this->sides[4], rot));
    rotatedCube.sides[9] = this->turnSide(this->replaceSide(this->sides[1], rot));
    rotatedCube.sides[10] = this->turnSide(this->replaceSide(this->sides[8], rot));
    rotatedCube.sides[11] = this->replaceSide(this->sides[0], rot);
    break;
  case 6:
    //Side 1 forwards rotate 2x
    rotatedCube.corners[0] = this->turnCornerRight(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[1] = this->turnCornerRight(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[2] = this->turnCornerRight(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[3] = this->turnCornerRight(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[4] = this->turnCornerLeft(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[5] = this->turnCornerLeft(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[6] = this->turnCornerLeft(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[7] = this->turnCornerLeft(this->replaceCorner(this->corners[0], rot));
    rotatedCube.sides[0] = this->turnSide(this->replaceSide(this->sides[3], rot));
    rotatedCube.sides[1] = this->turnSide(this->replaceSide(this->sides[2], rot));
    rotatedCube.sides[2] = this->turnSide(this->replaceSide(this->sides[1], rot));
    rotatedCube.sides[3] = this->turnSide(this->replaceSide(this->sides[0], rot));
    rotatedCube.sides[4] = this->replaceSide(this->sides[10], rot);
    rotatedCube.sides[5] = this->replaceSide(this->sides[9], rot);
    rotatedCube.sides[6] = this->replaceSide(this->sides[8], rot);
    rotatedCube.sides[7] = this->replaceSide(this->sides[11], rot);
    rotatedCube.sides[8] = this->replaceSide(this->sides[6], rot);
    rotatedCube.sides[9] = this->replaceSide(this->sides[5], rot);
    rotatedCube.sides[10] = this->replaceSide(this->sides[4], rot);
    rotatedCube.sides[11] = this->replaceSide(this->sides[7], rot);
    break;
  case 7:
    //Side 1 forwards rotate right
    rotatedCube.corners[0] = this->turnCornerLeft(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[1] = this->replaceCorner(this->corners[5], rot);
    rotatedCube.corners[2] = this->turnCornerRight(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[3] = this->turnCornerLeft(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[4] = this->turnCornerLeft(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[5] = this->turnCornerRight(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[6] = this->turnCornerRight(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[7] = this->replaceCorner(this->corners[3], rot);
    rotatedCube.sides[0] = this->replaceSide(this->sides[11], rot);
    rotatedCube.sides[1] = this->turnSide(this->replaceSide(this->sides[9], rot));
    rotatedCube.sides[2] = this->replaceSide(this->sides[5], rot);
    rotatedCube.sides[3] = this->turnSide(this->replaceSide(this->sides[7], rot));
    rotatedCube.sides[4] = this->turnSide(this->replaceSide(this->sides[8], rot));
    rotatedCube.sides[5] = this->turnSide(this->replaceSide(this->sides[1], rot));
    rotatedCube.sides[6] = this->turnSide(this->replaceSide(this->sides[4], rot));
    rotatedCube.sides[7] = this->replaceSide(this->sides[0], rot);
    rotatedCube.sides[8] = this->turnSide(this->replaceSide(this->sides[10], rot));
    rotatedCube.sides[9] = this->replaceSide(this->sides[2], rot);
    rotatedCube.sides[10] = this->turnSide(this->replaceSide(this->sides[6], rot));
    rotatedCube.sides[11] = this->turnSide(this->replaceSide(this->sides[3], rot));
    break;
  case 8:
    //Side 2 forwards
    rotatedCube.corners[0] = this->replaceCorner(this->corners[1], rot);
    rotatedCube.corners[1] = this->replaceCorner(this->corners[2], rot);
    rotatedCube.corners[2] = this->replaceCorner(this->corners[3], rot);
    rotatedCube.corners[3] = this->replaceCorner(this->corners[0], rot);
    rotatedCube.corners[4] = this->replaceCorner(this->corners[5], rot);
    rotatedCube.corners[5] = this->replaceCorner(this->corners[6], rot);
    rotatedCube.corners[6] = this->replaceCorner(this->corners[7], rot);
    rotatedCube.corners[7] = this->replaceCorner(this->corners[4], rot);
    rotatedCube.sides[0] = this->replaceSide(this->sides[1], rot);
    rotatedCube.sides[1] = this->replaceSide(this->sides[2], rot);
    rotatedCube.sides[2] = this->replaceSide(this->sides[3], rot);
    rotatedCube.sides[3] = this->replaceSide(this->sides[0], rot);
    rotatedCube.sides[4] = this->replaceSide(this->sides[5], rot);
    rotatedCube.sides[5] = this->replaceSide(this->sides[6], rot);
    rotatedCube.sides[6] = this->replaceSide(this->sides[7], rot);
    rotatedCube.sides[7] = this->replaceSide(this->sides[4], rot);
    rotatedCube.sides[8] = this->replaceSide(this->sides[9], rot);
    rotatedCube.sides[9] = this->replaceSide(this->sides[10], rot);
    rotatedCube.sides[10] = this->replaceSide(this->sides[11], rot);
    rotatedCube.sides[11] = this->replaceSide(this->sides[8], rot);
    break;
  case 9:
    //Side 2 forwards rotate left
    rotatedCube.corners[0] = this->turnCornerRight(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[1] = this->turnCornerLeft(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[2] = this->turnCornerLeft(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[3] = this->replaceCorner(this->corners[4], rot);
    rotatedCube.corners[4] = this->turnCornerRight(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[5] = this->replaceCorner(this->corners[2], rot);
    rotatedCube.corners[6] = this->turnCornerLeft(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[7] = this->turnCornerRight(this->replaceCorner(this->corners[5], rot));
    rotatedCube.sides[0] = this->replaceSide(this->sides[4], rot);
    rotatedCube.sides[1] = this->turnSide(this->replaceSide(this->sides[6], rot));
    rotatedCube.sides[2] = this->replaceSide(this->sides[10], rot);
    rotatedCube.sides[3] = this->turnSide(this->replaceSide(this->sides[8], rot));
    rotatedCube.sides[4] = this->turnSide(this->replaceSide(this->sides[7], rot));
    rotatedCube.sides[5] = this->replaceSide(this->sides[3], rot);
    rotatedCube.sides[6] = this->turnSide(this->replaceSide(this->sides[11], rot));
    rotatedCube.sides[7] = this->turnSide(this->replaceSide(this->sides[0], rot));
    rotatedCube.sides[8] = this->turnSide(this->replaceSide(this->sides[5], rot));
    rotatedCube.sides[9] = this->turnSide(this->replaceSide(this->sides[2], rot));
    rotatedCube.sides[10] = this->turnSide(this->replaceSide(this->sides[9], rot));
    rotatedCube.sides[11] = this->replaceSide(this->sides[1], rot);
    break;
  case 10:
    //Side 2 forwards rotate 2x
    rotatedCube.corners[0] = this->turnCornerRight(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[1] = this->turnCornerRight(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[2] = this->turnCornerRight(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[3] = this->turnCornerRight(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[4] = this->turnCornerLeft(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[5] = this->turnCornerLeft(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[6] = this->turnCornerLeft(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[7] = this->turnCornerLeft(this->replaceCorner(this->corners[1], rot));
    rotatedCube.sides[0] = this->turnSide(this->replaceSide(this->sides[0], rot));
    rotatedCube.sides[1] = this->turnSide(this->replaceSide(this->sides[3], rot));
    rotatedCube.sides[2] = this->turnSide(this->replaceSide(this->sides[2], rot));
    rotatedCube.sides[3] = this->turnSide(this->replaceSide(this->sides[1], rot));
    rotatedCube.sides[4] = this->replaceSide(this->sides[11], rot);
    rotatedCube.sides[5] = this->replaceSide(this->sides[10], rot);
    rotatedCube.sides[6] = this->replaceSide(this->sides[9], rot);
    rotatedCube.sides[7] = this->replaceSide(this->sides[8], rot);
    rotatedCube.sides[8] = this->replaceSide(this->sides[7], rot);
    rotatedCube.sides[9] = this->replaceSide(this->sides[6], rot);
    rotatedCube.sides[10] = this->replaceSide(this->sides[5], rot);
    rotatedCube.sides[11] = this->replaceSide(this->sides[4], rot);
    break;
  case 11:
    //Side 2 forwards rotate right
    rotatedCube.corners[0] = this->turnCornerLeft(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[1] = this->replaceCorner(this->corners[6], rot);
    rotatedCube.corners[2] = this->turnCornerRight(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[3] = this->turnCornerLeft(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[4] = this->turnCornerLeft(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[5] = this->turnCornerRight(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[6] = this->turnCornerRight(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[7] = this->replaceCorner(this->corners[0], rot);
    rotatedCube.sides[0] = this->replaceSide(this->sides[8], rot);
    rotatedCube.sides[1] = this->turnSide(this->replaceSide(this->sides[10], rot));
    rotatedCube.sides[2] = this->replaceSide(this->sides[6], rot);
    rotatedCube.sides[3] = this->turnSide(this->replaceSide(this->sides[4], rot));
    rotatedCube.sides[4] = this->turnSide(this->replaceSide(this->sides[9], rot));
    rotatedCube.sides[5] = this->turnSide(this->replaceSide(this->sides[2], rot));
    rotatedCube.sides[6] = this->turnSide(this->replaceSide(this->sides[5], rot));
    rotatedCube.sides[7] = this->replaceSide(this->sides[1], rot);
    rotatedCube.sides[8] = this->turnSide(this->replaceSide(this->sides[11], rot));
    rotatedCube.sides[9] = this->replaceSide(this->sides[3], rot);
    rotatedCube.sides[10] = this->turnSide(this->replaceSide(this->sides[7], rot));
    rotatedCube.sides[11] = this->turnSide(this->replaceSide(this->sides[0], rot));
    break;
  case 12:
    //Side 3 forwards
    rotatedCube.corners[0] = this->replaceCorner(this->corners[2], rot);
    rotatedCube.corners[1] = this->replaceCorner(this->corners[3], rot);
    rotatedCube.corners[2] = this->replaceCorner(this->corners[0], rot);
    rotatedCube.corners[3] = this->replaceCorner(this->corners[1], rot);
    rotatedCube.corners[4] = this->replaceCorner(this->corners[6], rot);
    rotatedCube.corners[5] = this->replaceCorner(this->corners[7], rot);
    rotatedCube.corners[6] = this->replaceCorner(this->corners[4], rot);
    rotatedCube.corners[7] = this->replaceCorner(this->corners[5], rot);
    rotatedCube.sides[0] = this->replaceSide(this->sides[2], rot);
    rotatedCube.sides[1] = this->replaceSide(this->sides[3], rot);
    rotatedCube.sides[2] = this->replaceSide(this->sides[0], rot);
    rotatedCube.sides[3] = this->replaceSide(this->sides[1], rot);
    rotatedCube.sides[4] = this->replaceSide(this->sides[6], rot);
    rotatedCube.sides[5] = this->replaceSide(this->sides[7], rot);
    rotatedCube.sides[6] = this->replaceSide(this->sides[4], rot);
    rotatedCube.sides[7] = this->replaceSide(this->sides[5], rot);
    rotatedCube.sides[8] = this->replaceSide(this->sides[10], rot);
    rotatedCube.sides[9] = this->replaceSide(this->sides[11], rot);
    rotatedCube.sides[10] = this->replaceSide(this->sides[8], rot);
    rotatedCube.sides[11] = this->replaceSide(this->sides[9], rot);
    break;
  case 13:
    //Side 3 forwards rotate left
    rotatedCube.corners[0] = this->turnCornerRight(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[1] = this->turnCornerLeft(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[2] = this->turnCornerLeft(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[3] = this->replaceCorner(this->corners[5], rot);
    rotatedCube.corners[4] = this->turnCornerRight(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[5] = this->replaceCorner(this->corners[3], rot);
    rotatedCube.corners[6] = this->turnCornerLeft(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[7] = this->turnCornerRight(this->replaceCorner(this->corners[6], rot));
    rotatedCube.sides[0] = this->replaceSide(this->sides[5], rot);
    rotatedCube.sides[1] = this->turnSide(this->replaceSide(this->sides[7], rot));
    rotatedCube.sides[2] = this->replaceSide(this->sides[11], rot);
    rotatedCube.sides[3] = this->turnSide(this->replaceSide(this->sides[9], rot));
    rotatedCube.sides[4] = this->turnSide(this->replaceSide(this->sides[4], rot));
    rotatedCube.sides[5] = this->replaceSide(this->sides[0], rot);
    rotatedCube.sides[6] = this->turnSide(this->replaceSide(this->sides[8], rot));
    rotatedCube.sides[7] = this->turnSide(this->replaceSide(this->sides[1], rot));
    rotatedCube.sides[8] = this->turnSide(this->replaceSide(this->sides[6], rot));
    rotatedCube.sides[9] = this->turnSide(this->replaceSide(this->sides[3], rot));
    rotatedCube.sides[10] = this->turnSide(this->replaceSide(this->sides[10], rot));
    rotatedCube.sides[11] = this->replaceSide(this->sides[2], rot);
    break;
  case 14:
    //Side 3 forwards rotate 2x
    rotatedCube.corners[0] = this->turnCornerRight(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[1] = this->turnCornerRight(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[2] = this->turnCornerRight(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[3] = this->turnCornerRight(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[4] = this->turnCornerLeft(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[5] = this->turnCornerLeft(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[6] = this->turnCornerLeft(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[7] = this->turnCornerLeft(this->replaceCorner(this->corners[2], rot));
    rotatedCube.sides[0] = this->turnSide(this->replaceSide(this->sides[1], rot));
    rotatedCube.sides[1] = this->turnSide(this->replaceSide(this->sides[0], rot));
    rotatedCube.sides[2] = this->turnSide(this->replaceSide(this->sides[3], rot));
    rotatedCube.sides[3] = this->turnSide(this->replaceSide(this->sides[2], rot));
    rotatedCube.sides[4] = this->replaceSide(this->sides[8], rot);
    rotatedCube.sides[5] = this->replaceSide(this->sides[11], rot);
    rotatedCube.sides[6] = this->replaceSide(this->sides[10], rot);
    rotatedCube.sides[7] = this->replaceSide(this->sides[9], rot);
    rotatedCube.sides[8] = this->replaceSide(this->sides[4], rot);
    rotatedCube.sides[9] = this->replaceSide(this->sides[7], rot);
    rotatedCube.sides[10] = this->replaceSide(this->sides[6], rot);
    rotatedCube.sides[11] = this->replaceSide(this->sides[5], rot);
    break;
  case 15:
    //Side 3 forwards rotate right
    rotatedCube.corners[0] = this->turnCornerLeft(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[1] = this->replaceCorner(this->corners[7], rot);
    rotatedCube.corners[2] = this->turnCornerRight(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[3] = this->turnCornerLeft(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[4] = this->turnCornerLeft(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[5] = this->turnCornerRight(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[6] = this->turnCornerRight(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[7] = this->replaceCorner(this->corners[1], rot);
    rotatedCube.sides[0] = this->replaceSide(this->sides[9], rot);
    rotatedCube.sides[1] = this->turnSide(this->replaceSide(this->sides[11], rot));
    rotatedCube.sides[2] = this->replaceSide(this->sides[7], rot);
    rotatedCube.sides[3] = this->turnSide(this->replaceSide(this->sides[5], rot));
    rotatedCube.sides[4] = this->turnSide(this->replaceSide(this->sides[10], rot));
    rotatedCube.sides[5] = this->turnSide(this->replaceSide(this->sides[3], rot));
    rotatedCube.sides[6] = this->turnSide(this->replaceSide(this->sides[6], rot));
    rotatedCube.sides[7] = this->replaceSide(this->sides[2], rot);
    rotatedCube.sides[8] = this->turnSide(this->replaceSide(this->sides[8], rot));
    rotatedCube.sides[9] = this->replaceSide(this->sides[0], rot);
    rotatedCube.sides[10] = this->turnSide(this->replaceSide(this->sides[4], rot));
    rotatedCube.sides[11] = this->turnSide(this->replaceSide(this->sides[1], rot));
    break;
  case 16:
    //Side 4 forwards
    rotatedCube.corners[0] = this->replaceCorner(this->corners[4], rot);
    rotatedCube.corners[1] = this->turnCornerRight(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[2] = this->turnCornerLeft(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[3] = this->turnCornerLeft(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[4] = this->turnCornerRight(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[5] = this->turnCornerRight(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[6] = this->replaceCorner(this->corners[2], rot);
    rotatedCube.corners[7] = this->turnCornerLeft(this->replaceCorner(this->corners[6], rot));
    rotatedCube.sides[0] = this->turnSide(this->replaceSide(this->sides[8], rot));
    rotatedCube.sides[1] = this->replaceSide(this->sides[4], rot);
    rotatedCube.sides[2] = this->turnSide(this->replaceSide(this->sides[6], rot));
    rotatedCube.sides[3] = this->replaceSide(this->sides[10], rot);
    rotatedCube.sides[4] = this->turnSide(this->replaceSide(this->sides[0], rot));
    rotatedCube.sides[5] = this->turnSide(this->replaceSide(this->sides[7], rot));
    rotatedCube.sides[6] = this->replaceSide(this->sides[3], rot);
    rotatedCube.sides[7] = this->turnSide(this->replaceSide(this->sides[11], rot));
    rotatedCube.sides[8] = this->replaceSide(this->sides[1], rot);
    rotatedCube.sides[9] = this->turnSide(this->replaceSide(this->sides[5], rot));
    rotatedCube.sides[10] = this->turnSide(this->replaceSide(this->sides[2], rot));
    rotatedCube.sides[11] = this->turnSide(this->replaceSide(this->sides[9], rot));
    break;
  case 17:
    //Side 4 forwards rotate left
    rotatedCube.corners[0] = this->replaceCorner(this->corners[7], rot);
    rotatedCube.corners[1] = this->turnCornerRight(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[2] = this->turnCornerLeft(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[3] = this->turnCornerLeft(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[4] = this->turnCornerRight(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[5] = this->turnCornerRight(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[6] = this->replaceCorner(this->corners[1], rot);
    rotatedCube.corners[7] = this->turnCornerLeft(this->replaceCorner(this->corners[5], rot));
    rotatedCube.sides[0] = this->turnSide(this->replaceSide(this->sides[11], rot));
    rotatedCube.sides[1] = this->replaceSide(this->sides[7], rot);
    rotatedCube.sides[2] = this->turnSide(this->replaceSide(this->sides[5], rot));
    rotatedCube.sides[3] = this->replaceSide(this->sides[9], rot);
    rotatedCube.sides[4] = this->turnSide(this->replaceSide(this->sides[3], rot));
    rotatedCube.sides[5] = this->turnSide(this->replaceSide(this->sides[6], rot));
    rotatedCube.sides[6] = this->replaceSide(this->sides[2], rot);
    rotatedCube.sides[7] = this->turnSide(this->replaceSide(this->sides[10], rot));
    rotatedCube.sides[8] = this->replaceSide(this->sides[0], rot);
    rotatedCube.sides[9] = this->turnSide(this->replaceSide(this->sides[4], rot));
    rotatedCube.sides[10] = this->turnSide(this->replaceSide(this->sides[1], rot));
    rotatedCube.sides[11] = this->turnSide(this->replaceSide(this->sides[8], rot));
    break;
  case 18:
    //Side 4 forwards rotate 2x
    rotatedCube.corners[0] = this->replaceCorner(this->corners[6], rot);
    rotatedCube.corners[1] = this->turnCornerRight(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[2] = this->turnCornerLeft(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[3] = this->turnCornerLeft(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[4] = this->turnCornerRight(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[5] = this->turnCornerRight(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[6] = this->replaceCorner(this->corners[0], rot);
    rotatedCube.corners[7] = this->turnCornerLeft(this->replaceCorner(this->corners[4], rot));
    rotatedCube.sides[0] = this->turnSide(this->replaceSide(this->sides[10], rot));
    rotatedCube.sides[1] = this->replaceSide(this->sides[6], rot);
    rotatedCube.sides[2] = this->turnSide(this->replaceSide(this->sides[4], rot));
    rotatedCube.sides[3] = this->replaceSide(this->sides[8], rot);
    rotatedCube.sides[4] = this->turnSide(this->replaceSide(this->sides[2], rot));
    rotatedCube.sides[5] = this->turnSide(this->replaceSide(this->sides[5], rot));
    rotatedCube.sides[6] = this->replaceSide(this->sides[1], rot);
    rotatedCube.sides[7] = this->turnSide(this->replaceSide(this->sides[9], rot));
    rotatedCube.sides[8] = this->replaceSide(this->sides[3], rot);
    rotatedCube.sides[9] = this->turnSide(this->replaceSide(this->sides[7], rot));
    rotatedCube.sides[10] = this->turnSide(this->replaceSide(this->sides[0], rot));
    rotatedCube.sides[11] = this->turnSide(this->replaceSide(this->sides[11], rot));
    break;
  case 19:
    //Side 4 forwards rotate right
    rotatedCube.corners[0] = this->replaceCorner(this->corners[5], rot);
    rotatedCube.corners[1] = this->turnCornerRight(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[2] = this->turnCornerLeft(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[3] = this->turnCornerLeft(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[4] = this->turnCornerRight(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[5] = this->turnCornerRight(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[6] = this->replaceCorner(this->corners[3], rot);
    rotatedCube.corners[7] = this->turnCornerLeft(this->replaceCorner(this->corners[7], rot));
    rotatedCube.sides[0] = this->turnSide(this->replaceSide(this->sides[9], rot));
    rotatedCube.sides[1] = this->replaceSide(this->sides[5], rot);
    rotatedCube.sides[2] = this->turnSide(this->replaceSide(this->sides[7], rot));
    rotatedCube.sides[3] = this->replaceSide(this->sides[11], rot);
    rotatedCube.sides[4] = this->turnSide(this->replaceSide(this->sides[1], rot));
    rotatedCube.sides[5] = this->turnSide(this->replaceSide(this->sides[4], rot));
    rotatedCube.sides[6] = this->replaceSide(this->sides[0], rot);
    rotatedCube.sides[7] = this->turnSide(this->replaceSide(this->sides[8], rot));
    rotatedCube.sides[8] = this->replaceSide(this->sides[2], rot);
    rotatedCube.sides[9] = this->turnSide(this->replaceSide(this->sides[6], rot));
    rotatedCube.sides[10] = this->turnSide(this->replaceSide(this->sides[3], rot));
    rotatedCube.sides[11] = this->turnSide(this->replaceSide(this->sides[10], rot));
    break;
  case 20:
    //Side 5 forwards
    rotatedCube.corners[0] = this->turnCornerLeft(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[1] = this->turnCornerLeft(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[2] = this->replaceCorner(this->corners[6], rot);
    rotatedCube.corners[3] = this->turnCornerRight(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[4] = this->replaceCorner(this->corners[0], rot);
    rotatedCube.corners[5] = this->turnCornerLeft(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[6] = this->turnCornerRight(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[7] = this->turnCornerRight(this->replaceCorner(this->corners[3], rot));
    rotatedCube.sides[0] = this->turnSide(this->replaceSide(this->sides[4], rot));
    rotatedCube.sides[1] = this->replaceSide(this->sides[8], rot);
    rotatedCube.sides[2] = this->turnSide(this->replaceSide(this->sides[10], rot));
    rotatedCube.sides[3] = this->replaceSide(this->sides[6], rot);
    rotatedCube.sides[4] = this->replaceSide(this->sides[1], rot);
    rotatedCube.sides[5] = this->turnSide(this->replaceSide(this->sides[9], rot));
    rotatedCube.sides[6] = this->turnSide(this->replaceSide(this->sides[2], rot));
    rotatedCube.sides[7] = this->turnSide(this->replaceSide(this->sides[5], rot));
    rotatedCube.sides[8] = this->turnSide(this->replaceSide(this->sides[0], rot));
    rotatedCube.sides[9] = this->turnSide(this->replaceSide(this->sides[11], rot));
    rotatedCube.sides[10] = this->replaceSide(this->sides[3], rot);
    rotatedCube.sides[11] = this->turnSide(this->replaceSide(this->sides[7], rot));
    break;
  case 21:
    //Side 5 forwards rotate left
    rotatedCube.corners[0] = this->turnCornerLeft(this->replaceCorner(this->corners[2], rot));
    rotatedCube.corners[1] = this->turnCornerLeft(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[2] = this->replaceCorner(this->corners[7], rot);
    rotatedCube.corners[3] = this->turnCornerRight(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[4] = this->replaceCorner(this->corners[1], rot);
    rotatedCube.corners[5] = this->turnCornerLeft(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[6] = this->turnCornerRight(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[7] = this->turnCornerRight(this->replaceCorner(this->corners[0], rot));
    rotatedCube.sides[0] = this->turnSide(this->replaceSide(this->sides[5], rot));
    rotatedCube.sides[1] = this->replaceSide(this->sides[9], rot);
    rotatedCube.sides[2] = this->turnSide(this->replaceSide(this->sides[11], rot));
    rotatedCube.sides[3] = this->replaceSide(this->sides[7], rot);
    rotatedCube.sides[4] = this->replaceSide(this->sides[2], rot);
    rotatedCube.sides[5] = this->turnSide(this->replaceSide(this->sides[10], rot));
    rotatedCube.sides[6] = this->turnSide(this->replaceSide(this->sides[3], rot));
    rotatedCube.sides[7] = this->turnSide(this->replaceSide(this->sides[6], rot));
    rotatedCube.sides[8] = this->turnSide(this->replaceSide(this->sides[1], rot));
    rotatedCube.sides[9] = this->turnSide(this->replaceSide(this->sides[8], rot));
    rotatedCube.sides[10] = this->replaceSide(this->sides[0], rot);
    rotatedCube.sides[11] = this->turnSide(this->replaceSide(this->sides[4], rot));
    break;
  case 22:
    //Side 5 forwards rotate 2x
    rotatedCube.corners[0] = this->turnCornerLeft(this->replaceCorner(this->corners[3], rot));
    rotatedCube.corners[1] = this->turnCornerLeft(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[2] = this->replaceCorner(this->corners[4], rot);
    rotatedCube.corners[3] = this->turnCornerRight(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[4] = this->replaceCorner(this->corners[2], rot);
    rotatedCube.corners[5] = this->turnCornerLeft(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[6] = this->turnCornerRight(this->replaceCorner(this->corners[5], rot));
    rotatedCube.corners[7] = this->turnCornerRight(this->replaceCorner(this->corners[1], rot));
    rotatedCube.sides[0] = this->turnSide(this->replaceSide(this->sides[6], rot));
    rotatedCube.sides[1] = this->replaceSide(this->sides[10], rot);
    rotatedCube.sides[2] = this->turnSide(this->replaceSide(this->sides[8], rot));
    rotatedCube.sides[3] = this->replaceSide(this->sides[4], rot);
    rotatedCube.sides[4] = this->replaceSide(this->sides[3], rot);
    rotatedCube.sides[5] = this->turnSide(this->replaceSide(this->sides[11], rot));
    rotatedCube.sides[6] = this->turnSide(this->replaceSide(this->sides[0], rot));
    rotatedCube.sides[7] = this->turnSide(this->replaceSide(this->sides[7], rot));
    rotatedCube.sides[8] = this->turnSide(this->replaceSide(this->sides[2], rot));
    rotatedCube.sides[9] = this->turnSide(this->replaceSide(this->sides[9], rot));
    rotatedCube.sides[10] = this->replaceSide(this->sides[1], rot);
    rotatedCube.sides[11] = this->turnSide(this->replaceSide(this->sides[5], rot));
    break;
  case 23:
    //Side 5 forwards rotate right
    rotatedCube.corners[0] = this->turnCornerLeft(this->replaceCorner(this->corners[0], rot));
    rotatedCube.corners[1] = this->turnCornerLeft(this->replaceCorner(this->corners[4], rot));
    rotatedCube.corners[2] = this->replaceCorner(this->corners[5], rot);
    rotatedCube.corners[3] = this->turnCornerRight(this->replaceCorner(this->corners[1], rot));
    rotatedCube.corners[4] = this->replaceCorner(this->corners[3], rot);
    rotatedCube.corners[5] = this->turnCornerLeft(this->replaceCorner(this->corners[7], rot));
    rotatedCube.corners[6] = this->turnCornerRight(this->replaceCorner(this->corners[6], rot));
    rotatedCube.corners[7] = this->turnCornerRight(this->replaceCorner(this->corners[2], rot));
    rotatedCube.sides[0] = this->turnSide(this->replaceSide(this->sides[7], rot));
    rotatedCube.sides[1] = this->replaceSide(this->sides[11], rot);
    rotatedCube.sides[2] = this->turnSide(this->replaceSide(this->sides[9], rot));
    rotatedCube.sides[3] = this->replaceSide(this->sides[5], rot);
    rotatedCube.sides[4] = this->replaceSide(this->sides[0], rot);
    rotatedCube.sides[5] = this->turnSide(this->replaceSide(this->sides[8], rot));
    rotatedCube.sides[6] = this->turnSide(this->replaceSide(this->sides[1], rot));
    rotatedCube.sides[7] = this->turnSide(this->replaceSide(this->sides[4], rot));
    rotatedCube.sides[8] = this->turnSide(this->replaceSide(this->sides[3], rot));
    rotatedCube.sides[9] = this->turnSide(this->replaceSide(this->sides[10], rot));
    rotatedCube.sides[10] = this->replaceSide(this->sides[2], rot);
    rotatedCube.sides[11] = this->turnSide(this->replaceSide(this->sides[6], rot));
    break;
  default:
    break;
  }
  return rotatedCube;
}


__int8 RubixCube20BF::replaceSide(__int8 side, int rot)
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


__int8 RubixCube20BF::replaceCorner(__int8 corner, int rot)
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

__int8 RubixCube20BF::turnSide(__int8 side)
{
  if((side&1) == 1)
    return side-1;
  else
    return side+1;
}

__int8 RubixCube20BF::turnCornerRight(__int8 corner)
{
  if((corner&3) < 2)
    return corner+1;
  else
    return corner-2;
}

__int8 RubixCube20BF::turnCornerLeft(__int8 corner)
{
  if((corner&3) > 0)
    return corner-1;
  else
    return corner+2;
}

RubixCube20BF::~RubixCube20BF()
{
  //dtor
}

