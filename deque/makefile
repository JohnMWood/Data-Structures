###############################################################
# Program:
#     Assignment 04, DEQUE
#     Brother Helfrich, CS235
# Author:
#     Etienne Beaulac & John Wood, Group 03
# Summary:
#     The deck is a double ended queue that will work in various
#	  ways for the implementation of this assignment. Using nowServing.cpp,
#     the deque will be utilized for the purposes of students waiting
#     in a ficticious linux lab. 
# Time:
#     5 Hours, sitting and working on the program together
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h assignment04.o nowServing.o
	g++ -o a.out assignment04.o nowServing.o
	tar -cf assignment04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment04.o       : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
assignment04.o: deque.h assignment04.cpp
	g++ -c assignment04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp
