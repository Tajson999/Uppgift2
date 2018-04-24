#include "Graph.h"
#include "Heap.h"
#include <iostream>
#include <string>
#include <fstream>

int main() {
	/*
	
	SWITCH LIST.H FILE
		change oneBackPtr to currentPtr in both remove funktions

	remove arc cause memoryleak
	
	
	*/
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
	
	system("pause");
	return 0;
}