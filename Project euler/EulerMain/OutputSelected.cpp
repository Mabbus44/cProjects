#include "OutputSelected.h"
#include <iostream>

OutputSelected::OutputSelected()
{
    reset();
}

OutputSelected::~OutputSelected()
{
    //dtor
}

void OutputSelected::output(unsigned long long num){
    if(shouldOutput(num)){
        std::string numStr = std::to_string(num);
        for( int i = numStr.size() - 3; i > 0; i -= 3 )
            numStr.insert(numStr.begin() + i, ',' );
        std::cout << numStr << std::endl;
    }
}

bool OutputSelected::shouldOutput(unsigned long long num){
    if(firstOutput || num >= nextOutput){
        if(num >= nextPow){
            pow = nextPow;
            nextPow *= 10;
        }
        nextOutput = num + pow;
        firstOutput = false;
        return true;
    }
    return false;
}

void OutputSelected::reset(){
    firstOutput = true;
    pow = 1;
    nextPow = 10;
}
