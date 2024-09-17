#include<iostream>
#include<list>
using namespace std;
//TIME COMPLEXITY IS MENTIONED AFTER EVERY FUNCTION....

template <class T>
class LINKED_LIST {
private:
	class node {
	public:
		T data;
		node* next;
		node() {}
		node(T d, node* n) :data(d), next(n) {}
	};

	node* head;
	node* tail;
	int size;

public:
	LINKED_LIST() :head(nullptr), tail(nullptr), size(0) {}

	~LINKED_LIST() {
		node* current = head;
		while (current != nullptr) {
			node* next = current->next;
			delete current;
			current = next;
		}
	}

	void insertAtStart(T const element) {//TIME COMPLEXITY O(1)
		node* newnode = new node(element, nullptr);
		if (head == nullptr) {
			head = newnode;
			tail = newnode;
		}
		else {
			newnode->next = head;
			head = newnode;
		}
		size++;
	}

	void insertAtEnd(T const element) {//TIME COMPLEXITY O(1)
		node* newnode = new node(element, nullptr);
		if (head == nullptr) {
			head = newnode;
			tail = newnode;
		}
		else {
			tail->next = newnode;
			tail = newnode;
		}
		size++;
	}

	void print() const { //TIME COMPLEXITY O(n)
		node* current = head;
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	bool search(T const& element) const {//TIME COMPLEXITY O(n)
		node* current = head;
		while (current != NULL) {
			if (current->data == element) {
				cout << element << " is found in the list " << endl;
				return true;
			}
			current = current->next;
		}

		cout <<element<<" is not in the list " << endl;
		return false;
	}

	bool isEmpty() const {//TIME COMPLEXITY O(1)
		return head == NULL;
	}

	void DeleteStart() {//TIME COMPLEXITY O(1)
		if (head == nullptr) {
			return; // list is empty
		}
		node* temp = head;
		head = temp->next;
		delete temp;
		size--;
	}

	void DeleteEnd() {//TIME COMPLEXITY O(n)
		if (head == nullptr) {
			return; // list is empty
		}
		if (head->next == nullptr) {
			delete head;
			head = NULL;
			tail = NULL;
			return;
		}
		node* temp = head;
		while (temp->next->next != nullptr) {
			temp = temp->next;
		}
		delete temp->next;
		temp->next = NULL;
		tail = temp;
		size--;
	}

	bool insertAfter(T const v1, T const v2) {// TIME COMPLEXITY O(n)
		node* current = head;
		while (current != nullptr) {
			if (current->data == v1) {
				node* found = current->next; // node to link with v2
				node* newnode = new node(v2);
				current->next = newnode;
				newnode->next = found;
				size++;
				return true;
			}
			current = current->next;
		}
		return false; // failure of insertion...
	}

	void deleteAll(T const v) {//TIME COMPLEXITY O(1)
		node* current = head;
		node* previous = NULL;
		while (current != nullptr) {
			if (current->data == v) {
				node* found = current->next;
				delete current;
				if (previous != NULL) {
					previous->next = found; // node after the deleted node...
				}
				else {
					head = found;
				}
				current = found;
				size--;
			}
			else {
				previous = current;
				current = current->next;
			}
		}
	}

	bool isSorted(LINKED_LIST<T> l1) {//TIME COMPLEXITY O(1)
		node* current = l1.head;
		T prevValue = current->data;

		while (current->next != nullptr) {
			current = current->next;
			if (current->data < prevValue) {
				return false; // list is not sorted
			}
			prevValue = current->data;
		}
		return true; // list is sorted
	}

	void removeDuplicates() { //TIME COMPLEXITY O(n^2)
		node* current = head;
		while (current != nullptr) {
			node* runner = current;
			while (runner->next != nullptr) {
				if (runner->next->data == current->data) {//runner->next= current->next runner is current node
					node* temp = runner->next;
					runner->next = runner->next->next;
					delete temp;
					size--;
				}
				else {
					runner = runner->next;
				}
			}
			current = current->next;
		}
	}

		void push_back(T const element) {//TIME COMPLEXITY O(1)
			node* newnode = new node(element, nullptr);
			if (head == nullptr) {
				head = newnode;
				tail = newnode;
			}
			else {
				tail->next = newnode;
				tail = newnode;
			}
			size++;
		}//PUSH BACK FUNCTION USED TO APPEND THE LINKED LIST AS IT IS NOT FOUND BUILTIN IN THE LIBARARY
		LINKED_LIST<T> merge(const LINKED_LIST<T>& other) const {
			LINKED_LIST<T> MERGED_LIST;
			node* current1 = this->head;
			node* current2 = other.head;

			// MERGING SMALLER VALUES FIRST TO FORM A SORTED LIST
			while (current1 != nullptr && current2 != nullptr) {//TIME COMPLEXITY O(n)
				if (current1->data <= current2->data) {
					MERGED_LIST.push_back(current1->data);
					current1 = current1->next;
				}
				else {
					MERGED_LIST.push_back(current2->data);
					current2 = current2->next;
				}
			}

			// MERGING REMAINING
			while (current1 != nullptr) {
				MERGED_LIST.push_back(current1->data);
				current1 = current1->next;
			}

			while (current2 != nullptr) {
				MERGED_LIST.push_back(current2->data);
				current2 = current2->next;
			}

			return MERGED_LIST;
		}
	};

	int main()
	{//TIME COMPLEXITY O(1)
		LINKED_LIST<int> obj;
		LINKED_LIST<int> obj1;
		obj.insertAtEnd(2);
		obj.insertAtEnd(6);
		obj.insertAtEnd(7);
		obj.insertAtEnd(9);
		obj.insertAtEnd(7);
		obj.insertAtEnd(8);
		obj.insertAtEnd(9);
		obj.deleteAll(7);
		obj.print();
		obj.search(2);
		obj.search(9);
		obj.search(10);
		obj.DeleteStart();
		obj.print();

		//filling list 2;
		obj1.insertAtEnd(7);
		obj1.insertAtEnd(10);
		obj1.insertAtEnd(12);
		obj1.insertAtEnd(14);

		LINKED_LIST<int> mergedList = obj.merge(obj1); 
		mergedList.print(); 
    }