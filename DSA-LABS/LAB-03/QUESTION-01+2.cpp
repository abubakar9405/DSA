#include <iostream>
using namespace std;

template<class T>
class CIRCULAR_LL {
public:
    class NODE {
    public:
        T data;
        NODE* next;
        NODE(T const element) : next(nullptr), data(element) {}
        
        // Forward declaration of the friend function
        friend bool isCircular(CIRCULAR_LL<T>&);
    };

    class iterator {
        NODE* current;
    public:
        iterator(NODE* node) : current(node) {}

        // Dereference operator
        T& operator*() {
            return current->data;
        }

        // Pre-increment operator
        iterator& operator++() {
            current = current->next;
            return *this;
        }

        // Equality operator (for comparison)
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
    };

    NODE* head;
    NODE* tail;
    CIRCULAR_LL() : head(nullptr), tail(nullptr) {}

    void InsertAtStart(T const element) {
        NODE* newnode = new NODE(element);
        if (head == nullptr) {
            head = newnode;
            tail = newnode;
            newnode->next = newnode;  // Pointing to itself
        } else {
            newnode->next = head;  // Storing old head in newnode->next
            head = newnode;  // Assigning newnode to head
            tail->next = head;  // Maintaining circular property
        }
    }

    bool inlist(T const element) {
        NODE* current = head;
        if (head == nullptr) return false; // Check if the list is empty
        do {
            if (current->data == element) {
                return true;
            }
            current = current->next; 
        } while (current != head);
        return false;
    }

    void InsertAfter(T const element1, T const element) {
        NODE* current = head;
        if (!(inlist(element1))) {
            cout << "Given number is not in the list\n";
            return;
        }
        NODE* newnode = new NODE(element);
        do {
            if (current->data == element1) {
                newnode->next = current->next;
                current->next = newnode;
                if (current == tail) {
                    tail = newnode;
                }
                return;
            }
            current = current->next;
        } while (current != head);
    }

    void InsertAtEnd(T const element) {
        NODE* newnode = new NODE(element);
        if (head == nullptr) {  // Empty case
            head = newnode;  // Head updated
            tail = newnode;  // Tail updated
            newnode->next = head; // Point new node to head
        } else {
            tail->next = newnode; // Link the old last node to the new node
            newnode->next = head; // Point new node to head
            tail = newnode; // Update the tail
        }
    }

    void DelFromStart() {
        if (head == nullptr) {
            cout << "NOTHING PRESENT IN THE LIST TO BE DELETED\n";
            return;
        }
        NODE* current = head;
        if (current == tail) { // Only one element in the list
            delete current;
            head = nullptr;
            tail = nullptr;
        } else {
            head = current->next;
            delete current;
            tail->next = head; // Maintain circular property
        }
    }

    void DelAfter(T const v1) {
        NODE* current = head;
        if (current == nullptr) {
            cout << "NOTHING PRESENT IN THE LIST TO BE DELETED\n";
            return;
        }
        do {
            if (current->data == v1) {
                NODE* nodeToDelete = current->next;
                if (nodeToDelete == head) {
                    cout << "Can't delete after head.\n";
                    return;
                }
                current->next = nodeToDelete->next;
                if (nodeToDelete == tail) {
                    tail = current;
                }
                delete nodeToDelete;
                return;
            }
            current = current->next;
        } while (current != head);
        cout << "Element " << v1 << " not found in the list.\n";
    }

    void DelEnd() {
        if (head == nullptr) {
            cout << "NOTHING PRESENT IN THE LIST TO BE DELETED\n";
            return;
        }
        if (head == tail) { // Only one element in the list
            delete tail;
            head = nullptr;
            tail = nullptr;
        } else {
            NODE* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = head; // Maintain circular property
        }
    }

    bool IsEmpty() {
        return head == nullptr; // Check if head is NULL
    }

    void print() {
        NODE* current = head;
        if (head == nullptr) {
            cout << "List is empty\n";
            return;
        }
        do {
            cout << current->data << "->";
            current = current->next;
        } while (current != head);
        cout << " (back to head)\n"; // Indicate it's circular
    }

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(tail->next);
    }

    void reverse() {
        if (head == nullptr || head->next == head) {
            return;
        }

        NODE* prev = nullptr;
        NODE* current = head;
        NODE* next = nullptr;
        tail = head;  // The current head will become the new tail

        do {
            next = current->next;  // Store the next node
            current->next = prev;  // Reverse the current node's pointer
            prev = current;        // Move prev one step forward
            current = next;        // Move current one step forward
        } while (current != head);

        head = prev; // After the loop, prev will be the new head
        tail->next = head;  // Maintain circular nature by pointing tail to head
    }
};

// Global function to check if the list is circular
template<class T>
bool isCircular(CIRCULAR_LL<T>& list) {
    if (list.head == nullptr) return false; // An empty list is not circular

    typename CIRCULAR_LL<T>::NODE* current = list.head; // Correctly use NODE type
    do {
        current = current->next;
    } while (current != nullptr && current != list.head);

    return current == list.head; // Returns true if we loop back to head
}

int main() {
    CIRCULAR_LL<int> cll;  // Define a Circular Linked List of type int

    // b. Insert 7 and 9 at Start
    cll.InsertAtStart(7);
    cll.InsertAtStart(9);

    // c. Insert 10 and 2 at End
    cll.InsertAtEnd(10);
    cll.InsertAtEnd(2);

    // d. Print the linked list
    cout << "List after inserting 7, 9 at start, and 10, 2 at end: ";
    cll.print();  // Should print: 9->7->10->2

    // e. Insert 1 after 2
    cll.InsertAfter(2, 1);

    // f. Print the linked list
    cout << "List after inserting 1 after 2: ";
    cll.print();  // Should print: 9->7->10->2->1

    // g. Delete from start
    cll.DelFromStart();
    cout << "List after deleting from start: ";
    cll.print();  // Should print: 7->10->2->1

    // h. Delete from end
    cll.DelEnd();
    cout << "List after deleting from end: ";
    cll.print();  // Should print: 7->10->2

    // i. Delete node after 10
    cll.DelAfter(10);
    cout << "List after deleting node after 10: ";
    cll.print();  // Should print: 7->10

    // j. Now reverse the Circular linked list
    cll.reverse();
    cout << "List after reversing: ";
    cll.print();  // Should print: 10->7

    // k. Check if list is empty
    cout << "Is the list empty? " << (cll.IsEmpty() ? "True" : "False") << endl;  // Should print: False

    // l. Insert 4 after 7
    cll.InsertAfter(7, 4);
    
    // m. Print the list
    cout << "List after inserting 4 after 7: ";
    cll.print();  // Should print: 10->7->4

    // n. Check if list is empty
    cout << "Is the list empty? " << (cll.IsEmpty() ? "True" : "False") << endl;  // Should print: False
cout << "Is the list circular? " << (isCircular(cll) ? "True" : "False") << endl;  // Should print: True

    return 0;
}
