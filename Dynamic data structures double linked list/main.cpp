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
};

int main() {
	Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	q.print();

	q.pop();
	q.pop();

	q.print();


	return 0;
}