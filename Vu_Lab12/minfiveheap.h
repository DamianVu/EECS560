
#ifndef MIN_F_H
#define MIN_F_H

#include "fiveheap.hpp"

class MinFiveHeap : public FiveHeap {
public:
	bool deletemin();

	bool deletemax();

	Edge * findmin();

	bool compare(Edge * a, Edge * b);

};

#endif
