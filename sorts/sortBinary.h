/***********************************************************************
 * Module:
 *    Week 11, Sort Binary
 *    Brother Helfrich, CS 235
 * Authors:
 *    Etienne Beaulac and John Wood (group 3)
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>

using namespace custom;

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   BST <T> bst;
   for (int i = 0; i < num; i++)
      bst.insert(array[i]);

   int i = 0;
   for (typename BST <T> :: iterator it = bst.begin(); it != bst.end(); ++it)
      array[i++] = *it;
}


#endif // SORT_BINARY_H
