
#include "skew.h"

Node * MaxSkewHeap::merge(Node * h1, Node * h2) {
	if (h1 == nullptr) return h2;
	if (h2 == nullptr) return h1;
	if (*h1 < *h2) { // Change to > for min heap
		Node * temp = h1;
		h1 = h2;
		h2 = temp;
	}
	Node * temp = h1 -> getRight();
	h1 -> setRight(h1 -> getLeft());
	h1 -> setLeft(merge(temp, h2));
	return h1;
}
