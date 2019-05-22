// skew.h
//
// Inherits from base class MergeHeap in mergeheap.hpp
//
// Overrides virtual method merge()
//
// For our skew heap, instead of an idea of rank like in a
//	leftist tree, we instead just swap the left an right
//	child during each merge.
//	This swap happens in lines 12-14 of skew.cpp

#ifndef SKEW_H
#define SKEW_H

#include "mergeheap.hpp"

class MaxSkewHeap : public MergeHeap {
public:
	Node * merge(Node * h1, Node * h2);
};

#endif
