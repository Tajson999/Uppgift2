#ifndef GRAPH_H
#define GRAPH_H
#include "List.h"
#include "Heap.h"
#include "AdjacencyInfo.h"

enum GraphType { DIRECTED, UNDIRECTED }; // used for member variable in the Graph
class Graph {
private:
	GraphType graphType;

	List<AdjacencyInfo> *nodes;
	int nrOfVertex;
	// for you to decide: member variables and helper functions
	// but you must use the List-class from the first
	// assignment for the adjacency lists that will
	// be used for representation of the Graph

public:

	Graph(GraphType graphType = DIRECTED, int nrOfVert = 0);
	Graph(const Graph& origin) = delete;
	Graph& operator=(const Graph& origin) = delete;
	virtual ~Graph();

	void reset(int nrOfVert, GraphType graphType);
	bool isDirected() const;
	bool addArc(int sourceVertex, int destinationVertex, int arcWeight);
	bool hasArc(int sourceVertex, int destinationVertex) const;
	bool removeArc(int sourceVertex, int destinationVertex, int arcWeight);
	int getNrOfVertices() const;
	int outDegreeOfVertex(int theVertex) const;
	int inDegreeOfVertex(int theVertex) const;
	List<int> getAllVerticesAdjacentTo(int theVertex) const;
	void minSpanTree(List<AdjacencyInfo> minSpanTree[], int cap, int &totalCost)const throw(...);
	void printGraph() const;
};
#endif // !GRAPH_H
