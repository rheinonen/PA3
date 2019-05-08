/** NAME: Robin Heinonen
  * DATE: 11/11/17
  * PID: A53091242
  * DESCRIPTION: huffman coding tree class definition
  * PA3 CSE 100 2017
  */

#include "HCTree.h"
#include "HCNode.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"
#include<vector>
#include<queue>
#include<stack>
#include<iterator>
#include<iostream>

void HCTree::deleteAll(HCNode* n)
{
  if(n==nullptr)
    return;
  deleteAll(n->c0);
  deleteAll(n->c1);
  delete n;
}

HCTree::~HCTree(){
  deleteAll(root);
};

void HCTree::makeHeader(ostream& out) const{
  preorder(root,out);
  out.put((unsigned char) 255); //signifies end of header. no ambiguity since a leaf must precede
}

void HCTree::preorder(HCNode* n,ostream& out) const{
  if(n==nullptr)
    return;
  if(n->c0==nullptr && n->c1==nullptr)
    {
      out.put((unsigned char) 1);
      out.flush();
      out.put(n->symbol);
      out.flush();
      return;
    }
  out.put((unsigned char) 0);
  out.flush();
  preorder(n->c0,out);
  preorder(n->c1,out);
}

void HCTree::build(istream& in)
{
  unsigned char next=in.get();
  if(next==255) //empty tree
    return;
  if(next==1) //singleton tree
  {
    next=in.get();
    root=new HCNode(0,next);
    in.get();
    return;
  }
  root=new HCNode(0,0);
  HCNode* curr=root;
  while(true){
    next=in.get();

    if(next==0) //nonleaf
    {
      if(curr->c0==nullptr)
      {
        curr->c0=new HCNode(0,0);
        curr->c0->p=curr;
        curr=curr->c0;
      }
      else
      {
        curr->c1=new HCNode(0,0);
        curr->c1->p=curr;
        curr=curr->c1;
      }
    }
    if(next==1) //leaf
    {
      next=in.get();
      if(curr->c0==nullptr)
      {
        curr->c0=new HCNode(0,next);
        curr->c0->p=curr;
      }
      else
      {
        curr->c1=new HCNode(0,next);
        curr->c0->p=curr;
        while(curr->p!=nullptr) //go back up tree
        {
          curr=curr->p;
          if(curr->c0==nullptr || curr->c1==nullptr)
            break;
        }
      }
      next=in.peek();
      if(next==255)
      {
        in.get();
        return;
      }
    }
  }
}

void HCTree::build(const vector<int> & freqs)
{
  std::priority_queue<HCNode*,vector<HCNode*>,HCNodePtrComp> pq;

  //if character appears at least once, create an HCNode and add it to priority queue
  for(int i=0;i<freqs.size();i++)
  {
    if(freqs[i]>0)
    {
      leaves[i]=new HCNode(freqs[i],i);
      pq.push(leaves[i]);
    }
  }

  if(pq.empty())
    return;

  //build tree
  while(pq.size()>1)
  {
    HCNode* n1= pq.top();
    pq.pop();
    HCNode* n2= pq.top();
    pq.pop();
    n1->p=new HCNode(n1->count+n2->count,n1->symbol,n2,n1);
    n2->p=n1->p;
    pq.push(n1->p);
  }

  this->root = pq.top();
}

void HCTree::encode(byte symbol,BitOutputStream& out) const{
  HCNode* curr=leaves[symbol];
  std::stack<int> bits;
  //handle edge case of only one unique symbol
  if(curr==root)
  {
    out.writeBit(0);
    return;
  }

  //ascend tree, adding bits to stack
  while(curr->p!=nullptr)
  {
    if(curr->p->c1==curr)
      bits.push(1);
    if(curr->p->c0==curr)
      bits.push(0);
    curr=curr->p;
  }
  while(!bits.empty())
  {
    out.writeBit(bits.top());
    bits.pop();
  }

}


void HCTree::encode(byte symbol, ofstream& out) const{
  HCNode* curr=leaves[symbol];
  std::stack<char> bits;
  //handle edge case of only one unique symbol
  if(curr==root)
  {
    out << '0';
    return;
  }
  //ascend tree, adding bits to stack
  while(curr->p!=nullptr)
  {
    if(curr->p->c1==curr)
      bits.push('1');
    if(curr->p->c0==curr)
      bits.push('0');
    curr=curr->p;
  }
  while(!bits.empty())
  {
    out << bits.top();
    bits.pop();
  }

}

unsigned char HCTree::decode(BitInputStream& in) const{

  //take care of case of singleton tree
  if(root->c0==nullptr && root->c1==nullptr)
  {
    in.readBit();
    return root->symbol;
  }
   //descend tree, outputting bits to stream
  HCNode* curr=root;
  while(curr->c0!=nullptr || curr->c1!=nullptr)
    {
      int next=in.readBit();
      if(next==1)
      {
        curr=curr->c1;
      }
      if(next==0)
      {
        curr=curr->c0;
      }
    }

  return curr->symbol;
}

int HCTree::decode(ifstream& in) const{

  //take care of case of singleton tree
  if(root->c0==nullptr && root->c1==nullptr)
  {
    in.get();
    return root->symbol;
  }

  //descend tree, outputting bits to stream
  HCNode* curr=root;
  while(curr->c0!=nullptr || curr->c1!=nullptr)
    {
      byte next=in.get();
      if(next=='1')
      {
        curr=curr->c1;
      }
      if(next=='0')
      {
        curr=curr->c0;
      }
    }

  return curr->symbol;
}

int HCTree::height(HCNode* n){
  //if the node is root, codeword is length 1
  if(n->p==nullptr)
    return 1;
  HCNode* curr=n;
  int count=0;
  while(curr->p!=nullptr)
  {
    curr=curr->p;
    count++;
  }

  return count;
}

int HCTree::endbits() const{
  unsigned int bitcount=0;
  for(int i=0;i<256;i++)
  {
    if(leaves[i]!=nullptr)
      bitcount+=leaves[i]->count*height(leaves[i]);
  }

  int out = bitcount%8;
  if(out==0)
    out=8;
  return out;
}
