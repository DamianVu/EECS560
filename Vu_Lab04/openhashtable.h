
#ifndef OHT_H
#define OHT_H

#include "linkedlist.h"
#include <iostream>

class OpenHashTable {
public:
	OpenHashTable(int size);
	~OpenHashTable();

	bool insert(int i);
	bool remove(int i);
	void print();
	bool find(int i);
	int hash(int i) { return i % mySize; }

private:
	LinkedList ** table;
	int mySize;

	int count();
};

#endif
