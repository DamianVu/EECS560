
#include "graph.h"

Graph::Graph() {
	built = false;
}

Graph::~Graph() {
	delete edgehandler;
}

void Graph::buildGraph(int ** costs, int numNodes) {
	edgehandler = new EdgeHandler(costs, numNodes);
	n = numNodes;
	built = true;
}

int *** Graph::BFS() {
	initializeLocals(true);
	// Edge Set 1: Tree Edges
	// Edge Set 2: Cross Edges

	Queue * q = new Queue();
	visited[0] = true;
	q -> enqueue(0);
	while (!q -> isEmpty()) {
		int w = q -> dequeue();
		Edge ** adjacent = edgehandler -> getOutgoingEdgesFrom(w);
		for (int i = 0; i < n - 1; i++) {
			Edge * e = adjacent[i];
			if (e -> getCost() == -1 || edgeAlreadyExists(e)) {
				continue;
			}
			int u = e -> getV();
			if (visited[u]) {
				// Add Cross Edge
				edgeSet2[size2] = e;
				size2++;
				continue;
			}
			// Mark as visited
			visited[u] = true;
			q -> enqueue(u);

			// Add Tree Edge
			edgeSet1[size1] = e;
			size1++;
		}
	}

	delete q;

	int *** ret = getTraversalLocals();

	resetLocals();

	return ret;
}

int *** Graph::DFS() {
	initializeLocals(true);

	DFSHelper(0);

	int *** ret = getTraversalLocals();

	resetLocals();

	return ret;
}

void Graph::DFSHelper(int v) {
	visited[v] = true;
	Edge ** adjacent = edgehandler -> getOutgoingEdgesFrom(v);
	for (int i = 0; i < n - 1; i++) {
		Edge * e = adjacent[i];
		if (e -> getCost() == -1 || edgeAlreadyExists(e)) {
			continue;
		}
		int u = e -> getV();
		if (visited[u]) {
			// Add Back Edge
			edgeSet2[size2] = e;
			size2++;
			continue;
		}
		edgeSet1[size1] = e;
		size1++;
		DFSHelper(u);
	}
}

int ** Graph::Kruskal() {
	initializeLocals(false);

	// Disjoint sets
	FindNode ** set = new FindNode * [n];
	for (int i = 0; i < n; i++)
		set[i] = new FindNode(i);

	MinFiveHeap m;
	Edge *** edges = edgehandler -> getAllEdges();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - 1; j++)
			if (edges[i][j] -> getCost() != -1)
				m.insert(edges[i][j]);
	m.buildheap();

	while (!m.isEmpty() && size1 != n - 1) {
		Edge * x = m.findmin();
		int u = x -> getU();
		int v = x -> getV();
		m.deletemin();
		if (*find(set[u]) != *find(set[v]) && !edgeAlreadyExists(x)) {
			edgeSet1[size1] = x;
			size1++;
			// Union the disjoint sets
			if (set[u] -> getRank() >= set[v] -> getRank()) {
				set[v] -> setParent(set[u]);
				set[u] -> setRank(set[v] -> getRank() + 1);
			} else {
				set[u] -> setParent(set[v]);
				set[v] -> setRank(set[u] -> getRank() + 1);
			}
		}
	}

	for (int i = 0; i < n; i++)
		delete set[i];
	delete [] set;

	int ** ret;

	if (size1 == n - 1)
		ret = getMSTLocals();
	else
		ret = nullptr;

	resetLocals();

	return ret;
}

int ** Graph::Prim() {
	initializeLocals(false);

	VertexSet V(n);
	V.insert(0);

	MinFiveHeap m;
	do {
		// Build heap of valid edges
		m.clearHeap();
		int * vertices = V.getVertices();
		int numVertices = V.getSize();
		for (int i = 0; i < numVertices; i++) {
			Edge ** edges = edgehandler -> getOutgoingEdgesFrom(vertices[i]);
			for (int j = 0; j < n - 1; j++) {
				Edge * x = edges[j];
				if (!V.contains(x -> getV()) && x -> getCost() != -1)
					m.insert(x);
			}
		}
		if (m.isEmpty()) break;
		m.buildheap();

		Edge * x = m.findmin();
		m.deletemin();
		edgeSet1[size1] = x;
		size1++;
		V.insert(x -> getV());
	} while (V.getSize() != n);

	int ** ret;

	if (size1 == n - 1)
		ret = getMSTLocals();
	else
		ret = nullptr;

	resetLocals();

	return ret;
}

int *** Graph::getTraversalLocals() {
	int *** ret = new int ** [2];
	ret[0] = new int * [size1 + 1];
	ret[1] = new int * [size2 + 1];
	for (int i = 0; i < size1; i++) {
		ret[0][i] = new int[2];
		Edge * e = edgeSet1[i];
		ret[0][i][0] = e -> getU();
		ret[0][i][1] = e -> getV();
	}
	for (int i = 0; i < size2; i++) {
		ret[1][i] = new int[2];
		Edge * e = edgeSet2[i];
		ret[1][i][0] = e -> getU();
		ret[1][i][1] = e -> getV();
	}
	ret[0][size1] = nullptr;
	ret[1][size2] = nullptr;
	return ret;
}

int ** Graph::getMSTLocals() {
	int ** ret = new int * [size1 + 1];
	for (int i = 0; i < size1; i++) {
		ret[i] = new int[3];
		Edge * e = edgeSet1[i];
		ret[i][0] = e -> getU();
		ret[i][1] = e -> getV();
		ret[i][2] = e -> getCost();
	}
	ret[size1] = nullptr;
	return ret;
}

bool Graph::edgeAlreadyExists(Edge * edge) {
	for (int i = 0; i < size1; i++)
		if (*edge == *edgeSet1[i]) return true;
	for (int i = 0; i < size2; i++)
		if (*edge == *edgeSet2[i]) return true;
	return false;
}

void Graph::initializeLocals(bool traversal) {
	// Max edges is (n*n - n) since graph is undirected
	int maxEdges = (n*n - n) / 2;
	edgeSet1 = new Edge * [maxEdges];
	size1 = 0;
	if (traversal) {
		size2 = 0;
		edgeSet2 = new Edge * [maxEdges];
		visited = new bool[n];
		for (int i = 0; i < n; i++) 
			visited[i] = false;
	}
}

void Graph::resetLocals() {
	delete [] edgeSet1;
	delete [] edgeSet2;
	edgeSet1 = nullptr;
	edgeSet2 = nullptr;
	delete [] visited;
	visited = nullptr;
	size1 = 0;
	size2 = 0;
}

FindNode * Graph::find(FindNode * f) {
	while (f -> getParent() != nullptr)
		f = f -> getParent();
	return f;
}
