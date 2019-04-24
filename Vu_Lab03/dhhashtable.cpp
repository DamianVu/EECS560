
#include "dhhashtable.h"

DoubleHashHashTable::DoubleHashHashTable(int iSize) : HashTable(iSize) {
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

int DoubleHashHashTable::hashf(char * x, int len, int times) {
	int hx = hashval(x, len);
	int f = R - (hx % R);
	return f * times;
}
