/***********************************************************************
 * Module:
 *    Week 11, Sort Quick
 *    Brother Helfrich, CS 235
 * Authors:
 *    John Wood and Etienne Beaulac (group 3)
 * Summary:
 *    This program will implement the Quick Sort
 ************************************************************************/

#ifndef SORT_QUICK_H
#define SORT_QUICK_H

/*****************************************************
 * SORT QUICK
 * Perform the quick sort
 ****************************************************/
template <class T>
void sortQuick(T array[], int num)
{
   if (num <= 1)
      return;

   int iDown = num - 1;
   int iEnd = num - 1;
   int iUp = 0;
   T pivotValue = array[iEnd / 2];

   while (iUp <= iDown)
   {
      while (iUp <= iEnd && pivotValue > array[iUp])
         ++iUp;

      while (iDown >= 0 && array[iDown] > pivotValue)
         --iDown;

      if (iUp <= iDown)
      {
         T temp = array[iUp];
         array[iUp] = array[iDown];
         array[iDown] = temp;
         iUp++;
         iDown--;
      }
   }

   sortQuick(array, iUp);
   sortQuick(array + iUp, iEnd - iUp + 1);
}


#endif // SORT_QUICK_H
