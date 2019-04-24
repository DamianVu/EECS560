// EECS 560 Lab 05
//
// Author: Damian Vu
// Binary search tree using pointers

#include "bst.h"
#include <iostream>
#include <fstream>

int main() {
	BST bst;
	std::ifstream input("data.txt");
	int inp;
	while (input >> inp)
		bst.insert(inp);


	// GUARD RECURSIVE OPERATIONS WHEN TREE IS EMPTY
	bool running = true;
	while (running) {
		std::cout << "1 -\tInsert\n2 -\tDelete\n3 -\tFind\n4 -\tFindMin\n5 -\tFindMax\n6 -\tPreorder\n7 -\tInorder\n8 -\tPostorder\n9 -\tLevelorder\n10 -\tExit\n> ";

		int choice;

		std::cin >> choice;

		switch (choice) {
			case 1:
				std::cout << "Enter a number to be inserted:\n> ";
				std::cin >> choice;
				bst.insert(choice);
				// Insert cannot fail. If it fails, let the program break
				std::cout << "Insert was successful\n";
			break;
			case 2:
				std::cout << "Enter a number to be deleted:\n> ";
				std::cin >> choice;
				if (bst.remove(choice)) {
					std::cout << "Delete was successful\n";
				} else {
					std::cout << "Delete failed. Number is not present in tree.\n";
				}
			break;
			case 3:
				std::cout << "Enter a number to be found:\n> ";
				std::cin >> choice;
				if (bst.find(choice)) {
					std::cout << "Number is present in tree.\n";
				} else {
					std::cout << "Number is NOT present in tree.\n";
				}
			break;
			case 4:
				if (bst.isEmpty())
					std::cout << "Tree is empty!!!\n";
				else
					std::cout << "Minimum number: " << bst.findMin() << "\n";
			break;
			case 5:
				if (bst.isEmpty())
					std::cout << "Tree is empty!!!\n";
				else
					std::cout << "Maximum number: " << bst.findMax() << "\n";
			break;
			case 6:
				if (bst.isEmpty())
					std::cout << "Tree is empty!!!\n";
				else
					bst.preorder();
			break;
			case 7:
				if (bst.isEmpty())
					std::cout << "Tree is empty!!!\n";
				else
					bst.inorder();
			break;
			case 8:
				if (bst.isEmpty())
					std::cout << "Tree is empty!!!\n";
				else
					bst.postorder();
			break;
			case 9:
				if (bst.isEmpty())
					std::cout << "Tree is empty!!!\n";
				else
					bst.levelorder();
			break;
			case 10:
			default:
				running = false;
			break;
		}
	}

	return 0;
}
