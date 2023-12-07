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
  vector<Hand*> hands;
  for(string row: input)
    hands.push_back(new Hand(row));

  //Sort hands
  bool swapped = true;
  while(swapped){
    swapped = false;
    for(int i=0; i<(int)hands.size(); i++){
      for(int i2=i+1; i2<(int)hands.size(); i2++){
        if((*(hands[i2])) < (*(hands[i]))){
          swapped = true;
          Hand* tempHand = hands[i];
          hands[i] = hands[i2];
          hands[i2] = tempHand;
        }
      }
    }
  }

  int sum = 0;
  for(int i=0; i<(int)hands.size(); i++){
    sum += (i+1) * hands[i]->bid();
  }

  cout << "part 1: " << sum << endl;
}

void Day07::part2(string filename){
  InputLoader loader(filename);
  vector<string> input = loader.toVectorStr();
  vector<Hand02*> hands;
  for(string row: input)
    hands.push_back(new Hand02(row));

  //Sort hands
  bool swapped = true;
  while(swapped){
    swapped = false;
    for(int i=0; i<(int)hands.size(); i++){
      for(int i2=i+1; i2<(int)hands.size(); i2++){
        if((*(hands[i2])) < (*(hands[i]))){
          swapped = true;
          Hand02* tempHand = hands[i];
          hands[i] = hands[i2];
          hands[i2] = tempHand;
        }
      }
    }
  }

  int sum = 0;
  for(int i=0; i<(int)hands.size(); i++){
    sum += (i+1) * hands[i]->bid();
  }

  cout << "part 2: " << sum << endl;
}

bool Hand::operator<(const Hand& other){
  if(_handType < other._handType)
    return true;
  else if(_handType > other._handType)
    return false;
  for(int i=0; i<5; i++){
    int cardA = cardToInt(_cards[i]);
    int cardB = cardToInt(other._cards[i]);
    if(cardA < cardB)
      return true;
    else if(cardA > cardB)
      return false;
  }
  return false;
}

bool Hand::operator>(const Hand& other){
  if(_handType > other._handType)
    return true;
  else if(_handType < other._handType)
    return false;
  for(int i=0; i<5; i++){
    int cardA = cardToInt(_cards[i]);
    int cardB = cardToInt(other._cards[i]);
    if(cardA > cardB)
      return true;
    else if(cardA < cardB)
      return false;
  }
  return false;
}

int Hand::cardToInt(char card){
  if((int)card >= 48 && (int)card <= 57)
    return (int)card -48;
  if(card == 'T')
    return 10;
  if(card == 'J')
    return 11;
  if(card == 'Q')
    return 12;
  if(card == 'K')
    return 13;
  if(card == 'A')
    return 14;
  return 0;
}

void Hand::load(string input){
  vector<string> inputSplit = InputLoader::splitString(input, {" "});
  for(int i=0; i<5; i++)
    _cards[i] = inputSplit[0][i];
  _bid = stoi(inputSplit[1]);
  setHandType();
}

void Hand::setHandType(){
  //Count cards of each type
  int count[5] = {0,0,0,0,0};
  char card[5];
  for(char c: _cards){
    bool found = false;
    int i=0;
    while(i<5 && count[i] > 0){
      if(card[i] == c){
        count[i]++;
        found = true;
      }
      i++;
    }
    if(!found){
      count[i]++;
      card[i] = c;
    }
  }

  //Sort counted cards
  bool swapped = true;
  while(swapped){
    swapped = false;
    for(int i=0; i<5; i++){
      for(int i2=i+1; i2<5; i2++){
        if(count[i2]>count[i]){
          swapped = true;
          char tempChar = card[i];
          int tempInt = count[i];
          card[i] = card[i2];
          count[i] = count[i2];
          card[i2] = tempChar;
          count[i2] = tempInt;
        }
      }
    }
  }

  //Determine type
  if(count[0] == 5)
    _handType = HandType::fiveOfAKind;
  else if(count[0] == 4)
    _handType = HandType::fourOfAKind;
  else if(count[0] == 3 && count[1] == 2)
    _handType = HandType::fullHouse;
  else if(count[0] == 3)
    _handType = HandType::threeOfAKind;
  else if(count[0] == 2 && count[1] == 2)
    _handType = HandType::twoPair;
  else if(count[0] == 2)
    _handType = HandType::onePair;
  else
    _handType = HandType::highCard;
}

int Hand02::cardToInt(char card){
  if((int)card >= 48 && (int)card <= 57)
    return (int)card -48;
  if(card == 'T')
    return 10;
  if(card == 'J')
    return 1;
  if(card == 'Q')
    return 12;
  if(card == 'K')
    return 13;
  if(card == 'A')
    return 14;
  return 0;
}

void Hand02::setHandType(){
  //Count cards of each type
  int count[5] = {0,0,0,0,0};
  char card[5];
  int jokerCount = 0;
  for(char c: _cards){
    if(c == 'J'){
      jokerCount++;
    }else{
      bool found = false;
      int i=0;
      while(i<5 && count[i] > 0){
        if(card[i] == c){
          count[i]++;
          found = true;
        }
        i++;
      }
      if(!found){
        count[i]++;
        card[i] = c;
      }
    }
  }

  //Sort counted cards
  bool swapped = true;
  while(swapped){
    swapped = false;
    for(int i=0; i<5; i++){
      for(int i2=i+1; i2<5; i2++){
        if(count[i2]>count[i]){
          swapped = true;
          char tempChar = card[i];
          int tempInt = count[i];
          card[i] = card[i2];
          count[i] = count[i2];
          card[i2] = tempChar;
          count[i2] = tempInt;
        }
      }
    }
  }

  //Determine type
  if(count[0]+jokerCount == 5)
    _handType = HandType::fiveOfAKind;
  else if(count[0]+jokerCount == 4)
    _handType = HandType::fourOfAKind;
  else if((count[0] == 3 && count[1] == 2) ||
          (count[0] == 3 && count[1] == 1 && jokerCount == 1) ||
          (count[0] == 3 && count[1] == 0 && jokerCount == 2) ||
          (count[0] == 2 && count[1] == 2 && jokerCount == 1) ||
          (count[0] == 2 && count[1] == 1 && jokerCount == 2))
    _handType = HandType::fullHouse;
  else if(count[0]+jokerCount == 3)
    _handType = HandType::threeOfAKind;
  else if((count[0] == 2 && count[1] == 2) ||
          (count[0] == 2 && count[1] == 1 && jokerCount >= 1) ||
          (count[0] == 2 && jokerCount >= 2) ||
          (count[0] == 1 && count[1] == 1 && jokerCount >= 2))
    _handType = HandType::twoPair;
  else if(count[0] == 2 || (count[0] == 1 && jokerCount == 1))
    _handType = HandType::onePair;
  else
    _handType = HandType::highCard;
}
