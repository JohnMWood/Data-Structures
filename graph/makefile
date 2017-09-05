###############################################################
# Program:
#     Assignment 13, Graph
#     Brother Helfrich, CS235
# Author:
#     John Wood and Etienne Beaulac (group 3)
# Summary:
#     Our implementation of the graph and application with the
#     solver.
# Time:
# 		4 Hours, time spend working together
# Most difficult part:
#		Debugging and making minor changes to the breadth-first search
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment13.o graph.o maze.o
	g++ -o a.out assignment13.o graph.o maze.o -g
	tar -cf assignment13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment13.o     : the driver program
#      graph.o            : the graph code
#      maze.o             : the maze reading and solving code
##############################################################
assignment13.o: graph.h vertex.h assignment13.cpp
	g++ -c assignment13.cpp -g

graph.o: graph.h vertex.h graph.cpp
	g++ -c graph.cpp -g

maze.o: maze.cpp maze.h vertex.h graph.h
	g++ -c maze.cpp -g
