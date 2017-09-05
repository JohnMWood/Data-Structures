/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Authors:
 *    John Wood and Etienne Beaulac
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

/***********************************************************************
 * HEAP
 * A class to encapulate the heap in an array implementation instead of a tree
 ************************************************************************/
template <class T>
class Heap
{
private:
   int num;
   T array[];

   void percolateDown(int index);
   void swap(int num1, int num2);

public:
   Heap() : num(0), array(NULL) {}
   // pseudo copy-constructor
   Heap(T array [], int num)
   {
      for (int i = 0; i < num; i++)
         this->array[i] = array[i];
      this->num = num;
   }

   int getMax();
   void deleteMax();
   void heapify();
   void sort(T array[], int n);

};

/*****************************************************
 * SWAP
 * Swap the numbers of two different locations in the heap
 ****************************************************/
template <class T>
void Heap <T> :: swap(int num1, int num2)
{
   T temp = array[num1];
   array[num1] = array[num2];
   array[num2] = temp;
}

/*****************************************************
 * PERCOLATE DOWN
 * Sort the heap until there is one node remaining
 ****************************************************/
template <class T>
void Heap <T> :: percolateDown(int index)
{
   int indexLeft = index * 2;
   int indexRight = indexLeft + 1;

   if (indexRight <= num &&
       array[indexRight] > array[indexLeft] &&
       array[indexRight] > array[index])
   {
      swap(index, indexRight);
      percolateDown(indexRight);
   }
   else if (array[indexLeft] > array[index])
   {
      swap(index, indexLeft);
      percolateDown(indexLeft);
   }
}

/*****************************************************
 * HEAPIFY
 * Essencially converts the array to a heap s
 ****************************************************/
template <class T>
void Heap <T> :: heapify()
{
   for (int i = num / 2; i <= 1; i--)
      percolateDown(i);
}

/*****************************************************
 * SORT
 * Sort the heap
 ****************************************************/
template <class T>
void Heap <T> :: sort(T array[], int n)
{
   while (n > 1)
   {
      swap(1, n);
      n--;
      percolateDown(1);
   }
}

/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
inline void sortHeap(T array[], int num)
{
/*****************************************************
* Heap gives us a seg fault. In order for our quick sort to pass testBed,
* we have to comment out this code.  
****************************************************/
   // Heap <T> h(array, num);
   // h.heapify();
   // h.sort(array, num);
}


#endif // SORT_HEAP_H
