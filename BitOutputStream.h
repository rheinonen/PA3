/** NAME: Robin Heinonen
  * DATE: 11/11/17
  * PID: A53091242
  * DESCRIPTION: bitwise output stream class header
  * PA3 CSE 100 2017
  */

#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H
#include <iostream>

class BitOutputStream{
private:
  unsigned char buf; // one byte buffer of bits
  int nbits; // how many bits have been written to buf
  std::ostream & out; // reference to the output stream to use

  /** given an input byte, set the nth bit from the right to the input bit and
   *  return the result
   */
  static unsigned char setBit(unsigned char input,int n,int bit);

public:

  /** Initialize a BitOutputStream that will use
   * the given ostream for output */
    BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0){}

    /** Send the buffer to the output, and clear it */
    void flush();

    /** Write i (assumed to be 0 or 1) to
      * the bit buffer, and increment the bit buffer index.
      * But flush the buffer first, if it is full.
      */

    void writeBit(int i);

};



#endif //BITOUTPUTSTREAM_H
