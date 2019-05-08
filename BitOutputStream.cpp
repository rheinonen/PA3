/** NAME: Robin Heinonen
  * DATE: 11/11/17
  * PID: A53091242
  * DESCRIPTION: bitwise output stream class definition
  * PA3 CSE 100 2017
  */

#include "BitOutputStream.h"
#include <iostream>

unsigned char BitOutputStream::setBit(unsigned char input,int n,int bit)
{
  return (~(1<<n) & input) | ((bit << n) & (1<<n));
}

void BitOutputStream::flush(){
  out.put(buf);
  out.flush();
  buf = 0;
  nbits=0;
}

void BitOutputStream::writeBit(int i){

  //write i to buffer at appropriate location
  buf=setBit(buf,7-nbits,i);

  //increment the counter
  nbits++;

  //flush buffer if full
  if(nbits==8)
  {
    flush();
  }
}
