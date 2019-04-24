// EECS 560 Lab 07
//
// Author: Damian Vu
// Two Three Tree
//
// All functions were implemented based on "2-3-trees.pdf"

#include "twothree.h"
// iostream included in twothree.h
#include <fstream>

int main() {
	std::ifstream input("data.txt");
	TwoThreeTree tree;

	char c;
	while (input >> c) {
		tree.insert(c);
	}

	bool running = true;
	while (running) {
		int choice;
		std::cout << "------------------------------------------------------------\nPlease choose one of the following commands:\n1- Insert\n2- Delete\n3- DeleteMin\n4- DeleteMax\n5- Find\n6- FindMin\n7- FindMax\n8- LevelOrder\n9- Exit\n> ";
		std::cin >> choice;
		switch (choice) {
			case 1:
				std::cout << "Enter character to be inserted:\n> ";
				std::cin >> c;
				if (tree.insert(c))
					std::cout << "Insert was successful\n";
				else
					std::cout << "Insert was unsuccessful\n";
			break;
			case 2:
				if (tree.isEmpty()) {
					std::cout << "Tree is empty!\n";
					break;
				}
				std::cout << "Enter character to be deleted:\n> ";
				std::cin >> c;
				if (tree.remove(c))
					std::cout << "Delete was successful\n";
				else
					std::cout << "Delete was unsuccessful\n";
			break;
			case 3:
				if (tree.isEmpty()) {
					std::cout << "Tree is empty!\n";
					break;
				}
				if (tree.removeMin())
					std::cout << "Delete was successful\n";
				else
					std::cout << "Delete was unsuccessful\n";
			break;
			case 4:
				if (tree.isEmpty()) {
					std::cout << "Tree is empty!\n";
					break;
				}
				if (tree.removeMax())
					std::cout << "Delete was successful\n";
				else
					std::cout << "Delete was unsuccessful\n";
			break;
			case 5:
				if (tree.isEmpty()) {
					std::cout << "Tree is empty!\n";
					break;
				}
				std::cout << "Enter a character to be found:\n> ";
				std::cin >> c;
				if (tree.find(c))
					std::cout << "Character found in tree\n";
				else
					std::cout << "Character not found in tree\n";
			break;
			case 6:
				if (tree.isEmpty()) {
					std::cout << "Tree is empty!\n";
					break;
				}
				std::cout << tree.findMin() << "\n";
			break;
			case 7:
				if (tree.isEmpty()) {
					std::cout << "Tree is empty!\n";
					break;
				}
				std::cout << tree.findMax() << "\n";
			break;
			case 8:
				tree.levelorder();
			break;
			case 9:
			default:
				running = false;
			break;
		}
		std::cout << "\n";
	}

	std::cout << "Done!\n";
}
