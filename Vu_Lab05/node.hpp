
#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
public:

	Node(T val) { myVal = val; }

	void setVal(T val) { myVal = val; }	
	void setLeft(Node * l) { left = l; }
	void setRight(Node * r) { right = r; }

	T getVal() { return myVal; }
	Node * getLeft() { return left; }
	Node * getRight() { return right; }
private:
	T myVal;
	Node * left = nullptr;
	Node * right = nullptr;
};

#endif
