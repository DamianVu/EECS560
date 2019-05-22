
#ifndef MAX_F_H
#define MAX_F_H

#include "fiveheap.hpp"

class MaxFiveHeap : public FiveHeap {
public:
	bool deletemin();

	bool deletemax();

	int findmin();

	int findmax();

	bool compare(int a, int b);

};

#endif
