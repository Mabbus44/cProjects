#include "Common.h"

InputLoader::InputLoader(std::string filename)
{
  _file.open(filename);
  if(!_file)
    std::cout << "failed to open file (" << filename << ")" << std::endl;
}

InputLoader::~InputLoader()
{
  _file.close();
}

void InputLoader::resetFile(){
  _file.clear();
  _file.seekg(0);
}

std::vector<std::string> InputLoader::splitString(std::string s, std::vector<std::string> delimiters){
  std::vector<std::string> ret;
  bool done=false;
  int delimLen;
  while(!done){
    size_t pos=std::string::npos;
    for(std::string d : delimiters){
      if(s.find(d)<pos){
        pos=s.find(d);
        delimLen=d.length();
      }
    }
    if(pos == std::string::npos)
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

std::vector<int> InputLoader::toInt(std::vector<std::string> vs){
  std::vector<int> vi;
  for(std::string s:vs){
    try{
      vi.push_back(stoi(trim(s)));
    }catch(...){
      std::cout << "could not convert \"" << trim(s) << "\" to int" << std::endl;
    }
  }
  return vi;
}

int InputLoader::toSingleInt(std::string s){
  try{
    return stoi(trim(s));
  }catch(...){
    std::cout << "could not convert \"" << trim(s) << "\" to int" << std::endl;
  }
  return 0;
}

std::vector<__int64> InputLoader::toInt64(std::vector<std::string> vs){
  std::vector<__int64> vi;
  for(std::string s:vs){
    char *endChar;
    const char* trimmedString = trim(s).c_str();
    __int64 convertedVal = strtoull(trimmedString, &endChar, 10);
    if(endChar != trimmedString)
      vi.push_back(convertedVal);
    else
      std::cout << "could not convert \"" << trim(s) << "\" to int" << std::endl;
  }
  return vi;
}

std::string InputLoader::ltrim(std::string s) {
  s.erase(s.begin(), find_if(s.begin(), s.end(),
    std::not_fn(isspace)));
  return s;
}

std::string InputLoader::rtrim(std::string s) {
  s.erase(find_if(s.rbegin(), s.rend(),
    std::not_fn(isspace)).base(), s.end());
  return s;
}

std::string InputLoader::trim(std::string s) {
  return ltrim(rtrim(s));
}

std::vector<int> InputLoader::toVectorInt(){
  std::vector<int> ret;
  int i;
  while(_file >> i)
    ret.push_back(i);
  return ret;
}

std::vector<std::vector<int>> InputLoader::toVectorInt2d(std::vector<std::string> delimiters){
  std::vector<std::vector<int>> ret;
  std::string line;
  while(getline(_file, line))
    ret.push_back(toInt(splitString(line, delimiters)));
  return ret;
}

std::vector<std::vector<__int64>> InputLoader::toVectorInt642d(std::vector<std::string> delimiters){
  std::vector<std::vector<__int64>> ret;
  std::string line;
  while(getline(_file, line))
    ret.push_back(toInt64(splitString(line, delimiters)));
  return ret;
}

std::vector<std::string> InputLoader::toVectorStr(){
  std::vector<std::string> ret;
  std::string line;
  while(getline(_file, line))
    ret.push_back(line);
  return ret;
}

std::vector<std::vector<std::string>> InputLoader::toVectorStr2d(std::vector<std::string> delimiters){
  std::vector<std::vector<std::string>> ret;
  std::string line;
  while(getline(_file, line))
    ret.push_back(splitString(line, delimiters));
  return ret;
}

std::vector<char> InputLoader::toVectorChar(){
  std::string  line;
  getline(_file, line);
  return std::vector<char>(line.begin(), line.end());
}

std::vector<std::vector<char>> InputLoader::toVectorChar2d(){
  std::vector<std::vector<char>> ret;
  std::string  line;
  while(getline(_file, line))
    ret.push_back(std::vector<char>(line.begin(), line.end()));
  return ret;
}

void PrimeFactorizer::findNewPrimes(int maxVal){
  int testVal=3;
  if(_primes.size() == 0){
    _primes.push_back(2);
  }else{
    testVal = _primes.back() + 2;
  }
  while(testVal <= maxVal){
    if(isPrime(testVal)){
      _primes.push_back(testVal);
    }
    testVal += 2;
  }
}

bool PrimeFactorizer::isPrime(int num){
  int i=0;
  while(_primes[i] * _primes[i] <= num){
    if(num % _primes[i] == 0)
      return false;
    i++;
    if(i >= (int)_primes.size())
      findNewPrimes(_primes.back() * 10);
  }
  return true;
}

std::vector<int> PrimeFactorizer::factorize(int num){
  std::vector<int> ret;
  int i=0;
  while(_primes[i] * _primes[i] < num){
    if(num % _primes[i] == 0){
      num /= _primes[i];
      ret.push_back(_primes[i]);
    }else{
      i++;
    }
    if(i >= (int)_primes.size()){
      findNewPrimes(_primes.back() * 10);
    }
  }
  if(num>1)
    ret.push_back(num);
  return ret;
}
