/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Etienne Beaulac & John Wood
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"
#include <iostream>
using namespace std;

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
    Node <T> * pHead = new Node <T> (array[0]);
    for (int i = 1; i < num; i++)
    {
        // Know when the node loop needs to end
        bool goLoop = true;
        int slot = 0;
        for (Node <T> * p = pHead; goLoop; p = p->pNext)
        {
            // If the desired element is smaller
            if (array[i] <= p->data)
            {
                p = insert(array[i], p, false);
                goLoop = false;
                // If we're in the first slot, update pHead
                if (slot == 0)
                    pHead = p;
            } // If it is bigger and there are no other nodes
            else if (!p->pNext)
            {
                p = insert(array[i], p, true);
                goLoop = false;
            }
            slot++;
        } // NODE FOR LOOP
    } // ARRAY FOR LOOP

    for (int i = 0; i < num; i++)
    {
        // Always check for NULL
        if (pHead)
            array[i] = pHead->data;
        if (pHead->pNext)
            pHead = pHead->pNext;
    }
}

#endif // INSERTION_SORT_H
