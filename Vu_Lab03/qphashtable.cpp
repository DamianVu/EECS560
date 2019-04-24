
#include "qphashtable.h"

QuadProbeHashTable::QuadProbeHashTable(int iSize) : HashTable(iSize) {
	// Let the base class do all the work
	myName = new char[18];
	myName[0] = 'Q';
	myName[1] = 'u';
	myName[2] = 'a';
	myName[3] = 'd';
	myName[4] = 'r';
	myName[5] = 'a';
	myName[6] = 't';
	myName[7] = 'i';
	myName[8] = 'c';
	myName[9] = ' ';
	myName[10] = 'P';
	myName[11] = 'r';
	myName[12] = 'o';
	myName[13] = 'b';
	myName[14] = 'i';
	myName[15] = 'n';
	myName[16] = 'g';
	myName[17] = 0;

}

int QuadProbeHashTable::hashf(char * x, int len, int times) {
	// We don't need h(x) for quadratic probing.
	return (times * times);
}
