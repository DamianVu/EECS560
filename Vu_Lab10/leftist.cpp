
#include "leftist.h"

Node * MaxLeftistHeap::merge(Node * h1, Node * h2) {
	if (h1 == nullptr) return h2;
	if (h2 == nullptr) return h1;
	if (*h1 < *h2) { // Change to > for min heap
		Node * temp = h1;
		h1 = h2;
		h2 = temp;
	}
	h1 -> setRight(merge(h1 -> getRight(), h2));
	if (rank(h1 -> getLeft()) < rank(h1 -> getRight())) {
		Node * temp = h1 -> getLeft();
		h1 -> setLeft(h1 -> getRight());
		h1 -> setRight(temp);
	}
	return h1;
}

int MaxLeftistHeap::rank(Node * node) {
	// Calculate minimum distance to external node (min = 1)
	if (node == nullptr) return 0;

	int leftRank = rank(node -> getLeft());
	int minRank = rank(node -> getRight());

	if (leftRank < minRank) minRank = leftRank;

	return minRank + 1;
}
