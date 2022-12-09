#include "Day07.h"

Day07::Day07()
{
  //ctor
}

Day07::~Day07()
{
  //dtor
}

void Day07::part1(string filename){
  InputLoader loader(filename);
  vector<string> input = loader.toVectorStr();
  Folder* folder = new Folder(nullptr, "/");
  for(string line: input){
    if(line[0] == '$'){
      if(line.substr(0,4).compare("$ cd") == 0)
        folder = folder->cd(line.substr(5, line.size()-5));
    }else{
      folder->addChild(line);
    }
  }
  folder = folder->cd("/");
  folder->diskSize();
  __int64 ans = folder->sumAllFoldersLessThan(100000);
  cout << "part 1: " << ans << endl;
}

void Day07::part2(string filename){
  InputLoader loader(filename);
  vector<string> input = loader.toVectorStr();
  Folder* folder = new Folder(nullptr, "/");
  for(string line: input){
    if(line[0] == '$'){
      if(line.substr(0,4).compare("$ cd") == 0)
        folder = folder->cd(line.substr(5, line.size()-5));
    }else{
      folder->addChild(line);
    }
  }
  folder = folder->cd("/");
  __int64 totalDiskSize = folder->diskSize();
  __int64 maxSize = 40000000;
  __int64 removeAtLeast = totalDiskSize-maxSize;
  folder->diskSize();
  __int64 ans = folder->biggestValSmallerThan(removeAtLeast, -1);
  cout << "part 2: " << ans << endl;
}

bool Folder::addChild(string input){
  size_t splitPos = input.find(" ");
  if(splitPos == string::npos || splitPos == input.size() || splitPos == 0)
    return false;
  string part1 = input.substr(0,splitPos);
  string part2 = input.substr(splitPos+1, input.size()-splitPos);
  if(part1.compare("dir") == 0){
    children.push_back(new Folder(this, part2));
    return true;
  }else{
    __int64 diskSize;
    try{
      diskSize =_atoi64(part1.c_str());
    }catch(...){
      cout << "could not convert \"" << part1 << "\" to __int64" << endl;
      return false;
    }
    children.push_back(new File(this, diskSize, part2));
    return true;
  }
}

Folder* Folder::cd(string dirName){
  if(dirName.compare("..") == 0)
    return (Folder*)parent;
  if(dirName.compare("/") == 0){
    DiskPos* ret = this;
    while(ret->parent)
      ret = ret->parent;
    return (Folder*)ret;
  }
  for (std::list<DiskPos*>::iterator it = children.begin(); it != children.end(); ++it)
    if((*it)->name.compare(dirName) == 0)
      return (Folder*)*it;
  cout << "Could not find child " + dirName << endl;
  return nullptr;
}

__int64 Folder::diskSize(){
  if(_diskSize > -1)
    return _diskSize;
  _diskSize = 0;
  for (std::list<DiskPos*>::iterator it = children.begin(); it != children.end(); ++it)
    _diskSize += (*it)->diskSize();
  return _diskSize;
}

void Folder::output(string tab){
  cout << tab << name << ": " << _diskSize << endl;
  for (std::list<DiskPos*>::iterator it = children.begin(); it != children.end(); ++it)
    (*it)->output(tab + " ");
}

__int64 Folder::sumAllFoldersLessThan(__int64 maxVal){
  __int64 sum=0;
  if(_diskSize <= maxVal)
    sum = _diskSize;
  for (std::list<DiskPos*>::iterator it = children.begin(); it != children.end(); ++it){
    if((*it)->getType() == DAY07_FOLDER)
      sum += ((Folder*)(*it))->sumAllFoldersLessThan(maxVal);
  }
  return sum;
}

__int64 Folder::biggestValSmallerThan(__int64 minVal, __int64 bestMatch){
  __int64 ret=bestMatch;
  if(bestMatch == -1 || (_diskSize < bestMatch && _diskSize >= minVal))
    ret = _diskSize;
  for (std::list<DiskPos*>::iterator it = children.begin(); it != children.end(); ++it){
    if((*it)->getType() == DAY07_FOLDER){
      __int64 childRet = ((Folder*)(*it))->biggestValSmallerThan(minVal, ret);
      if(childRet<ret)
        ret = childRet;
    }
  }
  return ret;
}
