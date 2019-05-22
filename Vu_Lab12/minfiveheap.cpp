#include "minfiveheap.h"

bool MinFiveHeap::deletemin() {
	if (size == 0) return false;

	size--;
	array[0] = array[size];
	heapify(0);

	return true;
}

bool MinFiveHeap::deletemax() {
	if (size == 0) return false;

	int maxloc = -1;
	Edge * maxEdge = nullptr;

	for (int i = size - 1; i >= 0; i--) {
		if (isParent(i)) break;
		if (!isParent(i) && (*array[i] > *maxEdge || maxEdge == nullptr)) {
			maxloc = i;
			maxEdge = array[i];
		}
	}

	if (maxloc != size - 1)
		array[maxloc] = array[size - 1];

	size--;

	return true;
}

Edge * MinFiveHeap::findmin() {
	if (size == 0) return nullptr;

	return array[0];
}


bool MinFiveHeap::compare(Edge * a, Edge * b) {
	return *a > *b;
}
