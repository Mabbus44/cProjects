#include <iostream>
#include "RubixCube.h"

RubixCube::RubixCube()
{
  parent = NULL;
  firstChild = NULL;
  sibling = NULL;
  //ctor
}

RubixCube& RubixCube::operator=(const RubixCube& other)
{
  for(int a=0; a<6; a++)
    for(int b=0; b<8; b++)
      this->colors[a][b] = other.colors[a][b];
  this->parent = other.parent;
  return *this;
}


bool RubixCube::operator==(const RubixCube& other)
{
  for(int s=0; s<6; s++)
    for(int b=0; b<8; b++)
      if(this->colors[s][b] != other.colors[s][b])
        return false;
  return true;
}

bool RubixCube::operator<(const RubixCube& other)
{
  for(int s=0; s<6; s++)
  {
    for(int b=0; b<8; b++)
    {
      if(this->colors[s][b] > other.colors[s][b])
        return false;
      if(this->colors[s][b] < other.colors[s][b])
        return true;
    }
  }
  return false;
}

bool RubixCube::operator>(const RubixCube& other)
{
  for(int s=0; s<6; s++)
  {
    for(int b=0; b<8; b++)
    {
      if(this->colors[s][b] < other.colors[s][b])
        return false;
      if(this->colors[s][b] > other.colors[s][b])
        return true;
    }
  }
  return false;
}

void RubixCube::print()
{
  std::cout << "       " << (int)(this->colors[4][0]) << " " << (int)(this->colors[4][1]) << " " << (int)(this->colors[4][2]) << std::endl;
  std::cout << "       " << (int)(this->colors[4][3]) << " " <<                             "4 " << (int)(this->colors[4][4]) << std::endl;
  std::cout << "       " << (int)(this->colors[4][5]) << " " << (int)(this->colors[4][6]) << " " << (int)(this->colors[4][7]) << std::endl << std::endl;
  std::cout << (int)(this->colors[0][0]) << " " << (int)(this->colors[0][1]) << " " << (int)(this->colors[0][2]) << "  " << (int)(this->colors[1][0]) << " " << (int)(this->colors[1][1]) << " " << (int)(this->colors[1][2]) << "  " << (int)(this->colors[2][0]) << " " << (int)(this->colors[2][1]) << " " << (int)(this->colors[2][2]) << "  " << (int)(this->colors[3][0]) << " " << (int)(this->colors[3][1]) << " " << (int)(this->colors[3][2])<< std::endl;
  std::cout << (int)(this->colors[0][3]) << " " <<                             "0 " << (int)(this->colors[0][4]) << "  " << (int)(this->colors[1][3]) << " " <<                             "1 " << (int)(this->colors[1][4]) << "  " << (int)(this->colors[2][3]) << " " <<                             "2 " << (int)(this->colors[2][4]) << "  " << (int)(this->colors[3][3]) << " " <<                             "3 " << (int)(this->colors[3][4])<< std::endl;
  std::cout << (int)(this->colors[0][5]) << " " << (int)(this->colors[0][6]) << " " << (int)(this->colors[0][7]) << "  " << (int)(this->colors[1][5]) << " " << (int)(this->colors[1][6]) << " " << (int)(this->colors[1][7]) << "  " << (int)(this->colors[2][5]) << " " << (int)(this->colors[2][6]) << " " << (int)(this->colors[2][7]) << "  " << (int)(this->colors[3][5]) << " " << (int)(this->colors[3][6]) << " " << (int)(this->colors[3][7])<< std::endl << std::endl;
  std::cout << "       " << (int)(this->colors[5][0]) << " " << (int)(this->colors[5][1]) << " " << (int)(this->colors[5][2]) << std::endl;
  std::cout << "       " << (int)(this->colors[5][3]) << " " <<                             "5 " << (int)(this->colors[5][4]) << std::endl;
  std::cout << "       " << (int)(this->colors[5][5]) << " " << (int)(this->colors[5][6]) << " " << (int)(this->colors[5][7]) << std::endl;
}


RubixCube RubixCube::returnChild(int move)
{
  RubixCube child = *this;
  child.parent = this;
  switch(move)
  {
  case 0:
    //Turn side 0 clockwise
    child.colors[0][0] = this->colors[0][5];
    child.colors[0][1] = this->colors[0][3];
    child.colors[0][2] = this->colors[0][0];
    child.colors[0][3] = this->colors[0][6];
    child.colors[0][4] = this->colors[0][1];
    child.colors[0][5] = this->colors[0][7];
    child.colors[0][6] = this->colors[0][4];
    child.colors[0][7] = this->colors[0][2];
    child.colors[5][0] = this->colors[1][0];
    child.colors[5][3] = this->colors[1][3];
    child.colors[5][5] = this->colors[1][5];
    child.colors[3][7] = this->colors[5][0];
    child.colors[3][4] = this->colors[5][3];
    child.colors[3][2] = this->colors[5][5];
    child.colors[4][0] = this->colors[3][7];
    child.colors[4][3] = this->colors[3][4];
    child.colors[4][5] = this->colors[3][2];
    child.colors[1][0] = this->colors[4][0];
    child.colors[1][3] = this->colors[4][3];
    child.colors[1][5] = this->colors[4][5];
    break;
  case 1:
    //Turn side 1 clockwise
    child.colors[1][0] = this->colors[1][5];
    child.colors[1][1] = this->colors[1][3];
    child.colors[1][2] = this->colors[1][0];
    child.colors[1][3] = this->colors[1][6];
    child.colors[1][4] = this->colors[1][1];
    child.colors[1][5] = this->colors[1][7];
    child.colors[1][6] = this->colors[1][4];
    child.colors[1][7] = this->colors[1][2];
    child.colors[4][5] = this->colors[0][7];
    child.colors[4][6] = this->colors[0][4];
    child.colors[4][7] = this->colors[0][2];
    child.colors[2][0] = this->colors[4][5];
    child.colors[2][3] = this->colors[4][6];
    child.colors[2][5] = this->colors[4][7];
    child.colors[5][2] = this->colors[2][0];
    child.colors[5][1] = this->colors[2][3];
    child.colors[5][0] = this->colors[2][5];
    child.colors[0][7] = this->colors[5][2];
    child.colors[0][4] = this->colors[5][1];
    child.colors[0][2] = this->colors[5][0];
    break;
  case 2:
    //Turn side 2 clockwise
    child.colors[2][0] = this->colors[2][5];
    child.colors[2][1] = this->colors[2][3];
    child.colors[2][2] = this->colors[2][0];
    child.colors[2][3] = this->colors[2][6];
    child.colors[2][4] = this->colors[2][1];
    child.colors[2][5] = this->colors[2][7];
    child.colors[2][6] = this->colors[2][4];
    child.colors[2][7] = this->colors[2][2];
    child.colors[4][7] = this->colors[1][7];
    child.colors[4][4] = this->colors[1][4];
    child.colors[4][2] = this->colors[1][2];
    child.colors[3][0] = this->colors[4][7];
    child.colors[3][3] = this->colors[4][4];
    child.colors[3][5] = this->colors[4][2];
    child.colors[5][7] = this->colors[3][0];
    child.colors[5][4] = this->colors[3][3];
    child.colors[5][2] = this->colors[3][5];
    child.colors[1][7] = this->colors[5][7];
    child.colors[1][4] = this->colors[5][4];
    child.colors[1][2] = this->colors[5][2];
    break;
  case 3:
    //Turn side 3 clockwise
    child.colors[3][0] = this->colors[3][5];
    child.colors[3][1] = this->colors[3][3];
    child.colors[3][2] = this->colors[3][0];
    child.colors[3][3] = this->colors[3][6];
    child.colors[3][4] = this->colors[3][1];
    child.colors[3][5] = this->colors[3][7];
    child.colors[3][6] = this->colors[3][4];
    child.colors[3][7] = this->colors[3][2];
    child.colors[4][2] = this->colors[2][7];
    child.colors[4][1] = this->colors[2][4];
    child.colors[4][0] = this->colors[2][2];
    child.colors[0][0] = this->colors[4][2];
    child.colors[0][3] = this->colors[4][1];
    child.colors[0][5] = this->colors[4][0];
    child.colors[5][5] = this->colors[0][0];
    child.colors[5][6] = this->colors[0][3];
    child.colors[5][7] = this->colors[0][5];
    child.colors[2][7] = this->colors[5][5];
    child.colors[2][4] = this->colors[5][6];
    child.colors[2][2] = this->colors[5][7];
    break;
  case 4:
    //Turn side 4 clockwise
    child.colors[4][0] = this->colors[4][5];
    child.colors[4][1] = this->colors[4][3];
    child.colors[4][2] = this->colors[4][0];
    child.colors[4][3] = this->colors[4][6];
    child.colors[4][4] = this->colors[4][1];
    child.colors[4][5] = this->colors[4][7];
    child.colors[4][6] = this->colors[4][4];
    child.colors[4][7] = this->colors[4][2];
    child.colors[3][2] = this->colors[0][2];
    child.colors[3][1] = this->colors[0][1];
    child.colors[3][0] = this->colors[0][0];
    child.colors[2][2] = this->colors[3][2];
    child.colors[2][1] = this->colors[3][1];
    child.colors[2][0] = this->colors[3][0];
    child.colors[1][2] = this->colors[2][2];
    child.colors[1][1] = this->colors[2][1];
    child.colors[1][0] = this->colors[2][0];
    child.colors[0][2] = this->colors[1][2];
    child.colors[0][1] = this->colors[1][1];
    child.colors[0][0] = this->colors[1][0];
    break;
  case 5:
    //Turn side 5 clockwise
    child.colors[5][0] = this->colors[5][5];
    child.colors[5][1] = this->colors[5][3];
    child.colors[5][2] = this->colors[5][0];
    child.colors[5][3] = this->colors[5][6];
    child.colors[5][4] = this->colors[5][1];
    child.colors[5][5] = this->colors[5][7];
    child.colors[5][6] = this->colors[5][4];
    child.colors[5][7] = this->colors[5][2];
    child.colors[1][5] = this->colors[0][5];
    child.colors[1][6] = this->colors[0][6];
    child.colors[1][7] = this->colors[0][7];
    child.colors[2][5] = this->colors[1][5];
    child.colors[2][6] = this->colors[1][6];
    child.colors[2][7] = this->colors[1][7];
    child.colors[3][5] = this->colors[2][5];
    child.colors[3][6] = this->colors[2][6];
    child.colors[3][7] = this->colors[2][7];
    child.colors[0][5] = this->colors[3][5];
    child.colors[0][6] = this->colors[3][6];
    child.colors[0][7] = this->colors[3][7];
    break;
  case 6:
    //Turn side 0 counter clockwise
    child.colors[0][5] = this->colors[0][0];
    child.colors[0][3] = this->colors[0][1];
    child.colors[0][0] = this->colors[0][2];
    child.colors[0][6] = this->colors[0][3];
    child.colors[0][1] = this->colors[0][4];
    child.colors[0][7] = this->colors[0][5];
    child.colors[0][4] = this->colors[0][6];
    child.colors[0][2] = this->colors[0][7];
    child.colors[1][0] = this->colors[5][0];
    child.colors[1][3] = this->colors[5][3];
    child.colors[1][5] = this->colors[5][5];
    child.colors[5][0] = this->colors[3][7];
    child.colors[5][3] = this->colors[3][4];
    child.colors[5][5] = this->colors[3][2];
    child.colors[3][7] = this->colors[4][0];
    child.colors[3][4] = this->colors[4][3];
    child.colors[3][2] = this->colors[4][5];
    child.colors[4][0] = this->colors[1][0];
    child.colors[4][3] = this->colors[1][3];
    child.colors[4][5] = this->colors[1][5];
    break;
  case 7:
    //Turn side 1 counter clockwise
    child.colors[1][5] = this->colors[1][0];
    child.colors[1][3] = this->colors[1][1];
    child.colors[1][0] = this->colors[1][2];
    child.colors[1][6] = this->colors[1][3];
    child.colors[1][1] = this->colors[1][4];
    child.colors[1][7] = this->colors[1][5];
    child.colors[1][4] = this->colors[1][6];
    child.colors[1][2] = this->colors[1][7];
    child.colors[0][7] = this->colors[4][5];
    child.colors[0][4] = this->colors[4][6];
    child.colors[0][2] = this->colors[4][7];
    child.colors[4][5] = this->colors[2][0];
    child.colors[4][6] = this->colors[2][3];
    child.colors[4][7] = this->colors[2][5];
    child.colors[2][0] = this->colors[5][2];
    child.colors[2][3] = this->colors[5][1];
    child.colors[2][5] = this->colors[5][0];
    child.colors[5][2] = this->colors[0][7];
    child.colors[5][1] = this->colors[0][4];
    child.colors[5][0] = this->colors[0][2];
    break;
  case 8:
    //Turn side 2 counter clockwise
    child.colors[2][5] = this->colors[2][0];
    child.colors[2][3] = this->colors[2][1];
    child.colors[2][0] = this->colors[2][2];
    child.colors[2][6] = this->colors[2][3];
    child.colors[2][1] = this->colors[2][4];
    child.colors[2][7] = this->colors[2][5];
    child.colors[2][4] = this->colors[2][6];
    child.colors[2][2] = this->colors[2][7];
    child.colors[1][7] = this->colors[4][7];
    child.colors[1][4] = this->colors[4][4];
    child.colors[1][2] = this->colors[4][2];
    child.colors[4][7] = this->colors[3][0];
    child.colors[4][4] = this->colors[3][3];
    child.colors[4][2] = this->colors[3][5];
    child.colors[3][0] = this->colors[5][7];
    child.colors[3][3] = this->colors[5][4];
    child.colors[3][5] = this->colors[5][2];
    child.colors[5][7] = this->colors[1][7];
    child.colors[5][4] = this->colors[1][4];
    child.colors[5][2] = this->colors[1][2];
    break;
  case 9:
    //Turn side 3 counter clockwise
    child.colors[3][5] = this->colors[3][0];
    child.colors[3][3] = this->colors[3][1];
    child.colors[3][0] = this->colors[3][2];
    child.colors[3][6] = this->colors[3][3];
    child.colors[3][1] = this->colors[3][4];
    child.colors[3][7] = this->colors[3][5];
    child.colors[3][4] = this->colors[3][6];
    child.colors[3][2] = this->colors[3][7];
    child.colors[2][7] = this->colors[4][2];
    child.colors[2][4] = this->colors[4][1];
    child.colors[2][2] = this->colors[4][0];
    child.colors[4][2] = this->colors[0][0];
    child.colors[4][1] = this->colors[0][3];
    child.colors[4][0] = this->colors[0][5];
    child.colors[0][0] = this->colors[5][5];
    child.colors[0][3] = this->colors[5][6];
    child.colors[0][5] = this->colors[5][7];
    child.colors[5][5] = this->colors[2][7];
    child.colors[5][6] = this->colors[2][4];
    child.colors[5][7] = this->colors[2][2];
    break;
  case 10:
    //Turn side 4 counter clockwise
    child.colors[4][5] = this->colors[4][0];
    child.colors[4][3] = this->colors[4][1];
    child.colors[4][0] = this->colors[4][2];
    child.colors[4][6] = this->colors[4][3];
    child.colors[4][1] = this->colors[4][4];
    child.colors[4][7] = this->colors[4][5];
    child.colors[4][4] = this->colors[4][6];
    child.colors[4][2] = this->colors[4][7];
    child.colors[0][2] = this->colors[3][2];
    child.colors[0][1] = this->colors[3][1];
    child.colors[0][0] = this->colors[3][0];
    child.colors[3][2] = this->colors[2][2];
    child.colors[3][1] = this->colors[2][1];
    child.colors[3][0] = this->colors[2][0];
    child.colors[2][2] = this->colors[1][2];
    child.colors[2][1] = this->colors[1][1];
    child.colors[2][0] = this->colors[1][0];
    child.colors[1][2] = this->colors[0][2];
    child.colors[1][1] = this->colors[0][1];
    child.colors[1][0] = this->colors[0][0];
    break;
  case 11:
    //Turn side 5 counter clockwise
    child.colors[5][5] = this->colors[5][0];
    child.colors[5][3] = this->colors[5][1];
    child.colors[5][0] = this->colors[5][2];
    child.colors[5][6] = this->colors[5][3];
    child.colors[5][1] = this->colors[5][4];
    child.colors[5][7] = this->colors[5][5];
    child.colors[5][4] = this->colors[5][6];
    child.colors[5][2] = this->colors[5][7];
    child.colors[0][5] = this->colors[1][5];
    child.colors[0][6] = this->colors[1][6];
    child.colors[0][7] = this->colors[1][7];
    child.colors[1][5] = this->colors[2][5];
    child.colors[1][6] = this->colors[2][6];
    child.colors[1][7] = this->colors[2][7];
    child.colors[2][5] = this->colors[3][5];
    child.colors[2][6] = this->colors[3][6];
    child.colors[2][7] = this->colors[3][7];
    child.colors[3][5] = this->colors[0][5];
    child.colors[3][6] = this->colors[0][6];
    child.colors[3][7] = this->colors[0][7];
    break;
  default:
    break;
  }
  return child;
}


RubixCube RubixCube::returnRot(int rot)
{
  RubixCube rotatedCube;
  rotatedCube.parent = this;
  switch(rot)
  {
  case 0:
    //Side 0 forwards
    rotatedCube.setSide(0, this, 3);
    rotatedCube.setSide(1, this, 0);
    rotatedCube.setSide(2, this, 1);
    rotatedCube.setSide(3, this, 2);
    rotatedCube.setSideRotLeft(4, this, 4);
    rotatedCube.setSideRotRight(5, this, 5);
    rotatedCube.swapNumber(0,1,2,3);
    break;
  case 1:
    //Side 0 forwards rotate left
    rotatedCube.setSideRotX(0, this, 4);
    rotatedCube.setSideRotLeft(4, this, 1);
    rotatedCube.setSideRotLeft(1, this, 0);
    rotatedCube.setSide(2, this, 5);
    rotatedCube.setSideRotLeft(5, this, 3);
    rotatedCube.setSideRotRight(3, this, 2);
    rotatedCube.swapNumber(0,1,4);
    rotatedCube.swapNumber(2,3,5);
    break;
  case 2:
    //Side 0 forwards rotate 2x
    rotatedCube.setSideRotX(1, this, 0);
    rotatedCube.setSideRotX(0, this, 1);
    rotatedCube.setSideRotX(3, this, 2);
    rotatedCube.setSideRotX(2, this, 3);
    rotatedCube.setSideRotRight(5, this, 4);
    rotatedCube.setSideRotLeft(4, this, 5);
    rotatedCube.swapNumber(0,1);
    rotatedCube.swapNumber(2,3);
    rotatedCube.swapNumber(4,5);
    break;
  case 3:
    //Side 0 forwards rotate right
    rotatedCube.setSideRotRight(5, this, 1);
    rotatedCube.setSideRotRight(1, this, 0);
    rotatedCube.setSideRotX(0, this, 5);
    rotatedCube.setSideRotRight(4, this, 3);
    rotatedCube.setSideRotLeft(3, this, 2);
    rotatedCube.setSide(2, this, 4);
    rotatedCube.swapNumber(0,1,5);
    rotatedCube.swapNumber(2,3,4);
    break;
  case 4:
    //Side 1 forwards
    rotatedCube.setSide(0, this, 0);
    rotatedCube.setSide(1, this, 1);
    rotatedCube.setSide(2, this, 2);
    rotatedCube.setSide(3, this, 3);
    rotatedCube.setSide(4, this, 4);
    rotatedCube.setSide(5, this, 5);
    break;
  case 5:
    //Side 1 forwards rotate left
    rotatedCube.setSideRotLeft(1, this, 1);
    rotatedCube.setSideRotLeft(2, this, 5);
    rotatedCube.setSideRotLeft(5, this, 0);
    rotatedCube.setSideRotLeft(0, this, 4);
    rotatedCube.setSideRotLeft(4, this, 2);
    rotatedCube.setSideRotRight(3, this, 3);
    rotatedCube.swapNumber(4,0,5,2);
    break;
  case 6:
    //Side 1 forwards rotate 2x
    rotatedCube.setSideRotX(1, this, 1);
    rotatedCube.setSideRotX(5, this, 4);
    rotatedCube.setSideRotX(4, this, 5);
    rotatedCube.setSideRotX(2, this, 0);
    rotatedCube.setSideRotX(0, this, 2);
    rotatedCube.setSideRotX(3, this, 3);
    rotatedCube.swapNumber(4,5);
    rotatedCube.swapNumber(0,2);
    break;
  case 7:
    //Side 1 forwards rotate right
    rotatedCube.setSideRotRight(1, this, 1);
    rotatedCube.setSideRotRight(0, this, 5);
    rotatedCube.setSideRotRight(5, this, 2);
    rotatedCube.setSideRotRight(2, this, 4);
    rotatedCube.setSideRotRight(4, this, 0);
    rotatedCube.setSideRotLeft(3, this, 3);
    rotatedCube.swapNumber(4,2,5,0);
    break;
  case 8:
    //Side 2 forwards
    rotatedCube.setSideRotRight(4, this, 4);
    rotatedCube.setSide(3, this, 0);
    rotatedCube.setSide(0, this, 1);
    rotatedCube.setSide(1, this, 2);
    rotatedCube.setSide(2, this, 3);
    rotatedCube.setSideRotLeft(5, this, 5);
    rotatedCube.swapNumber(2,1,0,3);
    break;
  case 9:
    //Side 2 forwards rotate left
    rotatedCube.setSideRotLeft(5, this, 1);
    rotatedCube.setSideRotLeft(1, this, 2);
    rotatedCube.setSideRotX(2, this, 5);
    rotatedCube.setSideRotLeft(4, this, 3);
    rotatedCube.setSideRotRight(3, this, 0);
    rotatedCube.setSide(0, this, 4);
    rotatedCube.swapNumber(2,1,5);
    rotatedCube.swapNumber(0,3,4);
    break;
  case 10:
    //Side 2 forwards rotate 2x
    rotatedCube.setSideRotX(2, this, 1);
    rotatedCube.setSideRotX(1, this, 2);
    rotatedCube.setSideRotX(0, this, 3);
    rotatedCube.setSideRotX(3, this, 0);
    rotatedCube.setSideRotRight(4, this, 5);
    rotatedCube.setSideRotLeft(5, this, 4);
    rotatedCube.swapNumber(2,1);
    rotatedCube.swapNumber(0,3);
    rotatedCube.swapNumber(4,5);
    break;
  case 11:
    //Side 2 forwards rotate right
    rotatedCube.setSideRotRight(4, this, 1);
    rotatedCube.setSideRotRight(1, this, 2);
    rotatedCube.setSideRotX(2, this, 4);
    rotatedCube.setSideRotRight(5, this, 3);
    rotatedCube.setSideRotLeft(3, this, 0);
    rotatedCube.setSide(0, this, 5);
    rotatedCube.swapNumber(2,1,4);
    rotatedCube.swapNumber(0,3,5);
    break;
  case 12:
    //Side 3 forwards
    rotatedCube.setSide(1, this, 3);
    rotatedCube.setSide(3, this, 1);
    rotatedCube.setSide(0, this, 2);
    rotatedCube.setSide(2, this, 0);
    rotatedCube.setSideRotX(4, this, 4);
    rotatedCube.setSideRotX(5, this, 5);
    rotatedCube.swapNumber(1,3);
    rotatedCube.swapNumber(0,2);
    break;
  case 13:
    //Side 3 forwards rotate left
    rotatedCube.setSideRotRight(0, this, 4);
    rotatedCube.setSideRotLeft(4, this, 0);
    rotatedCube.setSideRotLeft(1, this, 3);
    rotatedCube.setSideRotRight(3, this, 1);
    rotatedCube.setSideRotRight(2, this, 5);
    rotatedCube.setSideRotLeft(5, this, 2);
    rotatedCube.swapNumber(0,4);
    rotatedCube.swapNumber(1,3);
    rotatedCube.swapNumber(2,5);
    break;
  case 14:
    //Side 3 forwards rotate 2x
    rotatedCube.setSideRotX(0, this, 0);
    rotatedCube.setSideRotX(2, this, 2);
    rotatedCube.setSideRotX(1, this, 3);
    rotatedCube.setSideRotX(3, this, 1);
    rotatedCube.setSide(4, this, 5);
    rotatedCube.setSide(5, this, 4);
    rotatedCube.swapNumber(1,3);
    rotatedCube.swapNumber(4,5);
    break;
  case 15:
    //Side 3 forwards rotate right
    rotatedCube.setSideRotLeft(0, this, 5);
    rotatedCube.setSideRotRight(5, this, 0);
    rotatedCube.setSideRotRight(1, this, 3);
    rotatedCube.setSideRotLeft(3, this, 1);
    rotatedCube.setSideRotLeft(2, this, 4);
    rotatedCube.setSideRotRight(4, this, 2);
    rotatedCube.swapNumber(0,5);
    rotatedCube.swapNumber(1,3);
    rotatedCube.swapNumber(2,4);
    break;
  case 16:
    //Side 4 forwards
    rotatedCube.setSideRotRight(0, this, 0);
    rotatedCube.setSideRotX(4, this, 3);
    rotatedCube.setSideRotX(3, this, 5);
    rotatedCube.setSide(5, this, 1);
    rotatedCube.setSide(1, this, 4);
    rotatedCube.setSideRotLeft(2, this, 2);
    rotatedCube.swapNumber(1,5,3,4);
    break;
  case 17:
    //Side 4 forwards rotate left
    rotatedCube.setSideRotLeft(3, this, 5);
    rotatedCube.setSide(5, this, 0);
    rotatedCube.setSideRotRight(0, this, 3);
    rotatedCube.setSideRotX(4, this, 2);
    rotatedCube.setSideRotLeft(2, this, 1);
    rotatedCube.setSideRotLeft(1, this, 4);
    rotatedCube.swapNumber(0,5,3);
    rotatedCube.swapNumber(1,2,4);
    break;
  case 18:
    //Side 4 forwards rotate 2x
    rotatedCube.setSideRotRight(0, this, 2);
    rotatedCube.setSideRotLeft(2, this, 0);
    rotatedCube.setSideRotX(1, this, 4);
    rotatedCube.setSideRotX(4, this, 1);
    rotatedCube.setSide(3, this, 5);
    rotatedCube.setSide(5, this, 3);
    rotatedCube.swapNumber(0,2);
    rotatedCube.swapNumber(1,4);
    rotatedCube.swapNumber(3,5);
    break;
  case 19:
    //Side 4 forwards rotate right
    rotatedCube.setSideRotRight(1, this, 4);
    rotatedCube.setSideRotX(4, this, 0);
    rotatedCube.setSideRotRight(0, this, 1);
    rotatedCube.setSideRotRight(3, this, 5);
    rotatedCube.setSide(5, this, 2);
    rotatedCube.setSideRotLeft(2, this, 3);
    rotatedCube.swapNumber(0,4,1);
    rotatedCube.swapNumber(2,5,3);
    break;
  case 20:
    //Side 5 forwards
    rotatedCube.setSideRotX(3, this, 4);
    rotatedCube.setSide(4, this, 1);
    rotatedCube.setSide(1, this, 5);
    rotatedCube.setSide(5, this, 3);
    rotatedCube.setSideRotLeft(0, this, 0);
    rotatedCube.setSideRotRight(2, this, 2);
    rotatedCube.swapNumber(5,1,4,3);
    break;
  case 21:
    //Side 5 forwards rotate left
    rotatedCube.setSideRotLeft(0, this, 1);
    rotatedCube.setSideRotLeft(1, this, 5);
    rotatedCube.setSideRotX(5, this, 0);
    rotatedCube.setSideRotLeft(3, this, 4);
    rotatedCube.setSide(4, this, 2);
    rotatedCube.setSideRotRight(2, this, 3);
    rotatedCube.swapNumber(5,1,0);
    rotatedCube.swapNumber(2,4,3);
    break;
  case 22:
    //Side 5 forwards rotate 2x
    rotatedCube.setSideRotX(5, this, 1);
    rotatedCube.setSideRotX(1, this, 5);
    rotatedCube.setSideRotLeft(0, this, 2);
    rotatedCube.setSideRotRight(2, this, 0);
    rotatedCube.setSide(3, this, 4);
    rotatedCube.setSide(4, this, 3);
    rotatedCube.swapNumber(5,1);
    rotatedCube.swapNumber(2,0);
    rotatedCube.swapNumber(3,4);
    break;
  case 23:
    //Side 5 forwards rotate right
    rotatedCube.setSideRotRight(2, this, 1);
    rotatedCube.setSideRotRight(1, this, 5);
    rotatedCube.setSideRotX(5, this, 2);
    rotatedCube.setSide(4, this, 0);
    rotatedCube.setSideRotLeft(0, this, 3);
    rotatedCube.setSideRotRight(3, this, 4);
    rotatedCube.swapNumber(5,1,2);
    rotatedCube.swapNumber(3,0,4);
    break;
  default:
    break;
  }
  return rotatedCube;
}


void RubixCube::setSide(int side, RubixCube* other, int otherSide)
{
  this->colors[side][0] = other->colors[otherSide][0];
  this->colors[side][1] = other->colors[otherSide][1];
  this->colors[side][2] = other->colors[otherSide][2];
  this->colors[side][3] = other->colors[otherSide][3];
  this->colors[side][4] = other->colors[otherSide][4];
  this->colors[side][5] = other->colors[otherSide][5];
  this->colors[side][6] = other->colors[otherSide][6];
  this->colors[side][7] = other->colors[otherSide][7];
}


void RubixCube::setSideRotLeft(int side, RubixCube* other, int otherSide)
{
  this->colors[side][0] = other->colors[otherSide][2];
  this->colors[side][1] = other->colors[otherSide][4];
  this->colors[side][2] = other->colors[otherSide][7];
  this->colors[side][3] = other->colors[otherSide][1];
  this->colors[side][4] = other->colors[otherSide][6];
  this->colors[side][5] = other->colors[otherSide][0];
  this->colors[side][6] = other->colors[otherSide][3];
  this->colors[side][7] = other->colors[otherSide][5];
}


void RubixCube::setSideRotRight(int side, RubixCube* other, int otherSide)
{
  this->colors[side][0] = other->colors[otherSide][5];
  this->colors[side][1] = other->colors[otherSide][3];
  this->colors[side][2] = other->colors[otherSide][0];
  this->colors[side][3] = other->colors[otherSide][6];
  this->colors[side][4] = other->colors[otherSide][1];
  this->colors[side][5] = other->colors[otherSide][7];
  this->colors[side][6] = other->colors[otherSide][4];
  this->colors[side][7] = other->colors[otherSide][2];
}


void RubixCube::setSideRotX(int side, RubixCube* other, int otherSide)
{
  this->colors[side][0] = other->colors[otherSide][7];
  this->colors[side][1] = other->colors[otherSide][6];
  this->colors[side][2] = other->colors[otherSide][5];
  this->colors[side][3] = other->colors[otherSide][4];
  this->colors[side][4] = other->colors[otherSide][3];
  this->colors[side][5] = other->colors[otherSide][2];
  this->colors[side][6] = other->colors[otherSide][1];
  this->colors[side][7] = other->colors[otherSide][0];
}


void RubixCube::swapNumber(int a, int b)
{
  for(int side=0; side<6; side++)
  {
    for(int square=0; square<8; square++)
    {
      if(this->colors[side][square] == a)
        this->colors[side][square] = b;
      else if(this->colors[side][square] == b)
        this->colors[side][square] = a;
    }
  }
}


void RubixCube::swapNumber(int a, int b, int c)
{
  for(int side=0; side<6; side++)
  {
    for(int square=0; square<8; square++)
    {
      if(this->colors[side][square] == a)
        this->colors[side][square] = b;
      else if(this->colors[side][square] == b)
        this->colors[side][square] = c;
      else if(this->colors[side][square] == c)
        this->colors[side][square] = a;
    }
  }
}


void RubixCube::swapNumber(int a, int b, int c, int d)
{
  for(int side=0; side<6; side++)
  {
    for(int square=0; square<8; square++)
    {
      if(this->colors[side][square] == a)
        this->colors[side][square] = b;
      else if(this->colors[side][square] == b)
        this->colors[side][square] = c;
      else if(this->colors[side][square] == c)
        this->colors[side][square] = d;
      else if(this->colors[side][square] == d)
        this->colors[side][square] = a;
    }
  }
}

RubixCube::~RubixCube()
{
  //dtor
}


CubeContainer::CubeContainer()
{
  cube = NULL;
}


CubeContainer& CubeContainer::operator=(const RubixCube& other)
{
  if(cube)
    delete cube;
  cube = new RubixCube;
  *cube = other;
  return *this;
}


CubeContainer& CubeContainer::operator=(const CubeContainer& other)
{
  //Not deleting cube since im not sure how SET uses operator=
  cube = other.cube;
  return *this;
}


bool CubeContainer::operator==(const CubeContainer& other)
{
  return *(this->cube) == *(other.cube);
}


bool CubeContainer::operator<(const CubeContainer& other)
{
  return *(this->cube) < *(other.cube);
}


bool CubeContainer::operator>(const CubeContainer& other)
{
  return *(this->cube) > *(other.cube);
}


CubeContainer::~CubeContainer()
{

}
