/** NAME: Robin Heinonen
  * DATE: 11/11/17
  * PID: A53091242
  * DESCRIPTION: huffman coding tree node class header
  * PA3 CSE 100 2017
  */

#ifndef HCNODE_H
#define HCNODE_H

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
class HCNode {

public:
    int count;
    byte symbol; // byte in the file we're keeping track of
    HCNode* c0;  // pointer to '0' child
    HCNode* c1;  // pointer to '1' child
    HCNode* p;   // pointer to parent

    HCNode(int count,
      byte symbol,
      HCNode* c0 = nullptr,
      HCNode* c1 = nullptr,
      HCNode* p = nullptr)
        : count(count), symbol(symbol), c0(c0), c1(c1), p(p) { }

    /** overloaded less-than operator for comparing HCNodes, so that we can
    *  build a priority queue
    */
    bool operator<(const HCNode other) const;

};


/** For printing an HCNode to an ostream
 *  Possibly useful for debugging.
 */
ostream& operator<<(ostream&, const HCNode) __attribute__((weak)); // shut the linker up
ostream& operator<<(ostream& stm, const HCNode n) {
    stm << "[" << n.count << "," << (int) (n.symbol) << "]";
    return stm;
}


#endif // HCNODE_H
