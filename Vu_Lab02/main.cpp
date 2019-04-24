// EECS 560 Lab 02
//
// Author: Damian Vu
// Hash table with separate chaining (Open Hashing)
//
// This program uses an array of linked lists in order to create
//	a hash table that uses open hashing.
//
// This program receives initial data from "data.txt".
//	This data must first include the initial size of the table,
//	as the size will not change.
//
// The hash table should not allow duplicate values

#include <iostream>
#include <fstream>

#include "hashtable.h"

int main() {

	std::ifstream input("data.txt");

	int size;
	input >> size;
	HashTable table(size);
	while (input >> size) {
		table.insert(size);
	}

	bool running = true;
	while (running) {
		std::cout << "------------------------------------------------------------\nPlease choose one of the following commands:\n1- Insert\n2- Delete\n3- Find\n4- Print\n5- Exit\n>";
		int choice;
		std::cin >> choice;
		switch (choice) {
			case 1:
				std::cout << "Enter a number to be inserted:\n>";
				std::cin >> choice;
				if (table.insert(choice)) {
					std::cout << choice << " is added to the hash table\n\n";
				} else {
					std::cout << choice << " was NOT added because it already exists in the table\n\n";
				}
			break;
			case 2:
				std::cout << "Enter a number to be removed:\n>";
				std::cin >> choice;
				if (table.remove(choice)) {
					std::cout << choice << " was removed from the hash table.\n\n";
				} else {
					std::cout << choice << " could not be found in the hash table.\n\n";
				}
			break;
			case 3:
				std::cout << "Enter a number to be found:\n>";
				std::cin >> choice;
				if (table.find(choice)) {
					std::cout << choice << " was found in the hash table at location " << table.hash(choice) << ".\n\n";
				} else {
					std::cout << choice << " was not found in the hash table.\n\n";
				}
			break;
			case 4:
				std::cout << "\n";
				table.print();
				std::cout << "\n";
			break;
			case 5:
			default:
				running = false;
			break;
		}
	}
	return 0;
}
