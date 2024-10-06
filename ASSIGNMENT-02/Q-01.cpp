#include<iostream>
using namespace std;
template<class T>
class stack{
public:
int top;
T *arr;
int size;
stack(int capacity):top(-1),size(capacity){
    arr=new T[size];
}
~stack(){
    delete[] arr;
}
IS_FULL(){
    return top==(size-1);
}
IS_EMPTY(){
    return top==-1;
}
void push(T const element){
//edge cases
//case-01
if (IS_FULL())
{
  cerr<<"STACK OVERFLOW\n";
  return;
}
else{
    top++;
    arr[top]=element;
}
}
int pop(/*NO ARGS*/){
    //EDGE CASES
    //CASE-01 if stack is empty
    if (IS_EMPTY()) return -1;
    else{
        int element_to_return=arr[top];
        top--;
        return element_to_return;
    }    
}
 T peek(){
    cout<<arr[top];
    return arr[top];
}
void DISPLAY(){
    for (int  i = 0; i <= top; i++)
    {
       cout<<arr[i]<<" " ;
    }
    cout<<"\n";
}
bool palindrome_Checker(){
int front=this->top,rear=0;

while(front>rear){
if (arr[front]!=arr[rear])
{
    return false;
}
front--;
rear++;
}
return true;
}
};
int main() {
    // Create a stack of size 10
    stack<int> s(10);

    // Example 1: Palindrome case
    s.push(1);
    s.push(0);
    s.push(0);
    s.push(0);
    s.push(1);

    cout << "Stack contents: ";
    s.DISPLAY();  // Display stack contents

    if (s.palindrome_Checker()) {
        cout << "The stack is a palindrome." << endl;
    } else {
        cout << "The stack is NOT a palindrome." << endl;
    }

    // Example 2: Non-palindrome case
    stack<char> s2(10);
    s2.push('r');
    s2.push('a');
    s2.push('c');
    s2.push('e');
    s2.push('r');

    cout << "Stack contents: ";
    s2.DISPLAY();  // Display stack contents

    if (s2.palindrome_Checker()) {
        cout << "The stack is a palindrome." << endl;
    } else {
        cout << "The stack is NOT a palindrome." << endl;
    }

    return 0;
}
