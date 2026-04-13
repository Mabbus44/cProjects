#include "BigInt.h"
#include "OutputSelected.h"
#include<iostream>
#include<list>

BigInt::BigInt()
{
    data.clear();
    data.push_back(0);
}

BigInt::BigInt(int num)
{
    data.clear();
    data.push_back(num);
}

BigInt::~BigInt()
{
    //dtor
}

void BigInt::operator=(int other){
    data.clear();
    data.push_back(other);
}

void BigInt::operator=(BigInt other){
    data = other.data;
}

bool BigInt::operator<(BigInt& other){
    if(data.size() > other.data.size())
        return false;
    if(data.size() < other.data.size())
        return true;
    for(int i=data.size()-1; i>=0; i--){
        if(data[i] > other.data[i])
            return false;
        if(data[i] < other.data[i])
            return true;
    }
    return false;
}

bool BigInt::operator>(BigInt& other){
    if(data.size() > other.data.size())
        return true;
    if(data.size() < other.data.size())
        return false;
    for(int i=data.size()-1; i>=0; i--){
        if(data[i] > other.data[i])
            return true;
        if(data[i] < other.data[i])
            return false;
    }
    return false;
}

bool BigInt::operator==(BigInt& other){
    if(data.size() != other.data.size())
        return false;
    for(int i=data.size()-1; i>=0; i--){
        if(data[i] != other.data[i])
            return false;
    }
    return true;
}

BigInt& BigInt::operator++(){
    addToData(0, 1);
    return *this;
}

BigInt BigInt::operator*(BigInt other){
    BigInt ret;
    for(int a=0; a<(int)data.size(); a++)
        for(int b=0; b<(int)other.data.size(); b++)
            ret.addToData(a+b, data[a]*other.data[b]);
    return ret;
}

BigInt& BigInt::operator+=(BigInt& other){
    for(int i=0; i<(int)other.data.size(); i++)
        addToData(i, other.data[i]);
    return *this;
}

BigInt& BigInt::operator+=(unsigned long long& other){
    addToData(0, other);
    return *this;
}

void BigInt::addToData(int dataId, unsigned long long num){
    while(dataId >= (int)data.size())
        data.push_back(0);
    data[dataId] += num;
    if(data[dataId] >= POWER32){
        unsigned long long upper32Bits = (data[dataId] >> 32);      // Extract the upper 32 bits
        data[dataId] = (data[dataId] & MAX32);                      // Remove the upper 32 bits
        addToData(dataId+1, upper32Bits);                           // Add the upper 32 bits to the next data
    }
}

void BigInt::output(){
    if(data.size() == 0){
        std::cout << "0";
        return;
    }
    for(int i=data.size()-1; i>=0; i--){
        std::cout << data[i];
        if(i!=0)
            std::cout << ",";
    }
}

