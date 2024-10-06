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
return arr[top];
}
void DISPLAY(){
    for (int  i = 0; i <= top; i++)
    {
       cout<<arr[i]<<" " ;
    }
    cout<<"\n";
}
};
int main(){
stack<int>obj(6);
obj.push(1);
obj.push(2);
obj.push(3);
obj.push(4);
obj.push(5);
obj.push(6);
obj.DISPLAY();
obj.push(1);//over flow condition...
obj.pop();
obj.pop();
cout<<"displating stack after some popping \n";
obj.DISPLAY();
}