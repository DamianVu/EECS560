
#ifndef EH_H
#define EH_H

#include "edge.h"
#include <iostream>

class EdgeHandler {
public:
	EdgeHandler();
	EdgeHandler(int ** costs, int numEdges);

	~EdgeHandler();

	Edge ** getOutgoingEdgesFrom(int u);
	Edge *** getAllEdges();

private:
	Edge *** edges;
	int n;
};

#endif
