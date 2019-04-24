// hashtable.hpp
//
// Abstract class for a hash table of strings.
// Used to avoid duplicate functions across types of hash tables
//
// Children of this class NEED to override hashf()
// hashf() is the collision resolution side of the insertion, which
// should be the only way that two hash tables differ.

#ifndef HT_H
#define HT_H

#include <iostream>

class HashTable {
public:
	virtual int hashf(char * x, int len, int times) = 0; // Collision resolution function

	HashTable(int iSize) {
		count = 0;
		size = iSize;
		table = new char * [size];
		lengths = new int[size];
		for (int i = 0; i < size; i++) {
			table[i] = nullptr;
			lengths[i] = -1;
		}
	}

	~HashTable() {
		for (int i = 0; i < size; i++) {
			if (table[i] == nullptr) continue;
			delete [] table[i];
		}
		delete [] lengths;
		delete [] table;
		delete [] myName;
	}

	bool isPrime(int x) {
		for (int i = 2; i*i < x; i++) {
			if (x % i == 0) 
				return false;
		}
		return true;
	}

	int getNewSize() {
		int s = (size * 2) + 1;
		while (!isPrime(s))
			s = s + 1;
		return s;
	}

	int hashval(char * x, int len) {
		int s = (len > 8) ? 8 : len; // Will always be 8 or less
		int sum = 0;
		for (int i = 0; i < s; i++) {
			int weight = 1;
			for (int j = 0; j < i; j++)
				weight = weight * 10;
			sum += ((int)x[i]) * weight;
		}
		return sum;
	}

	int hash(char * x, int len) {
		return hashval(x,len) % size;
	}

	void rehash() {
		std::cout << "\n\nRehashing.....\n\n";
		int oldSize = size;
		size = getNewSize();
		char ** newTable = new char * [size];
		int * newLengths = new int[size];
		for (int i = 0; i < size; i++) {
			newTable[i] = nullptr;
			newLengths[i] = -1;
		}
		for (int i = 0; i < oldSize; i++) {
			// Basically inserting into the new table.
			if (table[i] == nullptr) continue;
			int loc = hash(table[i], lengths[i]);
			int tempCount = 0;
			while (newTable[loc] != nullptr) {
				tempCount++;
				loc = (hash(table[i], lengths[i]) + hashf(table[i], lengths[i], tempCount)) % size;
			}
			// We have our new location.
			newTable[loc] = table[i];
			newLengths[loc] = lengths[i];
			table[i] = nullptr;
			
		}

		// Delete old tables
		delete [] lengths;
		lengths = newLengths;
		newLengths = nullptr;

		delete [] table;
		table = newTable;
		newTable = nullptr;
		justRehashed = true;
	}

	void insert(char * x, int len) {
		if (findDup(x,len)) { // This function checks if the string already exists in the table.
			std::cout << myName << ": " << x << " is duplicated, can't be added to the hash table\n";
			delete [] x;
			return;
		}
		count++;
		double loadFactor = (double)count / (double)size;
		if (loadFactor > 0.5)
			rehash();

		int loc = hash(x, len);
		int tempCount = 0;
		while (table[loc] != nullptr) {
			// Find the new location
			tempCount++;
			loc = (hash(x,len) + hashf(x, len, tempCount)) % size;
		}
		// We have our new location.
		table[loc] = x;
		lengths[loc] = len;
		if (activated && !justRehashed)
			std::cout << myName << ": " << x << " is inserted into the hash table\n";

		if (justRehashed) {
			print();
			justRehashed = false;
		}
	}

	bool findDup(char * x, int len) {
		int count = 0;
		while (count < k) {
			// Check location
			int loc = (hash(x,len) + hashf(x,len,count)) % size;
			if (table[loc] == nullptr) return false; // Definitely not in table
			if (hashval(table[loc], lengths[loc]) == hashval(x, len)) return true;
			count++;
		}
		return false;
	}
	
	void remove(char * x, int len) {
		for (int i = 0; i < size; i++) {
			if (table[i] == nullptr) continue;
			if (lengths[i] == len) {
				bool foundWord = true;
				for (int j = 0; j < len; j++) {
					if (table[i][j] != x[j]){
						foundWord = false;
						break;
					}
				}
				if (foundWord) {
					// Delete the word
					delete [] table[i];
					table[i] = nullptr;
					lengths[i] = -1;
					count--;
					std::cout << myName << ": " << x << " is deleted from the hash table\n";
					return;
				}
			}
		}
		std::cout << myName << ": " << x << " cannot be found in the hash table\n";
	}

	void find(char * x, int len) {
		// Find if word is same
		int count = 0;
		while (count < k) {
			// Check location
			int loc = (hash(x,len) + hashf(x,len,count)) % size;
			if (table[loc] == nullptr) break; // Definitely not in table
			if (hashval(table[loc], lengths[loc]) == hashval(x,len)) {
				std::cout << myName << ": " << x << " is found at location " << loc << "\n";
				return;
			}
			count++;
		}

		char * revWord = new char[len + 1];
		for (int i = 0; i < len; i++)
			revWord[i] = x[len - 1 - i];
		revWord[len] = 0;

		// Find if word is reversed

		count = 0;
		while (count < k) {
			int loc = (hash(revWord,len) + hashf(revWord,len,count)) % size;
			if (table[loc] ==  nullptr) break; // Definitely not in table in rev order
			if (hashval(table[loc],lengths[loc]) == hashval(revWord, len)) {
				std::cout << myName << ": " << x << " is found in REVERSE ORDER at location " << loc << "\n";
				delete [] revWord;
				revWord = nullptr;
				return;
			}
			count++;
		}
		delete [] revWord;
		revWord = nullptr;
		std::cout << myName << ": " << x << " is not found in the table\n";
	}

	void findPalindromes() {
		int count = 0;
		std::cout << "Palindrome strings: ";
		for (int i = 0; i < size; i++) {
			if (table[i] == nullptr) continue;
			if (isPalindrome(i)){
				std::cout << table[i] << " ";
				count++;
			}
		}
		if (count == 0)
			std::cout << "None found!\n";
		std::cout << "\n";
	}

	bool isPalindrome(int index) {
		int len = lengths[index];
		bool isPalindrome = true;
		for (int i = 0; i < len; i++) {
			int revIndex = len - 1 - i;
			if (table[index][i] != table[index][revIndex]){
				isPalindrome = false;
				break;
			}
		}
		return isPalindrome;
	}

	void reverseString(int index) {
		if (table[index] == nullptr) {
			std::cout << "There is no string at location " << index << " with " << myName << ".\n";
			return;
		}
		int len = lengths[index];
		char * temp = new char[len + 1];
		for (int i = 0; i < len; i++) {
			int revIndex = len - 1 - i;
			temp[i] = table[index][revIndex];
		}
		temp[len] = 0;
		std::cout << myName << ": String \"" << table[index] << "\" is changed to \"" << temp << "\"\n";
		delete [] table[index];
		table[index] = temp;
		temp = nullptr;
	}

	void print() {
		std::cout << myName << ":\n\n";
		for (int i = 0; i < size; i++) {
			if (table[i] != nullptr)
				std::cout << i << ": " << table[i] << "\n";
		}
		std::cout << "\n\n";
	}

	void activate() {
		activated = true;
	}

protected:
	// Variables are protected so they can be accessed by children.
	char ** table;
	int * lengths;
	int size;
	int count;
	char * myName;
	bool activated = false;
	bool justRehashed = false;
	const int k = 11;
};

#endif
