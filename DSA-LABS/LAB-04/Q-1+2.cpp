#include<iostream>
#include<fstream>
using namespace std;
template<class T>
class QUE
{
public:
  int size;
  int front,rear;
  T* arr;

    QUE(int capacity){
        size=capacity;
        arr=new T(size);
        front=-1;
        rear=-1;
    }
     ~QUE(){
             delete[] arr;
     }
    int SIZE(){
        return size;//return size of que...
    }
    bool Is_Empty(){
       return front==-1;//condition to empty
    }
    bool Is_Full(){
        return (rear+1)%size==front;//condition to full...
    }
    T &FRONT(){
        if (front==-1)
        {
            cout<<"no element present\n";
            return 0;
        }
        else{
            return arr[front];
        }
    }
     T &REAR(){
        if (rear==-1)
        {
            cout<<"no element present\n";
            return 0;
        }
        else{
            return arr[rear];
        }
    }
   int DEQUE() {
        if (Is_Empty()) {
            cout << "Queue is empty, cannot dequeue." << endl;
            return -1;
        }

        int dequeuedValue = arr[front];
        if (front == rear) {  // If there's only one element left, reset front and rear
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % size;  // Circular increment of the front index
        }
        
        cout << "Dequeued " << dequeuedValue << endl;
        return dequeuedValue;
    }
 void ENQUE(T const &val){
if (Is_Full())
{
    cout<<"IS FULL\n";
    return;
}
if (Is_Empty())
{
    front=0;//rear incre later...
}
rear=(rear+1)%size;
arr[rear]=val;
 }
 void Display(){
    if (Is_Empty())
    {
        cout << "Queue is empty." << endl;
        return;
    }
    else{
        int i = front;
        while (true)
        {
            cout << arr[i] << " ";
            if (i == rear)
                break;
            i = (i + 1) % size;
        }
        cout << endl;
    }
    void scheduler(string processFile){
  ifstream MYREAD("processes.txt")
while (getline (MyReadFile, processFile)) {
  // Output the text from the file
  cout << myText;
}
    }
}
};
int main() {
    QUE<int> q(5); // Create a circular queue of size 5

    // Enqueue some elements
    q.ENQUE(1);
    q.ENQUE(2);
    q.ENQUE(3);
    q.ENQUE(4);
    q.ENQUE(5);

    cout << "Initial queue: ";
    q.Display();

    // Dequeue an element
    q.DEQUE();

    cout << "After dequeuing: ";
    q.Display();

    // Enqueue another element
    q.ENQUE(6);

    cout << "After enqueuing 6: ";
    q.Display();

    // Dequeue another element
    q.DEQUE();

    cout << "After dequeuing again: ";
    q.Display();

    return 0;
}