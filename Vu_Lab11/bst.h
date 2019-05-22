
#ifndef BST_H
#define BST_H

#include "node.hpp"
#include <iostream>

class BST {
public:
	// Let compiler auto-generate constructor for us
	BST() {}
	~BST();

	void insert(int x);
	bool remove(int x);

	bool find(int x) { return getNode(x, head) != nullptr; }
	int findMin() { return findMinHelper(head); }
	int findMax() { return findMaxHelper(head); }

	bool isEmpty() { return head == nullptr; }

	void preorder() { preorderHelper(head); std::cout << "\n"; }
	void inorder() { inorderHelper(head); std::cout << "\n"; }
	void postorder() { postorderHelper(head); std::cout << "\n"; }
	void levelorder();
private:
	Node<int> * head = nullptr;

	void printNode(Node<int> * node) { std::cout << node -> getVal() << " "; }

	Node<int> * getParent(int x, Node<int> * node);
	Node<int> * getNode(int x, Node<int> * node);
	Node<int> * getSmallestRightChild(Node<int> * node);
	Node<int> * getSmallestRightChildParent(Node<int> * node);

	int nodeType(Node<int> * node);

	// Recursive helper functions
	void removeHelper(Node<int> * parent, Node<int> * node);
	int findMinHelper(Node<int> * node);
	int findMaxHelper(Node<int> * node);
	void insertHelper(int x, Node<int> * node);
	void destructorHelper(Node<int> * node);
	void preorderHelper(Node<int> * node);
	void inorderHelper(Node<int> * node);
	void postorderHelper(Node<int> * node);
	void levelorderHelper(Node<int> * node, int level);
	int height(Node<int> * node); // Get's height of a given node
};

#endif
