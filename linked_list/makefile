###############################################################
# Program:
#     Assignment 06, NODE
#     Brother Helfrich, CS235
# Authors:
#     John Wood and Etienne Beaulac (Group 3)
# Summary:
#     Implements a linked-list and uses it to implement
#	  the Insertion Sort. The hardest part was figuring out
# 	  how to keep track of the head of the linked list.
# 	  3.5 hours, time spent working together
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h assignment06.o
	g++ -o a.out assignment06.o  -g
	tar -cf assignment06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment06.o      : the driver program
#      <anything else?>
##############################################################
assignment06.o: node.h assignment06.cpp sortInsertion.h
	g++ -c assignment06.cpp -g
