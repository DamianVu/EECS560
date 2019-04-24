
#ifndef QPHT_H
#define QPHT_H

#include "hashtable.hpp"

class QuadProbeHashTable : public HashTable {
public:
	QuadProbeHashTable(int m, int r, int k);
	int hashf(int x, int times);
};

#endif
