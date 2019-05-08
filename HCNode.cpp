/** NAME: Robin Heinonen
  * DATE: 11/11/17
  * PID: A53091242
  * DESCRIPTION: huffman coding tree node class definition
  * PA3 CSE 100 2017
  */

#include "HCNode.h"
#include <iostream>

bool HCNode::operator<(const HCNode other) const
{
  if(this->count == other.count)
    return this->symbol >other.symbol; //break ties using alphabetical order of symbols
  else
    return this->count > other.count;
}
