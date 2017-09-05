/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    John Wood and Etienne Beaulac (group 3)
 **********************************************************************/

#include "stock.h"
#include <cstdlib>
#include <string>        // for STRING
#include <sstream>       // for STRINGSTREAM
#include <iostream>      // for ISTREAM, OSTREAM, CIN, and COUT
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::stringstream;
using std::ostream;
using std::ios;
using namespace custom;

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
    // instructions
    cout << "This program will allow you to buy and sell stocks. "
         << "The actions are:\n";
    cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
    cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
    cout << "  display         - Display your current stock portfolio\n";
    cout << "  quit            - Display a final report and quit the program\n";
	cin.ignore();

    string input;
	queue <Buy> qBuy;
	list <Sell> list_sell;

    do
    {
        Dollars tempDollars;
        int tempAmount = 0;

        cout << "> ";
		getline(cin, input);

    	stringstream ss(input);
		for (int i = 0; i < 3; i++)
        {
            string tempString;

            if (i == 0)
            {
                ss >> tempString;
                input = tempString;
            }
            else if (i == 1)
            {
                ss >> tempString;
                tempAmount = atoi(tempString.c_str());
            }
            else if (i == 2)
                ss >> tempDollars; // convert string to dollars using insertion
        }

		if (input == "buy")
		{
            Buy newBuy(tempAmount, tempDollars);
            qBuy.push(newBuy);
		}
		else if (input == "sell")
		{
			if (!qBuy.empty())
			{
				sellStock(tempAmount, tempDollars, qBuy, list_sell);
			}
		}
		else if (input == "display")
		{
			display(qBuy, list_sell);
		}
		else if (input == "quit")
		{
		}
		else
		{
			cout << "Invalid input\n";
		}
    }
    while (input != "quit");
}

/************************************************
 * SELL STOCK
 * Sell stock according to the price and amount specified
 ***********************************************/
void sellStock(int sellAmount, Dollars money, queue <Buy> &qBuy,
               list <Sell> &list_sell)
{
    Sell newSell;
    Dollars tempProfit;
    try
    {
    	if ((qBuy.front().getAmount() - sellAmount) == 0) // if sell == queue amount
    	{
        	tempProfit = (money * sellAmount) - (qBuy.front().getValue() *
                                                 qBuy.front().getAmount());
        	qBuy.pop();

            Sell newSell(sellAmount, money, tempProfit);
        	list_sell.push_back(newSell);
    	}
    	else if ((qBuy.front().getAmount() - sellAmount) > 0) // less than the queue amount
    	{
            tempProfit = (money * sellAmount) - (qBuy.front().getValue() * sellAmount);
            qBuy.front().setAmount(qBuy.front().getAmount() - sellAmount);

            Sell newSell(sellAmount, money, tempProfit);
            list_sell.push_back(newSell);
    	}
        else // if there is overlap in our queue
        {
            int tempAmount = sellAmount;
            while (sellAmount > 0)
            {
                if (qBuy.front().getAmount() <= sellAmount)
                {
                    tempProfit = (money * qBuy.front().getAmount())
                               - (qBuy.front().getValue() * (qBuy.front().getAmount()));

                    sellAmount -= qBuy.front().getAmount();
                    qBuy.pop();

                    Sell newSell(tempAmount - sellAmount, money, tempProfit);
                    list_sell.push_back(newSell);
                }
                else
                {
                    tempProfit = (money * sellAmount) - (qBuy.front().getValue() *
                                 sellAmount);

                    qBuy.front().setAmount(qBuy.front().getAmount() - sellAmount);

                    Sell newSell(sellAmount, money, tempProfit);
                    list_sell.push_back(newSell);

                    sellAmount = 0;
                }
            }
        }
	}
	catch (...)
	{
        throw "ERROR";
	}
}

/************************************************
* DISPLAY
* Displays the amount currently held in stocks and sold
***********************************************/
void display(queue <Buy> qBuy, list <Sell> list_sell)
{
    Dollars tempProfit;

    if (!qBuy.empty())
    {
        int constSize = qBuy.size();
        cout << "Currently held:\n";
        for (int i = 0; i < constSize; i++)
        {
            qBuy.front().display();
            qBuy.pop();
        }
    }

    if (!list_sell.empty())
    {
        cout << "Sell History:\n";
        for (list<Sell>::iterator it = list_sell.begin();
             it != list_sell.end(); ++it)
        {
            it->display();
            tempProfit += it->getProfit();
        }
    }

    cout << "Proceeds: " << tempProfit << endl;
}

//void scanVector
