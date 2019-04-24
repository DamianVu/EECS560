// EECS 560 Lab 03
//
// Author: Damian Vu
// Closed hashing with double hashing and quadratic probing

#include <fstream>
#include <iostream>
#include "qphashtable.h"
#include "dhhashtable.h"

int main() {
	std::ifstream input("data.txt");

	int initialSize;
	input >> initialSize;

	QuadProbeHashTable qpht(initialSize);
	DoubleHashHashTable dhht(initialSize);


	// Since we can NOT use strings, let's get creative.

	int currentLen = 0;
	char c;
	char buffer[100];

	while (!input.eof()) {
		c = input.get();
		if (c == ' ') {
			// Add word to table
			if (currentLen == 0) continue;
			char * word = new char[currentLen + 1];
			char * word2 = new char[currentLen + 1];
			for (int i = 0; i < currentLen; i++) {
				word[i] = buffer[i];
				word2[i] = buffer[i];
			}
			word[currentLen] = 0;
			word2[currentLen] = 0;
			qpht.insert(word, currentLen);
			dhht.insert(word2, currentLen);
			word = nullptr;
			word2 = nullptr;
			currentLen = 0;
		} else if (c == '\n') {
			if (currentLen != 0) {
				currentLen--;
				char * word = new char[currentLen + 1];
				char * word2 = new char[currentLen + 1];
				for (int i = 0; i < currentLen; i++) {
					word[i] = buffer[i];
					word2[i] = buffer[i];
				}
				word[currentLen] = 0;
				word2[currentLen] = 0;
				qpht.insert(word, currentLen);
				dhht.insert(word2, currentLen);
				word = nullptr;
				word2 = nullptr;
			}
			break;
		} else {
			// Add char to list
			buffer[currentLen] = c;
			currentLen++;
		}
	}


	// Start outputting now.
	qpht.activate();
	dhht.activate();


	// Let's get running
	bool running = true;

	while (running) {
		std::cout << "\n------------------------------------------------------------\nPlease choose one of the following commands:\n1- Insert\n2- Delete\n3- Find\n4- FindPalindrome\n5- ReverseString\n6- Print\n7- Exit\n>";
		int choice;
		std::cin >> choice;
		char * word = nullptr;
		char * word2 = nullptr;

		switch (choice) {
			case 1:
				std::cout << "Enter a string to be inserted:\n>";
				currentLen = 0;
				c = std::cin.get();
				while (c = std::cin.get()) {
					if (c == '\n') {
						// Keep string
						word = new char[currentLen + 1];
						word2 = new char[currentLen + 1];
						for (int i = 0; i < currentLen; i++) {
							word[i] = buffer[i];
							word2[i] = buffer[i];
						}
						word[currentLen] = 0;
						word2[currentLen] = 0;
						break;
					}
					buffer[currentLen] = c;
					currentLen++;
				}
				// Need to copy word or else we will wind up with multiple deletes later :(
				qpht.insert(word, currentLen);
				dhht.insert(word2, currentLen);
				word = nullptr;
				word2 = nullptr;

			break;
			case 2:
				std::cout << "Enter a string to be deleted:\n>";
				currentLen = 0;
				c = std::cin.get();
				while (c = std::cin.get()) {
					if (c == '\n') {
						// Keep string
						word = new char[currentLen + 1];
						for (int i = 0; i < currentLen; i++) {
							word[i] = buffer[i];
						}
						word[currentLen] = 0;
						break;
					}
					buffer[currentLen] = c;
					currentLen++;
				}
				qpht.remove(word, currentLen);
				dhht.remove(word, currentLen);
				delete [] word;
				word = nullptr;
			break;
			case 3:
				std::cout << "Enter a string to be found:\n>";
				currentLen = 0;
				c = std::cin.get();
				while (c = std::cin.get()) {
					if (c == '\n') {
						// Keep string
						word = new char[currentLen + 1];
						for (int i = 0; i < currentLen; i++) {
							word[i] = buffer[i];
						}
						word[currentLen] = 0;
						break;
					}
					buffer[currentLen] = c;
					currentLen++;
				}
				qpht.find(word, currentLen);
				dhht.find(word, currentLen);
				delete[] word;
				word = nullptr;
			break;
			case 4:
				qpht.findPalindromes();
			break;
			case 5:
				std::cout << "Enter location of string you want to reverse:\n>";
				std::cin >> choice;
				qpht.reverseString(choice);
				dhht.reverseString(choice);
			break;
			case 6:
				qpht.print();
				dhht.print();
			break;
			case 7:
			default:
				running = false;
			break;
		}
	}


}
