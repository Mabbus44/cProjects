#include "Day09.h"

Day09::Day09()
{
  //ctor
}

Day09::~Day09()
{
  //dtor
}

void Day09::part1(std::string filename){
  InputLoader loader(filename);
  std::vector<char> input = loader.toVectorChar();
  std::vector<int> blocks;
  int id=0;
  bool isFile = true;
  for(char c: input){
    int digit = (int)c - 48;
    if(isFile){
      for(int i=0; i<digit; i++)
        blocks.push_back(id);
      id++;
    }else{
      for(int i=0; i<digit; i++){
        blocks.push_back(-1);
      }
    }
    isFile = !isFile;
  }
  int firstEmptyId = 0;
  for(int i=(int)blocks.size()-1; i>=0 && firstEmptyId < i; i--){
    firstEmptyId = firstEmpyBlock(blocks, firstEmptyId);
    if(firstEmptyId < i)
      swapBlocks(blocks, firstEmptyId, i);
  }
  __int64 sum=0;
  for(__int64 i=0; i<(__int64)blocks.size(); i++){
    if(blocks[i] > -1){
      sum += (__int64)(blocks[i])*i;
    }
  }
  std::cout << "part 1: " << sum << std::endl;
}

void Day09::part2(std::string filename){
  InputLoader loader(filename);
  std::vector<char> input = loader.toVectorChar();
  std::list<Point2D> blocks; // Point2D because I dont wanna create a new class "block". x=id, y=size
  int id=0;
  bool isFile = true;
  for(char c: input){
    int digit = (int)c - 48;
    if(isFile){
      blocks.push_back(Point2D(id, digit));
      id++;
    }else{
      blocks.push_back(Point2D(-1, digit));
    }
    isFile = !isFile;
  }
  std::list<Point2D>::iterator afterActiveBlock = blocks.end();
  while(afterActiveBlock != blocks.begin()){
    std::list<Point2D>::iterator activeBlock = std::prev(afterActiveBlock);
    if(activeBlock->x != -1){
      std::list<Point2D>::iterator freeSpotIt = firstSpotWhereBlockFits(blocks, activeBlock);
      if(freeSpotIt != blocks.end()){
        insertBlockAtIt(blocks, freeSpotIt, std::prev(afterActiveBlock));
      }
    }
    afterActiveBlock--;
  }
  __int64 checkSum = 0;
  int memPos = 0;
  for(Point2D block: blocks){
    checkSum += checksumForBlock(block, memPos);
    memPos += block.y;
  }
  std::cout << "part 2: " << checkSum << std::endl;
}

int Day09::firstEmpyBlock(std::vector<int>& blocks, int startId){
  for(int i=startId; i<(int)blocks.size(); i++)
    if(blocks[i] == -1)
      return i;
  return blocks.size();
}

void Day09::swapBlocks(std::vector<int>& blocks, int idA, int idB){
  int a = blocks[idA];
  blocks[idA] = blocks[idB];
  blocks[idB] = a;
}

std::list<Point2D>::iterator Day09::firstSpotWhereBlockFits(std::list<Point2D>& blocks, std::list<Point2D>::iterator fitBlock){
  for(std::list<Point2D>::iterator blockIt=blocks.begin(); blockIt!=blocks.end() && blockIt != fitBlock; blockIt++)
    if(blockIt->x == -1 && blockIt->y >= fitBlock->y)
      return blockIt;
  return blocks.end();
}

bool Day09::insertBlockAtIt(std::list<Point2D>& blocks, std::list<Point2D>::iterator insertAt, std::list<Point2D>::iterator insertBlock){
  if(insertAt == insertBlock || insertAt == blocks.end() || insertAt->x != -1 || insertAt->y < insertBlock->y){
    std::cout << "Invalid call of insertBlockAtIt" << std::endl;
    return false;
  }
  blocks.insert(insertAt, *insertBlock);
  if(insertAt->y == insertBlock->y)
    blocks.erase(insertAt);
  else
    insertAt->y = insertAt->y - insertBlock->y;
  insertBlock->x = -1;
  return true;
}

__int64 Day09::checksumForBlock(Point2D block, int firstId){
  if(block.x == -1)
    return 0;
  __int64 sum = 0;
  __int64 id = firstId;
  for(int i=0; i<block.y; i++){
    sum += id*block.x;
    id++;
  }
  return sum;
}
