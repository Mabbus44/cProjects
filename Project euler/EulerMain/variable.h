#include <string>
using namespace std;

#ifndef VARIABLE
#define VARIABLE

class Variable{
private:
  Variable* content;
  string type;
  string name;
public:
  Variable();
  Variable(string name, string type);
  bool add(string name, string type);
  bool insert(string name, string type);
  bool set(string type);
  bool rename(string name);
  bool checkName(string name);
  bool checkType(string type);
  string getType();
  string getName();
  Variable* next;
  Variable* prev;
};

#endif // VARIABLE
