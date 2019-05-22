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
	int maxval = -1;

	for (int i = size - 1; i >= 0; i--) {
		if (isParent(i)) break;
		if (!isParent(i) && (array[i] > maxval || maxval == -1)) {
			maxloc = i;
			maxval = array[i];
		}
	}

	if (maxloc != size - 1)
		array[maxloc] = array[size - 1];

	size--;

	return true;
}

int MinFiveHeap::findmin() {
	if (size == 0) return -1;

	return array[0];
}

int MinFiveHeap::findmax() {
	if (size == 0) return -1;
	int maxval = -1;
	for (int i = size - 1; i >= 0; i--) {
		if (isParent(i)) break;
		if (!isParent(i) && (array[i] > maxval || maxval == -1))
			maxval = array[i];
	}
	return maxval;
}

bool MinFiveHeap::compare(int a, int b) {
	return a > b;
}
