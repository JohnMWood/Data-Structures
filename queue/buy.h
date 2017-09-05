/***********************************************************************
 * File:
 *    buy.h
 * Summary:
 *    Our buy class
 * Authors:
 *    John Wood and Etienne Beaulac (group 3)
 **********************************************************************/
 #ifndef BUY_H
 #define BUY_H

#include "dollars.h"

/**********************************************************************
  * CLASS : BUY
  * Contains the logic to keep track of amount of stocks bought and
  * and its value.
  **********************************************************************/
class Buy
{
private:
    int amount;
    Dollars value;

public:
    Buy() : amount(0), value(0) {}
    Buy(int numStocks, Dollars money);
    Buy(const Buy & rhs);
    ~Buy();

    int getAmount()    { return amount; }
    Dollars getValue() { return value;  }

    void setAmount(int amount ) { this->amount = amount; }
    void setValue(int value )   { this->value  = value;  }

    void display()
    {
        std::cout << "\tBought " << amount
                  << " shares at " << value << std::endl;
    }
};

/**********************************************************************
 * BUY :: NON-DEFAULT CONSTRUCTOR
 **********************************************************************/
inline Buy :: Buy(int numStocks, Dollars money)
{
    amount = numStocks;
    value  = money;
}

/**********************************************************************
 * BUY :: COPY CONSTRUCTOR
 **********************************************************************/
inline Buy :: Buy(const Buy & rhs)
{
    this->amount = rhs.amount;
    this->value  = rhs.value;
}

/**********************************************************************
 * BUY :: DECONSTRUCTOR
 **********************************************************************/
inline Buy :: ~Buy()
{
    amount = 0;
    value  = 0;
}

 #endif // BUY_H
