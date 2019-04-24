
#include "bst.h"
#include <iomanip>

BST::~BST() {
	destructorHelper(head);
}

void BST::destructorHelper(Node<char *> * node) {
	if (node == nullptr)
		return;

	destructorHelper(node -> getLeft());
	destructorHelper(node -> getRight());

	delete node;
}

void BST::insert(char * x) {
	if (head == nullptr) {
		head = new Node<char *>(x);
	} else {
		insertHelper(x, head);
	}
}

void BST::insertHelper(char * x, Node<char *> * node) {
	if (ascii(x) < ascii(node -> getVal())) {
		if (node -> getLeft() == nullptr) {
			node -> setLeft(new Node<char *> (x));
		} else {
			insertHelper(x, node -> getLeft());
		}
	} else {
		if (node -> getRight() == nullptr) {
			node -> setRight(new Node<char *> (x));
		} else {
			insertHelper(x, node -> getRight());
		}
	}
}

void BST::levelorder() {
	// Queues are lame, so printing level by level should work
	std::cout << "\n_ indicates an empty space in the tree.\n\n";
	int h = height(head);
	for (int i = 1; i <= h; i++) {
		for (int j = i; j < h; j++)
			std::cout << "   ";
		levelorderHelper(head, i);
		std::cout << "\n";
	}
	std::cout << "\n";
}

void BST::levelorderHelper(Node<char *> * node, int level) {
	if (level == 1) {
		printNode(node);
		return;
	}
	if (node == nullptr) {
		levelorderHelper(nullptr, level - 1);
		levelorderHelper(nullptr, level - 1);
	} else {
		levelorderHelper(node -> getLeft(), level - 1);
		levelorderHelper(node -> getRight(), level - 1);
	}
}

void BST::printNode(Node<char *> * node) {
	if (node == nullptr)
		std::cout << "_   ";
	else
		std::cout << node -> getVal() << "   ";
}

int BST::height(Node<char *> * node) {
	if (node == nullptr) return 0;

	int l = height(node -> getLeft());
	int r = height(node -> getRight());

	if (l > r)
		return l + 1;
	else
		return r + 1;
}

int BST::ascii(char * word) {
	int sum = 0;
	int ind = 0;
	while (word[ind] != 0) {
		sum += (int) word[ind];
		ind++;
	}
	return sum;
}
