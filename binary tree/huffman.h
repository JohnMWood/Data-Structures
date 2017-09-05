/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Huffman class declaration and the huffman function for assignment08
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <fstream>
#include "vector.h"
#include "pair.h"
#include "bnode.h"
using std::cerr;
using std::cout;
using std::endl;
using namespace custom;

class Huffman
{
private:
   // used in reorganize as means of sorting the BNode tree into the huffTree
   int positionSmallest;
   int positionSmaller;
   int tempPosition;
   BNode <Pair <std::string, float> > * _smallest;
   BNode <Pair <std::string, float> > * _smaller;

   // reorganized huffman tree
   vector <BNode <Pair <std::string, float> > * > huffTree;

   // original pairs from the huffman.txt files
   vector <Pair <std::string, float> > originalPairs;

   // keeps track of the binary for each huffman code
   std::string binary;

   // a vector of pairs, with the original key and the binary huffman string
   vector <Pair <std::string, std::string> > finalPairs;

   BNode <Pair <std::string, float> > findSmallest();
   void reorganize();
   void reset();
   void scanBinaryTree(BNode <Pair <std::string, float> > * pHead, int direction);

public:
   Huffman() : positionSmallest(0), positionSmaller(0), _smallest(),
               _smaller(), huffTree() { }
   ~Huffman() { reset(); }

   void readFile(std::string filename);
   void huffmanize();
   void display();
   const vector <BNode <Pair<std::string, float> > * > & getHuffTree()
   { return huffTree; }
};

void huffman(std::string filename);


#endif // HUFFMAN_h
