/***********************************************************************
* File:
*    Hash.h
*    Brother Helfrich, CS 235
* Author:
*    John Wood and Etienne Beaulac (group 3)
* Summary:
*    Our implementation of the hash class
************************************************************************/
#ifndef HASH_H
#define HASH_H

#include "bst.h"
#include <cassert>
#include <string>
using std::string;
using namespace custom;

/***********************************************************************
* CLASS HASH (VIRTUAL)
* Our implementation of the Hash class
************************************************************************/
template <class T>
class Hash
{
private:
   BST <T> *table;
   int numElements;
   int numBuckets;
   // To check efficiency!!!
   int emptyBuckets;
   int maxSizeOfBuckets;

public:
   Hash(int num) : table(NULL), numElements(0), numBuckets(num)
   {
      try
      {
         table = new BST <T> [num];
      }
      catch (...)
      {
         throw "ERROR: Unable to allocate memory for the hash";
      }
   }
   Hash(const Hash <T> & rhs) : table(NULL), numElements(0), numBuckets(0) { *this = rhs; }
   ~Hash()                                                   { if (table) delete[] table; }

   Hash <T> & operator = (const Hash <T> & rhs)          throw (const char *);

   int size()     const { return numElements;      }
   int capacity() const { return numBuckets;       }
   bool empty()         { return numElements == 0; }
   void clear();
   void erase(const T & t);

   bool find(const T & t) const;
   void insert(const T & t)                              throw (const char *)
   {
      int i = hash(t);
      table[i].insert(t);
      numElements++;
   }

   virtual int hash(const T & t) const = 0;

   // To find the most efficient size
   void computeEfficiency();
   int getEmptyBuckets() { return emptyBuckets; }
   int getBiggestBucket() { return maxSizeOfBuckets; }
};

/***********************************************************************
* FIND
* Determines whether a value is in the hash or not
************************************************************************/
template <class T>
bool Hash <T> :: find(const T & t) const
{
   int i = hash(t);
   typename BST <T> :: iterator it;
   if (table[i].find(t) != it)
      return true;
   return false;
}

/***********************************************************************
* COMPUTE EFFICIENCY
* Computes the effiency of the hash
************************************************************************/
template <class T>
void Hash <T> :: computeEfficiency()
{
   emptyBuckets = 0;
   maxSizeOfBuckets = 0;
   for (int i = 0; i < numBuckets; ++i)
   {
      if (table[i].empty())
         emptyBuckets++;
      else if (table[i].size() > maxSizeOfBuckets)
         maxSizeOfBuckets = table[i].size();
   }
}

/***********************************************************************
* ASSIGNMENT OPERATOR
* Copy a hash
************************************************************************/
template <class T>
Hash <T> & Hash <T> :: operator = (const Hash <T> & rhs) throw (const char *)
{
   try
   {
      if (table == rhs.table)
         return *this;

      if (numBuckets < rhs.numBuckets)
      {
         numBuckets = rhs.numBuckets;
         numElements = rhs.numElements;
         if (table)
            delete[] table;
         table = new BST <T> [numBuckets];
      }

      for (int i = 0; i < rhs.capacity(); i++)
         table[i] = rhs.table[i];

      return *this;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the hash";
   }
}

/***********************************************************************
* CLEAR
* Clears all elements in the table
************************************************************************/
template <class T>
void Hash <T> :: clear()
{
   for (int i = 0; i < numBuckets; i++)
      table[i].clear();
   numElements = 0;
}

/***********************************************************************
* ERASE
* Erase a specific element in the table
************************************************************************/
template <class T>
void Hash <T> :: erase(const T & t)
{
   int i = hash(t);
   typename BST <T> :: iterator it = table[i].find(t);
   if (it)
      table[i].erase(it);
}

/****************************************
 * S HASH
 * A simple hash of strings
 ****************************************/
class SHash : public Hash <string>
{
public:
   SHash(int numBuckets)    throw (const char *) : Hash <string> (numBuckets) {}
   SHash(const SHash & rhs) throw (const char *) : Hash <string> (rhs)        {}

   // hash function for integers is simply to take the modulous
   int hash(const string & word) const;
};

/****************************************
 * S HASH :: hash
 * We took the total value of all ASCII characters in the word
 * and gave it the index of the remainder from the capacity.
 * We chose to use the total of ASCII characters because they where
 * a good way of analyzing the string and translated to an efficient and
 * smooth experience.
 ****************************************/
inline int SHash :: hash(const string & word) const
{
   int totalASCII = 0;
   for (int i = 0; i < word.length(); ++i)
      totalASCII += int(word[i]);

   int index = totalASCII % capacity();
   assert(0 <= index && index < capacity());
   return index;
}

#endif // hash
