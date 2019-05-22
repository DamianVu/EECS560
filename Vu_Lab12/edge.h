
#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
	Edge();
	Edge(int firstNode, int secondNode, int edgeCost);

	int getU() { return u; }
	int getV() { return v; }
	int getCost() { return cost; }

	bool operator >(const Edge & e);
	bool operator ==(const Edge & e);


private:
	int u;
	int v;
	int cost;
};

#endif
