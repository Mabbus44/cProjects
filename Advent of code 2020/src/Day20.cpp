#include "Day20.h"

void Tile::load(int id, vector<string> input){
  this->id = id;
  sides[0] = input[0];
  sides[1] = "";
  for(int row=0; row<(int)input.size(); row++)
    sides[1] = sides[1] + input[row].back();
  sides[2] = "";
  for(int col=input.back().size()-1; col>=0; col--)
    sides[2] = sides[2] + input.back()[col];
  sides[3] = "";
  for(int row=input.size()-1; row>=0; row--)
    sides[3] = sides[3] + input[row].front();
  for(int i=0; i<4; i++){
    matchCount[i] = 0;
    reversedSides[i] = "";
    for(int col=sides[i].size()-1; col >= 0; col--){
      reversedSides[i] = reversedSides[i] + sides[i][col];
    }
  }
  for(int y=0; y<10; y++){
    for(int x=0; x<10; x++){
      pic[y][x] = input[y][x];
    }
  }
}

void Tile::manipulate(int rot, int revX, int revY){
  /*cout << "Before manip ID:" << id << " rot:" << rot << " revX:" << revX << " revY:" << revY << endl;
  output();*/
  char newPic[10][10];
  for(int y=0; y<10; y++){
    for(int x=0; x<10; x++){
      int newX=x;
      int newY=y;
      switch(rot){
        case 1:
          newX = 9-y;
          newY = x;
          break;
        case 2:
          newX = 9-x;
          newY = 9-y;
          break;
        case 3:
          newX = y;
          newY = 9-x;
          break;
      }
      if(revX == REVERSED)
        newX = 9-newX;
      if(revY == REVERSED)
        newY = 9-newY;
      newPic[newY][newX] = pic[y][x];
    }
  }
  for(int y=0; y<10; y++)
    for(int x=0; x<10; x++)
      pic[y][x] = newPic[y][x];
  /*cout << "After manip " << id << endl;
  output();*/
}

tuple<int, int> Tile::matchSide(char side[10]){
  bool top = true;
  bool right = true;
  bool bottom = true;
  bool left = true;
  bool topRev = true;
  bool rightRev = true;
  bool bottomRev = true;
  bool leftRev = true;
  for(int i=0; i<10; i++){
    if(pic[0][i] != side[i])
      top=false;
    if(pic[0][9-i] != side[i])
      topRev=false;
    if(pic[i][9] != side[i])
      right=false;
    if(pic[9-i][9] != side[i])
      rightRev=false;
    if(pic[9][9-i] != side[i])
      bottom=false;
    if(pic[9][i] != side[i])
      bottomRev=false;
    if(pic[9-i][0] != side[i])
      left=false;
    if(pic[i][0] != side[i])
      leftRev=false;
  }
  int rev=NOT_REVERSED;
  if(topRev || rightRev || bottomRev || leftRev)
    rev = REVERSED;
  int dir = NO_SIDE;
  if(top || topRev)
    dir = TOP;
  if(right || rightRev)
    dir = RIGHT;
  if(bottom || bottomRev)
    dir = BOTTOM;
  if(left || leftRev)
    dir = LEFT;
  return make_tuple(dir,rev);
}

void Tile::output(){
  cout << "Tile " << id << ":" << endl;
  for(int y=0; y<10; y++){
    for(int x=0; x<10; x++){
      cout << pic[y][x];
    }
    cout << endl;
  }
  /*for(int i=0; i<4; i++){
    cout << matchCount[i] << endl;
  }*/
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
  vector<vector<string>> vvs=loader.toVectorStr2d({"Tile ", ":"});
  vector<Tile> tiles;
  int id;
  vector<string> input;
  bool newTile=true;
  for(vector<string> vs:vvs){
    if(newTile){
      id = stoi(vs[0]);
      newTile=false;
    }else if(vs.size() == 0){
        newTile=true;
        tiles.push_back(Tile(id, input));
        input.clear();
    } else{
      input.push_back(vs[0]);
    }
  }
  for(int tileId=0; tileId<(int)tiles.size(); tileId++){
    for(int sideId=0; sideId<4; sideId++){
      for(int tileId2=0; tileId2<(int)tiles.size(); tileId2++){
        for(int sideId2=0; sideId2<4 && tileId!=tileId2; sideId2++){
          if(tiles[tileId].sides[sideId].compare(tiles[tileId2].sides[sideId2]) == 0 || tiles[tileId].sides[sideId].compare(tiles[tileId2].reversedSides[sideId2]) == 0){
            //cout << tiles[tileId].id << ":" << sideId << " -> " << tiles[tileId2].id << ":" << sideId2 << endl;
            tiles[tileId].matchCount[sideId]++;
          }
        }
      }
    }
  }
  __int64 prod=1;
  for(Tile t: tiles){
    if(t.matchCount[0] + t.matchCount[1] + t.matchCount[2] + t.matchCount[3] == 2)
      prod *= t.id;
  }
  cout << "part 1: " << prod << endl;
}

void Day20::part2(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs=loader.toVectorStr2d({"Tile ", ":"});
  vector<Tile> tiles;
  int id;
  vector<string> input;
  bool newTile=true;
  for(vector<string> vs:vvs){
    if(newTile){
      id = stoi(vs[0]);
      newTile=false;
    }else if(vs.size() == 0){
        newTile=true;
        tiles.push_back(Tile(id, input));
        input.clear();
    } else{
      input.push_back(vs[0]);
    }
  }
  char biggerPicture[8*12][8*12];
  vector<Tile*> firstRow;
  firstRow.push_back(&(tiles[17]));
  bool firstRowDone=false;
  while(!firstRowDone){
    char rightSide[10];
    for(int i=0; i<10; i++)
      rightSide[i] = firstRow.back()->pic[9-i][9];
    int tileId;
    for(tileId=0; tileId<(int)tiles.size(); tileId++){
      if(tiles[tileId].id != firstRow.back()->id){
        int rot, dir, rev;
        tie(dir, rev) = tiles[tileId].matchSide(rightSide);
        if(dir != NO_SIDE){
          firstRow.push_back(&(tiles[tileId]));
          switch(dir){
            case TOP: rot = 3; break;
            case RIGHT: rot = 2; break;
            case BOTTOM: rot = 1; break;
            case LEFT: rot = 0; break;
          }
          tiles[tileId].manipulate(rot, NOT_REVERSED, rev);
          break;
        }
      }
    }
    if(tileId == (int)tiles.size())
      firstRowDone = true;
  }
  for(int tileCol=0; tileCol<(int)firstRow.size(); tileCol++){
    bool colDone=false;
    Tile* currentCol = firstRow[tileCol];
    for(int y=0; y<8; y++){
      for(int x=0; x<8; x++){
        biggerPicture[y][x+8*tileCol] = currentCol->pic[y+1][x+1];
      }
    }
    int row=1;
    while(!colDone){
      char bottomSide[10];
      for(int i=0; i<10; i++)
        bottomSide[i] = currentCol->pic[9][i];
      int tileId;
      for(tileId=0; tileId<(int)tiles.size(); tileId++){
        if(tiles[tileId].id != currentCol->id){
          int rot, dir, rev;
          tie(dir, rev) = tiles[tileId].matchSide(bottomSide);
          if(dir != NO_SIDE){
            currentCol = &(tiles[tileId]);
            switch(dir){
              case TOP: rot = 0; break;
              case RIGHT: rot = 3; break;
              case BOTTOM: rot = 2; break;
              case LEFT: rot = 1; break;
            }
            tiles[tileId].manipulate(rot, rev, NOT_REVERSED);
            for(int y=0; y<8; y++){
              for(int x=0; x<8; x++){
                biggerPicture[y+8*row][x+8*tileCol] = currentCol->pic[y+1][x+1];
              }
            }
            row++;
            break;
          }
        }
      }
      if(tileId == (int)tiles.size())
        colDone = true;
    }
  }
  Coord dragon[15] = {{0,18},
  {1,0}, {1,5}, {1,6}, {1,11}, {1,12}, {1,17}, {1,18}, {1,19},
  {2,1}, {2,4}, {2,7}, {2,10}, {2,13}, {2,16}};

  int dx=19;
  int dy=2;
  int matches=0;
  for(int rotations=0; rotations<8; rotations++){
    switch(rotations){
      case 1:
      case 3:
      case 5:
      case 7:
        for(int i=0; i<15; i++)
          dragon[i].y = dy-dragon[i].y;
        break;
      case 2:
      case 6:
        for(int i=0; i<15; i++)
          dragon[i].x = dx-dragon[i].x;
        break;
      case 4:
        swap(dx, dy);
        for(int i=0; i<15; i++)
          swap(dragon[i].x, dragon[i].y);
        break;
    }
    for(int y=0; y<8*12-dy; y++){
      for(int x=0; x<8*12-dx; x++){
        bool match=true;
        for(int di=0; match && di<15; di++){
          if(!(biggerPicture[y+dragon[di].y][x+dragon[di].x] == '#' ||
             biggerPicture[y+dragon[di].y][x+dragon[di].x] == 'O')){
            match = false;
          }
        }
        if(match){
          matches++;
          for(int di=0; match && di<15; di++){
            biggerPicture[y+dragon[di].y][x+dragon[di].x] = 'O';
          }
        }
      }
    }
  }
  int hashtagCount=0;
  for(int y=0; y<8*12; y++){
    for(int x=0; x<8*12; x++){
      /*if(x>0 && x%8==0)
        cout << " ";
      cout << biggerPicture[y][x];*/
      if(biggerPicture[y][x] == '#')
        hashtagCount++;
    }
    /*if(y>0 && (y+1)%8==0)
      cout << endl;
    cout << endl;*/
  }
  cout << "part 2: " << hashtagCount << endl;
}

