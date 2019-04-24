
#include "twothree.h"

TwoThreeTree::~TwoThreeTree() {
	if (root != nullptr)
		delete root;
}

bool TwoThreeTree::insert(char c) {
	if (isEmpty()) {
		// Set as root
		root = new TwoThreeNode(c, 0);
		return true;
	}
	if (find(c)) return false;

	TwoThreeNode * node = new TwoThreeNode(c, 0);
	pushdown(node, root);
	fixParents();
	return true;
}

void TwoThreeTree::fixParents() {
	// Remove this function after we fix pushdown/kickup
	if (root != nullptr)
		root -> setParent(nullptr);
	fixParentHelper(root);
}

void TwoThreeTree::fixParentHelper(TwoThreeNode * node) {
	if (node == nullptr) return;
	if (node -> getLeft() != nullptr)
		node -> getLeft() -> setParent(node);
	if (node -> getMiddle() != nullptr)
		node -> getMiddle() -> setParent(node);
	if (node -> getRight() != nullptr)
		node -> getRight() -> setParent(node);
	fixParentHelper(node -> getLeft());
	fixParentHelper(node -> getMiddle());
	fixParentHelper(node -> getRight());
}

void TwoThreeTree::pushdown(TwoThreeNode * inputNode, TwoThreeNode * node) {
	if (inputNode == nullptr) return;
	if (node -> isTerminalNode()) {
		// Terminal node optimization
		kickup(inputNode, node);
	} else {
		int w = ascii(inputNode -> getLeftVal());
		if (node -> isTwoNode()) {
			int x = ascii(node -> getLeftVal());
			if (w < x)
				pushdown(inputNode, node -> getLeft());
			else {
				pushdown(inputNode, node -> getRight());
			}
		} else {
			int x = ascii(node -> getLeftVal());
			int y = ascii(node -> getRightVal());
			if (w < x)
				pushdown(inputNode, node -> getLeft());
			else if (w > y)
				pushdown(inputNode, node -> getRight());
			else {
				pushdown(inputNode, node -> getMiddle());
			}
		}
	}
}

void TwoThreeTree::kickup(TwoThreeNode * inputNode, TwoThreeNode * node) {
	if (node == nullptr) {
		return;
	}
	if (node -> isTwoNode()) {
		// Absorb
		if (ascii(inputNode -> getLeftVal()) < ascii(node -> getLeftVal())) {
			node -> setRightVal(node -> getLeftVal());
			node -> setLeftVal(inputNode -> getLeftVal());
			node -> setLeft(inputNode -> getLeft());
			node -> setMiddle(inputNode -> getRight());
		} else {
			node -> setRightVal(inputNode -> getLeftVal());
			node -> setMiddle(inputNode -> getLeft());
			node -> setRight(inputNode -> getRight());
		}
		if (node -> getLeft() != nullptr)
			node -> getLeft() -> setParent(node);
		if (node -> getMiddle() != nullptr)
			node -> getMiddle() -> setParent(node);
		if (node -> getRight() != nullptr)
			node -> getRight() -> setParent(node);
		inputNode -> setLeft(nullptr);
		inputNode -> setMiddle(nullptr);
		inputNode -> setRight(nullptr);
		delete inputNode;
	} else {
		// Kicking up to a three node
		int w = ascii(inputNode -> getLeftVal());
		int x = ascii(node -> getLeftVal());
		int y = ascii(node -> getRightVal());
		if (w < x) {
			// Insert on left
			inputNode -> setParent(node);
			TwoThreeNode * newRight = new TwoThreeNode(node -> getRightVal(), 0);
			newRight -> setLeft(node -> getMiddle());
			newRight -> setRight(node -> getRight());
			newRight -> setParent(node);
			node -> setRightVal(0);
			node -> setLeft(inputNode);
			node -> setRight(newRight);
			node -> setMiddle(nullptr);
			kickup(node, node -> getParent());
		} else if (w > y) {
			// Insert on right
			inputNode -> setParent(node);
			TwoThreeNode * newLeft = new TwoThreeNode(node -> getLeftVal(), 0);
			newLeft -> setLeft(node -> getLeft());
			newLeft -> setRight(node -> getMiddle());
			newLeft -> setParent(node);
			node -> setLeftVal(node -> getRightVal());
			node -> setRightVal(0);
			node -> setLeft(newLeft);
			node -> setRight(inputNode);
			node -> setMiddle(nullptr);
			kickup(node, node -> getParent());
		} else {
			// Insert in middle
			if (node == root) {
				root = inputNode;
				inputNode -> setParent(nullptr);
			} else {
				TwoThreeNode * par = node -> getParent();
				inputNode -> setParent(par);
				if (par -> getLeft() == node)
					par -> setLeft(inputNode);
				else if (par -> getMiddle() == node)
					par -> setMiddle(inputNode);
				else
					par -> setRight(inputNode);
			}
			TwoThreeNode * newLeft = new TwoThreeNode(node -> getLeftVal(), 0);
			newLeft -> setLeft(node -> getLeft());
			newLeft -> setRight(inputNode -> getLeft());
			newLeft -> setParent(inputNode);
			TwoThreeNode * newRight = new TwoThreeNode(node -> getRightVal(), 0);
			newRight -> setLeft(inputNode -> getRight());
			newRight -> setRight (node -> getRight());
			newRight -> setParent(inputNode);
			inputNode -> setLeft(newLeft);
			inputNode -> setMiddle(nullptr);
			inputNode -> setRight(newRight);
			node -> setLeft(nullptr);
			node -> setMiddle(nullptr);
			node -> setRight(nullptr);
			delete node;
			kickup(inputNode, inputNode -> getParent());
		}
	}
}

bool TwoThreeTree::find(char c) {
	return findHelper(root, ascii(c));
}

bool TwoThreeTree::findHelper(TwoThreeNode * node, int a) {
	if (node == nullptr) return false;
	if (node -> isTwoNode()) {
		int nodeVal = ascii(node -> getLeftVal());
		if (nodeVal == a)
			return true;
		if (a < nodeVal)
			return findHelper(node -> getLeft(), a);
		else
			return findHelper(node -> getRight(), a);
	} else {
		int lNodeVal = ascii(node -> getLeftVal());
		int rNodeVal = ascii(node -> getRightVal());
		if (lNodeVal == a || rNodeVal == a)
			return true;
		if (a < lNodeVal)
			return findHelper(node -> getLeft(), a);
		if (a > rNodeVal)
			return findHelper(node -> getRight(), a);
		return findHelper(node -> getMiddle(), a);
	}
}

TwoThreeNode * TwoThreeTree::findNode(char c) {
	return findNodeHelper(root, ascii(c));
}

TwoThreeNode * TwoThreeTree::findNodeHelper(TwoThreeNode * node, int a) {
	if (node == nullptr) return nullptr;
	if (node -> isTwoNode()) {
		int nodeVal = ascii(node -> getLeftVal());
		if (nodeVal == a)
			return node;
		if (a < nodeVal)
			return findNodeHelper(node -> getLeft(), a);
		else
			return findNodeHelper(node -> getRight(), a);
	} else {
		int lNodeVal = ascii(node -> getLeftVal());
		int rNodeVal = ascii(node -> getRightVal());
		if (lNodeVal == a || rNodeVal == a)
			return node;
		if (a < lNodeVal)
			return findNodeHelper(node -> getLeft(), a);
		if (a > rNodeVal)
			return findNodeHelper(node -> getRight(), a);
		return findNodeHelper(node -> getMiddle(), a);
	}
}

bool TwoThreeTree::remove(char c) {
	if (!find(c))
		return false;
	removeDown(findNode(c), c);
	fixParents();
	return true;
}

void TwoThreeTree::removeDown(TwoThreeNode * node, char c) {
	if (node -> isTerminalNode()) {
		if (node -> isTwoNode()) {
			node -> setLeftVal(0);
			// node l/m/r pointers should be nullptr
			fixHole(node);
		} else {
			// Easiest case
			if (c == node -> getLeftVal())
				node -> setLeftVal(node -> getRightVal());
			node -> setRightVal(0);
		}
	} else {
		// Repl node HAS to be a terminal node
		if (node -> isTwoNode()) {
			// Find replacement
			char replChar = findMax(node -> getLeft());
			TwoThreeNode * replNode = findNode(replChar);
			if (replNode -> isTwoNode()) {
				// Will leave a hole
				node -> setLeftVal(replChar);
				replNode -> setLeftVal(0);
				fixHole(replNode);
			} else {
				// No hole necessary
				if (replChar == replNode -> getLeftVal())
					replNode -> setLeftVal(replNode -> getRightVal());
				replNode -> setRightVal(0);
				node -> setLeftVal(replChar);
			}
		} else {
			char replChar;
			bool left;
			if (c == node -> getLeftVal()) {
				replChar = findMax(node -> getLeft());
				left = true;
			}
			else {
				left = false;
				replChar = findMax(node -> getMiddle());
			}
			TwoThreeNode * replNode = findNode(replChar);
			if (replNode -> isTwoNode()) {
				// Will leave a hole
				if (left)
					node -> setLeftVal(replChar);
				else
					node -> setRightVal(replChar);
				replNode -> setLeftVal(0);
				fixHole(replNode);
			} else {
				// No hole necessary
				if (replChar == replNode -> getLeftVal())
					replNode -> setLeftVal(replNode -> getRightVal());
				replNode -> setRightVal(0);
				if (left)
					node -> setLeftVal(replChar);
				else
					node -> setRightVal(replChar);
			}
		}
	}
}

void TwoThreeTree::fixHole(TwoThreeNode * node) {
	if (!(node -> isHole())) {
		std::cout << "ERROR: FIXHOLE CALLED ON NON-HOLE NODE\n";
		return;
	}
	TwoThreeNode * parent = node -> getParent();
	if (parent == nullptr) {
		// Hole is now at the root.
		root = node -> getLeft();
		node -> setLeft(nullptr);
		node -> setMiddle(nullptr);
		node -> setRight(nullptr);
		delete node;
		return;
	}
	TwoThreeNode * sibling; 
	if (parent -> isTwoNode()) {
		bool sLeft;
		if (parent -> getLeft() == node) {
			sLeft = false;
			sibling = parent -> getRight();
		} else {
			sLeft = true;
			sibling = parent -> getLeft();
		}

		if (sibling -> isTwoNode()) {
			// Case 1
			TwoThreeNode * newHoleChild;
			if (sLeft) {
				newHoleChild = new TwoThreeNode(sibling -> getLeftVal(), parent -> getLeftVal());
				newHoleChild -> setLeft(sibling -> getLeft());
				newHoleChild -> setMiddle(sibling -> getRight());
				newHoleChild -> setRight(node -> getLeft());
			} else {
				newHoleChild = new TwoThreeNode(parent -> getLeftVal(), sibling -> getLeftVal());
				newHoleChild -> setLeft(node -> getLeft());
				newHoleChild -> setMiddle(sibling -> getLeft());
				newHoleChild -> setRight(sibling -> getRight());
			}
			newHoleChild -> setParent(node);

			TwoThreeNode * grandparent = parent -> getParent();
			node -> setParent(grandparent);
			node -> setLeft(newHoleChild);

			if (grandparent != nullptr) {
				if (grandparent -> getLeft() == parent)
					grandparent -> setLeft(node);
				else if (grandparent -> getRight() == parent)
					grandparent -> setRight(node);
				else
					grandparent -> setMiddle(node);
			}

			parent -> setLeft(nullptr);
			parent -> setMiddle(nullptr);
			parent -> setRight(nullptr);
			sibling -> setLeft(nullptr);
			sibling -> setMiddle(nullptr);
			sibling -> setRight(nullptr);
			delete parent;
			delete sibling;
			fixHole(node);
		} else {
			// Case 2
			// There will be no hole after this.
			TwoThreeNode * newParent;
			TwoThreeNode * newLeftChild;
			TwoThreeNode * newRightChild;
			if (sLeft) {
				newParent = new TwoThreeNode(sibling -> getRightVal(), 0);
				newLeftChild = new TwoThreeNode(sibling -> getLeftVal(), 0);
				newLeftChild -> setLeft(sibling -> getLeft());
				newLeftChild -> setRight(sibling -> getMiddle());
				newRightChild = new TwoThreeNode(parent -> getLeftVal(), 0);
				newRightChild -> setLeft(sibling -> getRight());
				newRightChild -> setRight(node -> getLeft());
			} else {
				newParent = new TwoThreeNode(sibling -> getLeftVal(), 0);
				newLeftChild = new TwoThreeNode(parent -> getLeftVal(), 0);
				newLeftChild -> setLeft(node -> getLeft());
				newLeftChild -> setRight(sibling -> getLeft());
				newRightChild = new TwoThreeNode(sibling -> getRightVal(), 0);
				newRightChild -> setLeft(sibling -> getMiddle());
				newRightChild -> setRight(sibling -> getRight());
			}
			newLeftChild -> setParent(newParent);
			newRightChild -> setParent(newParent);
			newParent -> setLeft(newLeftChild);
			newParent -> setRight(newRightChild);

			TwoThreeNode * grandparent = parent -> getParent();
			newParent -> setParent(grandparent);

			if (grandparent != nullptr) {
				if (grandparent -> getLeft() == parent)
					grandparent -> setLeft(newParent);
				else if (grandparent -> getRight() == parent)
					grandparent -> setRight(newParent);
				else
					grandparent -> setMiddle(newParent);
			} else {
				// This will be the new root
				root = newParent;
			}
			node -> setLeft(nullptr);
			node -> setMiddle(nullptr);
			node -> setRight(nullptr);
			parent -> setLeft(nullptr);
			parent -> setMiddle(nullptr);
			parent -> setRight(nullptr);
			sibling -> setLeft(nullptr);
			sibling -> setMiddle(nullptr);
			sibling -> setRight(nullptr);
			delete node;
			delete parent;
			delete sibling;
		}
	} else {
		TwoThreeNode * newParent;
		TwoThreeNode * newLeftChild;
		TwoThreeNode * newRightChild;
		if (parent -> getLeft() == node) {
			// Hole is on left
			sibling = parent -> getMiddle();
			if (sibling -> isTwoNode()) {
				// Case 3a
				// New left child is a three node
				newParent = new TwoThreeNode(parent -> getRightVal(), 0);
				newLeftChild = new TwoThreeNode(parent -> getLeftVal(), sibling -> getLeftVal());
				newLeftChild -> setLeft(node -> getLeft());
				newLeftChild -> setMiddle(sibling -> getLeft());
				newLeftChild -> setRight(sibling -> getRight());
				newLeftChild -> setParent(newParent);
				newRightChild = parent -> getRight();
				newRightChild -> setParent(newParent);
				newParent -> setLeft(newLeftChild);
				newParent -> setRight(newRightChild);

				TwoThreeNode * grandparent = parent -> getParent();
				newParent -> setParent(grandparent);

				if (grandparent != nullptr) {
					if (grandparent -> getLeft() == parent)
						grandparent -> setLeft(newParent);
					else if (grandparent -> getRight() == parent)
						grandparent -> setRight(newParent);
					else
						grandparent -> setMiddle(newParent);
				} else {
					root = newParent;
				}
				node -> setLeft(nullptr);
				node -> setMiddle(nullptr);
				node -> setRight(nullptr);
				parent -> setLeft(nullptr);
				parent -> setMiddle(nullptr);
				parent -> setRight(nullptr);
				sibling -> setLeft(nullptr);
				sibling -> setMiddle(nullptr);
				sibling -> setRight(nullptr);
				delete node;
				delete parent;
				delete sibling;
			} else {
				// Case 4a
				newParent = new TwoThreeNode(sibling -> getLeftVal(), parent -> getRightVal());
				newLeftChild = new TwoThreeNode(parent -> getLeftVal(), 0);
				newLeftChild -> setLeft(node -> getLeft());
				newLeftChild -> setRight(sibling -> getLeft());
				newLeftChild -> setParent(newParent);

				newRightChild = new TwoThreeNode(sibling -> getRightVal(), 0);
				newRightChild -> setLeft(sibling -> getMiddle());
				newRightChild -> setRight(sibling -> getRight());
				newRightChild -> setParent(newParent);

				newParent -> setLeft(newLeftChild);
				newParent -> setMiddle(newRightChild);
				newParent -> setRight(parent -> getRight());

				TwoThreeNode * grandparent = parent -> getParent();
				newParent -> setParent(grandparent);

				if (grandparent != nullptr) {
					if (grandparent -> getLeft() == parent)
						grandparent -> setLeft(newParent);
					else if (grandparent -> getRight() == parent)
						grandparent -> setRight(newParent);
					else
						grandparent -> setMiddle(newParent);
				} else {
					root = newParent;
				}
				node -> setLeft(nullptr);
				node -> setMiddle(nullptr);
				node -> setRight(nullptr);
				parent -> setLeft(nullptr);
				parent -> setMiddle(nullptr);
				parent -> setRight(nullptr);
				sibling -> setLeft(nullptr);
				sibling -> setMiddle(nullptr);
				sibling -> setRight(nullptr);
				delete node;
				delete parent;
				delete sibling;
			}
		} else if (parent -> getRight() == node) {
			// Hole is on right
			sibling = parent -> getMiddle();
			if (sibling -> isTwoNode()) {
				// Case 3b
				// New right child is a three node
				newParent = new TwoThreeNode(parent -> getLeftVal(), 0);
				newLeftChild = parent -> getLeft();
				newLeftChild -> setParent(newParent);
				newRightChild = new TwoThreeNode(sibling -> getLeftVal(), parent -> getRightVal());
				newRightChild -> setLeft(sibling -> getLeft());
				newRightChild -> setMiddle(sibling -> getRight());
				newRightChild -> setRight(node -> getLeft());
				newRightChild -> setParent(newParent);
				newParent -> setLeft(newLeftChild);
				newParent -> setRight(newRightChild);

				TwoThreeNode * grandparent = parent -> getParent();
				newParent -> setParent(grandparent);

				if (grandparent != nullptr) {
					if (grandparent -> getLeft() == parent)
						grandparent -> setLeft(newParent);
					else if (grandparent -> getRight() == parent)
						grandparent -> setRight(newParent);
					else
						grandparent -> setMiddle(newParent);
				} else {
					root = newParent;
				}
				node -> setLeft(nullptr);
				node -> setMiddle(nullptr);
				node -> setRight(nullptr);
				parent -> setLeft(nullptr);
				parent -> setMiddle(nullptr);
				parent -> setRight(nullptr);
				sibling -> setLeft(nullptr);
				sibling -> setMiddle(nullptr);
				sibling -> setRight(nullptr);
				delete node;
				delete parent;
				delete sibling;
			} else {
				// Case 4b
				newParent = new TwoThreeNode(parent -> getLeftVal(), sibling -> getRightVal());
				newLeftChild = new TwoThreeNode(sibling -> getLeftVal(), 0);
				newLeftChild -> setLeft(sibling -> getLeft());
				newLeftChild -> setRight(sibling -> getMiddle());
				newLeftChild -> setParent(newParent);

				newRightChild = new TwoThreeNode(parent -> getRightVal(), 0);
				newRightChild -> setLeft(sibling -> getRight());
				newRightChild -> setRight(node -> getLeft());
				newRightChild -> setParent(newParent);

				newParent -> setLeft(parent -> getLeft());
				newParent -> setMiddle(newLeftChild);
				newParent -> setRight(newRightChild);

				TwoThreeNode * grandparent = parent -> getParent();
				newParent -> setParent(grandparent);

				if (grandparent != nullptr) {
					if (grandparent -> getLeft() == parent)
						grandparent -> setLeft(newParent);
					else if (grandparent -> getRight() == parent)
						grandparent -> setRight(newParent);
					else
						grandparent -> setMiddle(newParent);
				} else {
					root = newParent;
				}
				node -> setLeft(nullptr);
				node -> setMiddle(nullptr);
				node -> setRight(nullptr);
				parent -> setLeft(nullptr);
				parent -> setMiddle(nullptr);
				parent -> setRight(nullptr);
				sibling -> setLeft(nullptr);
				sibling -> setMiddle(nullptr);
				sibling -> setRight(nullptr);
				delete node;
				delete parent;
				delete sibling;
			}
		} else {
			// Hole is in the middle (ambiguous?)
			// Let's use the sibling to the left.
			sibling = parent -> getLeft();
			if (sibling -> isTwoNode()) {
				// Case 3a
				newParent = new TwoThreeNode(parent -> getRightVal(), 0);
				newLeftChild = new TwoThreeNode(sibling -> getLeftVal(), parent -> getLeftVal());
				newLeftChild -> setLeft(sibling -> getLeft());
				newLeftChild -> setMiddle(sibling -> getRight());
				newLeftChild -> setRight(node -> getLeft());
				newLeftChild -> setParent(newParent);
				newRightChild = parent -> getRight();
				newRightChild -> setParent(newParent);
				newParent -> setLeft(newLeftChild);
				newParent -> setRight(newRightChild);

				TwoThreeNode * grandparent = parent -> getParent();
				newParent -> setParent(grandparent);

				if (grandparent != nullptr) {
					if (grandparent -> getLeft() == parent)
						grandparent -> setLeft(newParent);
					else if (grandparent -> getRight() == parent)
						grandparent -> setRight(newParent);
					else
						grandparent -> setMiddle(newParent);
				} else {
					root = newParent;
				}
				node -> setLeft(nullptr);
				node -> setMiddle(nullptr);
				node -> setRight(nullptr);
				parent -> setLeft(nullptr);
				parent -> setMiddle(nullptr);
				parent -> setRight(nullptr);
				sibling -> setLeft(nullptr);
				sibling -> setMiddle(nullptr);
				sibling -> setRight(nullptr);
				delete node;
				delete parent;
				delete sibling;
			} else {
				// Case 4a
				newParent = new TwoThreeNode(sibling -> getRightVal(), parent -> getRightVal());
				newLeftChild = new TwoThreeNode(sibling -> getLeftVal(), 0);
				newLeftChild -> setLeft(sibling -> getLeft());
				newLeftChild -> setRight(sibling -> getMiddle());
				newLeftChild -> setParent(newParent);

				newRightChild = new TwoThreeNode(parent -> getLeftVal(), 0);
				newRightChild -> setLeft(sibling -> getRight());
				newRightChild -> setRight(node -> getLeft());
				newRightChild -> setParent(newParent);

				newParent -> setLeft(newLeftChild);
				newParent -> setMiddle(newRightChild);
				newParent -> setRight(parent -> getRight());

				TwoThreeNode * grandparent = parent -> getParent();
				newParent -> setParent(grandparent);

				if (grandparent != nullptr) {
					if (grandparent -> getLeft() == parent)
						grandparent -> setLeft(newParent);
					else if (grandparent -> getRight() == parent)
						grandparent -> setRight(newParent);
					else
						grandparent -> setMiddle(newParent);
				} else {
					root = newParent;
				}
				node -> setLeft(nullptr);
				node -> setMiddle(nullptr);
				node -> setRight(nullptr);
				parent -> setLeft(nullptr);
				parent -> setMiddle(nullptr);
				parent -> setRight(nullptr);
				sibling -> setLeft(nullptr);
				sibling -> setMiddle(nullptr);
				sibling -> setRight(nullptr);
				delete node;
				delete parent;
				delete sibling;
			}
		}
	}
}

bool TwoThreeTree::removeMin() {
	return remove(findMin());
}

bool TwoThreeTree::removeMax() {
	return remove(findMax());
}

char TwoThreeTree::findMin(TwoThreeNode * node) {
	if (node == nullptr)
		return findMinHelper(root);
	return findMinHelper(node);
}

char TwoThreeTree::findMinHelper(TwoThreeNode * node) {
	if (node -> getLeft() == nullptr)
		return node -> getLeftVal();
	return findMinHelper(node -> getLeft());
}

char TwoThreeTree::findMax(TwoThreeNode * node) {
	if (node == nullptr)
		return findMaxHelper(root);
	return findMaxHelper(node);
}

char TwoThreeTree::findMaxHelper(TwoThreeNode * node) {
	if (node -> getRight() == nullptr) {
		if (node -> getRightVal() == 0)
			return node -> getLeftVal();
		return node -> getRightVal();
	}
	return findMaxHelper(node -> getRight());
}

void TwoThreeTree::levelorder() {
	int h = height(root);
	for (int i = 1; i <= h; i++) {
		levelorderHelper(root, i);
	}
	std::cout << "\n";
}

void TwoThreeTree::levelorderHelper(TwoThreeNode * node, int level) {
	if (node == nullptr) 
		return;
	if (level == 1) {
		printNode(node);
		return;
	}
	levelorderHelper(node -> getLeft(), level - 1);
	levelorderHelper(node -> getMiddle(), level - 1);
	levelorderHelper(node -> getRight(), level - 1);
}

void TwoThreeTree::printNode(TwoThreeNode * node) {
	if (node == nullptr) return;
	std::cout << node -> getLeftVal() << " ";
	if (node -> getRightVal() != 0)
		std::cout << node -> getRightVal() << " ";

}

int TwoThreeTree::height(TwoThreeNode * node) {
	if (node == nullptr) return 0;

	int l = height(node -> getLeft());
	int m = height(node -> getMiddle());
	int r = height(node -> getRight());

	if (l != m && m != r && l != r)
		std::cout << "Height is different :(\n";

	if (l > r)
		if (m > l) 
			return m + 1;
		else
			return l + 1;
	else
		if (m > r)
			return m + 1;
		else
			return r + 1;
}
