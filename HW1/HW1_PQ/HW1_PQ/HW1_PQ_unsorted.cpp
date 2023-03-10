//Implement a prioprity queue using an unsorted doubly linked list
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
using namespace std;

struct Node { // node of a doubly linked list
	int val;	// value stored at the node
	struct Node* next; // link to the next node
	struct Node* prev; // link to the previous node
	Node(int x) // initialize a new node 
	{
		val = x;
		next = NULL;
		prev = NULL;
	}
};

class UnsortedPQ {

private:
	Node* head;
	Node* tail;
	int length; 	// store the size of priority queue

public:
	UnsortedPQ() { 	// initialize an empty priority queue with a head and a tail of an empty doubly linked list
		head = new Node(NULL);
		tail = new Node(NULL);
		head->next = tail; 	// link between head and tail
		tail->prev = head;
		length = 0;
	}
	void insert(int val)
	{
		Node* temp = new Node(val);
		if (isEmpty()) {
			head->next = temp;
			tail->prev = temp;
			temp->next = tail;
			temp->prev = head;
		}
		else {
			temp->prev = tail->prev;
			tail->prev->next = temp;
			tail->prev = temp;
			temp->next = tail;
		}
		length++;
	}

	Node* min()
	{
		if (isEmpty()) {
			cout << "No elements!" << endl;
			return NULL;
		}
		else {
			Node* temp = head->next;
			Node* min = head->next;
			while (temp->next != NULL) {
				if (temp->val < min->val) {
					min = temp;
				}
				temp = temp->next;
			}
			return min;
		}
	}

	void removeMin()
	{
		if (isEmpty()) {
			cout << "There is no element to remove." << endl;
		}
		else {
			Node* temp = min();
			Node* x = temp->prev;
			Node* y = temp->next;
			y->prev = x;
			x->next = y;
			length--;
		}
	}

	int size() {
		return length;
	}

	bool isEmpty() {
		if (length == 0) {
			return true;
		}
		else
			return false;
	}

	void printPQ() {
		cout << "List of elements in the priority queue: ";
		Node* temp = head->next;
		while (temp != tail) {	 	// print the value of each element one-by-one
			cout << temp->val << " ";
			temp = temp->next;
		}
		cout << endl; 	// end the line
	}
};

int main() {
	UnsortedPQ pq;
	pq.insert(5);
	pq.printPQ();

	pq.insert(9);
	pq.printPQ();

	pq.insert(2);
	pq.printPQ();

	pq.insert(7);
	pq.printPQ();

	cout << "The minimum element in the priority queue is: " << pq.min()->val << endl;
	pq.removeMin();
	pq.printPQ();

	cout << "The size of the priority queue is: " << pq.size() << endl;
	pq.removeMin();
	pq.removeMin();
	pq.removeMin();
	pq.removeMin();

	cout << "The priority queue is empty: " << boolalpha << pq.isEmpty() << endl;

	// sorting using priority queue
	int A[10] = { 12, 8, 40, 6, 25, 81, 30, 4, 15, 2 }; 	// given an arry A with 10 numbers
	int B[10]; // sort the numbers into another array B
	int i = 0;
	for (int i = 0; i < 10; i++) {
		pq.insert(A[i]);
		pq.printPQ();
	}
	for (int i = 0; i < 10; i++) {
		B[i] = pq.min()->val;
		pq.removeMin();
		pq.printPQ();
	}
	for (int i = 0; i < 10; i++) { //print the array B
		cout << B[i] << " ";
	}

	return 0;
}
