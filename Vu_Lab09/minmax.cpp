
#include "minmax.h"

MinMaxHeap::MinMaxHeap() {
	building = true;
	size = 0;
	currentId = 1;
}

void MinMaxHeap::runSchedule() {
	// oh boy
	std::cout << "\nInitial Minmax Heap:\n";
	levelorder();
	std::cout << "\nScheduling output:\n";

	int timeCounter = 1;
	Process scheduled[100];
	int scheduledCounter = 0;

	// Copy the whole array to somewhere...
	for (int i = 1; i <= size; i++)
		copied[i] = array[i];
	oldSize = size;

	while (size > 0) {
		int timeLeft = 20;

		int processesRan = -1;
		Process ran[10];
		Process completed[10];
		int completedCount = 0;

		// RUN HIGHEST PRIORITY
		while (timeLeft != 0) {
			if (size == 0) break;
			processesRan++;
			if (array[1].getTime() >= timeLeft) {
				bool finished = array[1].getTime() == timeLeft;

				array[1].run(timeLeft);
				ran[processesRan] = array[1];
				timeLeft = 0;

				if (finished) {
					scheduled[scheduledCounter] = array[1];
					scheduledCounter++;
					completed[completedCount] = array[1];
					completedCount++;
					removeMin();
				}
			} else {
				timeLeft -= array[1].getTime();
				array[1].run(array[1].getTime());
				ran[processesRan] = array[1];
				scheduled[scheduledCounter] = array[1];
				scheduledCounter++;
				completed[completedCount] = array[1];
				completedCount++;
				removeMin();
			}
		}

		std::cout << "\nT" << timeCounter << ": 20 ms\n";
			for (int i = 0; i <= processesRan; i++) {
				ran[i].print();
				if (i != processesRan) std::cout << ", ";
			}
		std::cout << "\n";
		if (processesRan != completedCount - 1) {
			for (int i = 0; i <= processesRan; i++) {
				ran[i].printName();
				if (i == processesRan - 1) std::cout << " and ";
				else if (i != processesRan) std::cout << ", ";
			}
			if (processesRan == 0)
				std::cout << " is ";
			else
				std::cout << " are ";
			std::cout << "executed. ";
		}
		for (int i = 0; i < completedCount; i++) {
			completed[i].printName();
			if (i == completedCount - 2) std::cout << " and ";
			else if (i != completedCount - 1) std::cout << ", ";
		}
		if (completedCount != 0) {
			if (completedCount > 1)
				std::cout << " are ";
			else
				std::cout << " is ";
			std::cout << "completed and removed from heap.\n";
		}
		std::cout << "\nUpdated minmax heap:\n";
		levelorder();
		std::cout << "\n";

		timeCounter++;

		if (size == 0) break;

		// Reset and do it with 10.
		timeLeft = 10;
		processesRan = -1;
		completedCount = 0;

		// RUN LOWEST PRIORITY
		while (timeLeft != 0) {
			if (size == 0) break;
			processesRan++;
			int maxIndex;
			if (size == 1) 
				maxIndex = 1;
			else if (size == 2) 
				maxIndex = 2;
			else {
				if (array[2] > array[3])
					maxIndex = 2;
				else
					maxIndex = 3;
			}

			if (array[maxIndex].getTime() >= timeLeft) {
				bool finished = array[maxIndex].getTime() == timeLeft;

				array[maxIndex].run(timeLeft);
				ran[processesRan] = array[maxIndex];
				timeLeft = 0;

				if (finished) {
					scheduled[scheduledCounter] = array[maxIndex];
					scheduledCounter++;
					completed[completedCount] = array[maxIndex];
					completedCount++;
					removeMax();
				}
			} else {
				timeLeft -= array[maxIndex].getTime();
				array[maxIndex].run(array[maxIndex].getTime());
				ran[processesRan] = array[maxIndex];
				scheduled[scheduledCounter] = array[maxIndex];
				scheduledCounter++;
				completed[completedCount] = array[maxIndex];
				completedCount++;
				removeMax();
			}
		}

		std::cout << "\nT" << timeCounter << ": 10 ms\n";
			for (int i = 0; i <= processesRan; i++) {
				ran[i].print();
				if (i != processesRan) std::cout << ", ";
			}
		std::cout << "\n";
		if (processesRan != completedCount - 1) {
			for (int i = 0; i <= processesRan; i++) {
				ran[i].printName();
				if (i == processesRan - 1) std::cout << " and ";
				else if (i != processesRan) std::cout << ", ";
			}
			if (processesRan == 0)
				std::cout << " is ";
			else
				std::cout << " are ";
			std::cout << "executed. ";
		}
		for (int i = 0; i < completedCount; i++) {
			completed[i].printName();
			if (i == completedCount - 2) std::cout << " and ";
			else if (i != completedCount - 1) std::cout << ", ";
		}
		if (completedCount != 0) {
			if (completedCount > 1)
				std::cout << " are ";
			else
				std::cout << " is ";
			std::cout << "completed and removed from heap.\n";
		}
		std::cout << "\nUpdated minmax heap:\n";
		levelorder();
		std::cout << "\n";

		timeCounter++;
	}

	std::cout << "Scheduling order:\n";
	for (int i = 0; i < scheduledCounter; i++) {
		scheduled[i].printName();
		std::cout << " ";
	}
	std::cout << "\n";

	for (int i = 1; i <= oldSize; i++)
		array[i] = copied[i];
	size = oldSize;

}

void MinMaxHeap::insert(int p, int t) {
	Process temp(currentId, p, t);
	size++;
	array[size] = temp;
	currentId++;

	if (!building) {
		int temp = size / 2;
		while (temp != 0) {
			heapify(temp);
			temp = temp / 2;
		}
	}
}

void MinMaxHeap::buildheap() {
	for (int i = size / 2; i > 0; i--)
		heapify(i);
}

void MinMaxHeap::heapify(int index) {
	if (isMinLevel(index))
		heapifyMin(index);
	else
		heapifyMax(index);
}

void MinMaxHeap::heapifyMin(int index) {
	if (index > size / 2) return; // Not a parent
	// Find smallest child/grandchild
	int s = smallestDescendant(index);

	if (s != -1 && array[s] < array[index]) {
		// Swap
		Process temp = array[s];
		array[s] = array[index];
		array[index] = temp;

		// Check if swapped was not a direct child
		if (index != 1 && s != index * 2 && s != (index * 2) + 1) {
			// Swap with parent
			if (array[index] > array[index / 2]) {
				array[index] = array[index / 2];
				array[index / 2] = temp;
			}
			heapifyMin(index);
		}
	}
}

void MinMaxHeap::heapifyMax(int index) {
	if (index > size / 2) return;

	int l = largestDescendant(index);

	if (l != -1 && array[l] > array[index]) {
		// Swap
		Process temp = array[l];
		array[l] = array[index];
		array[index] = temp;

		// Check if swapped was not a direct child
		if (index != 1 && l != index * 2 && l != (index * 2) + 1) {
			// Swap with parent
			if (array[index] < array[index / 2]) {
				array[index] = array[index / 2];
				array[index / 2] = temp;
			}
			heapifyMax(index);
		}
	}
}

void MinMaxHeap::levelorder() {
	if (size == 0) {
		std::cout << "Heap is empty\n";
		return;
	}
	for (int i = 1; i <= size; i++) {
		array[i].printName();
		std::cout << " ";
		if (isPowerOfTwo(i + 1))
			std::cout << "\n";
		else if (i % 2 == 1 && i != size && i != 2)
			std::cout << "- ";
	}
	std::cout << "\n";
}

void MinMaxHeap::findMin() {
	if (size != 0)
		array[1].print();
}

void MinMaxHeap::findMax() {
	if (size != 0) {
		if (size == 2) {
			array[2].print();
		} else {
			if (array[2] > array[3])
				array[2].print();
			else
				array[3].print();
		}
	}
}

void MinMaxHeap::removeMin() {
	if (size != 0) {
		if (size == 1) {
			size--;
		} else {
			array[1] = array[size];
			size--;
			heapify(1);
		}
	}
}

void MinMaxHeap::removeMax() {
	if (size != 0) {
		if (size == 1 || size == 2) {
			size--;
		} else {
			if (array[2] > array[3]) {
				array[2] = array[size];
				size--;
				heapify(2);
			} else {
				array[3] = array[size];
				size--;
				heapify(3);
			}
		}
	}
}

int MinMaxHeap::smallestDescendant(int index) {
	if (index * 2 > size) return -1;
	int smallestIndex = index * 2;

	if (!((index * 2) + 1 > size) && array[(index * 2) + 1] < array[smallestIndex])
		smallestIndex++;
	int sl = smallestDescendant(index * 2);
	int sr = smallestDescendant((index * 2) + 1);
	if (sl != -1 && sr != -1) {
		if (array[sr] < array[sl])
			smallestIndex = sr;
		else
			smallestIndex = sl;
	} else {
		if (sl != -1 && array[sl] < array[smallestIndex])
			smallestIndex = sl;
		if (sr != -1 && array[sr] < array[smallestIndex])
			smallestIndex = sr;
	}
	return smallestIndex;
}

int MinMaxHeap::largestDescendant(int index) {
	if (index * 2 > size) return -1;
	int largestIndex = index * 2;

	if (!((index * 2) + 1 > size) && array[(index * 2) + 1] > array[largestIndex])
		largestIndex++;
	int ll = largestDescendant(index * 2);
	int lr = largestDescendant((index * 2) + 1);
	if (ll != -1 && lr != -1) {
		if (array[lr] > array[ll])
			largestIndex = lr;
		else
			largestIndex = ll;
	} else {
		if (lr != -1 && array[lr] > array[largestIndex])
			largestIndex = lr;
		if (ll != -1 && array[ll] > array[largestIndex])
			largestIndex = ll;
		}
	return largestIndex;
}

bool MinMaxHeap::isMinLevel(int index) {
	if (index == 1) return true;
	int times = 0;
	while (index != 1) {
		index = index / 2;
		times++;
	}
	return (times % 2 == 0) ? true : false;
}

bool MinMaxHeap::isPowerOfTwo(int x) {
	while (x % 2 == 0) x = x / 2;
	return x == 1;
}
