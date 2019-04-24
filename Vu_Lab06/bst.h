// bst.h
// Modified specifically for Lab 6 to use char *
//   and to get rid of extra overhead.

#ifndef BST_H
#define BST_H

#include "node.hpp"
#include <iostream>

class BST {
public:
	// Let compiler auto-generate constructor for us
	BST() {}
	~BST();

	void insert(char * x);

	bool isEmpty() { return head == nullptr; }

	void levelorder();
private:
	Node<char *> * head = nullptr;

	void printNode(Node<char *> * node);

	// Recursive helper functions
	void destructorHelper(Node<char *> * node);
	void insertHelper(char * x, Node<char *> * node);
	void levelorderHelper(Node<char *> * node, int level);
	int height(Node<char *> * node); // Get's height of a given node

	int ascii(char * word);
};

#endif
