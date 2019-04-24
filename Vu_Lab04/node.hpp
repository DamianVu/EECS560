// Templated Node class designed for holding a single object of type T
// This node is to be used in any data structure that requires knowledge of the next node in some sort of order

#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
public:
	// Let the default constructor be generated for us
	void setItem(T item) { myItem = item; }
	T getItem() { return myItem; }
	void setNext(Node<T> * next) { nextNode = next; }
	Node<T> * getNext() { return nextNode; }
private:
	T myItem;
	Node<T> * nextNode = nullptr;
};

#endif
