#include <iostream>
#include "RubixCube20B.h"

RubixCube20B::RubixCube20B()
{
  parent = NULL;
  firstChild = NULL;
  sibling = NULL;
  //ctor
}

RubixCube20B& RubixCube20B::operator=(const RubixCube20B& other)
{
  for(int a=0; a<12; a++)
  {
    if(a<8)
      this->corners[a] = other.corners[a];
    this->sides[a] = other.sides[a];
  }
  this->parent = other.parent;
  return *this;
}


bool RubixCube20B::operator==(const RubixCube20B& other)
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

bool RubixCube20B::operator<(const RubixCube20B& other)
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

bool RubixCube20B::operator>(const RubixCube20B& other)
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

void RubixCube20B::print()        //////////////////////TODOTODOTODOTODO
{
/*  std::cout << "       " << (int)(this->colors[4][0]) << " " << (int)(this->colors[4][1]) << " " << (int)(this->colors[4][2]) << std::endl;
  std::cout << "       " << (int)(this->colors[4][3]) << " " <<                             "4 " << (int)(this->colors[4][4]) << std::endl;
  std::cout << "       " << (int)(this->colors[4][5]) << " " << (int)(this->colors[4][6]) << " " << (int)(this->colors[4][7]) << std::endl << std::endl;
  std::cout << (int)(this->colors[0][0]) << " " << (int)(this->colors[0][1]) << " " << (int)(this->colors[0][2]) << "  " << (int)(this->colors[1][0]) << " " << (int)(this->colors[1][1]) << " " << (int)(this->colors[1][2]) << "  " << (int)(this->colors[2][0]) << " " << (int)(this->colors[2][1]) << " " << (int)(this->colors[2][2]) << "  " << (int)(this->colors[3][0]) << " " << (int)(this->colors[3][1]) << " " << (int)(this->colors[3][2])<< std::endl;
  std::cout << (int)(this->colors[0][3]) << " " <<                             "0 " << (int)(this->colors[0][4]) << "  " << (int)(this->colors[1][3]) << " " <<                             "1 " << (int)(this->colors[1][4]) << "  " << (int)(this->colors[2][3]) << " " <<                             "2 " << (int)(this->colors[2][4]) << "  " << (int)(this->colors[3][3]) << " " <<                             "3 " << (int)(this->colors[3][4])<< std::endl;
  std::cout << (int)(this->colors[0][5]) << " " << (int)(this->colors[0][6]) << " " << (int)(this->colors[0][7]) << "  " << (int)(this->colors[1][5]) << " " << (int)(this->colors[1][6]) << " " << (int)(this->colors[1][7]) << "  " << (int)(this->colors[2][5]) << " " << (int)(this->colors[2][6]) << " " << (int)(this->colors[2][7]) << "  " << (int)(this->colors[3][5]) << " " << (int)(this->colors[3][6]) << " " << (int)(this->colors[3][7])<< std::endl << std::endl;
  std::cout << "       " << (int)(this->colors[5][0]) << " " << (int)(this->colors[5][1]) << " " << (int)(this->colors[5][2]) << std::endl;
  std::cout << "       " << (int)(this->colors[5][3]) << " " <<                             "5 " << (int)(this->colors[5][4]) << std::endl;
  std::cout << "       " << (int)(this->colors[5][5]) << " " << (int)(this->colors[5][6]) << " " << (int)(this->colors[5][7]) << std::endl;
*/
}


RubixCube20B RubixCube20B::returnChild(int move)
{
  RubixCube20B child = *this;
  child.parent = this;
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
    child.corners[7] = this->turnCornerRight(this->corners[6]);
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


RubixCube20B RubixCube20B::returnRot(int rot)
{
  RubixCube20B rotatedCube;
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


__int8 RubixCube20B::replaceSide(__int8 side, int rot)
{
  return 0;
}


__int8 RubixCube20B::replaceCorner(__int8 corner, int rot)
{
    return 0;
}


__int8 RubixCube20B::turnSide(__int8 side)
{
  if((side&1) == 1)
    return side-1;
  else
    return side+1;
}

__int8 RubixCube20B::turnCornerRight(__int8 corner)
{
  if((corner&3) < 2)
    return corner+1;
  else
    return corner-2;
}

__int8 RubixCube20B::turnCornerLeft(__int8 corner)
{
  if((corner&3) > 0)
    return corner-1;
  else
    return corner+2;
}

RubixCube20B::~RubixCube20B()
{
  //dtor
}


CubeContainer20B::CubeContainer20B()
{
  cube = NULL;
}


CubeContainer20B& CubeContainer20B::operator=(const RubixCube20B& other)
{
  if(cube)
    delete cube;
  cube = new RubixCube20B;
  *cube = other;
  return *this;
}


CubeContainer20B& CubeContainer20B::operator=(const CubeContainer20B& other)
{
  //Not deleting cube since im not sure how SET uses operator=
  cube = other.cube;
  return *this;
}


bool CubeContainer20B::operator==(const CubeContainer20B& other)
{
  return *(this->cube) == *(other.cube);
}


bool CubeContainer20B::operator<(const CubeContainer20B& other) const
{
  return *(this->cube) < *(other.cube);
}


bool CubeContainer20B::operator>(const CubeContainer20B& other) const
{
  return *(this->cube) > *(other.cube);
}


CubeContainer20B::~CubeContainer20B()
{

}
