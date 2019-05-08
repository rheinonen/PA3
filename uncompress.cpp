/** NAME: Robin Heinonen
  * DATE: 11/11/17
  * PID: A53091242
  * DESCRIPTION: huffman compression driver program
  * PA3 CSE 100 2017
  */

#include "HCNode.h"
#include "HCTree.h"
#include "BitInputStream.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<iterator>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc!=3)
  {
    cout << "Error, wrong number of inputs" << endl;
    return -1;
  }

  char* infile=argv[1];
  char* outfile=argv[2];
  vector<int> freqs(256,0);
  ifstream in;
  in.open(infile);
  if(!in.is_open())
  {
      cout<< "Invalid input file. No file was opened. Please try again.\n";
      return -1;
  }

  //read in header and build huffman tree
  HCTree hct;
  hct.build(in);

  //get number of meaningful bits in last byte
  unsigned char endbits=in.get();

  ofstream out;
  out.open(outfile);
  BitInputStream bstream(in);

  //decode and write original message to outfile

  while(in.peek()!=EOF || bstream.getNBits()<endbits)
  {
    out.put(hct.decode(bstream));
    out.flush();
  }

  in.close();
  out.close();

  return 0;
}
