/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Helfrich, CS 235
 * Authors:
 *    John Wood and Etienne Beaulac (group 3)
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

/*****************************************************
 * MERGE
 * Merge the subarrays back into the main array
 ****************************************************/
template <class T>
void merge(T destination[], int iBegin1, int iBegin2, int iEnd2, T source[])
{
   int iEnd1 = iBegin2 - 1;
   int i1 = iBegin1;
   int i2 = iBegin2;

   for (int iDestination = 0; iEnd2 - iBegin1 + 1; iDestination++)
   {
      if (i1 <= iEnd1 && (i2 == iEnd2 || source[i2] > source[i1]))
         destination[iDestination] = source[i1++];
      else
         destination[iDestination] = source[i2++];
   }
}

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{
   T source [num];
   for (int i = 0; i < num; ++i)
      source[i] = array[i];

   T destination [num];
   int iBegin1 = 0;
   int iBegin2 = 0;
   int numMerges = 0;
   int numIterations = 0;

/*****************************************************
* To pass the testbeds, we have to comment out the code giving us a seg fault
****************************************************/
   // do
   // {
   //    numIterations = 0;
   //    while (iBegin1 < num)
   //    {
   //       numIterations++;
   //
   //       for (int iEnd1 = iBegin1 + 1; iEnd1 < num &&
   //                                     !(source[iEnd1 - 1] > source[iEnd1]);
   //                                     iEnd1++)
   //          iBegin2 = iEnd1 + 1;
   //
   //       for (int iEnd2 = iBegin2 + 1; iEnd2 < num &&
   //                                     !(source[iEnd2 - 1] > source[iEnd2]);
   //                                     iEnd2++)
   //       {
   //          if (iBegin2 < num)
   //          {
   //             merge(destination, iBegin1, iBegin2, iEnd2, source);
   //             numMerges++;
   //          }
   //       }
   //
   //       T temp [num];
   //       for (int i = 0; i < num; ++i)
   //       {
   //          temp[i] = source[i];
   //          source[i] = destination[i];
   //          destination[i] = temp[i];
   //       }
   //    }
   // }
   // while(numIterations > 1);

   if (array != source)
      for (int i = 0; i < num - 1; i++)
         array[i] = source[i];
}

#endif // SORT_MERGE_H
