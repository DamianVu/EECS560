// mergeheap.hpp
//
// Base class for MAX mergable 2-heap implementations
//
// Methods that must be overriden in child classes:
// merge
//
// This base class is suitable for any 2-heap that utilizes
//	merge for insertion and deletion of the max value.

#ifndef MERGEHEAP_HPP
#define MERGEHEAP_HPP

#include <iostream>
#include "node.hpp"

class MergeHeap {
public:
	MergeHeap() {
		head = nullptr;
	}

	// Deletion cascades (check node.hpp), so just delete head
	~MergeHeap() {
		if (head != nullptr) delete head;
	}

	// Pure virtual method. Must be overridden by children
	virtual Node * merge(Node * h1, Node * h2) = 0;

	void insert(int x) {
		// Create new node and merge with head
		Node * temp = new Node();
		temp -> setVal(x);
		head = merge(head, temp);
	}

	bool removeMax() {
		if (head == nullptr) return false;
		Node * temp = head;
		head = merge(head -> getLeft(), head -> getRight());
		temp -> setLeft(nullptr);  // So cascading works properly
		temp -> setRight(nullptr); // ^
		delete temp;
		return true;
	}

	// If tree is empty, returns -99999
	int findMax() {
		if (head == nullptr) return -99999;
		return head -> getVal();
	}

	void preorder() {
		preorderHelper(head);
		std::cout << "\n";
	}

	void inorder() {
		inorderHelper(head);
		std::cout << "\n";
	}

	void postorder() {
		postorderHelper(head);
		std::cout << "\n";
	}

	void levelorder() {
		// Non-queue based method of generating level order traversal
		int h = height(head);
		for (int i = 1; i <= h; i++) {
			levelorderHelper(head, i);
			std::cout << "\n";
		}
		std::cout << "\n";
	}

protected:
	// Protected variables can be accessed by children
	Node * head;

private:
	// Recursive helpers for printing tree traversals
	void preorderHelper(Node * node) {
		if (node == nullptr) return;
		print(node);
		preorderHelper(node -> getLeft());
		preorderHelper(node -> getRight());
	}

	void inorderHelper(Node * node) {
		if (node == nullptr) return;
		inorderHelper(node -> getLeft());
		print(node);
		inorderHelper(node -> getRight());
	}

	void postorderHelper(Node * node) {
		if (node == nullptr) return;
		postorderHelper(node -> getLeft());
		postorderHelper(node -> getRight());
		print(node);
	}

	void levelorderHelper(Node * node, int level) {
		if (node == nullptr) return;
		if (level == 1) {
			print(node);
			return;
		}
		levelorderHelper(node -> getLeft(), level - 1);
		levelorderHelper(node -> getRight(), level - 1);
	}

	// Prints a nodes value followed by a space
	void print(Node * node) {
		std::cout << node -> getVal() << " ";
	}

	// This function technically give the height of the tree plus 1.
	// This means an empty tree has a height of 0, and a tree with
	// a single node has a height of 1.
	int height(Node * node) {
		if (node == nullptr) return 0;

		int l = height(node -> getLeft());
		int r = height(node -> getRight());

		if (l > r)
			return l + 1;
		else
			return r + 1;
	}
};

#endif
