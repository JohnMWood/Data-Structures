/***********************************************************************
 * Header:
 *    WHOLENUMBER
 * Summary:
 *    Contains data-type that is able to handle numbers of arbitrary length
 *    using a list, where each node can go as high as 999
 * Author
 *    Etienne Beaulac & John Wood, Group 3
 ************************************************************************/
#ifndef WHOLENUMBER_H
#define WHOLENUMBER_H

#include "list.h"
#include <iostream>

using std::cerr;
using std::endl;
using namespace custom;
// using namespace std;

/*****************************************
 * WHOLENUMBER :: CLASS
 * Class definition of the WholeNumber class
 ****************************************/
class WholeNumber
{
public:
    list <unsigned int> nList;

    WholeNumber() {}
    WholeNumber(unsigned int num)
    {
        if (num < 1000)
            nList.push_back(num);
        else
        {
            while (num > 0)
            {
                nList.push_front(num % 1000);
                num /= 1000;
            }
        }
    }
    WholeNumber(const WholeNumber & rhs)                  { *this = rhs;     }
    list <unsigned int> getList() const                   { return nList;    }
    WholeNumber & operator = (const WholeNumber & rhs)    throw (const char *);
    WholeNumber & operator += (const WholeNumber & rhs);
    WholeNumber & operator -= (const WholeNumber & rhs);
private:
    void carry(list <unsigned int> :: reverse_iterator it);
    bool subCarry(list <unsigned int> :: reverse_iterator it);
};

inline void WholeNumber :: carry(list <unsigned int> :: reverse_iterator it)
{
    if (++it == NULL)
        nList.push_front(1);
    else
    {
        (*it)++;
        if ((*it) == 1000)
        {
            (*it) = 0;
            carry(it);
        }
    }
}

inline bool WholeNumber :: subCarry(list <unsigned int> :: reverse_iterator it)
{
    if (++it != NULL)
    {
        if ((*it) == 0)
        {
            return 1;
        }
        else
            (*it)--;
    }
    return 0;
}

inline WholeNumber & WholeNumber::operator -= (const WholeNumber & rhs)
{
    bool carry = 0;
    int count = 0;
    list<unsigned int>::reverse_iterator lhs_it = nList.rbegin();
    list<unsigned int>::reverse_iterator rhs_it = rhs.nList.rbegin();
    while (lhs_it != nList.rend() && rhs_it != rhs.nList.rend())
    {
        assert (*lhs_it < 1000);
        assert (*rhs_it < 1000);

        if (*rhs_it > *lhs_it)
        {
            if (subCarry(lhs_it))
                count++;
            int lhs = *lhs_it;
            int rhs = *rhs_it;

            lhs = lhs - rhs + 1000;
            if (carry)
            {
                lhs--;
                carry = false;
            }
            if (count == 1)
            {
                count = 0;
                carry = true;
            }
            assert(lhs >= 0);
            *lhs_it = lhs;
        }
        else
            *lhs_it = *lhs_it - *rhs_it;
        assert (*lhs_it < 1000);
        assert (*rhs_it < 1000);
        ++lhs_it;
        ++rhs_it;
    }
}

/*****************************************
 * WHOLENUMBER :: ADD UNTO
 * ADDS TWO WHOLE NUMBERS
 ****************************************/
inline WholeNumber & WholeNumber::operator += (const WholeNumber & rhs)
{
    list<unsigned int>::reverse_iterator lhs_it = nList.rbegin();
    list<unsigned int>::reverse_iterator rhs_it = rhs.nList.rbegin();
    // bool carry = false;
    while (rhs_it != rhs.nList.rend())
    {
        assert (*lhs_it < 1000);
        assert (*rhs_it < 1000);

        if (lhs_it != NULL)
        {
            unsigned int temp = *rhs_it + *lhs_it;
            if (temp > 999)
            {
                temp -= 1000;
                carry(lhs_it);
            }
            assert (lhs_it != NULL);
            *lhs_it = temp;
            assert (*lhs_it < 1000);
            assert (*rhs_it < 1000);
            ++lhs_it;
            ++rhs_it;
        }
        else
        {
            unsigned int temp = *rhs_it;
            nList.push_front(temp);
            assert (*lhs_it < 1000);
            assert (*rhs_it < 1000);
            rhs_it++;
        }
    }
}

/*****************************************
 * WHOLENUMBER :: ASSIGNMENT
 * Display the contents of the list forwards
 ****************************************/
inline WholeNumber & WholeNumber :: operator = (const WholeNumber & rhs) throw (const char *)
{
    nList = rhs.nList;
}

/*****************************************
 * WHOLENUMBER :: DISPLAY
 * Display the contents of the list forwards
 ****************************************/
inline std::ostream & operator << (std::ostream & out, WholeNumber & rhs)
{
    out << "\t";
    bool firstIteration = true;
    for (list<unsigned int>::iterator it = rhs.nList.begin(); it != rhs.nList.end(); ++it)
    {
        if (*it < 10 && !firstIteration) // Display some extra zeros if inside the number
            out << "00";
        else if (*it < 100 && !firstIteration)
            out << "0";
        out << *it;
        if (++it != rhs.nList.end()) // Put the comma if we're not at the end
            out << ",";
        --it;
        firstIteration = false;
    }
    return out;
}

#endif // WHOLENUMBER_H
