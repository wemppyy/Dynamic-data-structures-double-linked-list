#include <iostream>

using namespace std;

template <typename T>
class Queue {
private:
	struct Node {
		T data;
		Node* next;
		Node* prev;
	};

	Node* head;
	Node* tail;
	int size;
public:
	Queue() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	~Queue() {
		while (head != nullptr) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void push(T data) {
		Node* newNode = new Node;
		newNode->data = data;
		newNode->next = nullptr;
		newNode->prev = tail;

		if (tail != nullptr) {
			tail->next = newNode;
		}

		tail = newNode;

		if (head == nullptr) {
			head = newNode;
		}

		size++;
	}

	void pop() {
		if (head == nullptr) {
			return;
		}

		Node* temp = head;
		head = head->next;
		delete temp;

		if (head == nullptr) {
			tail = nullptr;
		}
		else {
			head->prev = nullptr;
		}

		size--;
	}

	T front() {
		if (head == nullptr) {
			throw "Queue is empty";
		}

		return head->data;
	}

	T back() {
		if (tail == nullptr) {
			throw "Queue is empty";
		}

		return tail->data;
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	void print() {
		Node* temp = head;
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	Queue<T>* clone() {
		Queue<T>* newQueue = new Queue<T>;
		Node* temp = head;
		while (temp != nullptr) {
			newQueue->push(temp->data);
			temp = temp->next;
		}
		return newQueue;
	}

	Queue<T>* operator+(Queue<T>& q) {
		Queue<T>* newQueue = clone();
		Node* temp = q.head;
		while (temp != nullptr) {
			newQueue->push(temp->data);
			temp = temp->next;
		}
		return newQueue;
	}

	Queue<T>* operator*(int n) {
		Queue<T>* newQueue = clone();
		for (int i = 0; i < n - 1; i++) {
			Node* temp = head;
			while (temp != nullptr) {
				newQueue->push(temp->data);
				temp = temp->next;
			}
		}
		return newQueue;
	}
};

int main() {
	Queue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	cout << "q1: ";
	q.print();

	Queue<int> q2;

	q2.push(6);
	q2.push(7);
	q2.push(8);
	q2.push(9);
	q2.push(10);

	cout << "q2: ";
	q2.print();

	Queue<int>* q3 = q + q2;

	cout << "q3: ";
	q3->print();

	Queue<int>* q4 = q * 2;

	cout << "q4: ";
	q4->print();

	return 0;
}