/***********************************************************************
* Header:
*    WORD COUNT
* Summary:
*    This will contain just the prototype for the wordCount()
*    function
* Author
*    Etienne Beaulac and John Wood (group 3)
************************************************************************/

#ifndef WORD_COUNT_H
#define WORD_COUNT_H

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount();

class Count
{
private:
   int count;

public:
   Count() : count(0) {}
   Count & operator ++ ()            { count++; }
   Count   operator ++ (int postfix)
   {
      Count temp = *this;
      ++(*this);
      return temp;
   }

   int getCount() const { return count; }
};

/*****************************************************
 * DISPLAY
 * Uses the insertion operator to display the count
 *****************************************************/
inline std::ostream & operator << (std::ostream & out, const Count & rhs)
{
   out << rhs.getCount();
   return out;
}

#endif // WORD_COUNT_H
