/** NAME: Robin Heinonen
  * DATE: 11/11/17
  * PID: A53091242
  * DESCRIPTION: huffman coding tree class header
  * PA3 CSE 100 2017
  */

#ifndef HCTREE_H
#define HCTREE_H
#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */
class HCNodePtrComp {
public:
    bool operator()(HCNode* &lhs, HCNode*& rhs) const {
        return *lhs < *rhs;
    }
};

/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class HCTree {
private:
    HCNode* root;
    vector<HCNode*> leaves;

    /* postorder delete helper method for destructor */
    void deleteAll(HCNode* n);

    /* helper function for header */
    void preorder(HCNode* n,ostream& out) const;

    /** gives the length of the codeword associated with the inputted
     * (leaf) node. used to compute (in advance) the # of meaningful bits
     * in the last byte of the compressed output
     */
     static int height(HCNode* n);

public:
    // explicit keyword is used to avoid accidental implicit conversions
    explicit HCTree() : root(nullptr) {
        leaves = vector<HCNode*>(256, (HCNode*) nullptr);
    }

    ~HCTree();

    /** produces space-efficient header for compression output.
     *  preorder scan the tree, printing 0 for a nonleaf and 1 (followed
     *  by correpsonding char) for a leaf.
     */
    void makeHeader(ostream& out) const;

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void build(const vector<int>& freqs);

    /** build coding tree from space-efficient header rather than freqs*/
    void build(istream& in);

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
     void encode(byte symbol, BitOutputStream& out) const;

    /** Write to the given ofstream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR STEP 1-3 BUT SHOULD NOT
     *  BE USED IN THE FINAL SUBMISSION.
     */
    void encode(byte symbol, ofstream& out) const;


    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
     unsigned char decode(BitInputStream& in) const;

    /** Return the symbol coded in the next sequence of bits (represented as
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR STEP 1-3 BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
    int decode(ifstream& in) const;

    /** anticipates the number of meaningful bits in the final byte of
      * the compressed output. assumes tree has already been built
      */
    int endbits() const;

};

#endif // HCTREE_H
