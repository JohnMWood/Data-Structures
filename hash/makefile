###############################################################
# Program:
#     Assignment 12, Hash
#     Brother Helfrich, CS235
# Author:
#     Group 3: John Wood, Etienne Beaulac
# Summary:
#     Total time together: 5 hours
#		Most difficult part: debugging the hash class
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment12.o spellCheck.o
	g++ -o a.out assignment12.o spellCheck.o -g
	tar -cf assignment12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week12.o     : the driver program
#      spellCheck.o   : the spell-check program and driver
##############################################################
assignment12.o: hash.h assignment12.cpp
	g++ -c assignment12.cpp -g

spellCheck.o: hash.h spellCheck.h spellCheck.cpp
	g++ -c spellCheck.cpp -g
