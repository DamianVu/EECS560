// Abstract class for a hash table of strings.
// Used to avoid duplicate functions across types of hash tables

// Children of this class NEED to override hashf()
// hashf() is the collision resolution side of the insertion, which
// should be the only way that two hash tables differ.

#ifndef HT_H
#define HT_H

#include <iostream>

class HashTable {
public:
	virtual int hashf(int x, int times) = 0; // Collision resolution function

	HashTable(int m, int ir, int ik) {
		size = m;
		r = ir;
		k = ik;
		table = new int[m];
		for (int i = 0; i < m; i++)
			table[i] = -1;
	}

	~HashTable() {
		delete [] table;
		delete [] myName;
	}

	int hash(int x) {
		return x % size;
	}

	bool insert(int x) {
		if (find(x))
			return false;

		int count = 0;
		int hashVal = hash(x);
		while (count < k) {
			int loc = (hashVal + (hashf(x, count))) % size;
			if (table[loc] == -1) {
				// Insert
				table[loc] = x;
				return true;
			}
			count++;
		}
		return false;
	}

	bool find(int x) {
		int count = 0;
		int hashVal = hash(x);
		while (count < k) {
			int loc = (hashVal + (hashf(x, count))) % size;
			if (table[loc] == x) return true;
			if (table[loc] == -1) return false;
			count++;
		}
		return false;
	}

	void print() {
		std::cout << myName << ":\n\n";
		for (int i = 0; i < size; i++) {
			std::cout << i << ": " << table[i] << "\n";
		}
		std::cout << "\n\n";
	}

protected:
	// Variables are protected so they can be accessed by children.
	int * table;
	int size;
	int r;
	int k;
	char * myName;
};

#endif
