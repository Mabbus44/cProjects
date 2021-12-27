#include "Day21.h"

Day21::Day21()
{
  //ctor
}

Day21::~Day21()
{
  //dtor
}

void Day21::part1(string filename){
  InputLoader loader(filename);
  pos[0]=4;
  pos[1]=7;
  score[0] = 0;
  score[1] = 0;
  die=0;
  int player=0;
  int64_t rolls=0;
  while(score[0]<1000 && score[1]<1000){
    int64_t inc =rollDie(3);
    pos[player] += inc;
    pos[player] = pos[player]%10;
    if(pos[player]==0)
      pos[player] = 10;
    score[player] += pos[player];
    rolls+=3;
    /*cout << "Player " << player+1 << " rolls" << endl;
    cout << "rools: " << rolls << endl;
    cout << "inc: " << inc << endl;
    cout << "pos: " << pos[0] << " " << pos[1] << endl;
    cout << "score: " << score[0] << " " << score[1] << endl;
    cout << endl;*/
    player = 1-player;
  }
  cout << "Part 1: " << score[player]*rolls << endl;
}

void Day21::part2(string filename){
  InputLoader loader(filename);
  //3 = 1 1 1
  //4 = 1 1 2
  //5 = 1 1 3
  //4 = 1 2 1
  //5 = 1 2 2
  //6 = 1 2 3
  //5 = 1 3 1
  //6 = 1 3 2
  //7 = 1 3 3

  //4 = 2 1 1
  //5 = 2 1 2
  //6 = 2 1 3
  //5 = 2 2 1
  //6 = 2 2 2
  //7 = 2 2 3
  //6 = 2 3 1
  //7 = 2 3 2
  //8 = 2 3 3

  //5 = 3 1 1
  //6 = 3 1 2
  //7 = 3 1 3
  //6 = 3 2 1
  //7 = 3 2 2
  //8 = 3 2 3
  //7 = 3 3 1
  //8 = 3 3 2
  //9 = 3 3 3

  //3 = 1 {111}
  //4 = 3 {112}{121}{211}
  //5 = 6 {113}{131}{311}{122}{212}{221}
  //6 = 7 {123}{132}{213}{231}{312}{321}{222}
  //7 = 6 {133}{313}{331}{223}{232}{322}
  //8 = 3 {233}{323}{332}
  //9 = 1 {333}

  int rolls=0;
  vector<GameState> states[2];
  states[0].push_back(GameState(4,7,0,0,1));
  int state=0;
  int64_t wins[2] = {0,0};
  int64_t newStates[10] = {0,0,0,1,3,6,7,6,3,1};
  int player = 0;
  int newPos;
  int newScore;
  while(states[state].size()>0){
    /*cout << "state: " << state << endl;
    cout << "rolls: " << rolls << endl;
    cout << "player: " << player << endl;
    cout << "states[0]: " << endl;
    for(GameState& g:states[0])
      cout << "    " << g.pos[0] << " " << g.pos[1] << " " << g.score[0] << " " << g.score[1] << " " << g.count << endl;
    cout << "states[1]: " << endl;
    for(GameState& g:states[1])
      cout << "    " << g.pos[0] << " " << g.pos[1] << " " << g.score[0] << " " << g.score[1] << " " << g.count << endl;
*/
    states[1-state].clear();
    for(GameState& g:states[state]){
      if(player==0){
        for(int i=3; i<10; i++){
          newPos = (g.pos[0]+i)%10;
          if(newPos==0)
            newPos = 10;
          newScore = g.score[0]+newPos;
          if(newScore>=21)
            wins[0]+=(g.count*newStates[i]);
          else
            states[1-state].push_back(GameState(newPos, g.pos[1], newScore, g.score[1], g.count*newStates[i]));
        }
      }else{
        for(int i=3; i<10; i++){
          newPos = (g.pos[1]+i)%10;
          if(newPos==0)
            newPos = 10;
          newScore = g.score[1]+newPos;
          if(newScore>=21)
            wins[1]+=(g.count*newStates[i]);
          else
          states[1-state].push_back(GameState(g.pos[0], newPos, g.score[0], newScore, g.count*newStates[i]));
        }
      }
    }
    rolls+=3;
    player = 1-player;
    state = 1-state;
    int lowScore=21;
    int highScore=0;
    cout << "state: " << state << endl;
    cout << "size: " << states[state].size() << endl;
    for(int i=0; i<(int)states[state].size(); i++){
      if(states[state][i].score[0]<lowScore && states[state][i].score[0]>states[state][i].score[1])
        lowScore = states[state][i].score[0];
      if(states[state][i].score[1]<lowScore && states[state][i].score[0]<states[state][i].score[1])
        lowScore = states[state][i].score[1];
      if(states[state][i].score[0]>highScore)
        highScore = states[state][i].score[0];
      if(states[state][i].score[1]>highScore)
        lowScore = states[state][i].score[1];
      if(states[state][i].score[0]>=21){
        wins[0] += states[state][i].count;
        states[state].erase(states[state].begin()+i);
        i--;
      }
      if(states[state][i].score[1]>=21){
        wins[1] += states[state][i].count;
        states[state].erase(states[state].begin()+i);
        i--;
      }
    }
    cout << "size: " << states[state].size() << endl;
    cout << lowScore << "-" << highScore << endl << endl;
  }
  int64_t moreWins;
  if(wins[0]>wins[1])
    moreWins=wins[0];
  else
    moreWins=wins[1];
  cout << "Part 2: " << moreWins << endl;
}

int64_t Day21::rollDie(int times){
  int64_t sum=0;
  for(int i=0; i<3; i++){
    die++;
    if(die>100)
      die=1;
    sum+=die;
  }
  return sum;
}
