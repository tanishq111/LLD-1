#include "Node.cpp"

class DLL {
    Node* head;
    Node* tail;
    int size;
public:
    DLL() : head(nullptr), tail(nullptr), size(0) {}

    // Add a new node to the front
    void addFront(int key, int value) {
        Node* newNode = new Node(key, value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    // Add a new node to the back
    void addBack(int key, int value) {
        Node* newNode = new Node(key, value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    // Remove a node from the front
    void removeFront() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        delete temp;
        size--;
    }

    // Remove a node from the back
    void removeBack() {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        delete temp;
        size--;
    }

    int getSize() const {
        return size;
    }
    
    Node* getHead() const {
        return head;
    }

    Node* getTail() const {
        return tail;
    }
};