
#include "openhashtable.h"

OpenHashTable::OpenHashTable(int size) {
	mySize = size;
	table = new LinkedList * [size];
	for (int i = 0; i < size; i++) {
		table[i] = new LinkedList();
	}
}

OpenHashTable::~OpenHashTable() {
	for (int i = 0; i < mySize; i++) {
		delete table[i];
	}
	delete [] table;
}

bool OpenHashTable::insert(int i) {
	int loc = hash(i);
	if (table[loc]->find(i)) return false;

	loc = hash(i);
	if (table[loc]->find(i)) {
		return false;
	} else {
		table[loc]->insert(i);
		return true;
	}
}

bool OpenHashTable::remove(int i) {
	int loc = hash(i);
	return (table[loc]->find(i) && table[loc]->remove(i));
}

void OpenHashTable::print() {
	std::cout << "Open Hashing:\n";
	for (int i = 0; i < mySize; i++) {
		std::cout << i << ":";
		table[i]->print();
	}
	std::cout << "\n";
}

bool OpenHashTable::find(int i) {
	return table[hash(i)]->find(i);
}
