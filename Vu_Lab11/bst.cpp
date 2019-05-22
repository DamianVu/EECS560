
#include "bst.h"

BST::~BST() {
	destructorHelper(head);
}

void BST::destructorHelper(Node<int> * node) {
	if (node == nullptr)
		return;

	destructorHelper(node -> getLeft());
	destructorHelper(node -> getRight());

	delete node;
}

void BST::insert(int x) {
	if (head == nullptr) {
		head = new Node<int>(x);
	} else {
		insertHelper(x, head);
	}
}

void BST::insertHelper(int x, Node<int> * node) {
	if (x < node -> getVal()) {
		if (node -> getLeft() == nullptr) {
			node -> setLeft(new Node<int> (x));
		} else {
			insertHelper(x, node -> getLeft());
		}
	} else {
		if (node -> getRight() == nullptr) {
			node -> setRight(new Node<int> (x));
		} else {
			insertHelper(x, node -> getRight());
		}
	}
}

bool BST::remove(int x) {
	Node<int> * delNode = getNode(x, head);
	if (delNode == nullptr) return false;
	Node<int> * parent = getParent(x, head);
	removeHelper(parent, delNode);
	return true;
}

void BST::removeHelper(Node<int> * parent, Node<int> * node) {
	int type = nodeType(node);
	bool nodeIsHead = parent == nullptr;
	bool left;
	if (!nodeIsHead)
		left = parent -> getLeft() == node;

	// 3 cases
	Node<int> * l = node -> getLeft();
	Node<int> * r = node -> getRight();
	Node<int> * temp = nullptr;
	Node<int> * tempParent = nullptr;
	Node<int> * tempChild = nullptr;
	int tempVal;
	switch (type) {
		case 1:
			// Case 1: Leaf node
			// Delete node and sever ties
			if (nodeIsHead) {
				delete node;
				head = nullptr;
			} else {
				delete node;
				if (left)
					parent -> setLeft(nullptr);
				else
					parent -> setRight(nullptr);
			}
		break;
		case 2:
			// Case 2: One child
			// Swap with child and delete
			if (l != nullptr) {
				temp = l;
			}
			else {
				temp = r;
			}
			if (nodeIsHead) {
				head = temp;
				delete node;
			} else {
				tempVal = temp -> getVal();
				temp -> setVal(node -> getVal());
				node -> setVal(tempVal);
				removeHelper(node, temp);
			}
		break;
		case 3:
			// Case 3: Two children
			// Swap with smallest right child then delete again
			tempChild = getSmallestRightChild(node -> getRight());
			if (tempChild == node -> getRight())
				tempParent = node;
			else
				tempParent = getSmallestRightChildParent(node -> getRight());
			tempVal = tempChild -> getVal();
			tempChild -> setVal(node -> getVal());
			node -> setVal(tempVal);
			removeHelper(tempParent, tempChild);
		break;
	}
}

int BST::nodeType(Node<int> * node) {
	if (node -> getLeft() == nullptr && node -> getRight() == nullptr)
		return 1;
	if (node -> getLeft() == nullptr || node -> getRight() == nullptr)
		return 2;
	return 3;
}

Node<int> * BST::getParent(int x, Node<int> * node) {
	if (node -> getVal() == x && node == head) return nullptr;
	
	if (x < node -> getVal()) {
		if (node -> getLeft() -> getVal() == x)
			return node;
		else
			return getParent(x, node -> getLeft());
	} else {
		if (node -> getRight() -> getVal() == x)
			return node;
		else
			return getParent(x, node -> getRight());
	}
}

Node<int> * BST::getNode(int x, Node<int> * node) {
	if (node == nullptr) return nullptr;
	if (node -> getVal() == x) return node;

	if (x < node -> getVal())
		return getNode(x, node -> getLeft());
	else
		return getNode(x, node -> getRight());
}

Node<int> * BST::getSmallestRightChild(Node<int> * node) {
	if (node -> getLeft() == nullptr)
		return node;
	return getSmallestRightChild(node -> getLeft());
}

Node<int> * BST::getSmallestRightChildParent(Node<int> * node) {
	if (node -> getLeft() -> getLeft() == nullptr)
		return node;
	return getSmallestRightChildParent(node -> getLeft());
}

int BST::findMinHelper(Node<int> * node) {
	if (node -> getLeft() == nullptr)
		return node -> getVal();
	else
		return findMinHelper(node -> getLeft());
}

int BST::findMaxHelper(Node<int> * node) {
	if (node -> getRight() == nullptr)
		return node -> getVal();
	else
		return findMaxHelper(node -> getRight());
}

void BST::preorderHelper(Node<int> * node) {
	if (node == nullptr) return;
	printNode(node);
	preorderHelper(node -> getLeft());
	preorderHelper(node -> getRight());
}

void BST::inorderHelper(Node<int> * node) {
	if (node == nullptr) return;
	inorderHelper(node -> getLeft());
	printNode(node);
	inorderHelper(node -> getRight());
}

void BST::postorderHelper(Node<int> * node) {
	if (node == nullptr) return;
	postorderHelper(node -> getLeft());
	postorderHelper(node -> getRight());
	printNode(node);
}

void BST::levelorder() {
	// Queues are lame, so printing level by level should work
	int h = height(head);
	for (int i = 1; i <= h; i++)
		levelorderHelper(head, i);
	std::cout << "\n";
}

void BST::levelorderHelper(Node<int> * node, int level) {
	if (node == nullptr) return;
	if (level == 1) {
		printNode(node);
		return;
	}
	levelorderHelper(node -> getLeft(), level - 1);
	levelorderHelper(node -> getRight(), level - 1);
}

int BST::height(Node<int> * node) {
	if (node == nullptr) return 0;

	int l = height(node -> getLeft());
	int r = height(node -> getRight());

	if (l > r)
		return l + 1;
	else
		return r + 1;
}
