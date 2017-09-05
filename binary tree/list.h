/***********************************************************************
* Program:
*    Assigment 07, list
*    Brother Helfrich, CS 235
* Authors:
*    John Wood and Etienne Beaulac (group 3)
* Summary:
*    Our implementation of the std::list, implementing linked-lists
************************************************************************/
#ifndef LIST_H
#define LIST_H

#include <assert.h>
#include <iostream>

namespace custom
{
/**************************************************
 * list :: Class Definition
 * The class definition for list with constructors,
 * member variables and methods defined
 *************************************************/
template <class T>
class list
{
public:
    list() : pHead(NULL), pTail(NULL), numElements(0) {}
    list(const list & rhs) throw (const char *) : pHead(NULL), pTail(NULL), numElements(0)
    {
        *this = rhs;
    }
    ~list() { clear(); }

    list <T> & operator = (const list <T> & rhs)         throw (const char *);
    int size()                const { return numElements;                   }
    bool empty()              const { return numElements == 0;              }
    void clear();

    void push_back(const T & t)                          throw (const char *);
    void push_front(const T & t)                         throw (const char *);
    void pop_back();
    void pop_front();
    const T & front()         const                      throw (const char *)
    {
        if (!empty()) return pHead->data;
        throw "ERROR: unable to access data from an empty list";
    }
    const T & back()          const                      throw (const char *)
    {
        if (!empty()) return pTail->data;
        throw "ERROR: unable to access data from an empty list";
    }
    T & front()                                          throw (const char *)
    {
        if (!empty()) return pHead->data;
        throw "ERROR: unable to access data from an empty list";
    }
    T & back()                                           throw (const char *)
    {
        if (!empty()) return pTail-> data;
        throw "ERROR: unable to access data from an empty list";
    }

    class Node;

    class iterator;
    iterator begin()          const { return iterator(pHead);               }
    iterator end()            const { return iterator(NULL);                }

    class reverse_iterator;
    reverse_iterator rbegin() const { return reverse_iterator(pTail);       }
    reverse_iterator rend()   const { return reverse_iterator(NULL);        }

    class const_iterator;
    const_iterator cbegin()   const { return const_iterator(pHead);         }
    const_iterator cend()     const { return const_iterator(NULL);          }

    class const_reverse_iterator;
    const_reverse_iterator crbegin() const { return const_reverse_iterator(pTail); }
    const_reverse_iterator crend()   const { return const_reverse_iterator(NULL);  }

    iterator erase(list <T> :: iterator it);
    iterator insert(list <T> :: iterator it, const T & t)
                                                         throw (const char *);

 public:
    Node * insert(const T & e, Node * pCurrent, bool after = false);
    Node * pHead;
    Node * pTail;
    int numElements;
 }; // list CLASS

/**************************************************
 * Node :: Class Definition
 * The class definition for Node with constructors and
 * member variables defined
 *************************************************/
template <class T>
class list <T> :: Node
{
public:
    T data;
    Node *pPrev;
    Node *pNext;

    Node() : pNext(NULL), pPrev(NULL), data()             {}
    Node(const T & t) : pNext(NULL), pPrev(NULL), data(t) {}
}; // Node

/*******************************************
 * LIST :: erase
 * Inserts a given element at a given location
 *******************************************/
template <class T>
typename list <T> :: iterator list <T> :: erase(list <T> :: iterator it)
{
    if (it == end())
        return it;

    Node * pDelete = it.p;
    if (!it.p->pNext)
    {
        pTail = it.p->pPrev;
        it.p->pPrev->pNext = NULL;
    }
    else if (!it.p->pPrev)
        pHead = it.p->pNext;
    else if (it.p->pNext)
    {
        it.p->pPrev->pNext = it.p->pNext;
        it.p->pNext->pPrev = it.p->pPrev;
    }

    delete pDelete;
    numElements--;

    return it;
}

/*******************************************
 * LIST :: insert
 * Inserts a given element at a given location
 *******************************************/
template <class T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it,
                                    const T & t) throw (const char *)
{
    try
    {
        Node *pNew = new Node (t);

        if (it.p == pHead) // beginning of list
        {
            pNew->pNext = it.p;
            it.p->pPrev = pNew;
            pHead = pNew;
        }
        else if (it.p) // Put before the desired node
        {
            pNew->pNext = it.p;
            pNew->pPrev = it.p->pPrev;
            it.p->pPrev = pNew;
            if (pNew->pPrev)
                pNew->pPrev->pNext = pNew;
            else
                pHead = pNew;
            --it;
        }
        else
        {
            pNew->pPrev = pTail;
            pNew->pPrev->pNext = pNew;
            pTail = pNew;
        }

        numElements++;
        return it;
    }
    catch (...)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
}

/*******************************************
 * LIST :: Assignment Operator
 * Copy the elements of one list to another
 *******************************************/
template <class T>
list <T> & list <T> :: operator = (const list <T> & rhs) throw (const char *)
{
    try
    {
        if (&rhs == this)
            return *this;

        clear();

        pHead = new Node (rhs.pHead->data);
        Node * pSrc = rhs.pHead;
        Node * pDes = pHead;

        for (pSrc = pSrc->pNext; pSrc; pSrc = pSrc->pNext)
            pDes = insert(pSrc->data, pDes, true);
        pTail = pDes;

        numElements = rhs.numElements;
        return *this;
    }
    catch (...)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
}

/**************************************************
 * LIST :: INSERT (private)
 * Inserts an element into a linked list either before
 * or after the specified Node
 *************************************************/
template <class T>
typename list <T> :: Node * list <T> :: insert(const T & e, Node * pCurrent, bool after)
{
    try
    {
        Node *pNew = new Node (e);

        if (pCurrent && !after) // Put before the desired node
        {
            pNew->pNext = pCurrent;
            pNew->pPrev = pCurrent->pPrev;
            pCurrent->pPrev = pNew;
            if (pNew->pPrev)
                pNew->pPrev->pNext = pNew;
        }
        if (pCurrent && after) // Put after the desired node
        {
            pNew->pPrev = pCurrent;
            pNew->pNext = pCurrent->pNext;
            pCurrent->pNext = pNew;
            if (pNew->pNext)
                pNew->pNext->pPrev = pNew;
        }

        return pNew;
    }
    catch (...)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
}

/**************************************************
 * LIST :: Clear
 * Clears the whole list
 *************************************************/
template <class T>
void list <T> :: clear()
{
    while (pHead)
    {
        Node * pDelete = pHead;
        pHead = pHead->pNext;
        delete pDelete;
    }
    pTail = NULL;
    numElements = 0;
}

/**************************************************
 * LIST :: Push Back
 * Pushes an element on the end of the list
 *************************************************/
template <class T>
void list <T> :: push_back(const T & t) throw (const char *)
{
    try
    {
        Node * pNew = new Node (t);

        if (pTail) // Put after the desired node
        {
            pNew->pPrev = pTail;
            pNew->pNext = NULL;
            pTail->pNext = pNew;
            pTail = pNew;
        }
        else
            pHead = pTail = pNew;

        numElements++;
    }
    catch (...)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
}

/**************************************************
 * LIST :: Push Front
 * Pushes an element on the front of the list
 *************************************************/
template <class T>
void list <T> :: push_front(const T & t) throw (const char *)
{
    try
    {
        Node * pNew = new Node (t);

        if (pHead) // Put before the desired node
        {
            pNew->pNext = pHead;
            pNew->pPrev = pHead->pPrev;
            pHead->pPrev = pNew;
            if (pNew->pPrev)
                pNew->pPrev->pNext = pNew;
            pHead = pNew;
        }
        else
            pHead = pTail = pNew;

        numElements++;
    }
    catch (...)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
}

/**************************************************
 * LIST :: Pop Back
 * Removes an element from the end of the list
 *************************************************/
template <class T>
void list <T> :: pop_back()
{
    if (pTail)
    {
        Node * pDelete = pTail;
        pTail = pTail->pPrev;
        delete pDelete;
        numElements--;
    }
}

/**************************************************
 * LIST :: Pop Front
 * Removes an element from the front of the list
 *************************************************/
template <class T>
void list <T> :: pop_front()
{
    if (pHead)
    {
        Node * pDelete = pHead;
        pHead = pHead->pNext;
        delete pDelete;
        numElements--;
    }
}

/**************************************************
 * LIST ITERATOR
 * An iterator through list
 *************************************************/
template <class T>
class list <T> :: iterator
{
public:
     // constructors, destructors, and assignment operator
     iterator()         : p(NULL)   {              }
     iterator(Node * p) : p(p)      {              }
     iterator(const iterator & rhs) { *this = rhs; }
     iterator & operator = (const iterator & rhs)
     {
         p = rhs.p;
 	     return *this;
     }

     // equals, not equals operator
     bool operator != (const iterator & rhs) const
     {
         return rhs.p != this->p;
     }
     bool operator == (const iterator & rhs) const
     {
         return rhs.p == this->p;
     }

     // dereference operator
     T & operator * () throw (const char *)
     {
         try
         {
             return p->data;
         }
         catch (...)
         {
             throw "ERROR: Cannot dereference iterator";
         }
     }

     // prefix increment
     iterator & operator ++ ()
     {
         if (p)
            p = p->pNext;
         return *this;
     }

     iterator & operator -- ()
     {
         if (p)
      	     p = p->pPrev;
         return *this;
     }

     // postfix increment
     iterator operator ++ (int postfix)
     {
         iterator tmp(*this);
         if (p)
            p = p->pNext;
         return tmp;
     }

     iterator operator -- (int postfix)
     {
         iterator tmp(*this);
         if (p)
      	     p = p->pPrev;
         return tmp;
     }

private:
     Node * p;
     friend class list;
};

/**************************************************
 * LIST REVERSE ITERATOR
 * A reverse iterator through list
 *************************************************/
template <class T>
class list <T> :: reverse_iterator
{
public:
     // constructors, destructors, and assignment operator
    reverse_iterator()         : p(NULL)   {              }
    reverse_iterator(Node * p) : p(p)      {              }
    reverse_iterator(const reverse_iterator & rhs) { *this = rhs; }
    reverse_iterator & operator = (const reverse_iterator & rhs)
    {
        p = rhs.p;
 	    return *this;
    }

    // equals, not equals operator
    bool operator != (const reverse_iterator & rhs) const
    {
        return rhs.p != this->p;
    }
    bool operator == (const reverse_iterator & rhs) const
    {
        return rhs.p == this->p;
    }

    // dereference operator
    T & operator * () throw (const char *)
    {
        try
        {
            return p->data;
        }
        catch (...)
        {
            throw "ERROR: Cannot dereference iterator";
        }
    }

    // prefix increment
    reverse_iterator & operator ++ ()
    {
        if (p)
            p = p->pPrev;
        return *this;
    }

    reverse_iterator & operator -- ()
    {
        if (p)
      	    p = p->pNext;
        return *this;
    }

    // postfix increment
    reverse_iterator operator ++ (int postfix)
    {
        reverse_iterator tmp(*this);
        if (p)
            p = p->pPrev;
        return tmp;
    }

    reverse_iterator operator -- (int postfix)
    {
        reverse_iterator tmp(*this);
        if (p)
      	    p = p->pNext;
        return tmp;
    }

private:
    Node * p;
    friend class list;
};

/**************************************************
 * LIST CONST_ITERATOR
 * A const iterator through list
 *************************************************/
template <class T>
class list <T> :: const_iterator
{
private:
    T * p;
    friend class list;
public:
    // constructors, destructors, and assignment operator
    const_iterator()      : p(NULL)             {              }
    const_iterator(T * p) : p(p)                {              }
    const_iterator(const const_iterator & rhs)  { *this = rhs; }
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

/**************************************************
 * LIST CONST REVERSE ITERATOR
 * A const reverse iterator through list
 *************************************************/
template <class T>
class list <T> :: const_reverse_iterator
{
public:
     // constructors, destructors, and assignment operator
    const_reverse_iterator()         : p(NULL)   {              }
    const_reverse_iterator(Node * p) : p(p)      {              }
    const_reverse_iterator(const iterator & rhs) { *this = rhs; }
    const_reverse_iterator & operator = (const const_reverse_iterator & rhs)
    {
        p = rhs.p;
 	    return *this;
    }

    // equals, not equals operator
    bool operator != (const const_reverse_iterator & rhs) const
    {
        return rhs.p != this->p;
    }
    bool operator == (const const_reverse_iterator & rhs) const
    {
        return rhs.p == this->p;
    }

    // dereference operator
    const T & operator * () throw (const char *)
    {
        try
        {
            return p->data;
        }
        catch (...)
        {
            throw "ERROR: Cannot dereference iterator";
        }
    }

    // prefix increment
    const_reverse_iterator & operator ++ ()
    {
        if (p)
            p = p->pPrev;
        return *this;
    }

    const_reverse_iterator & operator -- ()
    {
        if (p)
      	    p = p->pNext;
        return *this;
    }

    // postfix increment
    const_reverse_iterator operator ++ (int postfix)
    {
        const_reverse_iterator tmp(*this);
        if (p)
            p = p->pPrev;
        return tmp;
    }

    const_reverse_iterator operator -- (int postfix)
    {
        const_reverse_iterator tmp(*this);
        if (p)
      	    p = p->pNext;
        return tmp;
    }

private:
    Node * p;
    friend class list;
};

} // namespace custom

#endif // LIST_H
