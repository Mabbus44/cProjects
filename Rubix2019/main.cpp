#include <iostream>
#include <vector>
#include "RubixCube.h"

int main()
{
  RubixCube child, rotChild;
  RubixCube r;
  std::vector<RubixCube> rVector;
  std::vector<int> gVector;
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
  parentIndex = 0;
  generation = 1;
  generationEnd = 0;
  while(generation < 7)
  {
    //std::cout << "Parent: " << parentIndex << std::endl;
    //rVector[parentIndex].print();
    for(int move=0; move<12; move++)
    {
      child = rVector[parentIndex].returnChild(move);
      //std::cout << "  Child: " << move;
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
/*      if(unique)
        std::cout << "  unique" << std::endl;
      else
        std::cout << "  not unique" << std::endl;*/
      //child.print();
    }
    parentIndex++;
    if(parentIndex>showNext)
    {
      std::cout << generation << ":" << parentIndex << "/" << generationEnd << std::endl;
      showNext += (gVector[generation-1]/100+1);
    }
    if(parentIndex > generationEnd)
    {
      int genPop = gVector[generation-1];
      int newChildren = rVector.size() - generationEnd-1;
      double fertility = (newChildren) / ((double)genPop*12.0)*100.0;
      int notUsed;
      std::cout << std::endl << "Generation " << generation << std::endl;
      std::cout << "Total population " << generationEnd+1 << std::endl;
      std::cout << "Generation population " << genPop << std::endl;
      std::cout << "New children " << newChildren << " (" << fertility << "%)" << std::endl;
      generation++;
      gVector.push_back(rVector.size() - generationEnd-1);
      generationEnd = rVector.size()-1;
      std::cin >> notUsed;
    }
  }
  for(int i=0; i<gVector.size(); i++)
  {
    std::cout << "Generation " << i+1 << ": " << gVector[i] << std::endl;
  }
}
