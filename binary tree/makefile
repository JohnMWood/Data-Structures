###############################################################
# Program:
#     Assignment 08, Binary Tree
#     Brother Helfrich, CS235
# Author:
#     John Wood and Etienne Beaulac
# Summary:
#     Our implementation of the BNode tree and a huffman
#		code generator
# Time:
#     6 hours, 5 spent working together
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment08.o huffman.o
	g++ -o a.out assignment08.o huffman.o -g
	tar -cf assignment08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment08.o : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
assignment08.o: bnode.h huffman.h assignment08.cpp
	g++ -c assignment08.cpp -g

huffman.o: bnode.h vector.h huffman.h huffman.cpp
	g++ -c huffman.cpp -g
