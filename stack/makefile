###############################################################
# Program:
#     Assignment 02, STACK
#     Brother Helfrich, CS235
# Author:
#     Etienne Beaulac & John Wood
# Summary:
#     Encapsulates the notion of a stack. This works exactly
#		like the std::stack class. Any data-type is supported. 
#		the program is then used to solve infix, postfix, and prefix problems.
# Time:
#     10 hrs
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h assignment02.o infix.o 
	g++ -o a.out assignment02.o infix.o 
	tar -cf assignment02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment02.o       : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
assignment02.o: stack.h infix.h assignment02.cpp
	g++ -c assignment02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp