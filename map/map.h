/***********************************************************************
* Program:
*    Assignment 10, Map
*    Brother Helfrich, CS 235
* Authors:
*    John Wood and Etienne Beaulac (group 3)
* Summary:
*    Our class implementation of the map class
************************************************************************/
#ifndef MAP_H
#define MAP_H

#include "bst.h"
#include "pair.h"

namespace custom
{

template <class K, class V>
class map
{
private:
   BST <Pair <K, V> > bst;

public:
   map() : bst()                                    {                     }
   map(const map <K, V> & rhs) throw (const char *) { *this = rhs;        }
   ~map()                                           { bst.clear();        }
   map <K, V> & operator = (const map <K, V> & rhs) throw (const char *)
   {
      bst = rhs.bst;
   }

   V   operator [] (const K & k) const throw (const char *);
   V & operator [] (const K & k)       throw (const char *);

   int size()                                      { return bst.size();   }
   bool empty()                                    { return bst.empty();  }
   void clear()                                    { bst.clear();         }

   class iterator;
   iterator begin()                                { return bst.begin();  }
   iterator rbegin()                               { return bst.rbegin(); }
   iterator end()                                  { return bst.end();    }
   iterator rend()                                 { return bst.rend();   }
   iterator find(const K & k);
}; // map

/**************************************************
 * Map :: find
 * Finds the key, if not found creates it
 * Returns an iterator pointing to it
 *************************************************/
template <class K, class V>
typename map <K, V> :: iterator map <K, V> :: find(const K & k)
{
   Pair <K, V> pair(k, V());
   typename map <K, V> :: iterator it = bst.find(pair);
   if (end() != it)
      return it;
   else
   {
      bst.insert(pair);
      return bst.find(pair);
   }
}

/**************************************************
 * Map :: Access operator
 * Finds the value associated with the given key
 *************************************************/
template <class K, class V>
V & map <K, V> :: operator [] (const K & k)       throw (const char *)
{
   return (*find(k)).second;
}

/**************************************************
 * Map :: Access const operator
 * Finds the value associated with the given key
 *************************************************/
template <class K, class V>
V   map <K, V> :: operator [] (const K & k) const throw (const char *)
{
   return (*find(k)).getSecond();
}

/**************************************************
 * iterator:: Class Definition
 * An iterator through BST
 *************************************************/
template <class K, class V>
class map <K, V> :: iterator
{
private:
   typename BST <Pair <K, V> > :: iterator it;
   friend class map;
public:
   iterator() : it() { }
   iterator(typename BST <Pair <K, V> > :: iterator it)         { this->it = it; }
   iterator(typename BST <Pair <K, V> > :: reverse_iterator it) { this->it = it; }
	iterator(const iterator & rhs)                               { (*this) = rhs; }

   // assignment operator
   iterator & operator = (const iterator & rhs)           { it = rhs.it;         }
   bool operator != (const iterator & rhs) const          { return rhs.it != it; }
   bool operator == (const iterator & rhs) const          { return rhs.it == it; }
   Pair <K, V> & operator * ()                            { return *it;          }

   iterator & operator ++ ()                                             { ++it; }
   iterator & operator -- ()                                             { --it; }
   iterator operator ++ (int postfix)                                    { it++; }
   iterator operator -- (int postfix)                                    { it--; }
};

}; // namespace custom

#endif // MAP_H
