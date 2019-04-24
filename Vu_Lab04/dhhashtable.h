
#ifndef DHHT_H
#define DHHT_H

#include "hashtable.hpp"

class DoubleHashHashTable : public HashTable {
public:
	DoubleHashHashTable(int m, int r, int k);
	int hashf(int x, int times);

private:
};

#endif
