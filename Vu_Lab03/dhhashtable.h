
#ifndef DHHT_H
#define DHHT_H

#include "hashtable.hpp"

class DoubleHashHashTable : public HashTable {
public:
	DoubleHashHashTable(int iSize);
	int hashf(char * x, int len, int times);

private:
	int R = 5;
};

#endif
