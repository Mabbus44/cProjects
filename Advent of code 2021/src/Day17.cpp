#include "Day17.h"

Day17::Day17()
{
  //ctor
}

Day17::~Day17()
{
  //dtor
}


void Day17::part1(string filename){
  InputLoader loader(filename);
  int highestY = 0;
  int xVel=6, yVel=0;
  int result;

  while(yVel<10000){
    shoot(xVel,yVel);
    //cout << "shoot (" << xVel << ", " << yVel << ")" << endl;
    result = STILL_POSSIBLE;
    while(result==STILL_POSSIBLE){
      travel();
      //cout << "(" << x << ", " << y << ")";
      result = hitTarget();
      /*switch(result){
        case UNDERSHOOT:
          cout << "OVERSHOOT" << endl;
          break;
        case STILL_POSSIBLE:
          cout << "STILL_POSSIBLE" << endl;
          break;
        case HIT:
          cout << "HIT" << endl;
          break;
        case OVERSHOOT:
          cout << "OVERSHOOT" << endl;
          break;
        case UNKNOWN_MISS:
          cout << "UNKNOWN_MISS" << endl;
          break;
      }*/
    }
    if(result==OVERSHOOT){
      xVel=5;
      yVel++;
    }else if(result == HIT){
      highestY = yVel;
      cout << highestY << endl;
      xVel=5;
      yVel++;
    } else{
      xVel++;
    }
  }
  if(highestY%2==0)
    highestY = highestY/2*(highestY+1);
  else
    highestY = highestY/2*(highestY+1) + (highestY+1)/2;

  cout << "Part 1: " << highestY << endl;
}

void Day17::part2(string filename){
  InputLoader loader(filename);
  int hits = 0;
  int xVel=5, yVel=-300;
  int result;

  while(yVel<267){
    shoot(xVel,yVel);
    //cout << "shoot (" << xVel << ", " << yVel << ")" << endl;
    result = STILL_POSSIBLE;
    while(result==STILL_POSSIBLE){
      travel();
      //cout << "(" << x << ", " << y << ")";
      result = hitTarget();
      /*switch(result){
        case UNDERSHOOT:
          cout << "OVERSHOOT" << endl;
          break;
        case STILL_POSSIBLE:
          cout << "STILL_POSSIBLE" << endl;
          break;
        case HIT:
          cout << "HIT" << endl;
          break;
        case OVERSHOOT:
          cout << "OVERSHOOT" << endl;
          break;
        case UNKNOWN_MISS:
          cout << "UNKNOWN_MISS" << endl;
          break;
      }*/
    }
    if(result==OVERSHOOT){
      cout << "(" << xVel << ", " << yVel << ") OVERSHOOT" << endl;
      xVel=5;
      yVel++;
    }else if(result == HIT){
      cout << "(" << xVel << ", " << yVel << ") HIT" << endl;
      hits++;
      xVel++;
    } else{
      cout << "(" << xVel << ", " << yVel << ") MISS" << endl;
      xVel++;
      if(xVel>=targetXMax){
        xVel=5;
        yVel++;
      }
    }
  }
  cout << "Part 2: " << hits << endl;
}

int Day17::hitTarget(){
  //cout << y << " " << targetYMin << " " << targetYMax << " " << x << " " << targetXMin << " " << targetXMax << endl;
  if(y<targetYMin){
    if(x<targetXMin)
      return UNDERSHOOT;
    return UNKNOWN_MISS;
  }
  if(y>targetYMax){
    if(x>targetXMax)
      return OVERSHOOT;
    return STILL_POSSIBLE;
  }
  if(x>=targetXMin && x<=targetXMax)
    return HIT;
  return STILL_POSSIBLE;
}

void Day17::travel(){
  x += speedX;
  y += speedY;
  if(speedX>0)
    speedX--;
  else if(speedX<0)
    speedX++;
  speedY--;
}
