// EECS 560 Lab 01
//
// Author: Damian Vu
// Singly linked list
//
// This lab serves as a refresher to basic C++ concepts.
// Create a singly linked list along with extra functions
//
// This program pulls initial data from "data.txt", if "data.txt"
//	does not exist, the list should start as empty.

#include <iostream>
#include <fstream>

#include "linkedlist.h"

int main() {
	LinkedList list;
	
	std::ifstream input("data.txt");
	int i;
	while (input >> i) {
		list.insert(i);
	}

	bool running = true;
	while (running) {
		std::cout << "---------------------------------------------\nChoose one operation from the options below:\n1. Insert\n2. Delete\n3. Find Smallest number\n4. Find Largest number\n5. Average of numbers\n6. Merge2Lists\n7. Print\n8. Exit\n\n>> ";
		int choice;
		std::cin >> choice;
		switch (choice) {
			case 1:
				std::cout << "\nEnter element to be inserted in list: ";
				std::cin >> i;
				list.insert(i);
				std::cout << "\n";
			break;
			case 2:
				std::cout << "\nEnter the number to be deleted: ";
				std::cin >> i;
				if (list.remove(i))
					std::cout << "\nDelete was successful\n\n";
				else
					std::cout << "\nDelete failed. Number was not found in the list.\n\n";
			break;
			case 3:
				if (list.isEmpty())
					std::cout << "\nList is empty!\n\n";
				else
					std::cout << "\nSmallest number: " << list.smallest() << "\n\n";
			break;
			case 4:
				if (list.isEmpty())
					std::cout << "\nList is empty!\n\n";
				else
					std::cout << "\nLargest number: " << list.largest() << "\n\n";
			break;

			case 5:
				if (list.isEmpty())
					std::cout << "\nList is empty!\n\n";
				else
					std::cout << "\nAverage: " << list.average() << "\n\n";
			break;
			case 6:
				std::cout << "\n";
				list.mergeTwoLists();
			break;
			case 7:
				std::cout << "\nList: ";
				list.print();
			break;
			case 8:
			default:
				std::cout << "\nDone!\n";
				running = false;
			break;
		}
	}

	return 0;

}
