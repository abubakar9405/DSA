#include<iostream>
using namespace std;
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Function to rotate the list counterclockwise by k nodes
void rotate(Node*& head, int k) {
    if (!head || k == 0) return;

    Node* current = head;
    int length = 1;

    // Find the length of the linked list
    while (current->next != nullptr) {
        current = current->next;
        length++;
    }

    // If k is greater than the length of the list, adjust k
    k = k % length;

    if (k == 0) return; // No need to rotate if k is 0 or k == length

    // Make the list circular
    current->next = head;

    // Traverse to the kth node
    current = head;
    for (int i = 1; i < k; i++) {
        current = current->next;
    }

    // Set the new head and break the circular link
    head = current->next;
    current->next = nullptr;
}

// Utility function to print the list
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << "->";
        head = head->next;
    }
    cout <<"NULL";
}

// Utility function to insert a new node at the end of the list
void insert(Node*& head, int data) {
    Node* newNode = new Node(data);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}
// Function to reverse n nodes at a time
Node* nReverse(Node* head, int n) {
    if (!head) return nullptr;

    Node* current = head;
    Node* next = nullptr;
    Node* prev = nullptr;
    int count = 0;

    // Reverse the first n nodes
    while (current != nullptr && count < n) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }

    // Recursively reverse the rest of the list and link the two parts
    if (next != nullptr) {
        head->next = nReverse(next, n);
    }

    // prev is the new head after reversal
    return prev;
}
int main() {
    Node* head = nullptr;

    // Insert values into the list
    insert(head, 1);
    insert(head, 2);
    insert(head, 4);
    insert(head, 5);
    insert(head, 7);
    insert(head, 8);
    insert(head, 9);

    // Rotate by 2 nodes
    cout << "Original list: "<<endl;;
    printList(head);
    rotate(head, 2);
    cout << "After rotating by 2 nodes: \n";
    printList(head);

    // Reverse every 2 nodes
    head = nReverse(head, 2);
    cout << "After reversing every 2 nodes:\n ";
    printList(head);

    return 0;
}
