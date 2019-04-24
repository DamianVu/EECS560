// EECS 560 Lab 06
//
// Author: Damian Vu
// Optimal Binary Search Trees

#include <fstream>
#include <iostream>

#include "bst.h"

const bool DEBUG = false; // Set to true to see more info about cost and root array.

// GLOBAL VARIABLES

// Populated with parseData()
int numWords = 0;
int count = 0;
int * occurrences = nullptr;
double * probabilities = nullptr;
char ** words = nullptr;

// Populated with calculateOptimalBST()
double ** costs = nullptr;
int ** roots = nullptr;

// Forward declare (These are implemented at the bottom...)
int ascii(char * word);
void addWord(char * word);
void parseData();
void calculateOptimalBST();
void addToBST(BST * bst, int i, int j);

int main() {
	parseData(); // Separated to make main a little cleaner.

	// Now we have all words, occurrences, and probabilities sorted in ASCII order.

	// Initialize cost and root arrays
	// Weird sizes, can't think of a better way of doing it right now
	costs = new double * [numWords + 2];
	roots = new int * [numWords + 1];

	for (int i = 0; i <= numWords; i++)
		roots[i] = new int [numWords + 1];
	for (int i = 0; i < numWords + 2; i++)
		costs[i] = new double [numWords + 2];

	// Populate cost and root arrays
	calculateOptimalBST();

	// For debugging purposes
	if (DEBUG) {
		std::cout << "Probabilities:\n";
		for (int i = 0; i < numWords; i++)
			std::cout << probabilities[i] << " ";
		std::cout << "\nCosts array:\n";
		for (int i = 1; i <= numWords; i++) {
			for (int j = 1; j <= numWords; j++)
				std::cout << costs[i][j] << " ";
			std::cout << "\n";
		}
		std::cout << "Roots array\n";
		for (int i = 1; i <= numWords; i++) {
			for (int j = 1; j <= numWords; j++)
				std::cout << roots[i][j] << " ";
			std::cout << "\n";
		}
	}

	BST * bst = new BST();

	// Recursive call to add based on root array.
	addToBST(bst, 1, numWords);

	// Print BST
	bst -> levelorder();

	std::cout << "\nThe minimal cost is: " << costs[1][numWords] << ".\n";


	// Clean up
	delete bst;

	delete [] occurrences;
	delete [] probabilities;

	for (int i = 0; i < numWords + 2; i++) {
		if (i < numWords)
			delete [] words[i];
		if (i <= numWords)
			delete [] roots[i];
		delete [] costs[i];
	}

	delete [] words;
	delete [] roots;
	delete [] costs;

	return 0;
}

void parseData() {
	std::ifstream input("data.txt");

	// Since we can't use strings.
	int currentLen = 0;
	char c;
	char buffer[100];
	while (!input.eof()) {
		c = input.get();
		if (c == ' ') {
			// Add word to table
			if (currentLen == 0) continue;
			char * word = new char[currentLen + 1];
			for (int i = 0; i < currentLen; i++)
				word[i] = buffer[i];
			word[currentLen] = 0;
			currentLen = 0;
			addWord(word);
			word = nullptr;
		} else if (c == '\n') {
			if (currentLen != 0) {
				currentLen--;
				char * word = new char[currentLen + 1];
				for (int i = 0; i < currentLen; i++)
					word[i] = buffer[i];
				word[currentLen] = 0;
				currentLen = 0;
				addWord(word);
				word = nullptr;
			}
			break;
		} else {
			buffer[currentLen] = c;
			currentLen++;
		}
	}
}

int ascii(char * word) {
	int sum = 0;
	int ind = 0;
	while (word[ind] != 0) {
		sum += (int) word[ind];
		ind++;
	}
	return sum;
}

void addWord(char * word) {
	if (words == nullptr) {
		words = new char * [1];
		occurrences = new int [1];
		probabilities = new double [1];
		words[0] = word;
		occurrences[0] = 1;
		numWords++;
	} else {
		bool exists = false;
		for (int i = 0; i < numWords; i++) {
			int ind = 0;
			bool endWord = false;
			bool match = true;
			char * currentWord = words[i];

			while (!endWord) {
				if (word[ind] == 0 || currentWord[ind] == 0)
					break;
				if (word[ind] != currentWord[ind]) {
					match = false;
					break;
				}
				ind++;
			}

			if (match) {
				exists = true;
				occurrences[i]++;
				delete [] word;
				break;
			}
		}

		if (!exists) {
			// Add word to list.
			char ** tempW = new char * [numWords + 1];
			int * tempO = new int[numWords + 1];

			// Calculate spot for new word
			// This will keep them in ascending ASCII order.
			int spot = -1;
			int currentIndex = 0;
			int newAscii = ascii(word);
			while (spot == -1) {
				int wAscii = ascii(words[currentIndex]);
				if (newAscii > wAscii) {
					currentIndex++;
				} else if (newAscii < wAscii) {
					spot = currentIndex;
				} else {
					spot = currentIndex + 1;
				}

				if (currentIndex == numWords)
					spot = currentIndex;
			}
			
			bool foundSpot = false;
			for (int i = 0; i < numWords + 1; i++) {
				if (i == spot) {
					tempW[i] = word;
					tempO[i] = 1;
					foundSpot = true;
				} else {
					int ind = i;
					if (foundSpot) 
						ind = i - 1;
					tempW[i] = words[ind];
					tempO[i] = occurrences[ind];
				}
			}

			delete [] words;
			delete [] occurrences;
			delete [] probabilities;
			words = tempW;
			occurrences = tempO;
			tempW = nullptr;
			tempO = nullptr;
			numWords++;
			probabilities = new double [numWords];
		}
	}
	count++;
	for (int i = 0; i < numWords; i++)
		probabilities[i] = ((double) occurrences[i]) / count;
}

void calculateOptimalBST() {
	// Zero out whole array. This way we can avoid undefined behavior.
	for (int i = 0; i < numWords + 2; i++)
		for (int j = 0; j < numWords + 2; j++)
			costs[i][j] = 0;

	for (int i = 1; i <= numWords; i++)
		for (int j = i + 1; j < numWords + 2; j++)
			costs[i][j] = 999999; // Easier initialization. All costs should be less than this...

	// Calculate cost and root for single nodes
	for (int i = 1; i <= numWords; i++) {
		costs[i][i] = probabilities[i - 1];
		roots[i][i] = i;
	}

	// Calculate cost and root for j+1 nodes
	for (int j = 1; j < numWords; j++)
		for (int i = 1; i <= numWords - j; i++) {
			for (int k = i; k <= i + j; k++) {
				double temp = costs[i][k - 1] + costs[k + 1][i + j];
				if (temp < costs[i][i + j]) {
					// Cost is less, so set it.
					count++;
					costs[i][i + j] = temp;
					roots[i][i + j] = k;
				}
			}

			// Add sum(P_i,...,P_j)
			for (int k = i; k <= i + j; k++) {
				costs[i][i + j] += probabilities[k - 1];
			}
		}
}

void addToBST(BST * bst, int i, int j) {
	// Add words to tree in preorder. 
	// This should give us a tree representation with everything in the
	// 	 right place.
	if (j < i)
		return;
	bst -> insert(words[roots[i][j] - 1]);
	addToBST(bst, i, roots[i][j] - 1);
	addToBST(bst, roots[i][j] + 1, j);
}
