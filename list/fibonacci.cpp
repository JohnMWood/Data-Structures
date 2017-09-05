/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "wholeNumber.h"
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
    // show the first serveral Fibonacci numbers
    unsigned int number;
    cout << "How many Fibonacci numbers would you like to see? ";
    cin  >> number;

    // your code to display the first <number> Fibonacci numbers
    WholeNumber fibNum (1);
    WholeNumber fibNum2 (1);

    for (int i = 0; i < number; i++)
    {
        if (i == 0 || i == 1)
            cout << fibNum << endl;
        else
        {
            fibNum += fibNum2;
            cout << fibNum << endl;
            WholeNumber temp = fibNum;
            temp -= fibNum2;
            fibNum2 = temp;
        }
    }

    // prompt for a single large Fibonacci
    cout << "Which Fibonacci number would you like to display? ";
    cin  >> number;

    fibNum = 1;
    fibNum2 = 1;
    // your code to display the <number>th Fibonacci number
    for (int i = 0; i < number; i++)
    {
        if (i == 0 || i == 1)
            continue;
        else
        {
            fibNum += fibNum2;
            WholeNumber temp = fibNum;
            temp -= fibNum2;
            fibNum2 = temp;
        }
    }
    cout << fibNum << endl;

}
