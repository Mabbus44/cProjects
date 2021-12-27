#include "Day23.h"

myMap::myMap(const myMap& m){
  for(int i=0; i<2; i++){
    leftSafe[i] = m.leftSafe[i];
    rightSafe[i] = m.rightSafe[i];
  }
  for(int i=0; i<3; i++)
    middleSafe[i] = m.middleSafe[i];
  for(int i=0; i<4; i++){
    home[i] = m.home[i];
  }
  score = m.score;
}

void myMap::output(){
  cout << "#############" << endl;
  cout << "#" << valToChar(leftSafe[1]) << valToChar(leftSafe[0]) << ".";
  for(int i=0; i<3; i++){
    cout << valToChar(middleSafe[i]);
    if(i<2)
      cout << ".";
  }
  cout << "." << valToChar(rightSafe[0]) << valToChar(rightSafe[1]) << "#" << endl;
  for(int row=0; row<4; row++){
    if(row==0)
      cout << "###";
    else
      cout << "  #";
    for(int col=0; col<4; col++){
      if((int)home[col].size()>3-row)
        cout << valToChar(home[col][3-row]) << "#";
      else
        cout << ".#";
    }
    if(row==0)
      cout << "##";
    else
      cout << "  ";
    cout << endl;
  }
  cout << "  #########  " << endl;
  cout << "Score: " << score << endl;
}

char myMap::valToChar(int val){
  switch(val){
  case -1:
    return '.';
  case A:
    return 'A';
  case B:
    return 'B';
  case C:
    return 'C';
  case D:
    return 'D';
  }
  return 'X';//error
}

bool myMap::isDone(){
  for(int col=0; col<4; col++){
    if(home[col].size()<4)
      return false;
    for(int row=0; row<4; row++){
      if(home[col][row] != col)
        return false;
    }
  }
  return true;
}

int myMap::testAll(int depth, int minScore, string track){
  if(depth<7){
    //cout << track << " " << minScore << endl;
    /*cout << "Depth " << depth << endl;
    output();
    cout << endl;*/
  }
  if(isDone()){
    if(minScore == -1 || score< minScore){
      cout << track << " " << minScore << endl;
      //cout << "minScore " << minScore << endl;
      return score;
    }
    return minScore;
  }
  if(minScore!=-1 && score>=minScore)
    return minScore;
  for(int moveId=0; moveId<MOVE_COUNT; moveId++){
    for(int fromId=0; fromId<maxFromId[moveId]; fromId++){
      for(int toId=0; toId<maxToId[moveId]; toId++){
        if(isValid(moveId, fromId, toId)){
          myMap newMap(*this);
          newMap.makeMove(moveId, fromId, toId);
          int val=-1;
          if(depth>=0){
            val = newMap.testAll(depth+1, minScore, track+" - "
                                 +to_string(moveId)+"/"+to_string(MOVE_COUNT-1)+" "
                                 +to_string(fromId)+"/"+to_string(maxFromId[moveId]-1)+" "
                                 +to_string(toId)+"/"+to_string(maxToId[moveId]-1)
                                 );
            //cout << endl;
          }
          if(minScore == -1 || val<minScore)
            minScore = val;
        }
      }
    }
  }
  return minScore;
}

bool myMap::isValid(int moveId, int fromId, int toId){
  int movingAnimal=-1;
  if( moveId == HOME_HOME ||                        //Move from home
      moveId == HOME_LEFTSAFE ||
      moveId ==  HOME_RIGHTSAFE ||
      moveId ==  HOME_MIDDLESAFE){
    if(home[fromId].size()==0)                          //Source must have animal
      return false;
    bool allHomeAnimals = true;
    for(int animal:home[fromId])
      if(animal != fromId)
        allHomeAnimals = false;
    if(allHomeAnimals)                                  //Cannot move out animal from its home
      return false;
    movingAnimal=home[fromId].back();
  }
  if( moveId == HOME_HOME ||                        //Move to home
      moveId == LEFTSAFE_HOME ||
      moveId ==  RIGHTSAFE_HOME ||
      moveId ==  MIDDLESAFE_HOME){
    if(home[toId].size()==4)                            //Dest must not be full
      return false;
    for(int val:home[toId])                             //Dest must not contain anny forign animals
      if(val!=-1 && val != toId)
        return false;
  }
  if( moveId == LEFTSAFE_HOME){                    //Move from leftsafe
    if(leftSafe[fromId] == -1)                            //Source must have animal
      return false;
    if(fromId==1 && leftSafe[0] != -1)                    //Cannot move through [0] if occupied
      return false;
    movingAnimal=leftSafe[fromId];
  }
  if( moveId == RIGHTSAFE_HOME){                    //Move from rightsafe
    if(rightSafe[fromId] == -1)                            //Source must have animal
      return false;
    if(fromId==1 && rightSafe[0] != -1)                    //Cannot move through [0] if occupied
      return false;
    movingAnimal=rightSafe[fromId];
  }
  if( moveId == HOME_LEFTSAFE){                    //Move to leftsafe
    if(leftSafe[toId] != -1)                            //Dest must not be full
      return false;
    if(toId==1 && leftSafe[0] != -1)                    //Cannot move through [0] if occupied
      return false;
  }
  if( moveId == HOME_RIGHTSAFE){                    //Move to rightsafe
    if(rightSafe[toId] != -1)                            //Dest must not be full
      return false;
    if(toId==1 && rightSafe[0] != -1)                    //Cannot move through [0] if occupied
      return false;
  }
  if( moveId == MIDDLESAFE_HOME){                     //Move from middlesafe
    if(middleSafe[fromId] == -1)                           //Source must have animal
      return false;
    movingAnimal=middleSafe[fromId];
  }
  if( moveId == HOME_MIDDLESAFE){                    //Move to middlesafe
    if(middleSafe[toId] != -1)                            //Dest must not be full
      return false;
    /*for(int animal:home[movingAnimal]){                   //Must not block animals from its home to get to their home
      if(movingAnimal animal toId)
      if(movingAnimal>animal){
        if(movingAnimal>toId && animal<=toId)
          return false;
      }else if(animal>movingAnimal){
        if(animal>toId && movingAnimal<=toId)
          return false;
      }
    }*/
  }

  switch(moveId){
    case HOME_HOME:
      if(fromId==toId)                                    //Cant move to self
        return false;
      if(home[fromId].back() != toId)                     //Dest must be home for animal
        return false;
      if(fromId<toId){
        if(!middleFree(fromId, toId-1))
          return false;                                   //Middle must be free
      }else{
        if(!middleFree(toId, fromId-1))
          return false;
      }
      break;
    case HOME_LEFTSAFE:
      if(!middleFree(0, fromId-1))
        return false;                                     //Middle must be free
      break;
    case HOME_RIGHTSAFE:
      if(!middleFree(fromId, 2))
        return false;                                     //Middle must be free
      break;
    case HOME_MIDDLESAFE:
      if(fromId<=toId){
        if(!middleFree(fromId, toId-1))
          return false;                                     //Middle must be free
      }else{
        if(!middleFree(toId+1, fromId-1))
          return false;
      }
      break;
    case LEFTSAFE_HOME:
      if(leftSafe[fromId] != toId)                          //Dest must be home for animal
        return false;
      if(!middleFree(0, toId-1))
        return false;                                       //Middle must be free
      break;
    case RIGHTSAFE_HOME:
      if(rightSafe[fromId] != toId)                         //Dest must be home for animal
        return false;
      if(!middleFree(toId, 2))
        return false;                                       //Middle must be free
      break;
    case MIDDLESAFE_HOME:
      if(middleSafe[fromId] != toId)                        //Dest must be home for animal
        return false;
      if(fromId<toId){
        if(!middleFree(fromId+1, toId))
          return false;                                     //Middle must be free
      }else{
        if(!middleFree(toId, fromId-1))
          return false;
      }
      break;
  }
  return true;
}

bool myMap::middleFree(int fromId, int toId){
  //cout << "middleFree(" << fromId << ", " << toId << ")";
  for(int i=fromId; i<=toId; i++){
    if(i>=0 && i<=2 && middleSafe[i] != -1){
      //cout << " false" << endl;
      return false;
    }
  }
  //cout << " true" << endl;
  return true;
}

void myMap::makeMove(int moveId, int fromId, int toId){
  cout << "makeMove(" << moveId << ", " << fromId << ", " << toId << ")";
  int animal;
  int moves=0;
  if( moveId == HOME_HOME ||                          //From home
      moveId == HOME_LEFTSAFE ||
      moveId == HOME_RIGHTSAFE ||
      moveId == HOME_MIDDLESAFE){
    animal = home[fromId].back();
    home[fromId].pop_back();
    moves = 4-home[fromId].size();
  }
  if( moveId == LEFTSAFE_HOME){                      //From leftside
    animal = leftSafe[fromId];
    leftSafe[fromId] = -1;
    moves = fromId+1;
  }
  if( moveId == RIGHTSAFE_HOME){                     //From rightside
    animal = rightSafe[fromId];
    rightSafe[fromId] = -1;
    moves = fromId+1;
  }
  if( moveId == MIDDLESAFE_HOME){                    //From middleside
    animal = middleSafe[fromId];
    middleSafe[fromId] = -1;
  }
  cout << " from moves: " << moves;
  if( moveId == HOME_HOME ||                          //To home
      moveId == LEFTSAFE_HOME ||
      moveId == RIGHTSAFE_HOME ||
      moveId == MIDDLESAFE_HOME){
    home[toId].push_back(animal);
    moves += (4-home[toId].size()+1);
  }
  if( moveId == HOME_LEFTSAFE){                      //To leftside
    leftSafe[toId] = animal;
    moves+=toId+1;
  }
  if( moveId == HOME_RIGHTSAFE){                      //To rightside
    rightSafe[toId] = animal;
    moves+=toId+1;
  }
  if( moveId == HOME_MIDDLESAFE){                      //To middleside
    middleSafe[toId] = animal;
  }
  cout << " to moves: " << moves;
  switch(moveId){
    case HOME_HOME:
      moves += (abs(fromId-toId)*2);
      break;
    case HOME_LEFTSAFE:
      moves += (fromId*2);
      break;
    case HOME_RIGHTSAFE:
      moves += ((3-fromId)*2);
      break;
    case HOME_MIDDLESAFE:
      if(toId>fromId)
        moves += (toId-fromId)*2;
      if(fromId>toId+1)
        moves += (fromId-toId-1)*2;
      moves++;
      break;
    case LEFTSAFE_HOME:
      moves += toId*2;
      break;
    case RIGHTSAFE_HOME:
      moves += (3-toId)*2;
      break;
    case MIDDLESAFE_HOME:
      if(toId>fromId+1)
        moves += (toId-fromId-1)*2;
      if(fromId>toId)
        moves += (fromId-toId)*2;
      moves++;
      break;
  }
  int mul=1;
  for(int i=1; i<=animal; i++)
    mul *= 10;
  cout << " end moves: " << moves << endl;
  score += moves*mul;
}

Day23::Day23()
{
  //ctor
}

Day23::~Day23()
{
  //dtor
}

void Day23::part1(string filename){
  cout << "Part 1: " << 13495 << endl;
}

void Day23::part2(string filename){
  myMap m;
  /*cout << m.isDone() << endl;
  m.home[0] = {A,A,A,A};
  m.home[1] = {B,B,B,B};
  m.home[2] = {C,C,C,C};
  m.home[3] = {D,D,D,D};
  m.output();
  cout << m.isDone() << endl;*/
  /*m.home[3].pop_back();
  m.middleSafe[2] = B;*/
  vector<vector<int>> instructions = {
{HOME_RIGHTSAFE,2,1},
{HOME_RIGHTSAFE,2,0},
{HOME_LEFTSAFE,2,1},
{HOME_LEFTSAFE,1,0},
{HOME_MIDDLESAFE,2,0},
{HOME_HOME,1,2},
{HOME_MIDDLESAFE,1,2},
{HOME_HOME,1,2},
{MIDDLESAFE_HOME,2,1},
{HOME_HOME,3,1},
{RIGHTSAFE_HOME,0,1},
{HOME_RIGHTSAFE,3,0},
{HOME_HOME,3,2},
{HOME_HOME,3,1},
{MIDDLESAFE_HOME,0,3},
{LEFTSAFE_HOME,0,3},
{HOME_LEFTSAFE,0,0},
{HOME_HOME,0,3},
{HOME_HOME,0,3},
{HOME_HOME,0,2},
{LEFTSAFE_HOME,0,0},
{LEFTSAFE_HOME,1,0},
{RIGHTSAFE_HOME,0,0},
{RIGHTSAFE_HOME,1,0}
  };
  for(vector<int> inst:instructions){
    //cout << m.isValid(inst[0], inst[1], inst[2]) << endl;
    m.makeMove(inst[0], inst[1], inst[2]);
    //cout << m.isDone() << endl;
    m.output();

    cout << endl;
  }
  //m.testAll();
  cout << endl;
  cout << "Part 2: " << endl;
}
