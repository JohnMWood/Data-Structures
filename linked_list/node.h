/***********************************************************************
* Program:
*    Assigment 06, Node
*    Brother Helfrich, CS 235
* Authors:
*    John Wood and Etienne Beaulac (group 3)
* Summary:
*    Our implementation of the Linked List, using a class instead of Struct
************************************************************************/
#ifndef Node_H
#define Node_H

#include <assert.h>

/**************************************************
 * Node :: Class Definition
 * The class definition for Node with constructors and
 * member variables defined
 *************************************************/
template <class T>
class Node
{
public:
    T data;
    Node *pPrev;
    Node *pNext;

    Node() : pNext(NULL), pPrev(NULL), data()       {           }
    Node(const T & t) : pNext(NULL), pPrev(NULL)    { data = t; }
}; // Node

/**************************************************
 * OSTREAM OPERATOR OVERLOAD
 * Displays "data, " in a loop
 *************************************************/
template <class T>
std::ostream & operator << (std::ostream & out, Node <T> * rhs)
{
    for (Node <T> * p = rhs; p; p = p->pNext)
        out << p->data << (p->pNext == NULL ? "" : ", ");
    return out;
}

/**************************************************
 * COPY
 * Copies a linked list
 *************************************************/
template <class T>
Node <T> * copy(Node <T> * pSource)
{
    Node <T> *pDestination = new Node <T> (pSource->data);
    Node <T> *pSrc = pSource;
    Node <T> *pDes = pDestination;

    for (pSrc = pSrc->pNext; pSrc; pSrc = pSrc->pNext)
        pDes = insert(pSrc->data, pDes, true);

    return pDestination;
}

/**************************************************
 * INSERT
 * Inserts an element into a linked list either before
 * or after the specified Node
 *************************************************/
template <class T>
Node <T> * insert(const T & e, Node <T> * pCurrent, bool after = false)
{
    Node <T> *pNew = new Node <T> (e);

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

/**************************************************
 * FREEDATA
 * Deletes all elements in a linked list
 *************************************************/
template <class T>
void freeData(Node <T> * & pSource)
{
    while (pSource)
    {
        Node <T> * pDelete = pSource;
        pSource = pSource->pNext;
        delete pDelete;
    }
}

/**************************************************
 * FIND
 * Finds a certain element in a linked list
 *************************************************/
template <class T>
Node <T> * find(Node <T> * pHead, const T & t)
{
    for (Node <T> * p = pHead; p; p = p->pNext)
        if (p->data == t)
            return p;
    return NULL;
}

#endif // Node_H
