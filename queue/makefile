###############################################################
# Program:
#     Assignment 03, QUEUE
#     Brother Helfrich, CS235
# Author:
#     Etienne Beaulac & John Wood, Group 03
# Summary:
#     Our implementation of the queue STL class and our stock.cpp
#     and other associated classes for buying and selling stocks.
# Time:
#     10 hours, time spent working together
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment03.o dollars.o stock.o
	g++ -o a.out assignment03.o dollars.o stock.o
	tar -cf assignment03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      week03.o       : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
assignment03.o: queue.h assignment03.cpp
	g++ -c assignment03.cpp

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp

stock.o: stock.h stock.cpp buy.h sell.h dollars.o
	g++ -c stock.cpp
