#ifndef POLYMER_H
#define POLYMER_H

#include <string>

using namespace std;

class Polymer
{
  public:
    string line;
    Polymer();
    Polymer(string line);
    virtual ~Polymer();
    void reduce();
    void remove(char r);
  protected:

  private:
};

#endif // POLYMER_H
