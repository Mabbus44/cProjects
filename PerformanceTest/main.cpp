#include <iostream>
#include <inttypes.h>
#include <chrono>

using namespace std;


void set8bitIntsx48(__int8* reciever, __int8* sender);
void set64bitIntsx100(__int64* reciever, __int64* sender);

int main()
{
  double timePassed;
  auto chronoTimeStart = std::chrono::steady_clock::now();
  auto chronoTimeFinish = std::chrono::steady_clock::now();

  __int8* reciever = new __int8[48];
  __int8* sender = new __int8[48];
  __int64* reciever64 = new __int64;
  __int64* sender64 = new __int64;
  *sender64  = 64;
  for(int runs=0; runs<10; runs++)
  {
    chronoTimeStart = std::chrono::steady_clock::now();
    for(int i=0; i<1; i++)
    {
      set64bitIntsx100(reciever64, sender64);
      cout << *sender64 << " " << *reciever64 << endl;
      //set8bitIntsx48(reciever, sender);
    }
    chronoTimeFinish = std::chrono::steady_clock::now();
    timePassed  = (std::chrono::duration_cast<std::chrono::milliseconds>(chronoTimeFinish - chronoTimeStart).count())/1000.0;
    cout << "Run " << runs << ": " << timePassed << " s" << endl;
  }

  return 0;
}


void set8bitIntsx48(__int8* reciever, __int8* sender)
{
  reciever[0] = sender[0];
  reciever[1] = sender[1];
  reciever[2] = sender[2];
  reciever[3] = sender[3];
  reciever[4] = sender[4];
  reciever[5] = sender[5];
  reciever[6] = sender[6];
  reciever[7] = sender[7];
  reciever[8] = sender[8];
  reciever[9] = sender[9];
  reciever[10] = sender[10];
  reciever[11] = sender[11];
  reciever[12] = sender[12];
  reciever[13] = sender[13];
  reciever[14] = sender[14];
  reciever[15] = sender[15];
  reciever[16] = sender[16];
  reciever[17] = sender[17];
  reciever[18] = sender[18];
  reciever[19] = sender[19];
  reciever[20] = sender[20];
  reciever[21] = sender[21];
  reciever[22] = sender[22];
  reciever[23] = sender[23];
  reciever[24] = sender[24];
  reciever[25] = sender[25];
  reciever[26] = sender[26];
  reciever[27] = sender[27];
  reciever[28] = sender[28];
  reciever[29] = sender[29];
  reciever[30] = sender[30];
  reciever[31] = sender[31];
  reciever[32] = sender[32];
  reciever[33] = sender[33];
  reciever[34] = sender[34];
  reciever[35] = sender[35];
  reciever[36] = sender[36];
  reciever[37] = sender[37];
  reciever[38] = sender[38];
  reciever[39] = sender[39];
  reciever[40] = sender[40];
  reciever[41] = sender[41];
  reciever[42] = sender[42];
  reciever[43] = sender[43];
  reciever[44] = sender[44];
  reciever[45] = sender[45];
  reciever[46] = sender[46];
  reciever[47] = sender[47];
}

void set64bitIntsx100(__int64* reciever, __int64* sender)
{
  *reciever = 0;
  //*reciever=*sender&31;
  *reciever=(*sender&(31<<5))>>5;
}
