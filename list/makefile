###############################################################
# Program:
#     Assignment 07, LIST
#     Brother Helfrich, CS235
# Authors:
#     John Wood and Etienne Beaulac (Group 3)
# Summary:
#     This is our implementation of the STD::list class and the 
#     fibonacci numbers assignment. The assignment uses a 
#     wholeNumber class to calculate the sequence, which is much 
#     more efficient than using other methods. We also included 
#     a subtraction operator in wholeNumber, const_iterator, and 
#     a const_reverse_iterator as part of our solutions. 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h assignment07.o fibonacci.o wholeNumber.h
	g++ -o a.out assignment07.o fibonacci.o wholeNumber.h -g  -std=c++11
	tar -cf assignment07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment07.o : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
assignment07.o: list.h assignment07.cpp
	g++ -c assignment07.cpp -g  -std=c++11

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	g++ -c fibonacci.cpp -g  -std=c++11

clean:
	rm -f *.o
