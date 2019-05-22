
#include "edgehandler.h"

EdgeHandler::EdgeHandler() {}

EdgeHandler::EdgeHandler(int ** costs, int numEdges) {
	n = numEdges;
	edges = new Edge**[n];
	for (int i = 0; i < n; i++) {
		edges[i] = new Edge * [n - 1]; // Each node will only have max n-1 outgoing edges
		int loc = 0;
		for (int j = 0; j < n; j++) {
			if (i != j) {
				edges[i][loc] = new Edge(i, j, costs[i][j]);
				loc++;
			}
		}
	}
}

EdgeHandler::~EdgeHandler() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n-1; j++) {
			delete edges[i][j];
		}		
		delete [] edges[i];
	}
	delete [] edges;
}

Edge ** EdgeHandler::getOutgoingEdgesFrom(int u) {
	return edges[u];
}

Edge *** EdgeHandler::getAllEdges() {
	return edges;
}
