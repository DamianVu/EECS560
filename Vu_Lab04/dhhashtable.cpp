
#include "dhhashtable.h"

DoubleHashHashTable::DoubleHashHashTable(int m, int r, int k) : HashTable(m, r, k) {
	// Let the base class do all the work
	myName = new char[15];
	myName[0] = 'D';
	myName[1] = 'o';
	myName[2] = 'u';
	myName[3] = 'b';
	myName[4] = 'l';
	myName[5] = 'e';
	myName[6] = ' ';
	myName[7] = 'H';
	myName[8] = 'a';
	myName[9] = 's';
	myName[10] = 'h';
	myName[11] = 'i';
	myName[12] = 'n';
	myName[13] = 'g';
	myName[14] = 0;
}

int DoubleHashHashTable::hashf(int x, int times) {
	int f = r - (x % r);
	return f * times;
}
