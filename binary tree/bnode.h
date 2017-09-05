/***********************************************************************
* Program:
*    Assigment 08, Binary Tree
*    Brother Helfrich, CS 235
* Authors:
*    John Wood and Etienne Beaulac (group 3)
* Summary:
*    Our implementation of the Binary Tree class 
************************************************************************/
#ifndef BNODE_H
#define BNODE_H

#include <assert.h>

/**************************************************
 * BNode:: Class Definition
 * The class definition for BNode with constructors and
 * member variables defined
 *************************************************/
template <class T>
class BNode
{
public:
   T data;
   BNode *pParent;
   BNode *pRight;
   BNode *pLeft;

   BNode() : pParent(NULL), pRight(NULL), pLeft(NULL), data()             {   }
   BNode(const T & t) : pParent(NULL), pRight(NULL), pLeft(NULL), data(t) {   }
}; // BNode

/**************************************************
 * ADD LEFT
 * Add a given node to left
 **************************************************/
template <class T>
void addLeft (BNode <T> * pNode, BNode <T> * pAdd)
{
   if (pAdd)
      pAdd->pParent = pNode;
   pNode->pLeft = pAdd;
}

/**************************************************
 * ADD RIGHT
 * Add a given node to right
 **************************************************/
template <class T>
void addRight(BNode <T> * pNode, BNode <T> * pAdd)
{
   if (pAdd)
      pAdd->pParent = pNode;
   pNode->pRight = pAdd;
}

/**************************************************
 * ADD LEFT
 * Add a new node with given data to left
 **************************************************/
template <class T>
void addLeft (BNode <T> * pNode, const T & t) throw (const char *)
{
   try
   {
      BNode <T> *pAdd = new BNode <T> (t);
      pAdd->pParent = pNode;
      pNode->pLeft = pAdd;
   }
   catch (...)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/**************************************************
 * ADD RIGHT
 * Add a new node with given data to right
 **************************************************/
template <class T>
void addRight(BNode <T> * pNode, const T & t) throw (const char *)
{
   try
   {
      BNode <T> *pAdd = new BNode <T> (t);
      pAdd->pParent = pNode;
      pNode->pRight = pAdd;
   }
   catch (...)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/**************************************************
 * DELETE BINARY TREE
 * Recursively deletes the nodes of the binary tree
 **************************************************/
template <class T>
void deleteBTree(BNode <T> * & pNode)
{
   if (!pNode)
      return;
   deleteBTree(pNode->pLeft);
   deleteBTree(pNode->pRight);
   delete pNode;
}

/**************************************************
 * SIZE BINARY TREE
 * Recursively calculates the size of the tree
 **************************************************/
template <class T>
int sizeBTree(const BNode <T> * pRoot)
{
   if (!pRoot)
      return 0;
   else
      return (sizeBTree(pRoot->pLeft) + 1 + sizeBTree(pRoot->pRight));
}

/**************************************************
 * INSERTION OPERATOR
 * Recursively displays the contents of the tree in infix
 **************************************************/
template <class T>
inline std::ostream & operator << (std::ostream & out, const BNode <T> *rhs)
{
   if (!rhs)
      return out;

   std::cout << rhs->pLeft;
   out << rhs->data << " ";
   std::cout << rhs->pRight;
}

#endif // BNODE_H
