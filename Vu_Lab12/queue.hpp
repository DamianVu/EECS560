
#ifndef Q_H
#define Q_H

#include "node.hpp"

class Queue {
public:
	Queue() { 
		size = 0;
		head = nullptr;
	};

	bool isEmpty() { return size == 0; }

	void enqueue(int i) {
		if (head == nullptr) {
			head = new Node<int>(i);
		} else {
			Node<int> * current = head;
			while (current -> getNext() != nullptr)
				current = current -> getNext();
			current -> setNext(new Node<int>(i));
		}
		size++;
	}

	int dequeue() {
		if (head == nullptr) return -1;
		int ret = head -> getVal();
		Node<int> * temp = head;
		head = head -> getNext();
		size--;
		delete temp;
		return ret;
	}

private:
	int size;
	Node<int> * head;
};

#endif
