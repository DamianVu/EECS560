
#ifndef FH_H
#define FH_H

#include <iostream>

class FiveHeap {
public:
	FiveHeap() {
		building = true;
		size = 0;
		array = new int[10000000];
	}

	~FiveHeap() {
		delete [] array;
	}

	bool insert(int x) {
		if (size == 10000000) return false;

		array[size] = x;
		size++;

		if (!building) heapifyAfterInsert();

		return true;
	}

	void buildheap() {
		for (int i = getLastParent(); i >= 0; i--)
			heapify(i);
		building = false;
	}

	int getLastParent() {
		if (size == 0) return -1;

		int loc = -1;

		for (int i = size - 1; i >= 0; i--) {
			if (isParent(i)) {
				loc = i;
				break;
			}
		}

		if (loc == -1) return 0;
		return loc;
	}

	void heapifyAfterInsert() {
		int loc = (size - 2) / 5;

		while (loc != 0) {
			heapify(loc);
			loc = (loc - 1) / 5;
		}
		heapify(0);
	}

	void heapify(int index) {
		// Check if we should swap with any children and do it
		if (!isParent(index)) return;

		int firstChild = (5 * index) + 1;
		int lastChild = (5 * index) + 5;
		int swapLoc = -1;
		int swapValue = -1;

		for (int i = firstChild; i < size && i <= lastChild; i++) {
			if (compare(array[index], array[i])) {
				// Should swap
				if (swapValue == -1 || !compare(array[i], swapValue)) {
					swapValue = array[i];
					swapLoc = i;
				}
			}
		}

		if (swapLoc == -1) return;

		array[swapLoc] = array[index];
		array[index] = swapValue;

		heapify(swapLoc);
	}

	// Compare should return true if we should swap
	virtual bool compare(int a, int b) = 0;

	virtual bool deletemin() = 0;
	virtual bool deletemax() = 0;
	virtual int findmin() = 0;
	virtual int findmax() = 0;

	void levelorder() {
		for (int i = 0; i < size; i++) {
			std::cout << array[i] << " ";
			if (isPowerOfFive(i)) 
				std::cout << "\n";
			else if (i % 5 == 0 && i != size - 1) 
				std::cout << "- ";
		}
		std::cout << "\n";
	}

private:
	bool isPowerOfFive(int x) { // But not 1
		if (x == 0) return true;
		if (x == 1) return false;
		while (x % 5 == 0) x = x / 5;
		return x == 1;
	}

protected:
	int * array;
	int size;
	bool building;

	bool isParent(int index) {
		return size - 1 > (5 * index) + 1;
	}
};

#endif
