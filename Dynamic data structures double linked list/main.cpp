#include <iostream>
#include <stdexcept>

template <typename T>
class Array {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;
    int grow;

public:
    Array(int initialSize = 0, int growBy = 1) : head(nullptr), tail(nullptr), size(0), grow(growBy) {
        SetSize(initialSize, growBy);
    }

    ~Array() {
        RemoveAll();
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int newSize, int growBy = 1) {
        grow = growBy;
        if (newSize < size) {
            int diff = size - newSize;
            for (int i = 0; i < diff; ++i) {
                RemoveAt(size - 1);
            }
        }
        else if (newSize > size) {
            for (int i = size; i < newSize; ++i) {
                Add(T{});
            }
        }
    }

    int GetUpperBound() const {
        return size - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        Node* current = head;
        int count = 0;
        while (current && count < size) {
            current = current->next;
            ++count;
        }
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        if (tail) {
            tail->next = nullptr;
        }
    }

    void RemoveAll() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }

    T& GetAt(int index) {
        return GetNode(index)->data;
    }

    void SetAt(int index, const T& value) {
        GetNode(index)->data = value;
    }

    T& operator[](int index) {
        return GetAt(index);
    }

    void Add(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size;
    }

    void Append(const Array& other) {
        Node* current = other.head;
        while (current) {
            Add(current->data);
            current = current->next;
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            RemoveAll();
            Node* current = other.head;
            while (current) {
                Add(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    T* GetData() {
        if (!head) return nullptr;
        T* dataArray = new T[size];
        Node* current = head;
        for (int i = 0; i < size; ++i) {
            dataArray[i] = current->data;
            current = current->next;
        }
        return dataArray;
    }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of bounds");
        }
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = head;
            if (head) {
                head->prev = newNode;
            }
            head = newNode;
            if (!tail) {
                tail = head;
            }
        }
        else {
            Node* prevNode = GetNode(index - 1);
            newNode->next = prevNode->next;
            newNode->prev = prevNode;
            if (prevNode->next) {
                prevNode->next->prev = newNode;
            }
            prevNode->next = newNode;
            if (!newNode->next) {
                tail = newNode;
            }
        }
        ++size;
    }

    void RemoveAt(int index) {
        Node* nodeToDelete = GetNode(index);
        if (nodeToDelete->prev) {
            nodeToDelete->prev->next = nodeToDelete->next;
        }
        else {
            head = nodeToDelete->next;
        }
        if (nodeToDelete->next) {
            nodeToDelete->next->prev = nodeToDelete->prev;
        }
        else {
            tail = nodeToDelete->prev;
        }
        delete nodeToDelete;
        --size;
    }

private:
    Node* GetNode(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }
};

int main() {
    Array<int> arr(5, 2);
    for (int i = 0; i < arr.GetSize(); ++i) {
        arr[i] = i + 1;
    }
    arr.Add(6);
    arr.SetSize(10);
    arr.InsertAt(2, 99);
    arr.RemoveAt(4);
    arr.FreeExtra();

    for (int i = 0; i < arr.GetSize(); ++i) {
        std::cout << arr[i] << " ";
    }

    return 0;
}
