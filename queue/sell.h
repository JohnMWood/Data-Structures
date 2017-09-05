/***********************************************************************
 * File:
 *    sell.h
 * Summary:
 *    Our sell class
 * Authors:
 *    John Wood and Etienne Beaulac (group 3)
 **********************************************************************/
 #ifndef SELL_H
 #define SELL_H

 #include "dollars.h"


 /**********************************************************************
  * CLASS : SELL
  * Contains the logic to keep track of profit, amount of stocks sold,
  * and its value.
  **********************************************************************/
 class Sell
 {
 private:
     int amount;
     Dollars value;
     Dollars profit;

 public:
     Sell() : amount(0), value(0.0) {}
     Sell(int numStocks, Dollars money, Dollars newProfit);
     Sell(const Sell &rhs);
     ~Sell();

     int getAmount()     { return amount; }
     Dollars getValue()  { return value;  }
     Dollars getProfit() { return profit; }

     void display()
     {
         std::cout << "\tSold " << amount << " shares at " << value
                   << " for a profit of " << profit << std::endl;
     }
 };

 /**********************************************************************
  * SELL :: NON-DEFAULT CONSTRUCTOR
  **********************************************************************/
 inline Sell :: Sell(int numStocks, Dollars money, Dollars newProfit)
 {
     amount = numStocks;
     value  = money;
     profit = newProfit;
 }

 /**********************************************************************
  * SELL :: COPY CONSTRUCTOR
  **********************************************************************/
 inline Sell :: Sell(const Sell & rhs)
 {
     this->amount = rhs.amount;
     this->value  = rhs.value;
     this->profit = rhs.profit;
 }

 /**********************************************************************
  * SELL :: DECONSTRUCTOR
  **********************************************************************/
 inline Sell :: ~Sell()
 {
     amount = 0;
     value  = 0;
 }

 #endif // SELL_H
