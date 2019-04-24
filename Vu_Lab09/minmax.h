
#ifndef MM_H
#define MM_H

#include "process.h"

class MinMaxHeap {
public:
	MinMaxHeap();

	void insert(int p, int t);

	void buildheap();

	void heapify(int index);

	void levelorder();

	void runSchedule();

	void findMin();

	void findMax();

	void removeMin();

	void removeMax();

private:
	int size;
	int oldSize;
	int currentId;
	bool building;
	Process array[100];
	Process copied[100];

	void heapifyMin(int index);

	void heapifyMax(int index);

	bool isMinLevel(int index);

	bool isPowerOfTwo(int x);

	int smallestDescendant(int index);

	int largestDescendant(int index);
};

#endif
