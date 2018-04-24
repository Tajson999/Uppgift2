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

bool Graph::hasArc(int sourceVertex, int destinationVertex) const throw(...){
	if (sourceVertex < 0 || sourceVertex > nrOfVertex) {
		throw "Out of Bounds";
	}
	for (int i = 0; i < nodes[sourceVertex].length(); i++) {
		if (nodes[sourceVertex].getAt(i).getNeighbourVertex() == destinationVertex) {
			return true;
		}
	}
	return false;
}

bool Graph::removeArc(int sourceVertex, int destinationVertex, int arcWeight) {
	if (sourceVertex < 0 || sourceVertex > nrOfVertex) {
		throw "Out of Bounds";
	}
	bool removed = false;
	
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

	return removed;
}

int Graph::getNrOfVertices() const {
	return this->nrOfVertex;
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
