#include "Graph.h"

Graph::Graph(GraphType graphType, int nrOfVert) {
	this->graphType = graphType;
	this->nrOfVertex = nrOfVert;
	this->nodes = new List<AdjacencyInfo>[nrOfVertex];
}

Graph::~Graph() {
	delete[] nodes;
}

void Graph::reset(int nrOfVert, GraphType graphType) {
	delete[] nodes;
	this->nrOfVertex = nrOfVert;
	this->graphType = graphType;
	this->nodes = new List<AdjacencyInfo>[nrOfVertex];
}

bool Graph::isDirected() const {
	return !(this->graphType == DIRECTED);
}

bool Graph::addArc(int sourceVertex, int destinationVertex, int arcWeight) {
	if (sourceVertex < 0 || sourceVertex > nrOfVertex) {
		return false;
	}
	else if (destinationVertex < 0 || destinationVertex > nrOfVertex) {
		return false;
	}
	else {
		nodes[sourceVertex].insertAt(0, AdjacencyInfo(destinationVertex, arcWeight));
		return true;
	}
}

bool Graph::hasArc(int sourceVertex, int destinationVertex) const {
	bool hasArc = false;
	if (sourceVertex >= 0 && sourceVertex < nrOfVertex && nrOfVertex != 0) {
		for (int i = 0; i < nodes[sourceVertex].length(); i++) {
			if (nodes[sourceVertex].getAt(i).getNeighbourVertex() == destinationVertex) {
				hasArc = true;
			}
		}
	}
	
	return hasArc;
}

bool Graph::removeArc(int sourceVertex, int destinationVertex, int arcWeight) {
	bool removed = false;
	if (sourceVertex >= 0 && sourceVertex < nrOfVertex && nrOfVertex != 0) {
		for (int i = 0; !removed && i < nodes[sourceVertex].length(); i++) {

			if (nodes[sourceVertex].getAt(i).getNeighbourVertex() == destinationVertex && nodes[sourceVertex].getAt(i).getArcWeight() == arcWeight) {
				if (graphType == UNDIRECTED) {
					//could do a recursive call to removeArc with dest and src swaped but it would run one more time then it has to (3 in total)
					for (int j = 0; j < nodes[destinationVertex].length(); j++) {
						if (nodes[destinationVertex].getAt(j).getNeighbourVertex() == sourceVertex && nodes[destinationVertex].getAt(j).getArcWeight() == arcWeight) {
							nodes[destinationVertex].removeAt(j);
						}
					}
				}
				nodes[sourceVertex].removeAt(i);
				removed = true;
			}
		}
	}
	return removed;
}

int Graph::getNrOfVertices() const {
	return this->nrOfVertex;
}

int Graph::outDegreeOfVertex(int theVertex) const {
	int nrOfOutDegrees = 0;

	if (theVertex >= 0 && theVertex < nrOfVertex && nrOfVertex != 0) {
		nrOfOutDegrees = nodes[theVertex].length();
	}

	return nrOfOutDegrees;
}

int Graph::inDegreeOfVertex(int theVertex) const {
	int nrInVex = 0;
	for (int i = 0; i < nrOfVertex; i++) {
		if (i != theVertex) {
			for (int j = 0; j < nodes[i].length(); j++) {
				if (nodes[i].getAt(j).getNeighbourVertex() == theVertex) {
					nrInVex++;
				}
			}
		}
		
	}
	return nrInVex;
}

List<int> Graph::getAllVerticesAdjacentTo(int theVertex) const {
	List<int> list;
	if (graphType == UNDIRECTED) {
		for (int i = 0; i < nodes[theVertex].length(); i++) {
			list.insertAt(0, nodes[theVertex].getAt(i).getNeighbourVertex());
		}
	}
	else {
		for (int j = 0; j < nrOfVertex; j++) {
			for (int i = 0; i < nodes[j].length(); i++) {
				if (!list.findElement(nodes[j].getAt(i).getNeighbourVertex())) {
					list.insertAt(0, nodes[j].getAt(i).getNeighbourVertex());
				}
			}
		}
	}

	return list;
}

void Graph::minSpanTree(List<AdjacencyInfo> minSpanTree[], int cap, int & totalCost) const throw(...){
	if (graphType == DIRECTED) {
		throw "Graph is directed";
	}
	else if (cap < nrOfVertex) {
		throw "Array to small";
	}

	List<AdjacencyInfo> *nodesCopy = new List<AdjacencyInfo>[nrOfVertex];
	for (int i = 0; i < nrOfVertex; i++) {
		nodesCopy[i] = nodes[i];
	}

	totalCost = 0;	
	int failSafe = 0;
	int nrOfDoneVert = 0;
	Heap<AdjacencyInfo> heap;
	List<int> doneVert;
	//add first vertext to doneVert and add all the adyinfo to heap
	doneVert.insertAt(0, 0);
	for (int i = 0; i < nodes[0].length(); i++) {
		heap.insert(nodes[0].getAt(i));
	}

	while (nrOfDoneVert < (nrOfVertex-1) && failSafe < ((nrOfVertex * nrOfVertex) + 2)) {
		AdjacencyInfo comp = heap.getMin();
		//if it not leads to a doneVert
		if (!doneVert.findElement(comp.getNeighbourVertex())) {
			//add the const, add it to doneVert and add all adyinfo to heap
			totalCost += comp.getArcWeight();
			doneVert.insertAt(0, comp.getNeighbourVertex());
			for (int i = 0; i < nodes[comp.getNeighbourVertex()].length(); i++) {
				heap.insert(nodes[comp.getNeighbourVertex()].getAt(i));
			}
			//searching for the node that the current minimum arc is from
			//then adding the arc to the source and destinaion index of minSpanTee
			//then deleting the arc from the two nodes
			for (int i = 0; i < nrOfVertex; i++) {
				if (doneVert.findElement(i)) {
					for (int j = 0; j < nodesCopy[i].length(); j++) {
						if (nodesCopy[i].getAt(j) == comp) {
							//inserting the arc to the two nodes
							minSpanTree[i].insertAt(0, comp);
							minSpanTree[comp.getNeighbourVertex()].insertAt(0,AdjacencyInfo(i, comp.getArcWeight()));
							//deleting the arc from the sorce node
							nodesCopy[i].removeAt(j);
							//deleting the arc from the dest node
							for (int k = 0; k < nodesCopy[comp.getNeighbourVertex()].length(); k++) {
								if (nodesCopy[comp.getNeighbourVertex()].getAt(k).getNeighbourVertex() == i) {
									nodesCopy[comp.getNeighbourVertex()].removeAt(k);
								}
							}
						}
					}
				}
			}
			//increase nrOfDoneVert
			nrOfDoneVert++;
		}
		failSafe++;
	}
	delete[] nodesCopy;
}

void Graph::printGraph() const {
	if (graphType == 0) {
		cout << "The graph is directed" << endl;
	}
	else {
		cout << "The graph is undirected" << endl;
	}
	cout << "w = with weight" << endl;
	for (int i = 0; i < this->nrOfVertex; i++) {
		cout << "node " << i << " has arcs to: ";
		for (int j = 0; j < nodes[i].length(); j++) {
			cout << nodes[i].getAt(j).getNeighbourVertex() << "(w:"<< nodes[i].getAt(j).getArcWeight() << "), ";
		}
		cout << endl;
	}
}
