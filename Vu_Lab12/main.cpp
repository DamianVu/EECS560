
#include <iostream>
#include <fstream>

#include "graph.h"

void printEdgeSet(int *** set, int which) {
	int loc = 0;
	while (set[which][loc] != nullptr) {
		int u = set[which][loc][0];
		int v = set[which][loc][1];
		if (u > v) {
			int temp = v;
			v = u;
			u = temp;
		}
		std::cout << "(" << u << "," << v << ") ";
		loc++;
	}
	std::cout << "\n";
}

void printMST(int ** set) {
	int loc = 0;
	int totalCost = 0;
	while (set[loc] != nullptr) {
		int u = set[loc][0];
		int v = set[loc][1];
		int cost = set[loc][2];
		if (u > v) {
			int temp = v;
			v = u;
			u = temp;
		}
		std::cout << "(" << u << "," << v << "){" << cost << "} ";
		totalCost += cost;
		loc++;
	}
	std::cout << "\nTotal cost = " << totalCost << "\n";
}

int main() {
	Graph graph;

	std::ifstream input("data.txt");
	int ** costs;
	int numNodes;
	input >> numNodes;
	costs = new int * [numNodes];
	for (int i = 0; i < numNodes; i++) {
		costs[i] = new int[numNodes];
		for (int j = 0; j < numNodes; j++) {
			input >> costs[i][j];
		}
	}

	graph.buildGraph(costs, numNodes);

	for (int i = 0; i < numNodes; i++)
		delete [] costs[i];
	delete [] costs;

	bool running = true;

	while (running) {
		std::cout << "\n------------------------------------------------------------\nPlease choose one of the following commands:\n1- BFS\n2- DFS\n3- Kruskal MST\n4- Prim MST\n5- Exit\n> ";
		bool clearTraversal = false;
		bool clearMST = false;
		int c;

		int *** trav;
		int ** mst;

		std::cin >> c;
		switch (c) {
			case 1:
				trav = graph.BFS();
				std::cout << "Tree Edges: ";
				printEdgeSet(trav, 0);
				std::cout << "Cross Edges: ";
				printEdgeSet(trav, 1);
				clearTraversal = true;
			break;
			case 2:
				trav = graph.DFS();
				std::cout << "Tree Edges: ";
				printEdgeSet(trav, 0);
				std::cout << "Back Edges: ";
				printEdgeSet(trav, 1);
				clearTraversal = true;
			break;
			case 3:
				mst = graph.Kruskal();
				printMST(mst);
				clearMST = true;
			break;
			case 4:
				mst = graph.Prim();
				printMST(mst);
				clearMST = true;
			break;
			case 5:
			default:
				running = false;
			break;
		}

		int loc = 0;

		if (clearTraversal) {
			while (true) {
				if (trav[0][loc] == nullptr) break;
				delete [] trav[0][loc];
				delete [] trav[1][loc];
				loc++;
			}
			delete [] trav[0];
			delete [] trav[1];
			delete [] trav;
		} else if (clearMST) {
			while (true) {
				if (mst[loc] == nullptr) break;
				delete [] mst[loc];
				loc++;
			}
			delete [] mst;
		}
	}

	std::cout << "Byebye!\n";

	return 0;
}
