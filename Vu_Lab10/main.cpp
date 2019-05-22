// EECS 560 Lab 10
//
// Author: Damian Vu
// Max Leftist and Skew heaps
//
// Use pointer based implementations of Leftist and Skew heaps
// Gets initial heap data from "data.txt". If "data.txt"
//	does not exist, each heap will be start as empty.
//
// Due date: 04/24/2019

#include "leftist.h"
#include "skew.h"

#include <fstream>
#include <iostream>

int main() {
	MaxLeftistHeap left;
	MaxSkewHeap skew;

	std::ifstream input("data.txt");

	int x;
	while (input >> x) {
		left.insert(x);
		skew.insert(x);
	}

	bool running = true;

	while (running) {
		std::cout << "\n------------------------------------------------------------\nPlease choose one of the following commands:\n1- Insert\n2- Deletemax\n3- Findmax\n4- Preorder\n5- Inorder\n6- Postorder\n7- Levelorder\n8- Exit\n> ";

		std::cin >> x;

		switch (x) {
			case 1:
				std::cout << "Integer to insert: ";
				std::cin >> x;
				left.insert(x);
				skew.insert(x);
				std::cout << "Insert successful\n";
			break;
			case 2:
				if (left.removeMax() & skew.removeMax())
					std::cout << "Delete max successful\n";
				else
					std::cout << "UNSUCCESSFUL: Heaps are empty\n";
			break;
			case 3:
				if (left.findMax() == -99999)
					std::cout << "Heaps are empty!\n";
				else
					std::cout << "Leftist Heap Max: " << left.findMax() << "\nSkew Heap Max: " << skew.findMax() << "\n";
			break;
			case 4:
				std::cout << "Leftist Heap:\n";
				left.preorder();
				std::cout << "Skew Heap:\n";
				skew.preorder();
			break;
			case 5:
				std::cout << "Leftist Heap:\n";
				left.inorder();
				std::cout << "Skew Heap:\n";
				skew.inorder();
			break;
			case 6:
				std::cout << "Leftist Heap:\n";
				left.postorder();
				std::cout << "Skew Heap:\n";
				skew.postorder();
			break;
			case 7:
				std::cout << "Leftist Heap:\n";
				left.levelorder();
				std::cout << "Skew Heap:\n";
				skew.levelorder();
			break;
			case 8:
			default:
				running = false;
			break;
		}
	}

}
