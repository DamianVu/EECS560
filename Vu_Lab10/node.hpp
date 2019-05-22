// node.hpp
// Basic 2-node class that holds an int as its value
// Contains operator override for <,> for comparisons
//
// Destructor is set so deletion cascades, i.e., make sure
// 	that when you delete single nodes in main tree, you set
//	the left and right pointers to null so they are not accidentally
//	deleted.

#ifndef NODE_HPP
#define NODE_HPP

class Node {
public:
	Node() {}
	~Node() {
		if (left != nullptr) delete left;
		if (right != nullptr) delete right;
	}

	void setVal(int v) { val = v; }
	void setLeft(Node * l) { left = l; }
	void setRight(Node * r) { right = r; }

	int getVal() { return val; }
	Node * getLeft() { return left; }
	Node * getRight() { return right; }

	bool operator < (const Node& n) {
		return val < n.val;
	}

	bool operator > (const Node & n) {
		return val > n.val;
	}

private:
	int val = -1;
	Node * left = nullptr;
	Node * right = nullptr;
};

#endif
