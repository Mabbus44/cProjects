#include "Common.h"

InputLoader::InputLoader(string filename)
{
  _file.open(filename);
  if(!_file)
    cout << "failed to open file (" << filename << ")" << endl;
}

InputLoader::~InputLoader()
{
  _file.close();
}

void InputLoader::resetFile(){
  _file.clear();
  _file.seekg(0);
}

vector<string> InputLoader::splitString(string s, vector<string> delimiters){
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

vector<int> InputLoader::toInt(vector<string> vs){
  vector<int> vi;
  for(string s:vs){
    try{
      vi.push_back(stoi(trim(s)));
    }catch(...){
      cout << "could not convert \"" << trim(s) << "\" to int" << endl;
    }
  }
  return vi;
}

vector<int64_t> InputLoader::toBigInt(vector<string> vs){
  vector<int64_t> vi;
  for(string s:vs){
    try{
      vi.push_back(stoull(trim(s)));
    }catch(...){
      cout << "could not convert \"" << trim(s) << "\" to int" << endl;
    }
  }
  return vi;
}

string InputLoader::ltrim(string s) {
  s.erase(s.begin(), find_if(s.begin(), s.end(),
    not1(ptr_fun<int, int>(isspace))));
  return s;
}

string InputLoader::rtrim(string s) {
  s.erase(find_if(s.rbegin(), s.rend(),
    not1(ptr_fun<int, int>(isspace))).base(), s.end());
  return s;
}

string InputLoader::trim(string s) {
  return ltrim(rtrim(s));
}

vector<int> InputLoader::toVectorInt(){
  vector<int> ret;
  int i;
  while(_file >> i)
    ret.push_back(i);
  return ret;
}

vector<vector<int>> InputLoader::toVectorInt2d(vector<string> delimiters){
  vector<vector<int>> ret;
  string line;
  while(getline(_file, line))
    ret.push_back(toInt(splitString(line, delimiters)));
  return ret;
}

vector<string> InputLoader::toVectorStr(){
  vector<string> ret;
  string line;
  while(getline(_file, line))
    ret.push_back(line);
  return ret;
}

vector<vector<string>> InputLoader::toVectorStr2d(vector<string> delimiters){
  vector<vector<string>> ret;
  string line;
  while(getline(_file, line))
    ret.push_back(splitString(line, delimiters));
  return ret;
}

vector<vector<char>> InputLoader::toVectorChar2d(){
  vector<vector<char>> ret;
  string line;
  while(getline(_file, line))
    ret.push_back(vector<char>(line.begin(), line.end()));
  return ret;
}
