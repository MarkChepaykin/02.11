#include <iostream>
#include <stdexcept>

using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int data) : data(data), prev(nullptr), next(nullptr) {}
};

class EmptyListException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Attempted to remove from an empty list.";
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void append(int data) {
        Node* newNode = new Node(data);
        if (!newNode) {
            throw std::bad_alloc();
        }

        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void prepend(int data) {
        Node* newNode = new Node(data);
        if (!newNode) {
            throw std::bad_alloc();
        }

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void removeLast() {
        if (tail == nullptr) {
            throw EmptyListException();
        }

        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
    }

    void display() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    DoublyLinkedList list;

  
    try {
        list.append(10);
        list.append(20);
        list.prepend(5);
        cout << "List after appending and prepending elements:" << endl;
        list.display();
    }
    catch (const std::bad_alloc& e) {
        cout << "Memory allocation failed: " << e.what() << endl;
    }

   
    try {
        list.removeLast();
        cout << "List after removing the last element:" << endl;
        list.display();
    }
    catch (const EmptyListException& e) {
        cout << e.what() << endl;
    }

   
    try {
       
        list.removeLast();
        list.removeLast(); 
        list.removeLast();
    }
    catch (const EmptyListException& e) {
        cout << e.what() << endl;
    }

    return 0;
}
