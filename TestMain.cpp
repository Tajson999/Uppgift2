#include "Graph.h"
#include "Heap.h"
#include <iostream>
#include <string>
#include <fstream>

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Graph graph;
	string fileName;
	cout << "Enter filename: ";
	cin >> fileName;
	getchar();
	ifstream file;
	file.open(fileName, ios::in);
	if (file.is_open()) {
		int from, to, weight, nodes;
		char directed;
		file >> nodes;
		file >> directed;
		if (directed == 'U') {
			graph.reset(nodes, UNDIRECTED);
		}
		else {
			graph.reset(nodes, DIRECTED);
		}
		while (file >> from >> to >> weight) {
			if (directed == 'U') {
				graph.addArc(from, to, weight);
				graph.addArc(to, from, weight);
			}
			else {
				graph.addArc(from, to, weight);
			}
		}
		
		file.close();
	}
	else {
		cout << "error opening file" << endl;
	}
	
	graph.printGraph();

	cout << endl << endl;

	int totalcost = 0;
	List<AdjacencyInfo> adjList[40];
	int cap = 40;
	try {
		graph.minSpanTree(adjList, cap, totalcost);
	}
	catch (char *s) {
		cout << s << endl;
	}
	cout << "total cost " << totalcost << endl;
	for (int i = 0; i < 9 ; i++) {
		cout << "node " << i << " has arcs to: ";
		if (adjList[i].length() != 0) {
			for (int j = 0; j < adjList[i].length(); j++) {
				cout << adjList[i].getAt(j).getNeighbourVertex() << "(w:" << adjList[i].getAt(j).getArcWeight() << "), ";
			}
		}
		
		cout << endl;
	}
	cout << endl << endl;
	if (graph.hasArc(0, 3)) {
		cout << "the garph has a arc from 0 to 3\n";
	}
	else {
		cout << "the graph has not a arc from 0 to 3\n";
	}

	if (graph.hasArc(3, 0)) {
		cout << "the garph has a arc from 3 to 0\n";
	}
	else {
		cout << "the graph has not a arc from 3 to 0\n";
	}

	if (graph.hasArc(0, 4)) {
		cout << "the garph has a arc from 0 to 4\n";
	}
	else {
		cout << "the graph has not a arc from 0 to 4\n";
	}
	
	if (graph.removeArc(0, 3, 10)) {
		cout << "removed a arc between 0 and 3 with weight 10\n";
	}else{
		cout << "did not removed a arc between 0 and 3 with weight 10\n";
	}

	if (graph.hasArc(0, 3)) {
		cout << "the garph has a arc from 0 to 3\n";
	}
	else {
		cout << "the graph has not a arc from 0 to 3\n";
	}

	if (graph.hasArc(3, 0)) {
		cout << "the garph has a arc from 3 to 0\n";
	}
	else {
		cout << "the graph has not a arc from 3 to 0\n";
	}

	if (graph.removeArc(0, 3, 10)) {
		cout << "removed a arc between 0 and 3 with weight 10\n";
	}
	else {
		cout << "did not removed a arc between 0 and 3 with weight 10\n";
	}

	if (graph.removeArc(3, 0, 10)) {
		cout << "removed a arc between 3 and 0 with weight 10\n";
	}
	else {
		cout << "did not removed a arc between 3 and 0 with weight 10\n";
	}

	

	cout << "node 6 has " << graph.inDegreeOfVertex(6) << " in degrees\n";
	cout << "node 5 has " << graph.outDegreeOfVertex(5) << " out degress\n\n";
	

	cout << "node 4 has ";
	List<int> a = graph.getAllVerticesAdjacentTo(4);
	for (int i = 0; i < a.length(); i++) {
		cout << a.getAt(i) << " ";
	}
	cout << "as neibors\n\n";

	if (graph.hasArc(100, 2)) {
		cout << "the graph has a arc from 100 to 2\n";
	}
	else {
		cout << "the graph has not a arc from 100 to 2\n";
	}
	

	if (graph.hasArc(-100, 2)) {
		cout << "the graph has a arc from -100 to 2\n";
	}
	else {
		cout << "the graph has not a arc from -100 to 2\n";
	}

	if (graph.removeArc(100, 2,30)) {
		cout << "removed a arc between 100 and 2 with weight 30\n";
	}
	else {
		cout << "did not removed a arc between 100 and 2 with weight 30\n";
	}

	if (graph.removeArc(-100, 2,30)) {
		cout << "removed a arc between 100 and 2 with weight 30\n";
	}
	else {
		cout << "did not removed a arc between 100 and 2 with weight 30\n";
	}

	
	cout << "node 10 has " << graph.outDegreeOfVertex(10) << " out degrees\n";
	cout << "node -10 has " << graph.outDegreeOfVertex(-10) << " out degrees\n";

	cout << endl << endl;
	graph.reset(2,DIRECTED);
	graph.printGraph();


	
	system("pause");
	return 0;
}