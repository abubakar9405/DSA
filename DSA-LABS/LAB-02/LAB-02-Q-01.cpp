#include<iostream>
using namespace std;

template<typename T>
class DL {
    struct NODE {
        T data;
        NODE* next;
        NODE* prev;
    };
    NODE* head;
    NODE* tail;

public:
    DL() : head(nullptr), tail(nullptr) {} 
   
    void insertAtHead(T const element) {
        NODE* newnode = new NODE;
        newnode->data = element;
        newnode->prev = nullptr; 

        if (head != nullptr) {
            head->prev = newnode; 
        } else {
            tail = newnode; 
        }

        newnode->next = head;
        head = newnode; 
    }

        void insertAtTail(T const element) {
        if (head == nullptr) {  
            head = new NODE;
            head->data = element;
            head->next = nullptr;
            head->prev = nullptr;
            tail = head;  
        } else {
            NODE* newnode = new NODE;
            newnode->data = element;
            newnode->next = nullptr;
            newnode->prev = tail;   
            tail->next = newnode;   
            tail = newnode;         
        }
    }

    void print() const {
        NODE* current = head;
        while (current != nullptr) { 
            cout << current->data << "->";
            current = current->next;
        }
        cout << "NULL\n";  
            }

    void printReverse() {
        NODE* current = tail;
        while (current != nullptr) {
            cout << current->data << "->";
            current = current->prev;
        }
        cout << "NULL\n";
    }

    void DeleteAtStart() {
        if (head == nullptr) {
            cout << "The list is empty\n";
            return;
        }
        NODE* current = head;
        head = current->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;  
        }
        delete current;
    }

    void DeleteAtEnd() {
        if (head == nullptr) {
            cout << "The list is empty\n";
            return;
        }
        NODE* current = tail;
        if (tail->prev != nullptr) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = tail = nullptr;  
        }
        delete current;
    }

    void swapNodes(int n) {
        if (n <= 0) {
            return; 
                    }

        NODE* startNth = head;
        NODE* endNth = tail;

        // Find the nth node from the start
        int count = 1;
        while (count < n && startNth != nullptr) {
            startNth = startNth->next;
            count++;
        }

        count = 1;
        while (count < n && endNth != nullptr) {
            endNth = endNth->prev;
            count++;
        }

        if (startNth == nullptr || endNth == nullptr) {
            return; // nodes do not exist
        }

        T temp = startNth->data;
        startNth->data = endNth->data;
        endNth->data = temp;
    }
};

int main() {
    DL<int> obj;
    obj.insertAtHead(2);
    obj.insertAtHead(3);
    obj.insertAtHead(4);
    obj.insertAtHead(5);
    obj.insertAtHead(6);
    obj.insertAtTail(21);
    obj.insertAtTail(24);
    obj.insertAtTail(256);
    obj.insertAtTail(25);
    obj.insertAtTail(23);
    cout << "Printing after insertion\n";
    obj.print();
    cout<<"printing reversed LL\n";
        obj.printReverse();
obj.DeleteAtStart();
cout<<"printing after deleting at start\n";
obj.print();
cout<<"printing after deleting at the end\n";
obj.DeleteAtEnd();
obj.print();
cout<<"printing after swapping nodes\n";
obj.swapNodes(2);
obj.print();
    return 0;
}
