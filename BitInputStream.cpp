/** NAME: Robin Heinonen
  * DATE: 11/11/17
  * PID: A53091242
  * DESCRIPTION: bitwise input stream class definition
  * PA3 CSE 100 2017
  */

#include "BitInputStream.h"
#include <iostream>

int BitInputStream::getBit(unsigned char byte,int n){
  return (byte>>n)&1;
}

void BitInputStream::fill(){
  buf=in.get();
  nbits=0;
}

int BitInputStream::readBit(){
  //fill the buffer if all bits are read
  if(nbits==8)
    fill();

  //get the appropriate bit from the buffer
  int bit=getBit(buf,7-nbits);

  //increment the counter
  nbits++;
  return bit;
}
