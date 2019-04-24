// EECS 560 Lab 09
//
// Author: Damian Vu
// Fair scheduler using a minmax heap

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "minmax.h"

int main() {
	MinMaxHeap heap;

	std::ifstream input("data.txt");
	int currentLen = 0;
	char c;
	char buffer[256];

	while (!input.eof()) {
		c = input.get();
		if (c == ' ' || c == '\n') {
			// We should have something like "(x,y),"
			if (currentLen == 0) continue;
			int firstNumStart = 1;
			int firstNumEnd;
			int secondNumStart;
			int secondNumEnd;
			for (int i = 1; i < currentLen; i++) {
				if (buffer[i] == ',') {
					firstNumEnd = i;
					secondNumStart = i + 1;
				}
				else if (buffer[i] == ')') {
					secondNumEnd = i;
					break;
				}
			}
			char * firstNum = new char[firstNumEnd - firstNumStart + 1];
			char * secondNum = new char[secondNumEnd - secondNumStart + 1];
			int loc = 0;
			for (int i = firstNumStart; i < firstNumEnd; i++) {
				firstNum[loc] = buffer[i];
				loc++;
			}
			firstNum[firstNumEnd - firstNumStart] = 0;
			loc = 0;
			for (int i = secondNumStart; i < secondNumEnd; i++) {
				secondNum[loc] = buffer[i];
				loc++;
			}
			secondNum[secondNumEnd - secondNumStart] = 0;
			heap.insert(atoi(firstNum), atoi(secondNum));
			delete [] firstNum;
			delete [] secondNum;
			currentLen = 0;
		} else {
			buffer[currentLen] = c;
			currentLen++;
		}
	}

	heap.buildheap();

	bool running = true;

	while (running) {
		std::cout << "\n\n------------------------------------------------------------\nPlease choose one of the following commands:\n1- Insert\n2- DeleteMin\n3- DeleteMax\n4- FindMin\n5- FindMax\n6- RunSchedule\n7- Exit\n>";
		int choice;

		std::cin >> choice;

		char * firstNum;
		char * secondNum;
		int firstNumStart = 1;
		int firstNumEnd, secondNumStart, secondNumEnd;
		int loc;

		switch (choice) {
			case 1:
				std::cout << "Add a process:\n>";
				std::cin >> buffer;
				for (int i = 1; i < 256; i++) {
					if (buffer[i] == ',') {
						firstNumEnd = i;
						secondNumStart = i + 1;
					} else if (buffer[i] == ')') {
						secondNumEnd = i;
						break;
					}
				}
				firstNum = new char[firstNumEnd - firstNumStart + 1];
				secondNum = new char[secondNumEnd - secondNumStart + 1];
				loc = 0;
				for (int i = firstNumStart; i < firstNumEnd; i++) {
					firstNum[loc] = buffer[i];
					loc++;
				}
				firstNum[firstNumEnd - firstNumStart] = 0;
				loc = 0;
				for (int i = secondNumStart; i < secondNumEnd; i++) {
					secondNum[loc] = buffer[i];
					loc++;
				}
				secondNum[secondNumEnd - secondNumStart] = 0;
				heap.insert(atoi(firstNum), atoi(secondNum));
				delete [] firstNum;
				delete [] secondNum;
			break;
			case 2:
				heap.removeMin();
			break;
			case 3:
				heap.removeMax();
			break;
			case 4:
				heap.findMin();
			break;
			case 5:
				heap.findMax();
			break;
			case 6:
				heap.runSchedule();
			break;
			case 7:
			default:
				running = false;
			break;
		}
	}


}
