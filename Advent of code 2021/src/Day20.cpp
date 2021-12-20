#include "Day20.h"

void FloorImage::loadTranslationSheet(string input){
  translationSheet.clear();
  for(char c:input){
    if(c=='.')
      translationSheet.push_back(false);
    else
      translationSheet.push_back(true);
  }
}

void FloorImage::loadFloorImage(vector<string> input){
  fImg.clear();
  int lineId=0;
  /*for(int i=0; i<100; i++){
    fImg.push_back({});
    for(int i2=0; i2<100; i2++){
      fImg[i].push_back(false);
    }
  }*/
  for(string line:input){
    fImg.push_back({});
    int cId=0;
    for(char c:line){
      if(c=='.')
        //fImg[lineId][cId]=false;
        fImg[lineId].push_back(false);
      else
        //fImg[lineId][cId]=true;
        fImg[lineId].push_back(true);
      cId++;
    }
    lineId++;
  }
}

void FloorImage::output(){
  for(bool p:translationSheet){
    if(p)
      cout << "#";
    else
      cout << ".";
  }
  cout << endl << endl;
  for(vector<bool>& line: fImg){
    for(bool p:line){
      if(p)
        cout << "#";
      else
        cout << ".";
    }
    cout << endl;
  }
}

void FloorImage::addRow(int dir){
  vector<bool> newRow(fImg[0].size());
  for(int i=0; i<(int)fImg[0].size(); i++)
    newRow[i] = outsideVal;
  switch(dir){
    case UP:
      fImg.insert(fImg.begin(), newRow);
      break;
    case DOWN:
      fImg.push_back(newRow);
      break;
    case LEFT:
      for(int i=0; i<(int)fImg.size(); i++)
        fImg[i].insert(fImg[i].begin(), outsideVal);
      break;
    case RIGHT:
      for(int i=0; i<(int)fImg.size(); i++)
        fImg[i].push_back(outsideVal);
      break;
  }
}

bool FloorImage::getPixel(int x, int y){
  if(x<0 || y<0 || x>=(int)fImg[0].size() || y>=(int)fImg.size())
    return outsideVal;
  return fImg[y][x];
}

bool FloorImage::translatePixel(int x, int y){
  int sum=0;
  int digit=256;
  for(int row=-1; row<=1; row++){
    for(int col=-1; col<=1; col++){
      if(getPixel(x+col, y+row))
        sum += digit;
      digit = digit/2;
    }
  }
  return translationSheet[sum];
}

void FloorImage::translatePicture(){
  addRow(UP);
  addRow(DOWN);
  addRow(LEFT);
  addRow(RIGHT);
  vector<vector<bool>> imgCopy = fImg;
  for(int y=0; y<(int)imgCopy.size(); y++){
    for(int x=0; x<(int)imgCopy[0].size(); x++){
      imgCopy[y][x] = translatePixel(x, y);
    }
  }
  fImg=imgCopy;
  outsideVal = !outsideVal;
}

int FloorImage::countPixels(){
  int sum=0;
  for(int y=0; y<(int)fImg.size(); y++){
    for(int x=0; x<(int)fImg[0].size(); x++){
      if(fImg[y][x])
        sum++;
    }
  }
  return sum;
}

Day20::Day20()
{
  //ctor
}

Day20::~Day20()
{
  //dtor
}

void Day20::part1(string filename){
  InputLoader loader(filename);
  FloorImage floor;
  vector<string> vs = loader.toVectorStr();
  floor.loadTranslationSheet(vs[0]);
  vs.erase(vs.begin());
  vs.erase(vs.begin());
  floor.loadFloorImage(vs);

  floor.translatePicture();
  floor.translatePicture();
  cout << "Part 1: " << floor.countPixels() << endl;
  for(int i=0; i<48; i++)
    floor.translatePicture();
  cout << "Part 2: " << floor.countPixels() << endl;
}

void Day20::part2(string filename){
}
