/** NAME: Robin Heinonen
  * DATE: 11/11/17
  * PID: A53091242
  * DESCRIPTION: huffman decompression driver program
  * PA3 CSE 100 2017
  */

#include "HCNode.h"
#include "HCTree.h"
#include "BitOutputStream.h"
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
  vector<int> freqs(256,0);
  char* infile=argv[1];
  char* outfile=argv[2];
  ifstream in;
  in.open(infile);
  if(!in.is_open())
  {
      cout<< "Invalid input file. No file was opened. Please try again.\n";
      return -1;
  }
  //read in frequencies
  while(in.peek()!=EOF)
  {
    byte nextChar=in.get();
    freqs[nextChar]++;
  }
  in.close();

  //build huffman tree
  HCTree hct;
  hct.build(freqs);

  ofstream out;
  out.open(outfile);
  BitOutputStream bstream(out);

  //write file header
  hct.makeHeader(out);
  out.put((unsigned char) hct.endbits());
  out.flush();

  in.open(infile);

  //encode and write to file
  while(in.peek()!=EOF)
  {
    byte nextChar=in.get();
    hct.encode(nextChar,bstream);
  }

  //flush out any extra bits in the buffer, padding with zeros if necessary
  for(int i=0;i<7;i++)
    bstream.writeBit(0);

  in.close();

  out.close();

  return 0;
}
