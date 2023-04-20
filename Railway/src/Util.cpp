#include "Util.h"

vector<string> splitString(string s, vector<string> delimiters){
  vector<string> ret;
  bool done=false;
  int delimLen;
  while(!done){
    size_t pos=string::npos;
    for(string d : delimiters){
      if(s.find(d)<pos){
        pos=s.find(d);
        delimLen=d.length();
      }
    }
    if(pos == string::npos)
      done=true;
    else{
      if(pos>0)
        ret.push_back(s.substr(0, pos));
      s.erase(0, pos + delimLen);
    }
  }
  if(s.length()>0)
    ret.push_back(s);
  return ret;
}
