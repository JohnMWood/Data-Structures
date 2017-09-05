/***********************************************************************
* Program:
*    Assigment 05, Set
*    Brother Helfrich, CS 235
* Authors:
*    John Wood and Etienne Beaulac (group 3)
* Summary:
*    Our implementation of the STL set class, with a const iterator
*    and subtraction operator overload for the difference function
************************************************************************/
#ifndef SET_H
#define SET_H

#include <assert.h>
#include <cstdlib>

namespace custom
{

/**************************************************
 * SET :: Class Definition
 * The class definition for set with methods and
 * member variables defined
 *************************************************/
template <class T>
class set
{
private:
    T *array;
    int numElements;
    int numCapacity;

    int findIndex(T t) const;
    void resize(int numCapacity) throw (const char *);

public:
    set() : array(NULL), numElements(0), numCapacity(0) { }
    set(int newCapacity) : array(NULL), numElements(0)
    {
        numCapacity = newCapacity;
    }
    set(const set &rhs) : array(NULL), numElements(0), numCapacity(0)
    {
        *this = rhs;
    }
    ~set()                          { if(numCapacity > 0) delete [] array;  }
    set <T> & operator = (const set <T> & rhs) throw (const char *);

    int size()              const   { return numElements;                   }
    bool empty()            const   { return numElements == 0;              }
    void clear()                    { numElements = 0;                      }

    class iterator;
    iterator begin()        const   { return iterator(array);               }
    iterator end()          const   { return iterator(array + numElements); }

    class const_iterator;
    const_iterator cbegin() const   { return const_iterator(array);         }
    const_iterator cend()   const
    {
        return const_iterator(array + numElements);
    }

    iterator find(T t)      const;
    void insert(T t);
    void erase(set <T> :: iterator & it);

    // intersection, union, and difference operators
    set <T> operator && (const set <T> & rhs) const throw (const char *);
    set <T> operator || (const set <T> & rhs) const throw (const char *);
    set <T> operator -  (const set <T> & rhs) const throw (const char *);
}; // set



/**************************************************
 * SET ITERATOR
 * An iterator through set
 *************************************************/
template <class T>
class set <T> :: iterator
{
public:
    // constructors, destructors, and assignment operator
    iterator()      : p(NULL)      {              }
    iterator(T * p) : p(p)         {              }
    iterator(const iterator & rhs) { *this = rhs; }
    iterator & operator = (const iterator & rhs)
    {
	this->p = rhs.p;
	return *this;
    }

    // equals, not equals operator
    bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
    bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

    // dereference operator
    T & operator * ()
    {
	return *p;
    }

    // prefix increment
    iterator & operator ++ ()
    {
        p++;
        return *this;
    }

    iterator & operator -- ()
    {
     	p--;
       	return *this;
    }

    // postfix increment
    iterator operator ++ (int postfix)
    {
       	iterator tmp(*this);
       	p++;
       	return tmp;
    }

    iterator operator -- (int postfix)
    {
       	iterator tmp(*this);
       	p--;
       	return tmp;
    }

private:
    T * p;
};

/**************************************************
 * SET CONST_ITERATOR
 * An iterator through set
 *************************************************/
template <class T>
class set <T> :: const_iterator
{
private:
    T * p;

public:
    // constructors, destructors, and assignment operator
    const_iterator()      : p(NULL)      {              }
    const_iterator(T * p) : p(p)         {              }
    const_iterator(const const_iterator & rhs) { *this = rhs; }
    iterator & operator = (const iterator & rhs)
    {
       	this->p = rhs.p;
       	return *this;
     }

     // equals, not equals operator
     bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
     bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

     // dereference operator
     // const before == return value is const
     // const after  == cannot change values within the function
     const T operator * () const
     {
       	return *p;
     }

     // prefix increment
     const_iterator & operator ++ ()
     {
       	p++;
       	return *this;
     }

     const_iterator & operator -- ()
     {
       	p--;
       	return *this;
     }

     // postfix increment
     const_iterator operator ++ (int postfix)
     {
       	iterator tmp(*this);
       	p++;
       	return tmp;
     }

     const_iterator operator -- (int postfix)
     {
        iterator tmp(*this);
        p--;
        return tmp;
     }
};

/*******************************************
 * SET :: Assignment Operator
 * Copy the elements of one set to another
 *******************************************/
template <class T>
set <T> & set <T> :: operator = (const set <T> & rhs) throw (const char *)
{
    if (&rhs == this)
        return *this;

    // if the current set does not have enough capacity,
    // give the current set more
    if (numCapacity < rhs.size())
		resize(rhs.size());

    assert(numCapacity >= rhs.size());
    for (int i = 0; i < rhs.size(); i++)
       	array[i] = rhs.array[i];

    numElements = rhs.numElements;
    numCapacity = rhs.numCapacity;

    return *this;
}

/*******************************************
 * SET :: RESIZE
 * Resize to accommodate for more elements in the set
 *******************************************/
template <class T>
inline void set <T> :: resize(int newCapacity) throw (const char *)
{
    assert(numCapacity >= 0);
    if(newCapacity == 0)
        return;

    T *temp;
    try
    {
    	temp = new T[newCapacity];
    }
    catch (...)
    {
       	throw "ERROR: Unable to alloacate a new buffer for set";
    }

    for (int i = 0; i < size(); i++)
       	temp[i] = array[i];
    delete [] array;
    array = temp;
    numCapacity = newCapacity;
    assert(size() <= numCapacity);
}

/*******************************************
 * SET :: INSERT
 * Get the index where the new element will go (if the element
 * is not already in the set), move all the other elements to the
 * right, and insert the element into the set
 *******************************************/
template <class T>
inline void set <T> :: insert(T t)
{
    int iInsert = findIndex(t);
    if(iInsert >= 0)
        return;
    if(numCapacity == 0)
        resize(2);
    else if(numElements + 1 == numCapacity)
        resize(numCapacity * 2);

    iInsert = -1 + -iInsert;
    assert(iInsert >= 0);

    for(int i = numElements; i >= iInsert; i--)
        array[i + 1] = array[i];

    array[iInsert] = t;
    numElements++;
}

/*******************************************
 * SET :: FINDINDEX
 * Uses a binary search to find a given element
 * in a set and return its index
 *******************************************/
template <class T>
inline int set <T> :: findIndex(T t) const
{
    int iBegin = 0;
    int iEnd = numElements - 1;
    int iMiddle;

    while(iBegin <= iEnd)
    {
        iMiddle = (iBegin + iEnd) / 2;
        if(t == array[iMiddle])
            return iMiddle;
        if(t < array[iMiddle])
            iEnd = iMiddle - 1;
        else
            iBegin = iMiddle + 1;
    }
    return -1 - iBegin;
}

/*******************************************
 * SET :: FIND
 * If the element is in set, return an iterator to it,
 * otherwise, return an iterator to the end of the set
 *******************************************/
template <class T>
typename set <T> :: iterator set <T> :: find(T t) const
{
    int iInsert = findIndex(t);
    if(iInsert < 0)
        return end();

    return iterator(array + iInsert);
}

/*******************************************
 * SET :: ERASE
 * Find an element in a set and delete it
 *******************************************/
template <class T>
inline void set <T> :: erase(set <T> :: iterator & it)
{
    int iErase = findIndex(*it);
    if(array[iErase] == *it)
    {
        for(int i = iErase; i < numElements; i++)
            array[i] = array[i + 1];
        numElements--;
    }
}

/*******************************************
 * SET :: INTERSECTION
 * Find all elements in common between two sets
 * and return a new set with those elements
 *******************************************/
template <class T>
set <T> set <T> :: operator && (const set <T> & rhs) const throw (const char *)
{
    int iSet1 = 0;
    int iSet2 = 0;
    set <T> newSet;
    while(iSet1 < numElements || iSet2 < rhs.numElements)
    {
        if(iSet1 == numElements)
            return newSet;
        else if(iSet2 == rhs.numElements)
            return newSet;
        else if(array[iSet1] == rhs.array[iSet2])
        {
            newSet.insert(array[iSet1]);
            iSet1++;
            iSet2++;
        }
        else if(array[iSet1] < rhs.array[iSet2])
            iSet1++;
        else
            iSet2++;
    }
    return newSet;
}

/*******************************************
 * SET :: UNION
 * Creates a new set with all elements between
 * two sets
 *******************************************/
template <class T>
set <T> set <T> :: operator || (const set <T> & rhs) const throw (const char *)
{
    int iSet1 = 0;
    int iSet2 = 0;
    set <T> newSet;
    while(iSet1 < numElements || iSet2 < rhs.numElements)
    {
        if(iSet1 == numElements)
            newSet.insert(rhs.array[iSet2++]);
        else if(iSet2 == rhs.numElements)
            newSet.insert(array[iSet1++]);
        else if(array[iSet1] == rhs.array[iSet2])
        {
            newSet.insert(array[iSet1]);
            iSet1++;
            iSet2++;
        }
        else if(array[iSet1] < rhs.array[iSet2])
            newSet.insert(array[iSet1++]);
        else
            newSet.insert(rhs.array[iSet2++]);
    }
    return newSet;
}

/*******************************************
 * SET :: DIFFERENCE
 * Returns a new set with all of the elements of a set
 * minus the elements of a second set
 *******************************************/
template <class T>
set <T> set <T> :: operator - (const set <T> & rhs) const throw (const char *)
{
    int iSet1 = 0;
    int iSet2 = 0;
    set <T> newSet;
    while(iSet1 < numElements || iSet2 < rhs.numElements)
    {
        if(iSet1 == numElements)
            return newSet;
        else if(iSet2 == rhs.numElements)
            newSet.insert(array[iSet1++]);
        else if(array[iSet1] == rhs.array[iSet2])
        {
            iSet1++;
            iSet2++;
        }
        else if(array[iSet1] < rhs.array[iSet2])
            newSet.insert(array[iSet1++]);
        else
            iSet2++;
    }
    return newSet;
}

} // namespace custom

#endif // SET_H
