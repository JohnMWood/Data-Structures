###############################################################
# Program:
#     Assignment 10, Map
#     Brother Helfrich, CS235
# Author:
#     Etienne Beaulac and John Wood (group 3)
# Summary:
#     Our implementation of the std map class
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment10.o wordCount.o
	g++ -o a.out assignment10.o wordCount.o -g
	tar -cf assignment10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment10.o : the driver program
#      wordCount.o    : the wordCount() function
##############################################################
assignment10.o: pair.h map.h bst.h assignment10.cpp
	g++ -c assignment10.cpp -g

wordCount.o: map.h bst.h wordCount.h wordCount.cpp
	g++ -c wordCount.cpp -g
