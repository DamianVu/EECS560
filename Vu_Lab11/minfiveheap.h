
#ifndef MIN_F_H
#define MIN_F_H

#include "fiveheap.hpp"

class MinFiveHeap : public FiveHeap {
public:
	bool deletemin();

	bool deletemax();

	int findmin();

	int findmax();

	bool compare(int a, int b);

};

#endif
