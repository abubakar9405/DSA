#include <iostream>

using namespace std;

template <typename T>
class Stack {
private:
    T* arr;         // Array to store stack elements
    int capacity;   // Maximum number of elements in stack
    int topIndex;   // Index of the top element
    int count;      // Current number of elements

public:
    Stack(int size) : capacity(size), topIndex(-1), count(0) {
        arr = new T[capacity];
    }

    ~Stack() {
        delete[] arr;
    }

    int size() const {
        return count;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool top(T& element) const {
        if (isEmpty()) {
            return false; // Stack is empty
        }
        element = arr[topIndex]; // Assign top element to the reference
        return true;
    }

    void pop() {
        if (isEmpty()) {
            throw "Stack is empty. Cannot pop.";
        }
        topIndex--;
        count--;
    }

    void push(T const& element) {
        if (count == capacity) {
            throw "Stack is full. Cannot push.";
        }
        arr[++topIndex] = element;
        count++;
    }
};
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string InfixToPostFix(const string& infix) {
    Stack<char> stack(infix.length());
    string postfix;
    
    for (int i = 0; i < infix.length(); ++i) {
        char ch = infix[i];
        
        if (isdigit(ch)) {
            postfix += ch; // Add operands to postfix
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            char topElement;
            while (stack.top(topElement) && topElement != '(') {
                postfix += topElement;
                stack.pop();
            }
            stack.pop(); // Remove '(' from stack
        } else { // Operator
            char topElement;
            while (!stack.isEmpty() && stack.top(topElement) && precedence(topElement) >= precedence(ch)) {
                postfix += topElement;
                stack.pop();
            }
            stack.push(ch);
        }
    }

    // Pop all remaining operators from the stack
    while (!stack.isEmpty()) {
        char topElement;
        stack.top(topElement);
        postfix += topElement;
        stack.pop();
    }

    return postfix;
}
int main() {
    string infix = "1+2*3";
    string postfix = InfixToPostFix(infix);
    
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;

    return 0;
}