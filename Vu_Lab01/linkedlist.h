// linkedlist.h
//
// This class creates a singly linked list with functions
//	to fit the lab descriptions

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

	// Smallest, Largest, and Average assume the 
	// list is not empty when it is called
	int smallest();
	int largest();
	double average();

	void mergeTwoLists();
	void print();
	void sort();

private:
	Node<int> * head = nullptr;

	bool isSorted();
};

#endif
