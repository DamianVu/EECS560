
#include "hashtable.h"

HashTable::HashTable(int size) {
	mySize = size;
	table = new LinkedList * [size];
	for (int i = 0; i < size; i++) {
		table[i] = new LinkedList();
	}
}

HashTable::~HashTable() {
	for (int i = 0; i < mySize; i++) {
		delete table[i];
	}
	delete [] table;
}

bool HashTable::insert(int i) {
	int loc = hash(i);
	if (table[loc]->find(i)) return false;

	if (shouldRehash()) rehash();
	loc = hash(i);
	if (table[loc]->find(i)) {
		return false;
	} else {
		table[loc]->insert(i);
		return true;
	}
}

bool HashTable::remove(int i) {
	int loc = hash(i);
	return (table[loc]->find(i) && table[loc]->remove(i));
}

void HashTable::print() {
	for (int i = 0; i < mySize; i++) {
		std::cout << i << ":";
		table[i]->print();
	}
}

bool HashTable::find(int i) {
	return table[hash(i)]->find(i);
}

void HashTable::rehash() {
	// Find new size
	int newSize = getNewSize();

	// Create new table
	LinkedList ** newTable = new LinkedList * [newSize];
	for (int i = 0; i < newSize; i++) 
		newTable[i] = new LinkedList();

	// Insert all old numbers into new table
	for (int i = 0; i < mySize; i++) {
		int put = table[i]->take();
		while (put != -1) {
			int newLoc = put % newSize;
			newTable[newLoc]->insert(put);
			put = table[i]->take();
		}
	}

	// Delete old table
	for (int i = 0; i < mySize; i++) {
		delete table[i];
	}
	delete [] table;

	// Set new variables
	table = newTable;
	mySize = newSize;

	std::cout << "Hash Table is rehashed\n";
}

int HashTable::getNewSize() {
	int c = (mySize * 2) + 1;
	while (!isPrime(c)) c++;
	return c;
}

int HashTable::isPrime(int x) {
	for (int i = 2; i * i < x; i++) {
		if (x % i == 0) return false;
	}
	return true;
}

int HashTable::count() {
	int c = 0;
	for (int i = 0; i < mySize; i++) {
		c += table[i]->count();
	}
	return c;
}
