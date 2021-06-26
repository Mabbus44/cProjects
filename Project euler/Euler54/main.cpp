#include <iostream>
#include <fstream>
#include <string>

class Card{
private:
public:
  int value;
  int suit;
  
  bool setCard(char* card);
};




class Hand{
private:
  void sort();
public:
  bool onePair;
  bool twoPairs;
  bool threeOfAKind;
  bool straight;
  bool flush;
  bool fullHouse;
  bool fourOfAKind;
  bool straightFlush;
  bool royalFlush;

  int onePairHiCard;
  int twoPairsHiCard;
  int twoPairsHiHiCard;
  int threeOfAKindHiCard;
  int straightHiCard;
  int fullHouseHiCard;
  int fullHouseHiHiCard;
  int fourOfAKindHiCard;
  int straightFlushHiCard;
  Card cards[5];
  bool beat(Hand* other);
  void evaluate();
  bool output();
};




bool Card::setCard(char* card){
  switch(card[0])
  {
    case 'A':
      value=14;
      break;
    case '2':
      value=2;
      break;
    case '3':
      value=3;
      break;
    case '4':
      value=4;
      break;
    case '5':
      value=5;
      break;
    case '6':
      value=6;
      break;
    case '7':
      value=7;
      break; 
    case '8':
      value=8;
      break;
    case '9':
      value=9;
      break;
    case 'T':
      value=10;
      break;
    case 'J':
      value=11;
      break;
    case 'Q':
      value=12;
      break;
    case 'K':
      value=13;
      break;
  }
  switch(card[1])
  {
    case 'H':
      suit=0;
      break;
    case 'D':
      suit=1;
      break;
    case 'C':
      suit=2;
      break;
    case 'S':
      suit=3;
      break;
  } 
  return true;
}





void Hand::sort(){
  bool done=false;
  while(!done){							//repeat untli done
    done=true;							//defaul done
    for(int i=0; i<4; i++){
      if(cards[i].value > cards[i+1].value){			//check if a bigger card is before a smaller card
	int a=cards[i].value;					//if so swap them
	cards[i].value=cards[i+1].value;
	cards[i+1].value=a;
	done=false;						//and restart sorting
      }
    }
  }
}
  
  
  
  
  
bool Hand::beat(Hand* other){
  evaluate();
  other->evaluate();
  //************************************ Royal flush ****************************************
  if(royalFlush && !other->royalFlush)
    return true;
  if(!royalFlush && other->royalFlush)
    return false;
  if(royalFlush && other->royalFlush)
    std::cout << "UNDECIDED CASE!!!";
  //************************************ Straight flush ****************************************
  if(straightFlush && !other->straightFlush)
    return true;
  if(!straightFlush && other->straightFlush)
    return false;
  if(straightFlush && other->straightFlush){
    if(straightFlushHiCard>other->straightFlushHiCard)
      return true;
    if(straightFlushHiCard<other->straightFlushHiCard)
      return false;
    std::cout << "UNDECIDED CASE!!!";
  }
  //************************************ Four of a kind ****************************************
  if(fourOfAKind && !other->fourOfAKind)
    return true;
  if(!fourOfAKind && other->fourOfAKind)
    return false;
  if(fourOfAKind && other->fourOfAKind){
    if(fourOfAKindHiCard>other->fourOfAKindHiCard)
      return true;
    if(fourOfAKindHiCard<other->fourOfAKindHiCard)
      return false;
    for(int i=4; i>=0; i--){
      if(cards[i].value>other->cards[i].value)
	return true;
      if(cards[i].value<other->cards[i].value)
	return false;
    }
    std::cout << "UNDECIDED CASE!!!";
  }
  //************************************ Full house ****************************************
  if(fullHouse && !other->fullHouse)
    return true;
  if(!fullHouse && other->fullHouse)
    return false;
  if(fullHouse && other->fullHouse){
    if(fullHouseHiHiCard>other->fullHouseHiHiCard)
      return true;
    if(fullHouseHiHiCard<other->fullHouseHiHiCard)
      return false;
    if(fullHouseHiCard>other->fullHouseHiCard)
      return true;
    if(fullHouseHiCard<other->fullHouseHiCard)
      return false;
    std::cout << "UNDECIDED CASE!!!";
  }
  //************************************ Flush ****************************************
  if(flush && !other->flush)
    return true;
  if(!flush && other->flush)
    return false;
  if(flush && other->flush){
    std::cout << "UNDECIDED CASE!!!";
  }
  //************************************ Straight ****************************************
  if(straight && !other->straight)
    return true;
  if(!straight && other->straight)
    return false;
  if(straight && other->straight){
    if(straightHiCard>other->straightHiCard)
      return true;
    if(straightHiCard<other->straightHiCard)
      return false;
    std::cout << "UNDECIDED CASE!!!";
  }
  //************************************ Three of a kind ****************************************
  if(threeOfAKind && !other->threeOfAKind)
    return true;
  if(!threeOfAKind && other->threeOfAKind)
    return false;
  if(threeOfAKind && other->threeOfAKind){
    if(threeOfAKindHiCard>other->threeOfAKindHiCard)
      return true;
    if(threeOfAKindHiCard<other->threeOfAKindHiCard)
      return false;
    for(int i=4; i>=0; i--){
      if(cards[i].value>other->cards[i].value)
	return true;
      if(cards[i].value<other->cards[i].value)
	return false;
    }
    std::cout << "UNDECIDED CASE!!!";
  }
  //************************************ Two pairs ****************************************
  if(twoPairs && !other->twoPairs)
    return true;
  if(!twoPairs && other->twoPairs)
    return false;
  if(twoPairs && other->twoPairs){
    if(twoPairsHiHiCard>other->twoPairsHiHiCard)
      return true;
    if(twoPairsHiHiCard<other->twoPairsHiHiCard)
      return false;
    if(twoPairsHiCard>other->twoPairsHiCard)
      return true;
    if(twoPairsHiCard<other->twoPairsHiCard)
      return false;
    for(int i=4; i>=0; i--){
      if(cards[i].value>other->cards[i].value)
	return true;
      if(cards[i].value<other->cards[i].value)
	return false;
    }
    std::cout << "UNDECIDED CASE!!!";
  }
  //************************************ Pair ****************************************
  if(onePair && !other->onePair)
    return true;
  if(!onePair && other->onePair)
    return false;
  if(onePair && other->onePair){
    if(onePairHiCard>other->onePairHiCard)
      return true;
    if(onePairHiCard<other->onePairHiCard)
      return false;
    for(int i=4; i>=0; i--){
      if(cards[i].value>other->cards[i].value)
	return true;
      if(cards[i].value<other->cards[i].value)
	return false;
    }
    std::cout << "UNDECIDED CASE!!!";
  }
  //************************************ High card ****************************************
  for(int i=4; i>=0; i--){
    if(cards[i].value>other->cards[i].value)
      return true;
    if(cards[i].value<other->cards[i].value)
      return false;
  }
  std::cout << "UNDECIDED CASE!!!";
}





void Hand::evaluate(){
  bool gotIt;
  sort();							//sort hand from smallest to biggest card
  //************************************ Royal flush ****************************************
  gotIt=true;
  for(int i=0; i<5; i++){
    if(cards[i].value!=i+10)					//10 11 12 13 14
      gotIt=false;
    if(cards[i].suit!=cards[0].suit)				//all suits the same
      gotIt=false;
  }
  royalFlush=gotIt;
  //************************************ Straight flush ****************************************
  gotIt=true;
  for(int i=1; i<5; i++){
    if(cards[i].value!=cards[i-1].value+1)			//a a+1 a+2 a+3 a+4
      gotIt=false;
  }
  straightFlushHiCard=cards[4].value;				//cards[4] is biggest
  if(cards[0].value==2 && cards[1].value==3 && cards[2].value==4 && cards[3].value==5 && cards[4].value==14){  //or 2 3 4 5 14
    straightFlushHiCard=cards[3].value;				//cards[3] is biggest
    gotIt=true;
  }
  for(int i=1; i<5; i++){					//all suits the same
    if(cards[i].suit!=cards[0].suit)
      gotIt=false;
  }
  straightFlush=gotIt;
  //************************************ Four of a kind ****************************************
  gotIt=true;
  for(int i=0; i<3; i++){
    if(cards[i].value!=cards[i+1].value)				//v0=v1=v2=v3
      gotIt=false;
  }
  if(!gotIt){
    gotIt=true;
    for(int i=1; i<4; i++){
      if(cards[i].value!=cards[i+1].value)			//v1=v2=v3=v4
	gotIt=false;
    }
  }
  fourOfAKindHiCard=cards[3].value;				//cards[1,2,3] is biggest
  fourOfAKind=gotIt;
  //************************************ Full house ****************************************
  gotIt=false;
  if(cards[0].value==cards[1].value && cards[2].value==cards[3].value && cards[2].value==cards[4].value){	//a a b b b
    gotIt=true;
    fullHouseHiCard=cards[0].value;
    fullHouseHiHiCard=cards[2].value;
  }
  if(cards[0].value==cards[1].value && cards[0].value==cards[2].value && cards[3].value==cards[4].value){	//a a a b b
    gotIt=true;
    fullHouseHiCard=cards[3].value;
    fullHouseHiHiCard=cards[0].value;
  }
  fullHouse=gotIt;
  //************************************ Flush ****************************************
  gotIt=true;
  for(int i=1; i<5; i++){					//all suits the same
    if(cards[i].suit!=cards[0].suit)
      gotIt=false;
  }
  flush=gotIt;
  //************************************ Straight ****************************************
  gotIt=true;
  for(int i=1; i<5; i++){
    if(cards[i].value!=cards[i-1].value+1)			//a a+1 a+2 a+3 a+4
      gotIt=false;
  }
  straightHiCard=cards[4].value;					//cards[4] is biggest
  if(cards[0].value==2 && cards[1].value==3 && cards[2].value==4 && cards[3].value==5 && cards[4].value==14){  //or 2 3 4 5 14
    straightHiCard=cards[3].value;					//cards[3] is biggest
    gotIt=true;
  }
  straight=gotIt;  
  //************************************ Three of a kind ****************************************
  gotIt=true;
  for(int i=0; i<2; i++){
    if(cards[i].value!=cards[i+1].value)				//a a a x x
      gotIt=false;
  }
  if(!gotIt){
    gotIt=true;
    for(int i=1; i<3; i++){
      if(cards[i].value!=cards[i+1].value)			//x a a a x
	gotIt=false;
    }
  }
  if(!gotIt){
    gotIt=true;
    for(int i=2; i<4; i++){
      if(cards[i].value!=cards[i+1].value)			//x x a a a
	gotIt=false;
    }
  }
  threeOfAKindHiCard=cards[2].value;
  threeOfAKind=gotIt;
  //************************************ Two pairs ****************************************
  gotIt=false;
  if(cards[0].value==cards[1].value && cards[2].value==cards[3].value){	//a a b b x
    gotIt=true;
    twoPairsHiCard=cards[0].value;
    twoPairsHiHiCard=cards[2].value;
  }
  if(cards[0].value==cards[1].value && cards[3].value==cards[4].value){	//a a x b b
    gotIt=true;
    twoPairsHiCard=cards[0].value;
    twoPairsHiHiCard=cards[3].value;
  }
  if(cards[1].value==cards[2].value && cards[3].value==cards[4].value){	//x a a b b
    gotIt=true;
    twoPairsHiCard=cards[1].value;
    twoPairsHiHiCard=cards[3].value;
  }
  twoPairs=gotIt;
  //************************************ Pair ****************************************
  gotIt=false;
  for(int i=0; i<4 && !gotIt; i++){
    if(cards[i].value==cards[i+1].value){				//two cards of the same value
      onePairHiCard=cards[i].value;
      gotIt=true;
    }
  }
  onePair=gotIt;
}





bool Hand::output(){
  for(int i=0; i<5; i++)
    std::cout << cards[i].suit << "-" << cards[i].value << "   ";
  std::cout << std::endl;
  if(royalFlush){
    std::cout << "Royal Flush" << std::endl;
    return true;
  }
  if(straightFlush){
    std::cout << "Straight Flush, Hicard = " << straightFlushHiCard << std::endl;
    return true;
  }
  if(fourOfAKind){
    std::cout << "Four Of A Kind, Hicard = " << fourOfAKindHiCard << std::endl;
    return true;
  }
  if(fullHouse){
    std::cout << "Full House, HiHicard = " << fullHouseHiHiCard << ", Hicard = " << fullHouseHiCard << std::endl;
    return true;
  }
  if(flush){
    std::cout << "Flush" << std::endl;
    return true;
  }
  if(straight){
    std::cout << "Straight, Hicard = " << straightHiCard << std::endl;
    return true;
  }
  if(threeOfAKind){
    std::cout << "Three Of A Kind, Hicard = " << threeOfAKindHiCard << std::endl;
    return true;
  }
  if(twoPairs){
    std::cout << "Two Pairs, HiHicard = " << twoPairsHiHiCard << ", Hicard = " << twoPairsHiCard << std::endl;
    return true;
  }
  if(onePair){
    std::cout << "One Pair, Hicard = " << onePairHiCard << std::endl;
    return true;
  }
  return true;
}





int main(int argc, char **argv) {
  std::ifstream words;							//File
  char* card = new char[2];						//Card from file
  Hand player1, player2;						//Two pokerhands
  int p1Score=0;							//Player1 score
  words.open("poker.txt");  
  
  for(int i2=0; i2<1000; i2++){
    for(int i=0; i<5; i++){						//Read player 1 cards
      words.read(card,2);							//Read card
      player1.cards[i].setCard(card);					//Set card
      words.read(card,1);							//Toss away space or newline
    }
    for(int i=0; i<5; i++){						//Read player 1 cards
      words.read(card,2);							//Read card
      player2.cards[i].setCard(card);					//Set card
      words.read(card,1);							//Toss away space or newline
    }

    if(player1.beat(&player2)){
      if(player1.threeOfAKind || player2.threeOfAKind)
	std::cout << std::endl << std::endl << "Player one won" << std::endl;
      p1Score++;
    }
    else{
      if(player1.threeOfAKind || player2.threeOfAKind)
	std::cout << std::endl << std::endl << "Player two won" << std::endl;
    }
    if(player1.threeOfAKind || player2.threeOfAKind){
      player1.output();
      std::cout << std::endl;
      player2.output();
    }
  }
  std::cout << std::endl << "Player one won " << p1Score << " times" << std::endl;

  delete[] card;
  words.close();
  return 0;
}