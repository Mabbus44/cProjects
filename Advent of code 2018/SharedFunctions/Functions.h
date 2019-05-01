#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <fstream>
#include <string>
#include <list>

using namespace std;

int nextNumber(string line, unsigned int& index, bool first = false);
bool isNumber(char letter);

#endif // FUNCTIONS_H_INCLUDED
