#include "Day24.h"
int GLOBALID = 1;

void Hex::connectHex(Hex* other, int dir){
  ngbr[dir] = other;
  switch(dir){
  case w:
    other->ngbr[e] = this;
    break;
  case e:
    other->ngbr[w] = this;
    break;
  case nw:
    other->ngbr[se] = this;
    break;
  case ne:
    other->ngbr[sw] = this;
    break;
  case sw:
    other->ngbr[ne] = this;
    break;
  case se:
    other->ngbr[nw] = this;
    break;
  default:
    cout << "ERROR" << endl;
  }
}

void Hex::output(){
  int nwId=0, neId=0, swId=0, seId=0, wId=0, eId=0;
  if(ngbr[nw] != nullptr)
    nwId = ngbr[nw]->id;
  if(ngbr[ne] != nullptr)
    neId = ngbr[ne]->id;
  if(ngbr[sw] != nullptr)
    swId = ngbr[sw]->id;
  if(ngbr[se] != nullptr)
    seId = ngbr[se]->id;
  if(ngbr[w] != nullptr)
    wId = ngbr[w]->id;
  if(ngbr[e] != nullptr)
    eId = ngbr[e]->id;
  cout << "   " << setfill('0') << setw(3) << nwId << "   " << setfill('0') << setw(3) << neId << endl;
  cout << setfill('0') << setw(3) << wId << "   " << setfill('0') << setw(3) << id << "   " << setfill('0') << setw(3) << eId << endl;
  cout << "   " << setfill('0') << setw(3) << swId << "   " << setfill('0') << setw(3) << seId << endl;
}

bool Hex::calcNewIsWhite(){
  bool expansionNeeded = false;
  int blackNeighbours=0;
  for(int dir=0; dir<6; dir++){
    if(ngbr[dir] == nullptr){
      if(!isWhite)
        expansionNeeded = true;
    }else{
      if(!(ngbr[dir]->isWhite))
        blackNeighbours++;;
    }
  }
  if(!isWhite)
    newIsWhite = (blackNeighbours == 0 || blackNeighbours >2);
  else
    newIsWhite = (blackNeighbours != 2);
  return expansionNeeded;
}

Day24::Day24()
{
  //ctor
}

Day24::~Day24()
{
  //dtor
}

void Day24::part1(string filename){
  InputLoader loader(filename);
  vector<string> vs = loader.toVectorStr();
  vector<vector<int>> inst;
  Hex* center = new Hex();
  for(string s: vs){
    inst.push_back(strToInst(s));
  }
  for(vector<int> vi: inst){
    flipHex(center, vi);
  }
  cout << "part 1: " << countBlack(center) << endl;
}

void Day24::part2(string filename){
  InputLoader loader(filename);
  vector<string> vs = loader.toVectorStr();
  vector<vector<int>> inst;
  Hex* center = new Hex();
  for(string s: vs){
    inst.push_back(strToInst(s));
  }
  for(vector<int> vi: inst){
    flipHex(center, vi);
  }
  for(int i=0; i<100; i++){
    applyPattern(center);
  }
  cout << "part 2: " << countBlack(center) << endl;
}

void Day24::spawnHexRound(Hex* spawnHex){
  while(spawnHex->ngbr[w] != nullptr)
    spawnHex = spawnHex->ngbr[w];
  Hex* lastCreated = nullptr;
  Hex* forbiddenHex = spawnHex;
  spawnHex = spawnHexRow(spawnHex, lastCreated, nw, ne, w);
  forbiddenHex = forbiddenHex->ngbr[nw];
  spawnHex = spawnHexRow(spawnHex, lastCreated, ne, e, nw);
  spawnHex = spawnHexRow(spawnHex, lastCreated, e, se, ne);
  spawnHex = spawnHexRow(spawnHex, lastCreated, se, sw, e);
  spawnHex = spawnHexRow(spawnHex, lastCreated, sw, w, se);
  spawnHex = spawnHexRow(spawnHex, lastCreated, w, nw, sw, forbiddenHex);
  spawnHex->ngbr[w]->connectHex(spawnHex->ngbr[nw], ne);
}

Hex* Day24::spawnHexRow(Hex* spawnHex, Hex*& lastCreated, int spawnDir, int moveDir, int connectDir, Hex* forbiddenHexAddr){
  bool done=false;
  while(!done){
    spawnHex->connectHex(new Hex(), spawnDir);
    if(lastCreated != nullptr){
      spawnHex->connectHex(lastCreated, connectDir);
      lastCreated->connectHex(spawnHex->ngbr[spawnDir], moveDir);
    }
    lastCreated = spawnHex->ngbr[spawnDir];
    if(spawnHex->ngbr[moveDir] != forbiddenHexAddr)
      spawnHex = spawnHex->ngbr[moveDir];
    else
      done=true;
  }
  return spawnHex;
}

vector<int> Day24::strToInst(string s){
  vector<int> ret;
  int sPos = 0;
  while(sPos<(int)s.size()){
    if(s[sPos] == 'w'){
      ret.push_back(w);
      sPos++;
    }else if(sPos+1<(int)s.size() && s[sPos] == 'n' && s[sPos+1] == 'w'){
      ret.push_back(nw);
      sPos+=2;
    }else if(sPos+1<(int)s.size() && s[sPos] == 'n' && s[sPos+1] == 'e'){
      ret.push_back(ne);
      sPos+=2;
    }else if(s[sPos] == 'e'){
      ret.push_back(e);
      sPos++;
    }else if(sPos+1<(int)s.size() && s[sPos] == 's' && s[sPos+1] == 'w'){
      ret.push_back(sw);
      sPos+=2;
    }else if(sPos+1<(int)s.size() && s[sPos] == 's' && s[sPos+1] == 'e'){
      ret.push_back(se);
      sPos+=2;
    }
  }
  return ret;
}

string intDirToChar(int dir){
  switch(dir){
  case w:
    return "w";
  case nw:
    return "nw";
  case ne:
    return "ne";
  case e:
    return "e";
  case sw:
    return "sw";
  case se:
    return "se";
  default:
    return "ERROR";
  }
}

void Day24::flipHex(Hex* center, vector<int> inst){
  bool fail = true;
  Hex* flippingHex = center;
  int instId=0;
  while(fail){
    fail = false;
    for(int i=instId; i<(int)inst.size() && !fail; i++){
      if(flippingHex->ngbr[inst[i]] == nullptr){
        fail = true;
        instId = i;
      }
      else{
        flippingHex = flippingHex->ngbr[inst[i]];
      }
    }
    if(fail){
      spawnHexRound(center);
    }else{
      flippingHex->isWhite = !(flippingHex->isWhite);
    }
  }
}

int Day24::countBlack(Hex* center){
  int blacks = 0;
  int sideLen = 1;
  Hex* currHex = center;
  if(!(center->isWhite))
    blacks = 1;
  while(currHex->ngbr[w] != nullptr){
    currHex = currHex->ngbr[w];
    for(int dir=0; dir<6; dir++){
      for(int i=0; i<sideLen; i++){
        currHex = currHex->ngbr[dir];
        if(!(currHex->isWhite))
          blacks++;
      }
    }
    sideLen++;
  }
  return blacks;
}

void Day24::applyPattern(Hex* center){
  int sideLen = 1;
  Hex* currHex = center;
  currHex->calcNewIsWhite();
  while(currHex->ngbr[w] != nullptr){
    currHex = currHex->ngbr[w];
    for(int dir=0; dir<6; dir++){
      for(int i=0; i<sideLen; i++){
        currHex = currHex->ngbr[dir];
        if(currHex->calcNewIsWhite())
          spawnHexRound(center);
      }
    }
    sideLen++;
  }
  sideLen = 1;
  currHex = center;
  currHex->isWhite = currHex->newIsWhite;
  while(currHex->ngbr[w] != nullptr){
    currHex = currHex->ngbr[w];
    for(int dir=0; dir<6; dir++){
      for(int i=0; i<sideLen; i++){
        currHex = currHex->ngbr[dir];
        currHex->isWhite = currHex->newIsWhite;
      }
    }
    sideLen++;
  }
}
