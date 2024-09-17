#include <iostream>
#include <set>

using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T data) : data(data), next(nullptr) {}
};

template<typename T>
class LisIterator {
private:
    Node<T>* current;
public:
    LisIterator(Node<T>* node = nullptr) : current(node) {}

    bool NotNull() const {
        return current != nullptr;
    }

    bool NextNotNull() const {
        return current && current->next != nullptr;
    }

    Node<T>* First(Node<T>* head) {
        return head;
    }

    Node<T>* Next() {
        if (current) {
            current = current->next;
        }
        return current;
    }

    T getData() const {
       if (current) {
    return current->data;
} else {
    return T();  // Return default value for type T
} 
  }
};

template<typename T>
class SinglyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~SinglyLinkedList() {
        while (head != nullptr) {
            deleteAtStart();
        }
    }

    void insert(const T& element) {
        Node<T>* newNode = new Node<T>(element);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void print() const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void printNth(int index) const {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds" << endl;
            return;
        }
        Node<T>* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        cout << "Data at index " << index << ": " << temp->data << endl;
    }

    bool search(const T& element) const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == element) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void deleteAtStart() {
        if (head == nullptr) return;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
        if (head == nullptr) tail = nullptr;
    }

    int sum() const {
        int totalSum = 0;
        Node<T>* temp = head;
        while (temp != nullptr) {
            totalSum += temp->data;
            temp = temp->next;
        }
        return totalSum;
    }

    SinglyLinkedList<T> Union(LisIterator<T> it1, LisIterator<T> it2) {
        SinglyLinkedList<T> unionList;
        set<T> elements;  // To avoid duplicates

        // Process first iterator's list
        while (it1.NotNull()) {
            if (elements.find(it1.getData()) == elements.end()) {
                elements.insert(it1.getData());
                unionList.insert(it1.getData());
            }
            it1.Next();
        }

        // Process second iterator's list
        while (it2.NotNull()) {
            if (elements.find(it2.getData()) == elements.end()) {
                elements.insert(it2.getData());
                unionList.insert(it2.getData());
            }
            it2.Next();
        }

        return unionList;
    }

    LisIterator<T> getIterator() const {
        return LisIterator<T>(head);
    }
};

int main() {
    SinglyLinkedList<int> list1;
    list1.insert(1);
    list1.insert(2);
    list1.insert(5);
    list1.insert(6);
    list1.insert(8);
    list1.insert(6);

    SinglyLinkedList<int> list2;
    list2.insert(4);
    list2.insert(3);
    list2.insert(5);
    list2.insert(9);
    list2.insert(7);

    cout << "List 1: ";
    list1.print();

    cout << "List 2: ";
    list2.print();

    LisIterator<int> it1 = list1.getIterator();
    LisIterator<int> it2 = list2.getIterator();

    SinglyLinkedList<int> unionList = list1.Union(it1, it2);

    cout << "Union of List 1 and List 2: ";
    unionList.print();

    return 0;
}
