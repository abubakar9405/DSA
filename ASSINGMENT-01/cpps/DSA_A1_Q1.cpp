#include <iostream>
using namespace std;
//checking git
template <typename T>
class SortedSet {
    class NODE {
    public:
        NODE* next;
        T data;

        NODE(T value) : data(value), next(NULL) {}  // Constructor for NODE
    };

public:
    NODE* head;
    NODE* tail;

    SortedSet() : head(NULL), tail(NULL) {}  // INITIALIZER LIST...

    // Destructor to free memory
    ~SortedSet() {
        clear();
    }

    // Function to clear the list
    void clear() {
        NODE* current = head;
        while (current != NULL) {
            NODE* nextPtr = current->next;  // Storing next node in next pointer
            delete current;
            current = nextPtr;
        }
        head = NULL;
        tail = NULL;
    }

    // Copy constructor for deep copy
    SortedSet(const SortedSet& other) : head(NULL), tail(NULL) {
        NODE* current = other.head;
        while (current != NULL) {
            SORTED_INSERTION(current->data);
            current = current->next;
        }
    }

    // Copy assignment operator for deep copy
    SortedSet& operator=(const SortedSet& other) {
        if (this != &other) {
            clear();  // Clear current list
            NODE* current = other.head;
            while (current != NULL) {
                SORTED_INSERTION(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Function to insert elements in sorted order
    void SORTED_INSERTION(T const element) {
        NODE* newnode = new NODE(element);
        NODE* current = head;

        // Empty list case
        if (head == NULL) {
            head = newnode;
            tail = newnode;
            return;
        }

        // Insertion at head (smaller element)
        if (element < head->data) {
            newnode->next = head;
            head = newnode;
            return;
        }

        // Traversing through the list
        while (current->next != NULL && current->next->data < element) {
            current = current->next;
        }

        if (current->data == element) {
            delete newnode;  // Preventing duplicates
            return;
        }

        // Inserting the new node
        newnode->next = current->next;
        current->next = newnode;

        // Edge case if new node is at the end
        if (newnode->next == NULL) {
            tail = newnode;
        }
    }

    // Function to delete node at a specific index
    void Delete(int index) {
        if (head == NULL) {
            cout << "List is empty, cannot delete.\n";
            return;
        }

        NODE* current = head;
        NODE* prev = NULL;
        int count = 1;

        // Deletion at head
        if (index == 1) {
            if (head->next == NULL) {  // Single element case
                cout << "It is the only element present in the list.\n";
                delete head;
                head = tail = NULL;
                return;
            } else {
                head = current->next;
                delete current;
                return;
            }
        }

        // Traversing to the node at the desired index
        while (current != NULL && count != index) {
            prev = current;
            current = current->next;
            count++;
        }

        // Out of bound check
        if (current == NULL) {
            cout << "Index out of bounds.\n";
            return;
        }

        // Deleting the node at the desired index
        prev->next = current->next;

        // If deleting at the tail, update the tail pointer
        if (current->next == NULL) {
            tail = prev;
        }
        delete current;
    }

    // Print function to print the list
    void print() {
        NODE* current = head;
        if (current == NULL) {
            cout << "Your list is empty.\n";
            return;
        }

        while (current != NULL) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL\n";
    }

    // Function to find the union of two sets
    void unionSet(SortedSet<T> const& SORTED_OBJ) {
        NODE* current = this->head;  // Start of this list
        NODE* current1 = SORTED_OBJ.head;  // Start of the list passed as an argument
        SortedSet<T> result;  // To store the union of both sets

        while (current != NULL && current1 != NULL) {
            if (current->data < current1->data) {
                result.SORTED_INSERTION(current->data);
                current = current->next;
            } else if (current->data > current1->data) {
                result.SORTED_INSERTION(current1->data);
                current1 = current1->next;
            } else {  // If elements are equal
                result.SORTED_INSERTION(current->data);
                current = current->next;
                current1 = current1->next;
            }
        }

        // Insert remaining elements
        while (current != NULL) {
            result.SORTED_INSERTION(current->data);
            current = current->next;
        }
        while (current1 != NULL) {
            result.SORTED_INSERTION(current1->data);
            current1 = current1->next;
        }

        *this = result;  // Updating the result with the current pointer of the instance
    }

    // Function to find the intersection of two sets
    void intersection(SortedSet<T> const& Sorted_OBJ) {
        NODE* current = this->head;  // Start of the first list
        NODE* current1 = Sorted_OBJ.head;  // Start of the second list
        SortedSet<T> result;  // Resultant set to store the intersection

        while (current != NULL && current1 != NULL) {
            if (current->data == current1->data) {
                result.SORTED_INSERTION(current->data);  // Insert the common element
                current = current->next;
                current1 = current1->next;
            } else if (current->data < current1->data) {
                current = current->next;  // Move forward in the first list if it's smaller
            } else {
                current1 = current1->next;  // Move forward in the second list if it's smaller
            }
        }

        *this = result;  // Updating the current list with the intersection result
    }
};

int main() {
    SortedSet<int> obj;  // First list
    obj.SORTED_INSERTION(3);
    obj.SORTED_INSERTION(4);
    obj.SORTED_INSERTION(2);
    obj.SORTED_INSERTION(1);
    obj.SORTED_INSERTION(5);
    cout << "printing list 1\n";
    obj.print();  // Printing the first list

    SortedSet<int> obj1;  // Second list
    obj1.SORTED_INSERTION(7);
    obj1.SORTED_INSERTION(6);
    obj1.SORTED_INSERTION(9);
    obj1.SORTED_INSERTION(2);
    obj1.SORTED_INSERTION(4);
    cout << "printing list 2\n";
    obj1.print();  // Printing the second list

    obj.unionSet(obj1);
    cout << "printing list 1 after union with list 2\n";
    obj.print();  // Printing the union of the two lists

    obj1.intersection(obj);
    cout << "printing list 2 after intersection with list 1\n";
    obj1.print();  // Printing the intersection of the two lists
    obj.Delete(2);
    cout<<"print list 1 after deleting at index 2\n";
    obj.print();
    obj1.Delete(2);
    cout<<"printing list 2 after deleting at index 2\n";
    obj1.print();
    return 0;
}
