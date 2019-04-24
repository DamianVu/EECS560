// linkedlist.h
//
// This file defines a singly linked list using nodes that contain integers.
// This linked list inserts at the beginning of the list.
#ifndef LL_H
#define LL_H

#include "node.hpp"
#include <iostream>

class LinkedList {
public:
	LinkedList() {}
	~LinkedList();

	bool isEmpty() { return head == nullptr; }

	void insert(int i);
	bool remove(int i);

	int take();

	int count();

	bool find(int i);

	void print();

private:
	Node<int> * head = nullptr;
};

#endif
