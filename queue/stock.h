/***********************************************************************
 * Header:
 *    STOCK
 * Summary:
 *    This will contain just the prototype for stocksBuySell(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef STOCK_H
#define STOCK_H

#include <iostream>      // for ISTREAM, OSTREAM, CIN, and COUT
#include <list>          // for VECTOR
#include "queue.h"       // for QUEUE
#include "dollars.h"
#include "buy.h"
#include "sell.h"
using std::list;
using namespace custom;


 /**********************************************************************
  * STOCKSBUYSELL :: Buys and sells stock, displaying history
  **********************************************************************/
void stocksBuySell();

 /**********************************************************************
  * SELLSTOCK :: Takes care of the logic for selling and buying stock
  **********************************************************************/
void sellStock(int sellAmount, Dollars money, queue <Buy> &qBuy,
             list <Sell> &list_sell);

 /**********************************************************************
  * DISPLAY :: Displays the history of bought and sold stocks, as well as
  * the profit.
  **********************************************************************/
void display(queue <Buy> qBuy, list <Sell> list_sell);

#endif // STOCK_H
