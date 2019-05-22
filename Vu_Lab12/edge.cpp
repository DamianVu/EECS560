
#include "edge.h"

Edge::Edge() {

}

Edge::Edge(int firstNode, int secondNode, int edgeCost) {
	u = firstNode;
	v = secondNode;
	cost = edgeCost;
}

bool Edge::operator > (const Edge & e) {
	return cost > e.cost;
}

bool Edge::operator == (const Edge & e) {
	return (u == e.u && v == e.v) || (u == e.v && v == e.u);
}
