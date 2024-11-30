#include "Day03.h"

Day03::Day03()
{
  //ctor
}

Day03::~Day03()
{
  //dtor
}

void Day03::part1(std::string filename){
  InputLoader loader(filename);
  std::vector<char> input = loader.toVectorChar();
  Point2D p(0,0);
  std::set<Point2D> points;
  points.insert(p);
  for(char c:input){
    if(c == '<')
      p = p + Point2D(-1, 0);
    if(c == '>')
      p = p + Point2D(1, 0);
    if(c == '^')
      p = p + Point2D(0, -1);
    if(c == 'v')
      p = p + Point2D(0, 1);
    points.insert(p);
  }
  std::cout << "part 1: " << points.size() << std::endl;
}

void Day03::part2(std::string filename){
  InputLoader loader(filename);
  std::vector<char> input = loader.toVectorChar();
  Point2D p[2];
  p[0] = Point2D(0,0);
  p[1] = Point2D(0,0);
  std::set<Point2D> points;
  points.insert(p[0]);
  int turn = 0;
  for(char c:input){
    if(c == '<')
      p[turn] = p[turn] + Point2D(-1, 0);
    if(c == '>')
      p[turn] = p[turn] + Point2D(1, 0);
    if(c == '^')
      p[turn] = p[turn] + Point2D(0, -1);
    if(c == 'v')
      p[turn] = p[turn] + Point2D(0, 1);
    points.insert(p[turn]);
    turn = 1-turn;
  }
  std::cout << "part 2: " << points.size() << std::endl;}
