#include "Day22.h"

Day22::Day22()
{
  //ctor
}

Day22::~Day22()
{
  //dtor
}

void Day22::part1(string filename){
  InputLoader loader(filename);
  vector<int> deck1 = {26,14,6,34,37,9,17,39,4,5,1,8,49,16,18,47,20,31,23,19,35,41,28,15,44};
  vector<int> deck2 = {7,2,10,25,29,46,40,45,11,50,42,24,38,13,36,22,33,3,43,21,48,30,32,12,27};
  while(deck1.size()>0 && deck2.size()>0){
    if(deck1[0] > deck2[0]){
      deck1.push_back(deck1[0]);
      deck1.push_back(deck2[0]);
    }else{
      deck2.push_back(deck2[0]);
      deck2.push_back(deck1[0]);
    }
    deck1.erase(deck1.begin());
    deck2.erase(deck2.begin());
  }
  vector<int> winner;
  if(deck1.size()>0)
    winner=deck1;
  else
    winner=deck2;
  __int64 sum=0;
  __int64 digits = winner.size();
  for(int i=0; i<digits; i++){
    sum += winner[i] * (digits-i);
  }
  cout << "part 1: " << sum << endl;
}

void Day22::part2(string filename){
  InputLoader loader(filename);
  vector<int> deck1 = {26,14,6,34,37,9,17,39,4,5,1,8,49,16,18,47,20,31,23,19,35,41,28,15,44};
  vector<int> deck2 = {7,2,10,25,29,46,40,45,11,50,42,24,38,13,36,22,33,3,43,21,48,30,32,12,27};
  /*deck1={43,19};
  deck2={2,29,14};*/
  runGame(deck1, deck2, {});
  cout << "part 2: " << winnerScore << endl;
}

int Day22::runGame(vector<int> deck1, vector<int> deck2, vector<int> rounds){
  /*cout << "runGame({";
  bool first=true;
  for(int d:deck1){
    if(!first)
      cout << ",";
    first = false;
    cout << d;
  }
  cout << "},{";
  first=true;
  for(int d:deck2){
    if(!first)
      cout << ",";
    first = false;
    cout << d;
  }
  cout << "})" << endl;*/
  vector<vector<int>> allDeck1;
  vector<vector<int>> allDeck2;
  allDeck1.push_back(deck1);
  allDeck2.push_back(deck2);

  int totalWinner=0;
  rounds.push_back(0);
  while(totalWinner==0){
    rounds.back()++;
    int winner;
    if((int)deck1.size() > deck1[0] && (int)deck2.size() > deck2[0]){
      winner=runGame(vector<int>(deck1.begin()+1, deck1.begin()+deck1[0]+1),vector<int>(deck2.begin()+1, deck2.begin()+deck2[0]+1), rounds);
    }else{
      if(deck1[0]>deck2[0])
        winner = 1;
      else
        winner = 2;
    }
    if(winner == 1){
      deck1.push_back(deck1[0]);
      deck1.push_back(deck2[0]);
    }else{
      deck2.push_back(deck2[0]);
      deck2.push_back(deck1[0]);
    }
    deck1.erase(deck1.begin());
    deck2.erase(deck2.begin());
    if(deck2.size() == 0 || rounds.back()>20000)
      totalWinner = 1;
    if(deck1.size() == 0)
      totalWinner = 2;
    for(int deckId=0; totalWinner == 0 && deckId<(int)allDeck1.size(); deckId++){
      bool match=true;
      if(deck1.size() != allDeck1[deckId].size() || deck2.size() != allDeck2[deckId].size())
        match=false;
      for(int cardId=0; match && cardId<(int)deck1.size(); cardId++){
        if(deck1[cardId] != allDeck1[deckId][cardId])
          match = false;
      }
      for(int cardId=0; match && cardId<(int)deck2.size(); cardId++){
        if(deck2[cardId] != allDeck2[deckId][cardId])
          match = false;
      }
      if(match)
        totalWinner = 1;
    }
    allDeck1.push_back(deck1);
    allDeck2.push_back(deck2);
    if(false && rounds[0]==331){
      for(int r:rounds){
        cout << " " << r;
      }
      cout << ": " << totalWinner << endl;
    }
    if(false && rounds.size() == 3 && rounds[0]==331 && rounds[1] == 216){
      for(int d:deck1)
        cout << " " << d;
      cout << ",";
      for(int d:deck2)
        cout << " " << d;
      cout << endl;
    }
  }
  vector<int> winnerDeck;
  if(totalWinner == 1)
    winnerDeck=deck1;
  else
    winnerDeck=deck2;
  __int64 digits = winnerDeck.size();
  winnerScore = 0;
  for(int i=0; i<digits; i++)
    winnerScore += winnerDeck[i] * (digits-i);
  //cout << "TotalWinner: " << totalWinner << " (" << rounds.back() << ")" << endl;
  return totalWinner;
}
