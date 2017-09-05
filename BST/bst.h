/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Helfrich, CS 235
 * Authors:
 *    John Wood and Etienne Beaulac (Group 3)
 * Summary:
 *    Our implementation of the binary search tree, using a binary tree
 *    nested class
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "stack.h"
#include <iostream>

namespace custom
{
/**************************************************
 * BST:: Class Definition
 * The class definition for binary search tree
 * with constructors and member variables defined
 *************************************************/
template <class T>
class BST
{
public:
   // constructors
   BST() : root(NULL), numElements(0) {}
   BST(const BST &rhs) : root(NULL), numElements(0) { *this = rhs; }
   ~BST() {}

   // operators
   BST <T> & operator = (const BST <T> &rhs) throw (const char *)
   {
      root = copyBinaryTree(rhs.getRoot());
      numElements = rhs.numElements;
   }

   class BNode;

   // iterators
   class iterator;
   iterator begin()          const;
   iterator end()            const { return iterator(NULL);               }

   // class reverse_iterator;
   class reverse_iterator;
   reverse_iterator rbegin()         const;
   reverse_iterator rend()           const { return reverse_iterator(NULL);               }

   int size()                const { return numElements;                  }
   bool empty()              const { return numElements == 0;             }
   void clear()                    { deleteBinaryTree(root); root = NULL; }
   BNode * getRoot()         const { return root;                         }

   void insert(const T &t) throw (const char *);
   void remove(BST <T> :: iterator it);
   iterator find(const T &t);
private:
   BNode * root;
   int numElements;

   BNode * findSuccessor(BNode * del, bool right);
   void deleteBinaryTree(BNode * del, int dir);
   BNode * copyBinaryTree(const BNode * src);

   void addRight(BNode * pNode, const T & t) throw (const char *);
   void addLeft (BNode * pNode, const T & t) throw (const char *);
   void addRight(BNode * pNode, BNode * pAdd);
   void addLeft (BNode * pNode, BNode * pAdd);
}; // BST

/**************************************************
 * BNode:: Class Definition
 * The class definition for BNode with constructors and
 * member variables defined
 *************************************************/
template <class T>
class BST <T> :: BNode
{
public:
   T data;
   BNode *pParent;
   BNode *pRight;
   BNode *pLeft;
   bool isRed;

   BNode() : pParent(NULL), pRight(NULL), pLeft(NULL), data(), isRed(false)             {   }
   BNode(const T & t) : pParent(NULL), pRight(NULL), pLeft(NULL), data(t), isRed(false) {   }

// more added private functions to BNode
private:
   friend class BST;
   void verifyRB(int depth);
   void verifyBST();
   void balance();
}; // BNode

/**************************************************
 * BST :: find
 * Finds a BNode
 *************************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: find(const T &t)
{
   assert(root);
   BNode * temp = root;
   BNode * pos;
   while (temp)
   {
      pos = temp;
      if (temp->data > t)
         temp = temp->pLeft;
      else if (temp->data < t)
         temp = temp->pRight;
      else
         return iterator(temp);
   }

   return iterator(NULL);
}

/**************************************************
 * BST :: remove
 * removes a BNode
 *************************************************/
template <class T>
void BST <T> :: remove(BST <T> :: iterator it)
{
   if (it == end())
      return;

   bool right = false;

   BNode * pDelete = it.nodes.top();
   if (pDelete->pParent && pDelete->pParent->pRight == pDelete)
      right = true;

   BNode * temp;
   // NO CHILDREN
   if (!pDelete->pRight && !pDelete->pLeft)
   {
      if (right)
         pDelete->pParent->pRight = NULL;
      else
         pDelete->pParent->pLeft = NULL;
      delete pDelete;
      numElements--;
      return;
   }
   // RIGHT CHILD
   if (pDelete->pRight && !pDelete->pLeft)
   {
      temp = pDelete->pRight;
      if (right)
         pDelete->pParent->pRight = temp;
      else
         pDelete->pParent->pLeft = temp;
      delete pDelete;
      numElements--;
      return;
   }
   // LEFT CHILD
   if (!pDelete->pRight && pDelete->pLeft)
   {
      temp = pDelete->pLeft;
      if (right)
         pDelete->pParent->pRight = temp;
      else
         pDelete->pParent->pLeft = temp;
      delete pDelete;
      numElements--;
      return;
   }
   else // TWO CHILDREN
   {
      assert(pDelete->pRight && pDelete->pLeft);
      BNode * successor = findSuccessor(pDelete, true);

      if (pDelete->pParent)
         successor->pParent = pDelete->pParent;

      successor->pRight = pDelete->pRight;
      successor->pLeft = pDelete->pLeft;

      if (pDelete->pParent)
      {
         if (right)
            successor->pParent->pRight = successor;
         else
            successor->pParent->pLeft = successor;
      }
      else
      {
         successor->pParent = NULL;
         root = successor;
      }

      successor->pRight->pParent = successor;
      successor->pLeft->pParent = successor;

      delete pDelete;
      numElements--;
   }
}

/**************************************************
 * BST :: findSuccessor
 * Finds the successor of the BNode being removed
 *************************************************/
template <class T>
typename BST <T> :: BNode * BST <T> :: findSuccessor(BNode * del, bool right = false)
{
   BNode * successor;
   if (right)
      successor = findSuccessor(del->pRight);
   else
   {
      if (!del->pLeft)
      {
         if (del->pRight)
         {
            del->pRight->pParent = del->pParent;
            del->pParent->pLeft = del->pRight;
         }
         else
            del->pParent->pLeft = NULL;
         return del;
      }
      successor = findSuccessor(del->pLeft);
   }
   return successor;
}

/**************************************************
 * BST :: deleteBinaryTree
 * Deletes a binary tree
 *************************************************/
template <class T>
void BST <T> :: deleteBinaryTree(BNode * del, int dir = 0)
{
   if (!del)
      return;
   deleteBinaryTree(del->pLeft, 1);
   deleteBinaryTree(del->pRight, 2);
   delete del;
   numElements--;
}

/**************************************************
 * BST :: ADD RIGHT
 * Add a new node with given data to right
 **************************************************/
template <class T>
void BST <T> :: addRight(BNode * pNode, const T & t) throw (const char *)
{
   try
   {
      BNode *pAdd = new BNode (t);
      pAdd->pParent = pNode;
      pNode->pRight = pAdd;
   }
   catch (...)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/**************************************************
 * BST :: ADD LEFT
 * Add a new node with given data to left
 **************************************************/
template <class T>
void BST <T> :: addLeft (BNode * pNode, const T & t) throw (const char *)
{
   try
   {
      BNode *pAdd = new BNode(t);
      pAdd->pParent = pNode;
      pNode->pLeft = pAdd;
   }
   catch (...)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/**************************************************
 * BST :: ADD RIGHT
 * Add a given node to right
 **************************************************/
template <class T>
void BST <T> :: addRight(BNode * pNode, BNode * pAdd)
{
   if (pAdd)
      pAdd->pParent = pNode;
   pNode->pRight = pAdd;
}

/**************************************************
 * BST :: ADD LEFT
 * Add a given node to left
 **************************************************/
template <class T>
void BST <T> :: addLeft (BNode * pNode, BNode * pAdd)
{
   if (pAdd)
      pAdd->pParent = pNode;
   pNode->pLeft = pAdd;
}

/**************************************************
 * BST :: insert
 * Inserts an element inside the BST
 **************************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char *)
{
   try
   {
      if (!root)
      {
         root = new BNode (t);
         numElements++;
         return;
      }
   }
   catch (...)
   {
      throw "ERROR: Unable to allocate a node";
   }

   BNode * temp = root;
   BNode * pos;
   while (temp)
   {
      pos = temp;
      if (temp->data >= t)
         temp = temp->pLeft;
      else
         temp = temp->pRight;
   }
   if (pos->data >= t)
   {
      addLeft(pos, t);
      if (!pos->isRed)
         pos->pLeft->isRed = true;
      if (pos->isRed)
      {
         pos->isRed = false;
         if (pos->pParent->pRight)
            pos->pParent->pRight->isRed = false;
         else if(pos->pParent->pLeft)
            pos->pParent->pLeft->isRed = false;
         pos->pLeft->isRed = true;
      }
   }
   else
   {
      addRight(pos, t);
      if (!pos->isRed)
         pos->pRight->isRed = true;
      if (pos->isRed)
      {
         pos->isRed = false;
         if (pos->pParent->pRight)
            pos->pParent->pRight->isRed = false;
         else if(pos->pParent->pLeft)
            pos->pParent->pLeft->isRed = false;
         pos->pRight->isRed = true;
      }
   }
   numElements++;
}

/**************************************************
 * BST :: copyBinaryTree
 * Copies a binary tree
 *************************************************/
template <class T>
typename BST <T> :: BNode * BST <T> :: copyBinaryTree(const BNode * src)
{
   if (!src)
      return NULL;

   BNode * pTemp;

   try
   {
      pTemp = new BNode (src->data);
   }
   catch (...)
   {
      throw "ERROR: Unable to allocate a node";
   }
   if (pTemp->pLeft = copyBinaryTree(src->pLeft))
      pTemp->pLeft->pParent = pTemp;
   if (pTemp->pRight = copyBinaryTree(src->pRight))
      pTemp->pRight->pParent = pTemp;

   return pTemp;
}

/**************************************************
 * iterator:: Class Definition
 * An iterator through BST
 *************************************************/
template <class T>
class BST <T> :: iterator
{
private:
   stack <BNode *> nodes;
   friend class BST;
public:
   iterator(BNode * p = NULL)      { nodes.push(p);     }
	iterator(stack <BNode *> & s)   { nodes = s;         }
	iterator(const iterator & rhs)  { nodes = rhs.nodes; }

   iterator & operator = (const iterator & rhs)
   {
      nodes = rhs.nodes;
      return *this;
   }

   iterator & operator = (const reverse_iterator & rhs)
   {
      nodes = rhs.nodes;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const
   {
      return rhs.nodes.top() != nodes.top();
   }

   bool operator != (const reverse_iterator & rhs) const
   {
      return rhs.nodes.top() != nodes.top();
   }

   bool operator == (const iterator & rhs) const
   {
      return rhs.nodes.top() == nodes.top();
   }

   bool operator == (const reverse_iterator & rhs) const
   {
      return rhs.nodes.top() == nodes.top();
   }

   // dereference operator
   T & operator * () throw (const char *)
   {
      try
      {
         return nodes.top()->data;
      }
      catch (...)
      {
         throw "ERROR: Cannot dereference iterator";
      }
   }

   // prefix increment & decrement
   iterator & operator ++ ();
   iterator & operator -- ();

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator it = *this;
		++(*this);
		return it;
   }

   iterator operator -- (int postfix)
   {
      iterator it = *this;
		--(*this);
		return it;
   }
};

/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator ++ ()
{
   if (nodes.top() == NULL)
      return *this;

   // Have a right child
   if (nodes.top()->pRight)
   {
      nodes.push(nodes.top()->pRight);

      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);

      return *this;
   }

   assert(!nodes.top()->pRight);
   BNode * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (!nodes.top())
      return *this;

   while (nodes.top() && pSave == nodes.top()->pRight)
	{
		pSave = nodes.top();
		nodes.pop();
	}

   return *this;
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. Note that this implementation uses
 *     a stack of nodes to remember where we are. This stack
 *     is called "nodes".
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BNode * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}

/**************************************************
 * reverse_iterator:: Class Definition
 * A reverse_iterator through BST
 *************************************************/
template <class T>
class BST <T> :: reverse_iterator
{
private:
   stack <BNode *> nodes;
   friend class BST;
public:
   reverse_iterator(BNode * p = NULL)      { nodes.push(p);     }
	reverse_iterator(stack <BNode *> & s)   { nodes = s;         }
	reverse_iterator(const reverse_iterator & rhs)  { nodes = rhs.nodes; }

   reverse_iterator & operator = (const reverse_iterator & rhs)
   {
      nodes = rhs.nodes;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const reverse_iterator & rhs) const
   {
      return rhs.nodes.top() != nodes.top();
   }
   bool operator == (const reverse_iterator & rhs) const
   {
      return rhs.nodes.top() == nodes.top();
   }

   // dereference operator
   T & operator * () throw (const char *)
   {
      try
      {
         return nodes.top()->data;
      }
      catch (...)
      {
         throw "ERROR: Cannot dereference reverse_iterator";
      }
   }

   // prefix increment & decrement
   reverse_iterator & operator ++ ();
   reverse_iterator & operator -- ();

   // postfix increment
   reverse_iterator operator ++ (int postfix)
   {
      reverse_iterator it = *this;
		++(*this);
		return it;
   }

   reverse_iterator operator -- (int postfix)
   {
      reverse_iterator it = *this;
		--(*this);
		return it;
   }
};

/**************************************************
 * BST REVERSE_ITERATOR :: DECREMENT PREFIX
 *     advance by one. Note that this implementation uses
 *     a stack of nodes to remember where we are. This stack
 *     is called "nodes".
 * Author:      Br. Helfrich
 * Modified by: const Etienne Beaulac & John Wood
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
typename BST <T> :: reverse_iterator & BST <T> :: reverse_iterator :: operator -- ()
{
   if (nodes.top() == NULL)
      return *this;

   // Have a right child
   if (nodes.top()->pRight)
   {
      nodes.push(nodes.top()->pRight);

      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);

      return *this;
   }

   assert(!nodes.top()->pRight);
   BNode * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (!nodes.top())
      return *this;

   while (nodes.top() && pSave == nodes.top()->pRight)
	{
		pSave = nodes.top();
		nodes.pop();
	}

   return *this;
}

/**************************************************
 * BST REVERSE_ITERATOR :: INCREMENT PREFIX
 * Increment from right side, backwards
 *************************************************/
template <class T>
typename BST <T> :: reverse_iterator & BST <T> :: reverse_iterator :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BNode * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}

/**************************************************
 * BST :: BEGIN
 * ITERATOR BEGIN
 **************************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: begin() const
{
   if (!root)
      return iterator(NULL);

   stack <BNode *> tempStack;
   BNode * temp = root;
   while (temp)
   {
      tempStack.push(temp);
      temp = temp->pLeft;
   }

   return iterator(tempStack);
}

/**************************************************
 * BST :: RBEGIN
 * REVERSE ITERATOR BEGIN
 **************************************************/
template <class T>
typename BST <T> :: reverse_iterator BST <T> :: rbegin() const
{
   if (!root)
      return reverse_iterator(NULL);

   stack <BNode *> tempStack;
   BNode * temp = root;
   while (temp)
   {
      tempStack.push(temp);
      temp = temp->pRight;
   }

   return reverse_iterator(tempStack);
}

}; // custom

#endif // BST_H
