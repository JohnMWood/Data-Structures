/***********************************************************************
* Header:
*    Go Fish
* Summary:
*    This will contain just the prototype for the goFish() function
* Authors:
*    John Wood and Etienne Beaulac (group 3)
************************************************************************/

#ifndef GO_FISH_H
#define GO_FISH_H
#include "set.h"
#include "card.h"
using namespace custom;

/**************************************************
 * GO FISH
 * Play the game of "Go Fish"
 *************************************************/
void goFish();
set <Card> readFile() throw (const char *);



#endif // GO_FISH_H
