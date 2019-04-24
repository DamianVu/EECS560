
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
	if (head == nullptr) {
		// If the list is empty, we set the front
		head = newNode;
	} else {
		// Add to the end
		Node<int> * temp = head;
		while (temp->getNext() != nullptr)
			temp = temp->getNext();
		// Should be at the end of the list
		temp->setNext(newNode);
	}
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

int LinkedList::smallest() {
	// Should not be called if the list is empty
	int smallest = head->getItem();
	Node<int> * current = head->getNext();
	while (current != nullptr) {
		if (current->getItem() < smallest) 
			smallest = current->getItem();
		current = current->getNext();
	}
	return smallest;
}

int LinkedList::largest() {
	// Should not be called if the list is empty
	int largest = head->getItem();
	Node<int> * current = head->getNext();
	while (current != nullptr) {
		if (current->getItem() > largest) 
			largest = current->getItem();
		current = current->getNext();
	}
	return largest;
}

double LinkedList::average() {
	// Should not be called if the list is empty
	double sum = head->getItem();
	int count = 1;
	Node<int> * current = head->getNext();
	while (current != nullptr) {
		sum += current->getItem();
		current = current->getNext();
		count++;
	}
	return sum / count;

}

void LinkedList::mergeTwoLists() {
	// Use IO streams
	std::cout << "Enter new list to be merged (do not put spaces after the last number)\n\n";
	int a;
	std::cin >> a;
	insert(a);
	while (true) {
		if (std::cin.peek() == '\n') break;
		std::cin >> a;
		insert(a);
	}
	sort();
	std::cout << "\nMerged List: ";
	print();
}

void LinkedList::print() {
	if (head != nullptr) {
		Node<int> * current = head;
		while (current != nullptr) {
			std::cout << current->getItem() << " ";
			current = current->getNext();
		}
	}
	std::cout << "\n\n";
}

void LinkedList::sort() {
	if (head == nullptr || head->getNext() == nullptr) return;
	// We were not restricted as to which sort type to use,
	//	so bubble sort is used.

	// This sort is actually even more inefficient due to relying on
	//	isSorted(). This can be easily fixed; it was a lazy start to
	//	the semester.
	while (!isSorted()) {
		Node<int> * first = head;
		Node<int> * second = head->getNext();
		// Swap head if necessary
		if (second->getItem() < first->getItem()) {
			first->setNext(second->getNext());
			second->setNext(first);
			head = second;
			second = first->getNext();
		} else {
			first = second;
			second = second->getNext();
		}
		Node<int> * prev = head;
		while (second != nullptr) {
			if (second->getItem() < first->getItem()) {
				first->setNext(second->getNext());
				second->setNext(first);
				prev->setNext(second);
				second = first->getNext();
			} else {
				first = second;
				second = second->getNext();
			}
			prev = prev->getNext();
		}
	}
}

bool LinkedList::isSorted() {
	if (head == nullptr) return true;
	Node<int> * first = head;
	Node<int> * second = head->getNext();
	while (second != nullptr) {
		if (second->getItem() < first->getItem()) return false;
		first = second;
		second = second->getNext();
	}
	return true;
}
