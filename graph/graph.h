/***********************************************************************
* File:
*    graph.h
*    Brother Helfrich, CS 235
* Author:
*    John Wood and Etienne Beaulac (group 3)
* Summary:
*    Our implementation of the graph class
************************************************************************/
#ifndef GRAPH_H
#define GRAPH_H

#include "set.h"
#include "vector.h"
#include "vertex.h"
#include <cstdlib>
using namespace custom;

/***********************************************************************
* CLASS GRAPH
* Our implementation of the Graph class
************************************************************************/
class Graph
{
private:
   set <Vertex> *adjTable;
   int numElements;

public:
   Graph(int num) : adjTable(NULL), numElements(num)
   {
      try
      {
         adjTable = new set <Vertex> [num];
      }
      catch (...)
      {
         throw "ERROR: Unable to allocate memory for the graph";
      }
   }
   Graph(const Graph & rhs) : adjTable(NULL), numElements(0) { *this = rhs; }
   ~Graph()                              { if (adjTable) delete[] adjTable; }

   Graph & operator = (const Graph & rhs)       throw (const char *);

   int size()     const                               { return numElements; }
   void clear()
   {
      for (int i = 0; i < numElements; i++)
         adjTable[i].clear();
   }

   bool isEdge(const Vertex & v1, const Vertex & v2) const;
   set <Vertex> findEdges(const Vertex & v);
   void add(const Vertex & v1, const Vertex & v2);
   void add(const Vertex & v1, const set <Vertex> & v2);
   vector <Vertex> findPath(const Vertex & v1, const Vertex & v2);
};

#endif /* GRAPH_H */
