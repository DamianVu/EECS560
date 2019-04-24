// hashtable.h
//
// This class creates an array of pointers to LinkedLists
//	to store the hash table data.

#ifndef HT_H
#define HT_H

#include "linkedlist.h"
#include <iostream>

class HashTable {
public:
	HashTable(int size);
	~HashTable();

	bool insert(int i);
	bool remove(int i);
	void print();
	bool find(int i);
	int hash(int i) { return i % mySize; }

private:
	LinkedList ** table;
	int mySize;

	int count();
	int getNewSize();
	int isPrime(int x);
	void rehash();
	bool shouldRehash() { return (count() / mySize) > 0; }
};

#endif
