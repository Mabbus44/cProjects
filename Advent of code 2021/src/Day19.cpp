#include "Day19.h"

void MyCoord::output(){
  cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}

int MyCoord::getLen(){
  return abs(x) + abs(y) + abs(z);
}

bool MyCoord::possibleMatch(const MyCoord& other){
  return abs(x)+abs(y)+abs(z)==abs(other.x)+abs(other.y)+abs(other.z);
}

bool MyCoord::match(const MyCoord& other){
  vector<int> coords;
  coords.push_back(abs(x));
  coords.push_back(abs(y));
  coords.push_back(abs(z));
  sort(coords.begin(), coords.end());
  vector<int> otherMyCoords;
  otherMyCoords.push_back(abs(other.x));
  otherMyCoords.push_back(abs(other.y));
  otherMyCoords.push_back(abs(other.z));
  sort(otherMyCoords.begin(), otherMyCoords.end());
  if((coords[1]-coords[0])!=(otherMyCoords[1]-otherMyCoords[0]))
    return false;
  if((coords[2]-coords[1])!=(otherMyCoords[2]-otherMyCoords[1]))
    return false;
  return true;
}

void Scanner::output(){
  for(MyCoord& b:coords){
    b.output();
  }
}

void Scanner::loadMyCoord(string line){
  InputLoader loader;
  vector<string> vs = loader.splitString(line, {","});
  if(vs.size()!=3)
    return;
  vector<int> vi = loader.toInt(vs);
  MyCoord b;
  b.x=vi[0];
  b.y=vi[1];
  b.z=vi[2];
  coords.push_back(b);
}

MyCoord MyCoord::rot(int rotation){
  MyCoord ret;
  switch(rotation){
    case 0:     //x = x
      ret.x=this->x;
      ret.y=this->y;
      ret.z=this->z;
      break;
    case 1:
      ret.x=this->x;
      ret.y=-this->y;
      ret.z=-this->z;
      break;
    case 2:
      ret.x=this->x;
      ret.y=-this->z;
      ret.z=this->y;
      break;
    case 3:
      ret.x=this->x;
      ret.y=this->z;
      ret.z=-this->y;
      break;
    case 4:     //x=y
      ret.x=this->y;
      ret.y=this->z;
      ret.z=this->x;
      break;
    case 5:
      ret.x=this->y;
      ret.y=-this->z;
      ret.z=-this->x;
      break;
    case 6:
      ret.x=this->y;
      ret.y=-this->x;
      ret.z=this->z;
      break;
    case 7:
      ret.x=this->y;
      ret.y=this->x;
      ret.z=-this->z;
      break;
    case 8:     //x=z
      ret.x=this->z;
      ret.y=this->x;
      ret.z=this->y;
      break;
    case 9:
      ret.x=this->z;
      ret.y=-this->x;
      ret.z=-this->y;
      break;
    case 10:
      ret.x=this->z;
      ret.y=-this->y;
      ret.z=this->x;
      break;
    case 11:
      ret.x=this->z;
      ret.y=this->y;
      ret.z=-this->x;
      break;
    case 12:    //x=-x
      ret.x=-this->x;
      ret.y=this->z;
      ret.z=this->y;
      break;
    case 13:
      ret.x=-this->x;
      ret.y=-this->z;
      ret.z=-this->y;
      break;
    case 14:
      ret.x=-this->x;
      ret.y=-this->y;
      ret.z=this->z;
      break;
    case 15:
      ret.x=-this->x;
      ret.y=this->y;
      ret.z=-this->z;
      break;
    case 16:    //x=-y
      ret.x=-this->y;
      ret.y=this->x;
      ret.z=this->z;
      break;
    case 17:
      ret.x=-this->y;
      ret.y=-this->x;
      ret.z=-this->z;
      break;
    case 18:
      ret.x=-this->y;
      ret.y=-this->z;
      ret.z=this->x;
      break;
    case 19:
      ret.x=-this->y;
      ret.y=this->z;
      ret.z=-this->x;
      break;
    case 20:    //x=-z
      ret.x=-this->z;
      ret.y=this->y;
      ret.z=this->x;
      break;
    case 21:
      ret.x=-this->z;
      ret.y=-this->y;
      ret.z=-this->x;
      break;
    case 22:
      ret.x=-this->z;
      ret.y=-this->x;
      ret.z=this->y;
      break;
    case 23:
      ret.x=-this->z;
      ret.y=this->x;
      ret.z=-this->y;
      break;
  }
  return ret;
}

void Scanner::rotationSanityCheck(){
  MyCoord start;
  start.x = 1;
  start.y = 2;
  start.z = 3;
  for(int i=0; i<24; i++){
    MyCoord b = start.rot(i);
    int negCount=0;
    if(b.x<0)
      negCount++;
    if(b.y<0)
      negCount++;
    if(b.z<0)
      negCount++;
    int diffCount=0;
    if(abs(b.x)!=abs(start.x))
      diffCount++;
    if(abs(b.y)!=abs(start.y))
      diffCount++;
    if(abs(b.z)!=abs(start.z))
      diffCount++;
    if(diffCount==1)
      cout << "ERRROROROOR" << endl;
    if(diffCount>0)
      diffCount--;
    bool same = false;
    if(abs(b.x)==abs(b.y))
      same = true;
    if(abs(b.y)==abs(b.z))
      same = true;
    if(abs(b.z)==abs(b.x))
      same = true;
    cout << same << " " << diffCount+negCount << " " << diffCount << " " << negCount << endl;
    if(same || (diffCount+negCount)%2==1)
      cout << "Errorororororo" << endl;
  }
}

int Scanner::compare(Scanner* other){
  for(int myCoord1ID=0; myCoord1ID<(int)coords.size()-11; myCoord1ID++){
    for(int myCoord2ID=myCoord1ID+1; myCoord2ID<(int)coords.size()-10; myCoord2ID++){
      MyCoord myDist1 = coords[myCoord1ID]-coords[myCoord2ID];
      for(int otherMyCoord1ID=0; otherMyCoord1ID<(int)other->coords.size(); otherMyCoord1ID++){
        for(int otherMyCoord2ID=0; otherMyCoord2ID<(int)other->coords.size(); otherMyCoord2ID++){
          if(otherMyCoord1ID!=otherMyCoord2ID){
            MyCoord otherDist1 = other->coords[otherMyCoord1ID]-other->coords[otherMyCoord2ID];
            if(myDist1.possibleMatch(otherDist1)){
              for(int myCoord3ID=myCoord2ID+1; myCoord3ID<(int)coords.size()-9; myCoord3ID++){ //-9 because there has to be 12 points left to be matched
                MyCoord myDist2 = coords[myCoord1ID]-coords[myCoord3ID];
                MyCoord myDist3 = coords[myCoord2ID]-coords[myCoord3ID];
                for(int otherMyCoord3ID=0; otherMyCoord3ID<(int)other->coords.size(); otherMyCoord3ID++){
                  if(otherMyCoord1ID!=otherMyCoord3ID && otherMyCoord2ID!=otherMyCoord3ID){
                    MyCoord otherDist2 = other->coords[otherMyCoord1ID]-other->coords[otherMyCoord3ID];
                    MyCoord otherDist3 = other->coords[otherMyCoord2ID]-other->coords[otherMyCoord3ID];
                    if(myDist2.possibleMatch(otherDist2) && myDist3.possibleMatch(otherDist3)){
                      for(int rot=0; rot<24; rot++){
                        MyCoord otherRotMyCoord1 = other->coords[otherMyCoord1ID].rot(rot);
                        MyCoord dist = otherRotMyCoord1-coords[myCoord1ID];
                        MyCoord otherRotMyCoord2 = other->coords[otherMyCoord2ID].rot(rot)-dist;
                        MyCoord otherRotMyCoord3 = other->coords[otherMyCoord3ID].rot(rot)-dist;
                        if(coords[myCoord2ID]==otherRotMyCoord2 && coords[myCoord3ID]==otherRotMyCoord3){
                          int matches=3;
                          for(int myCoord4ID=myCoord3ID+1; myCoord4ID-matches<(int)coords.size()-11; myCoord4ID++){ //-11 because if we have 11 matches we want to check all coords
                            for(int otherMyCoord4ID=0; otherMyCoord4ID<(int)other->coords.size(); otherMyCoord4ID++){
                              if(otherMyCoord4ID != otherMyCoord1ID &&
                                  otherMyCoord4ID != otherMyCoord2ID &&
                                  otherMyCoord4ID != otherMyCoord3ID &&
                                  coords[myCoord4ID] == (other->coords[otherMyCoord4ID].rot(rot)-dist))
                                matches++;
                              if(matches>=12){
                                other->relativeTo = this;
                                other->rotationToRel = rot;
                                other->distToRel = dist;
                                return rot;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return -1;
}

vector<MyCoord> Scanner::convertToBase(vector<MyCoord>& convCoords){
  if(relativeTo){
    for(MyCoord& c:convCoords){
      c=c.rot(rotationToRel)-distToRel;
    }
    return relativeTo->convertToBase(convCoords);
  }
  return convCoords;
}

Day19::Day19()
{
  //ctor
}

Day19::~Day19()
{
  //dtor
}

void Day19::part1(string filename){
  InputLoader loader(filename);
  vector<string> lines = loader.toVectorStr();
  vector<Scanner*> scanners;
  Scanner* lastScanner;
  int id=0;
  for(string line:lines){
    if(line.substr(0,3)=="---"){
      lastScanner=new Scanner();
      lastScanner->id = id;
      id++;
      scanners.push_back(lastScanner);
    }else{
      lastScanner->loadMyCoord(line);
    }
  }
  vector<int> unmappedScanners;
  vector<int> mappedScanners;
  mappedScanners.push_back(0);
  for(int i=1; i<(int)scanners.size(); i++)
    unmappedScanners.push_back(i);
  for(int i=0; i<(int)mappedScanners.size(); i++){
    for(int i2=0; i2<(int)unmappedScanners.size(); i2++){
      int rot=scanners[mappedScanners[i]]->compare(scanners[unmappedScanners[i2]]);
      if(rot!=-1){
        cout << "scanner[" << unmappedScanners[i2] << "] relative to scanner[" << mappedScanners[i] << "]" << endl;
        mappedScanners.push_back(unmappedScanners[i2]);
        unmappedScanners.erase(unmappedScanners.begin()+i2);
        i2--;
      }
    }
  }

  vector<MyCoord> allCoords;
  for(Scanner* s: scanners){
    vector<MyCoord> temp1;
    temp1.push_back(s->myPos);
    vector<MyCoord> temp2 = s->convertToBase(temp1);
    s->myPos = temp2[0];
    vector<MyCoord> co = s->convertToBase(s->coords);
    for(int i=0; i<(int)co.size(); i++){
      bool exists=false;
      for(int i2=0; !exists && i2<(int)allCoords.size(); i2++)
        if(allCoords[i2] == co[i])
          exists = true;
      if(!exists)
        allCoords.push_back(co[i]);
    }
  }
  cout << "Part 1: " << allCoords.size() << endl;

  int maxDist=0;
  for(int i1=0; i1<(int)scanners.size(); i1++){
    for(int i2=0; i2<(int)scanners.size(); i2++){
      if(i1!=i2 && maxDist<(scanners[i1]->myPos-scanners[i2]->myPos).getLen()){
        maxDist = (scanners[i1]->myPos-scanners[i2]->myPos).getLen();
      }
    }
  }
  cout << "Part 2: " << maxDist << endl;
}

void Day19::part2(string filename){
}
