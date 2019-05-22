// leftist.h
//
// Inherits from base class MergeHeap in mergeheap.hpp
//
// Overrides virtual method merge()
//
// For our leftist heap, we utilize an idea of a rank of each
//	node which tells us the shortest path from that node
//	to an external node in the extended tree.
//	This can be seen in line 13 of leftist.cpp

#ifndef LEFTIST_H
#define LEFTIST_H

#include "mergeheap.hpp"

class MaxLeftistHeap : public MergeHeap {
public:
	Node * merge(Node * h1, Node * h2);

private:
	int rank(Node * node);
};

#endif
