/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    John Wood and Etienne Beaulac (group 3)
* Summary:
*    This is all the functions necessary to play Go Fish!
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "set.h"
#include "card.h"
#include "goFish.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using namespace custom;
#define NUMBER_ROUNDS 5

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
    set <Card> hand = readFile();
    cout << "We will play " << NUMBER_ROUNDS << " rounds of Go Fish.  "
         << "Guess the card in the hand\n";

    // Count the number of matches
    int matches = 0;
    for(int i = 0; i < NUMBER_ROUNDS; i++)
    {
        Card temp;
        cout << "round " << i + 1 << ": ";
        cin >> temp;
        set <Card> :: iterator itCard = hand.find(temp);

        // Check to see if it's the same card and that it exists
        if(temp == *itCard && temp != "-INVALID-")
        {
            cout << "\tYou got a match!\n";
            hand.erase(itCard);
            matches++;
        }
        else
            cout << "\tGo Fish!\n";
    } // FOR loop

    // Display the number of matches
    cout << "You have " << matches << " matches!\n";
    // Display the remaining cards
    cout << "The remaining cards: ";

    int count = 0;
    for(set <Card> :: iterator itCard = hand.begin(); itCard != hand.end();
        ++itCard)
    {
        // Check to see if it's the last element
        if(count < hand.size() - 1)
            cout << *itCard << ", ";
        else
            cout << *itCard << endl;
        count++;
    }
}

/**********************************************************************
 * READFILE
 * Reads the file of cards and inserts it into a set of cards.
 ***********************************************************************/
set <Card> readFile() throw (const char *)
{
    ifstream fin;
    try
    {
        // Try opening the file
        fin.open("/home/cs235/week05/hand.txt");
    }
    catch(...)
    {
        throw "ERROR: Could not read file";
    }
    // Create our hand of cards
    set <Card> hand;
    // A temp card that we will insert into our hand
    Card temp;

    while(fin >> temp)
        hand.insert(temp);

    // Don't forget to close the file
    fin.close();
    return hand;
}
