/***********************************************************************
* File:
*    graph.cpp
*    Brother Helfrich, CS 235
* Author:
*    John Wood and Etienne Beaulac (group 3)
* Summary:
*    Our implementation of the graph class
************************************************************************/

#include "graph.h"
#include "deque.h"

/***********************************************************************
* ADD
* Adds an edge to a graph by specifying two vertices
************************************************************************/
void Graph :: add(const Vertex & v1, const Vertex & v2)
{
   adjTable[v1.index()].insert(v2);
}

/***********************************************************************
* ADD
* Adds an edge to a graph by specifying a vertex and a set of vertices
************************************************************************/
void Graph :: add(const Vertex & v1, const set <Vertex> & v2)
{
   for (set <Vertex> :: iterator it = v2.begin(); it != v2.end(); ++it)
      adjTable[v1.index()].insert(*it);
}

/***********************************************************************
* IS EDGE
* Indicates whether an edge exists between two vertices
************************************************************************/
bool Graph :: isEdge(const Vertex & v1, const Vertex & v2) const
{
   return adjTable[v1.index()].find(v2) != adjTable[v1.index()].end();
}

/***********************************************************************
* FIND EDGES
* Retrieves a set of all the edges relating to a given vertex
************************************************************************/
set <Vertex> Graph :: findEdges(const Vertex & v)
{
   return adjTable[v.index()];
}

/***********************************************************************
* FIND PATH
* Returns a list of nodes leading from one vertex to another
************************************************************************/
vector <Vertex> Graph :: findPath(const Vertex & v1, const Vertex & v2)
{
   int distance = 0;
   vector <Vertex> distances(size());
   vector <Vertex> predecessor(size());

   deque <Vertex> toVisit;
   toVisit.push_back(v1);
   for (int i = 0; i < size(); ++i)
      distances[i] = -1;

   while (!toVisit.empty() && distances[v2.index()] == -1)
   {
      Vertex v = toVisit.front();
      toVisit.pop_front();

      if (distances[v.index()] > distance)
         distance++;

      set <Vertex> s = findEdges(v);
      for (set <Vertex> :: iterator it = s.begin(); it != s.end(); ++it)
      {
         if (distances[(*it).index()] == -1)
         {
            distances[(*it).index()] = distance + 1;
            predecessor[(*it).index()] = v;
            toVisit.push_back(*it);
         }
      }
   }
   distance++;

   vector <Vertex> error;
   if (distances[v2.index()] == -1)
      return error;

   vector <Vertex> path;
   path.push_back(v2);
   for (int i = 1; i <= distance; ++i)
      path.push_back(predecessor[path[i - 1].index()]);

   return path;
}

/***********************************************************************
* ASSIGNMENT OPERATOR
* Copy a graph
************************************************************************/
Graph & Graph :: operator = (const Graph & rhs) throw (const char *)
{
   try
   {
      if (adjTable == rhs.adjTable)
         return *this;

      if (numElements < rhs.numElements)
      {
         numElements = rhs.numElements;
         if (adjTable)
            delete[] adjTable;
         adjTable = new set <Vertex> [numElements];
      }

      for (int i = 0; i < rhs.numElements; i++)
         adjTable[i] = rhs.adjTable[i];

      return *this;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate memory for the graph";
   }
}
