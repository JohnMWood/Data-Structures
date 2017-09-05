###############################################################
# Program:
#     assignment 05, SET
#     Brother Helfrich, CS235
# Authors:
#     John Wood and Etienne Beaulac (group 3)
# Summary:
#     Our implementation of the set STD data structure with a
#	  version of go fish that uses our set class
# Time:
#	  6 Hours, time spent working together 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment05.o goFish.o card.o
	g++ -o a.out assignment05.o goFish.o card.o
	tar -cf assignment05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment05.o       : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
assignment05.o: set.h goFish.h assignment05.cpp
	g++ -c assignment05.cpp

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c goFish.cpp

card.o: card.h card.cpp
	g++ -c card.cpp
