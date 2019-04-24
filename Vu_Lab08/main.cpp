// EECS 560 Lab 08
//
// Author: Damian Vu
// Min and Max 5-Heaps

#include <fstream>
#include "minfiveheap.h"
#include "maxfiveheap.h"

int main() {
	MinFiveHeap min;
	MaxFiveHeap max;

	std::ifstream input("data.txt");

	int x;
	while (input >> x) {
		min.insert(x);
		max.insert(x);
	}
	min.buildheap();
	max.buildheap();

	bool running = true;

	while (running) {
		std::cout << "------------------------------------------------------------\nPlease choose one of the following commands:\n1- Insert\n2- DeleteMin\n3- DeleteMax\n4- FindMin\n5- FindMax\n6- LevelOrder\n7- Exit\n> ";
		
		std::cin >> x;
		switch(x) {
			case 1:
				std::cout << "Enter number to be inserted: ";
				std::cin >> x;
				min.insert(x);
				max.insert(x);
				
				std::cout << "Min 5 Heap:\n";
				min.levelorder();
				std::cout << "\nMax 5 Heap:\n";
				max.levelorder();
			break;
			case 2:
				min.deletemin();
				max.deletemin();

				std::cout << "Min 5 Heap:\n";
				min.levelorder();
				std::cout << "\nMax 5 Heap:\n";
				max.levelorder();
			break;
			case 3:
				min.deletemax();
				max.deletemax();
				
				std::cout << "Min 5 Heap:\n";
				min.levelorder();
				std::cout << "\nMax 5 Heap:\n";
				max.levelorder();
			break;
			case 4:
				std::cout << "Minimum value: " << min.findmin() << "\n";
			break;
			case 5:
				std::cout << "Maximum value: " << min.findmax() << "\n";
			break;
			case 6:
				std::cout << "Min 5 Heap:\n";
				min.levelorder();
				std::cout << "\nMax 5 Heap:\n";
				max.levelorder();
			break;
			case 7:
			default:
				running = false;
			break;
		}
	}
}
