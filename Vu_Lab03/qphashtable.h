
#ifndef QPHT_H
#define QPHT_H

#include "hashtable.hpp"

class QuadProbeHashTable : public HashTable {
public:
	QuadProbeHashTable(int iSize);
	int hashf(char * x, int len, int times);
};

#endif
