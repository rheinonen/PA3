/** NAME: Robin Heinonen
  * DATE: 11/11/17
  * PID: A53091242
  * DESCRIPTION: bitwise input stream class header
  * PA3 CSE 100 2017
  */

#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H
#include <iostream>

class BitInputStream {
private:
  unsigned char buf; //one byte buffer of bits
  int nbits;         //how many bits have been read from buffer
  std::istream & in; //input stream to use

  /* given a byte, returns nth bit from the right */
  static int getBit(unsigned char byte, int n);

public:
  /* constructor for BitInputStream */
  BitInputStream(std::istream & is): in(is),nbits(8),buf(0){}

  /* fill the buffer from the input */
  void fill();

  /* public getter method for nbits */
  int getNBits()
  {
    return nbits;
  }

  /** Read the next bit from the buffer
    * Fill the buffer from the input stream first if needed
    * Return 1 if the bit read is 1
    * Return 0 if the bit read is 0
    */
  int readBit();

};


#endif //BITINPUTSTREAM_H
