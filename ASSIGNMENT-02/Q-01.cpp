#include<iostream>
using namespace std;

template<class T>
class stack {
public:
    int top;
    T* arr;
    int size;
    
    // Constructor
    stack(int capacity) : top(-1), size(capacity) {
        arr = new T[size];
    }
    
    // Destructor
    ~stack() {
        delete[] arr;
    }
    
    bool IS_FULL() {
        return top == (size - 1);
    }
    
    bool IS_EMPTY() {
        return top == -1;
    }
    
    void push(T const element) {
        if (IS_FULL()) {
            cerr << "STACK OVERFLOW\n";
            return;
        }
        top++;
        arr[top] = element;
    }
    
    T pop() {
        if (IS_EMPTY()) return -1;
        else {
            T element_to_return = arr[top];
            top--;
            return element_to_return;
        }
    }

    T peek() {
        return arr[top];
    }
    
    void DISPLAY() {
        for (int i = 0; i <= top; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    
    // Recursive palindrome checker
    bool palindrome_Checker_Recursive(int front, int rear) {
        if (front <= rear) {
            return true;
        }
        if (arr[front] != arr[rear]) {
            return false;
        }
        return palindrome_Checker_Recursive(front - 1, rear + 1);
    }

    bool palindrome_Checker() {
        return palindrome_Checker_Recursive(this->top, 0);  // Initial call with front and rear positions
    }
};

int main() {
    // Example 1: Palindrome case (integers)
    stack<int> s(10);

    s.push(1);
    s.push(0);
    s.push(0);
    s.push(0);
    s.push(1);

    cout << "Stack contents (integers): ";
    s.DISPLAY();  // Display stack contents

    if (s.palindrome_Checker()) {
        cout << "The integer stack is a palindrome." << endl;
    } else {
        cout << "The integer stack is NOT a palindrome." << endl;
    }

    // Example 2: Non-palindrome case (characters)
    stack<char> s2(10);
    s2.push('r');
    s2.push('a');
    s2.push('c');
    s2.push('e');
    s2.push('r');

    cout << "Stack contents (characters): ";
    s2.DISPLAY();  // Display stack contents

    if (s2.palindrome_Checker()) {
        cout << "The character stack is a palindrome." << endl;
    } else {
        cout << "The character stack is NOT a palindrome." << endl;
    }

    return 0;
}
