#ifndef COMMON_H
#define COMMON_H
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class InputLoader
{
  public:
    InputLoader();
    InputLoader(string filename);
    virtual ~InputLoader();
    void resetFile();
    vector<string> splitString(string s, vector<string> delimiters = {", "});
    vector<int> toInt(vector<string> vs);
    string ltrim(string s);
    string rtrim(string s);
    string trim(string s);
    vector<int> toVectorInt();
    vector<vector<int>> toVectorInt2d(vector<string> delimiters = {", "});
    vector<string> toVectorStr();
    vector<vector<string>> toVectorStr2d(vector<string> delimiters = {", "});
    vector<vector<char>> toVectorChar2d();

  protected:

  private:
    ifstream _file;
};

#endif // COMMON_H
