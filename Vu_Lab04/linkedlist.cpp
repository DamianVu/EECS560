
#include "linkedlist.h"

LinkedList::~LinkedList() {
	while (head != nullptr) {
		Node<int> * temp = head->getNext();
		delete head;
		head = temp;
	}
}

void LinkedList::insert(int i) {
	Node<int> * newNode = new Node<int>();
	newNode->setItem(i);
	Node<int> * temp = head;
	head = newNode;
	newNode->setNext(temp);
	temp = nullptr;
	newNode = nullptr;
}

bool LinkedList::remove(int i) {
	if (head == nullptr) return false;
	if (head->getItem() == i) { // Case 0
		Node<int> * temp = head;
		head = head->getNext();
		delete temp;
		return true;
	}
	Node<int> * prev = head;
	Node<int> * search = prev->getNext();
	while (search != nullptr) { // Case n: n>0
		if (search->getItem() == i) {
			prev->setNext(search->getNext());
			delete search;
			return true;
		}
		prev = search;
		search = search->getNext();
	}
	return false;
}

int LinkedList::take() {
	if (head == nullptr) return -1;
	int retVal = head->getItem();
	Node<int> * temp = head->getNext();
	delete head;
	head = temp;
	temp = nullptr;
	return retVal;
}

int LinkedList::count() {
	int sum = 0;
	Node<int> * temp = head;
	while (temp != nullptr) {
		sum++;
		temp = temp->getNext();
	}
	return sum;
}

bool LinkedList::find(int i) {
	Node<int> * temp = head;
	while (temp != nullptr) {
		if (temp->getItem() == i) return true;
		temp = temp->getNext();
	}
	return false;
}

void LinkedList::print() {
	if (head != nullptr) {
		Node<int> * current = head;
		while (current != nullptr) {
			std::cout << " -> " << current->getItem();
			current = current->getNext();
		}
	}
	std::cout << "\n";
}
