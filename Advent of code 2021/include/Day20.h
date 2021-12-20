#ifndef DAY20_H
#define DAY20_H
#include <iostream>
#include <vector>
#include "Common.h"

enum {UP, DOWN, LEFT, RIGHT};

class FloorImage{
  public:
    FloorImage(){}
    virtual ~FloorImage(){}
    void loadTranslationSheet(string input);
    void loadFloorImage(vector<string> input);
    void output();
    void addRow(int dir);
    bool getPixel(int x, int y);
    bool translatePixel(int x, int y);
    void translatePicture();
    int countPixels();
    vector<vector<bool>> fImg;
    vector<bool> translationSheet;
    bool outsideVal=false;
};
class Day20
{
  public:
    Day20();
    virtual ~Day20();
    void part1(string filename);
    void part2(string filename);

  protected:

  private:
};

#endif // DAY20_H
