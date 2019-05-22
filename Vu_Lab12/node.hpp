
#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
public:

	Node(T val) { myVal = val; }

	void setVal(T val) { myVal = val; }	
	void setNext(Node * r) { next = r; }

	T getVal() { return myVal; }
	Node * getNext() { return next; }
private:
	T myVal;
	Node * next = nullptr;
};

#endif
