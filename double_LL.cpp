#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
    Node* tail;
public:
    CircularLinkedList() { tail = nullptr; }

    // Insert at end
    void insertEnd(int val) {
        Node* newNode = new Node(val);
        if (!tail) {
            tail = newNode;
            tail->next = tail;
        } else {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Insert at beginning
    void insertBegin(int val) {
        Node* newNode = new Node(val);
        if (!tail) {
            tail = newNode;
            tail->next = tail;
        } else {
            newNode->next = tail->next;
            tail->next = newNode;
        }
    }

    // Insert at position (1-based)
    void insertAtPosition(int val, int pos) {
        if (pos == 1) {
            insertBegin(val);
            return;
        }
        Node* temp = tail->next;
        int count = 1;
        while (count < pos - 1 && temp != tail) {
            temp = temp->next;
            count++;
        }
        if (count != pos - 1) {
            cout << "Position out of range\n";
            return;
        }
        Node* newNode = new Node(val);
        newNode->next = temp->next;
        temp->next = newNode;
        if (temp == tail) tail = newNode;
    }

    // Delete from beginning
    void deleteBegin() {
        if (!tail) return;
        Node* head = tail->next;
        if (head == tail) {
            delete head;
            tail = nullptr;
        } else {
            tail->next = head->next;
            delete head;
        }
    }

    // Delete from end
    void deleteEnd() {
        if (!tail) return;
        Node* head = tail->next;
        if (head == tail) {
            delete tail;
            tail = nullptr;
        } else {
            Node* temp = head;
            while (temp->next != tail) temp = temp->next;
            temp->next = tail->next;
            delete tail;
            tail = temp;
        }
    }

    // Delete at position (1-based)
    void deleteAtPosition(int pos) {
        if (!tail) return;
        Node* head = tail->next;
        if (pos == 1) {
            deleteBegin();
            return;
        }
        Node* temp = head;
        int count = 1;
        while (count < pos - 1 && temp->next != head) {
            temp = temp->next;
            count++;
        }
        if (temp->next == head) {
            cout << "Position out of range\n";
            return;
        }
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        if (toDelete == tail) tail = temp;
        delete toDelete;
    }

    // Search for a value
    bool search(int val) {
        if (!tail) return false;
        Node* temp = tail->next;
        do {
            if (temp->data == val) return true;
            temp = temp->next;
        } while (temp != tail->next);
        return false;
    }

    // Count nodes
    int countNodes() {
        if (!tail) return 0;
        int count = 0;
        Node* temp = tail->next;
        do {
            count++;
            temp = temp->next;
        } while (temp != tail->next);
        return count;
    }

    // Display circular linked list
    void display() {
        if (!tail) { cout << "List is empty\n"; return; }
        Node* temp = tail->next;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != tail->next);
        cout << "(head)\n";
    }

    // Reverse circular linked list
    void reverse() {
        if (!tail || tail->next == tail) return;
        Node* prev = tail;
        Node* curr = tail->next;
        Node* next;
        Node* head = tail->next;
        do {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        } while (curr != head);
        tail = head;
    }
};

// Test all operations
int main() {
    CircularLinkedList cll;
    
    cll.insertEnd(10);
    cll.insertEnd(20);
    cll.insertEnd(30);
    cll.insertBegin(5);
    cll.insertAtPosition(15, 3);
    cll.display();
    
    cout << "Count: " << cll.countNodes() << "\n";

    cll.deleteBegin();
    cll.deleteEnd();
    cll.deleteAtPosition(2);
    cll.display();

    cout << "Search 15: " << (cll.search(15) ? "Found" : "Not Found") << "\n";

    cll.reverse();
    cll.display();

    return 0;
}
