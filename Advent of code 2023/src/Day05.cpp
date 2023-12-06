#include "Day05.h"

Day05::Day05()
{
  //ctor
}

Day05::~Day05()
{
  //dtor
}

void Day05::part1(string filename){
  InputLoader loader(filename);
  vector<string> input = loader.toVectorStr();
  vector<__int64> seeds = InputLoader::toInt64(InputLoader::splitString(input[0], {"seeds: ", " "}));
  vector<ConversionCollection> collections;
  int row=1;
  while(row<(int)input.size()){
    while(row<(int)input.size() && ((int)input[row][0] < 48 || (int)input[row][0] > 57)){ //While not numbers
      row++;
    }
    vector<string> collectionInput;
    while(row<(int)input.size() && ((int)input[row][0] >= 48 && (int)input[row][0] <= 57)){ //While numbers
      collectionInput.push_back(input[row]);
      row++;
    }
    if((int)collectionInput.size() > 0)
      collections.push_back(ConversionCollection(collectionInput));
  }
  __int64 minVal = -1;
  for(__int64 seed: seeds){
    __int64 convertedSeed = seed;
    for(ConversionCollection& cc: collections){
      convertedSeed = cc.convert(convertedSeed);
    }
    if(minVal == -1 || convertedSeed < minVal)
      minVal = convertedSeed;
  }
  cout << "part 1: " << minVal << endl;
}

void Day05::part2(string filename){
  InputLoader loader(filename);
  vector<string> input = loader.toVectorStr();
  vector<__int64> seeds = InputLoader::toInt64(InputLoader::splitString(input[0], {"seeds: ", " "}));
  vector<Range> seedRanges;
  for(int i=0; i<(int)seeds.size() / 2; i++)
    seedRanges.push_back(Range(seeds[i*2], seeds[i*2+1]));
  vector<ConversionCollection> collections;
  int row=1;
  while(row<(int)input.size()){
    while(row<(int)input.size() && ((int)input[row][0] < 48 || (int)input[row][0] > 57)){ //While not numbers
      row++;
    }
    vector<string> collectionInput;
    while(row<(int)input.size() && ((int)input[row][0] >= 48 && (int)input[row][0] <= 57)){ //While numbers
      collectionInput.push_back(input[row]);
      row++;
    }
    if((int)collectionInput.size() > 0)
      collections.push_back(ConversionCollection(collectionInput));
  }

  __int64 minVal = -1;
  vector<Range> convertedSeeds = combineRanges(seedRanges);
  for(ConversionCollection& cc: collections){
    vector<Range> conv = cc.convertRange(convertedSeeds);
    convertedSeeds = combineRanges(conv);
  }
  for(Range& r: convertedSeeds){
    if(minVal == -1 || r.start() < minVal)
      minVal = r.start();
  }

  cout << "part 2: " << minVal << endl;
}

vector<Range> Day05::combineRanges(vector<Range> input){
  vector<Range> ret;
  for(Range& checkRange: input){
    bool combined = false;
    for(Range& r: ret){
      if(r.tryCombine(checkRange)){
        combined = true;
      }
    }
    if(!combined)
      ret.push_back(checkRange);
  }
  bool combined = true;
  while(combined){
    combined = false;
    for(int i = 0; i<(int)ret.size(); i++){
      for(int i2 = i+1; i2<(int)ret.size(); i2++){
        if(ret[i].tryCombine(ret[i2])){
          combined = true;
          ret.erase(next(ret.begin(), i2), next(ret.begin(), i2+1));
        }
      }
    }
  }
  return ret;
}

bool Range::tryCombine(Range other){
  if(other._start >= _start && other._start < _start + _len){
    __int64 endVal = _start + _len;
    if(other._start + other._len > endVal)
      endVal = other._start + other._len;
    if(other._start < _start)
      _start = other._start;
    _len = endVal - _start;
    return true;
  }
  return false;
}

void Range::output(){
  cout << _start << " - " << _start+_len-1 << endl;
}

void Conversion::load(string input){
  vector<string> splittedString = InputLoader::splitString(input, {" "});
  vector<__int64> inputVals = InputLoader::toInt64(splittedString);
  _destStart = inputVals[0];
  _sourceStart = inputVals[1];
  _length = inputVals[2];
}

bool Conversion::inRange(__int64 input){
  return input >= _sourceStart && input < _sourceStart+_length;
}

__int64 Conversion::convert(__int64 input){
  if(inRange(input)){
    return input - _sourceStart + _destStart;
  }
  return input;
}

vector<Range> Conversion::convertRange(vector<Range> input){
  vector<Range> ret;
  for(Range& r: input){
    vector<Range> newRet = convertRange(r);
    ret.insert(ret.end(), newRet.begin(), newRet.end());
  }

  return ret;
}

vector<Range> Conversion::convertRange(Range input){
  vector<Range> ret;
  __int64 rangeStart = input.start();
  if(rangeStart < _sourceStart)
    rangeStart = _sourceStart;
  __int64 rangeEnd = input.start() + input.len();
  if(rangeEnd > _sourceStart + _length)
    rangeEnd = _sourceStart + _length;
  __int64 convFactor = _destStart - _sourceStart;
  if(rangeEnd > rangeStart)
    ret.push_back(Range(rangeStart + convFactor, rangeEnd - rangeStart));
  return ret;
}

void Conversion::output(){
  cout << _destStart << " " << _sourceStart << " " << _length << endl;
}

void ConversionCollection::load(vector<string> input){
  for(string conversionInput: input)
    _conversions.push_back(Conversion(conversionInput));
}

vector<__int64> ConversionCollection::convert(vector<string> input){
  vector<__int64> ret;
  for(string inVal: input)
    ret.push_back(convert(InputLoader::toInt64({inVal})[0]));
  return ret;
}

__int64 ConversionCollection::convert(__int64 input){
  __int64 convertedVal = input;
  for(Conversion& c: _conversions)
    if(c.inRange(input))
      convertedVal = c.convert(input);
  return convertedVal;
}

vector<Range> ConversionCollection::convertRange(vector<Range> input){
  vector<Range> convertedVal;
  bool initBounds = false;
  for(Conversion& c: _conversions)  //Find ranges inside conversions
  {
    if(!initBounds || c.start() < _leftBound)
      _leftBound = c.start();
    if(!initBounds || c.end() > _rightBound)
      _rightBound = c.end();
    initBounds = true;
    vector<Range> newConvertedVal = c.convertRange(input);
    convertedVal.insert(convertedVal.end(), newConvertedVal.begin(), newConvertedVal.end());
  }

  for(Range& r: input){ //Find ranges outside conversions
    vector<Range> newConvertedVal = rangesOutsideConversions(r);
    convertedVal.insert(convertedVal.end(), newConvertedVal.begin(), newConvertedVal.end());
  }

  return convertedVal;
}

vector<Range> ConversionCollection::rangesOutsideConversions(Range input){
  vector<Range> ret;
  if(input.start() < _leftBound){
    __int64 rangeEnd = _leftBound;
    if(rangeEnd > input.start() + input.len())
      rangeEnd = input.start() + input.len();
    ret.push_back(Range(input.start(), rangeEnd - input.start()));
  }
  if(input.start() + input.len() -1 > _rightBound){
    __int64 rangeStart = _rightBound + 1;
    if(rangeStart < input.start())
      rangeStart = input.start();
    __int64 rangeEnd = input.start() + input.len();
    ret.push_back(Range(rangeStart, rangeEnd - rangeStart));
  }
  __int64 holeStart = _leftBound;
  while(holeStart != _rightBound + 1){
    bool inRange = true;
    while(inRange){
      inRange = false;
      for(Conversion& c: _conversions)
      {
        if(c.inRange(holeStart)){
          holeStart =c.end() + 1;
          inRange = true;
        }
      }
    }
    if(holeStart != _rightBound + 1){
      __int64 holeEnd;
      bool holdEndInitialized = false;
      for(int i=0; i<(int)_conversions.size(); i++){
        if(_conversions[i].start() > holeStart && (!holdEndInitialized || _conversions[i].start() < holeEnd)){
          holeEnd = _conversions[i].start();
          holdEndInitialized = true;
        }
      }
        ret.push_back(Range(holeStart, holeEnd - holeStart));
      holeStart = holeEnd;
    }
  }
  return ret;
}

void ConversionCollection::output(){
  for(Conversion& c: _conversions)
    c.output();
}
