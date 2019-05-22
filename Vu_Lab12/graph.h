
#ifndef GRAPH_H
#define GRAPH_H

#include "edgehandler.h"
#include "minfiveheap.h"
#include "queue.hpp"
#include "findnode.hpp"
#include "vertexset.hpp"

class Graph {
public:
	Graph();
	~Graph();

	void buildGraph(int ** costs, int n);

	// Triple pointers for returning edges
	int *** BFS();
	int *** DFS();
	int ** Kruskal();
	int ** Prim();

private:
	bool built;
	bool * visited;
	int n; // Number of nodes
	EdgeHandler * edgehandler;

	Edge ** edgeSet1;
	Edge ** edgeSet2;
	int size1; // For edgeSet1
	int size2; // For edgeSet2

	void DFSHelper(int v);

	int *** getTraversalLocals();
	int ** getMSTLocals();
	bool primEdge(Edge * edge);
	bool edgeAlreadyExists(Edge * edge);
	void initializeLocals(bool traversal);
	void resetLocals();

	FindNode * find(FindNode * f);

};

#endif
