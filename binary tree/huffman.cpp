/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    John Wood and Etienne Beaulac (Group 3)
 * Summary:
 *    This program will implement the huffman() function and huffman class
 *    methods to create a huffman code generator
 ************************************************************************/

#include "huffman.h"

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(std::string filename)
{
   Huffman huff;
   huff.readFile(filename);
   huff.huffmanize();
   huff.display();
}

/*******************************************
 * READFILE
 * Read in a huffman.txt file, store data in originalPairs and huffTree
 *******************************************/
void Huffman :: readFile(std::string filename)
{
   std::string name; // name of pair
   float value;      // value of pair

   std::ifstream fin(filename.c_str());
   while(fin >> name)
   {
      fin >> value;

      Pair <std::string, float> _pair(name, value);
      originalPairs.push_back(_pair);

      BNode <Pair <std::string, float> > * _BNode =
         new BNode <Pair <std::string, float> > (_pair);
      huffTree.push_back(_BNode);
   }

   fin.close();
}

/*******************************************
 * HUFFMANIZE
 * With the help of reorganize(), recursively takes the huffman BNodes,
 * and sorts them into a proper huffman tree for later use
 *******************************************/
void Huffman :: huffmanize()
{
   if (huffTree.size() == 1)
      return;

   _smallest = new BNode <Pair <std::string, float> > (findSmallest());
   positionSmallest = tempPosition;
   huffTree[tempPosition]->data.first = "overwrite";
   huffTree[tempPosition]->data.second = -1;

   _smaller = new BNode <Pair <std::string, float> > (findSmallest());
   positionSmaller = tempPosition;
   huffTree[tempPosition]->data.first = "overwrite";
   huffTree[tempPosition]->data.second = -1;

   reorganize();
   huffmanize();
}

/*******************************************
 * FINDSMALLEST
 * Find smallest BNode in the huffman tree
 *******************************************/
BNode <Pair <std::string, float> > Huffman :: findSmallest()
{
   Pair <std::string, float> smallestPair(huffTree[0]->data.first, huffTree[0]->data.second);
   if (huffTree[0]->data.second == -1)
      smallestPair.second = huffTree[1]->data.second;
   tempPosition = 0;
   for (int i = 0; i < huffTree.size(); i++)
      if (huffTree[i]->data.second < smallestPair.second && huffTree[i]->data.second != -1)
      {
         tempPosition = i;
         smallestPair.first = huffTree[i]->data.first;
         smallestPair.second = huffTree[i]->data.second;
      }

   return (*huffTree[tempPosition]);
}

/*******************************************
 * REORGANIZE
 * Takes the correct BNode, makes a placeholder node, and attaches the two
 * smallest BNodes choosen by Huffmanize, effectively reorganizing the tree
 * into a huffman tree.
 *******************************************/
void Huffman :: reorganize()
{
   Pair <std::string, float> newPair("placeholder", _smallest->data.second +
                                              _smaller->data.second);
   BNode <Pair <std::string, float> > *newNode = new BNode <Pair <std::string, float> > (newPair);

   addLeft(newNode, _smallest);
   addRight(newNode, _smaller);

   if (positionSmaller > positionSmallest)
   {
      huffTree[positionSmallest] = newNode;
      huffTree[positionSmaller] = huffTree[huffTree.size() - 1];
   }
   else
   {
      huffTree[positionSmaller] = newNode;
      huffTree[positionSmallest] = huffTree[huffTree.size() - 1];
   }

   vector <BNode <Pair <std::string, float> > * > huffTemp;
   for (int i = 0; i < huffTree.size() - 1; i++)
      huffTemp.push_back(huffTree[i]);
   huffTree = huffTemp;

   reset();
}

/**************************************************
 * RESET
 * Resets the position member variables for other
 * iterations of huffmanize
 **************************************************/
void Huffman :: reset()
{
   positionSmallest = 0;
   positionSmaller = 0;
   tempPosition = 0;
}

/**************************************************
 * DISPLAY
 * Display the huffman codes, in the same order they were found in the
 * original file
 **************************************************/
void Huffman :: display()
{
   scanBinaryTree(huffTree[0], 0);
   for (int i = 0; i < originalPairs.size(); i++)
      for (int j = 0; j < finalPairs.size(); j++)
         if (originalPairs[i].first == finalPairs[j].first)
            cout << finalPairs[j].first << " = " << finalPairs[j].second << endl;
}

/**************************************************
 * SCAN BINARY TREE
 * Recursively scans the organized huffman tree, calculates the codes,
 * and stores data in finalPairs, a vector of pairs.
 **************************************************/
void Huffman :: scanBinaryTree(BNode <Pair <std::string, float> > * pHead, int direction)
{
   if (pHead == NULL)
      return;

   if (direction == 1)
      binary += "0";
   if (direction == 2)
      binary += "1";

   if (!pHead->pLeft && !pHead->pRight)
   {
      Pair <std::string, std::string> tempPair(pHead->data.first, binary);
      finalPairs.push_back(tempPair);
   }

   scanBinaryTree(pHead->pLeft, 1);
   scanBinaryTree(pHead->pRight, 2);
   
   if (!binary.empty())
      binary.erase(binary.size() - 1);
}
