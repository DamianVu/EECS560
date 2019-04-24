
#ifndef TWOTHREE_H
#define TWOTHREE_H

#include "twothreenode.hpp"
#include <iostream>

class TwoThreeTree {
public:
	TwoThreeTree() {}
	~TwoThreeTree();

	bool isEmpty() { return root == nullptr; }
	bool insert(char c); // True if inserted, False if duplicate
	bool find(char c); // True if found, False otherwise
	bool remove(char c); // True if deleted, False if not present
	bool removeMin(); // True if deleted, False if empty
	bool removeMax(); // True if deleted, False if empty

	char findMin(TwoThreeNode * node = nullptr); // Return min char
	char findMax(TwoThreeNode * node = nullptr); // Return max char

	void levelorder(); // Print in level order


private:
	TwoThreeNode * root = nullptr;

	TwoThreeNode * findNode(char c);

	TwoThreeNode * findNodeHelper(TwoThreeNode * node, int a);

	bool findHelper(TwoThreeNode * node, int a);

	char findMinHelper(TwoThreeNode * node);

	char findMaxHelper(TwoThreeNode * node);

	void printNode(TwoThreeNode * node);

	void pushdown(TwoThreeNode * inputNode, TwoThreeNode * node);

	void kickup(TwoThreeNode * inputNode, TwoThreeNode * node);

	void fixParents();

	void fixParentHelper(TwoThreeNode * node);

	void levelorderHelper(TwoThreeNode * node, int level);

	void removeDown(TwoThreeNode * node, char c);

	void fixHole(TwoThreeNode * node);

	int ascii(char c) { return (int)c; }

	int height(TwoThreeNode * node);
};

#endif
