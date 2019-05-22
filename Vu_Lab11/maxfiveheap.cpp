#include "maxfiveheap.h"

bool MaxFiveHeap::deletemin() {
	if (size == 0) return false;

	int minloc = -1;
	int minval = -1;

	for (int i = size -1; i >= 0; i--) {
		if (isParent(i)) break;
		if (!isParent(i) && (array[i] < minval || minval == -1)) {
			minval = array[i];
			minloc = i;
		}
	}

	if (minloc != size - 1)
		array[minloc] = array[size - 1];

	size--;

	return true;
}

bool MaxFiveHeap::deletemax() {
	if (size == 0) return false;

	size--;
	array[0] = array[size];
	heapify(0);

	return true;
}

int MaxFiveHeap::findmin() {
	if (size == 0) return -1;

	int minval = -1;
	for (int i = size -1; i >= 0; i--) {
		if (isParent(i)) break;
		if (!isParent(i) && (array[i] < minval || minval == -1))
			minval = array[i];
	}

	return minval;
}

int MaxFiveHeap::findmax() {
	if (size == 0) return -1;

	return array[0];
}

bool MaxFiveHeap::compare(int a, int b) {
	return a < b;
}
