#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

template<class T>
class QUE {
public:
    int size;
    int front, rear;
    T* arr;

    QUE(int capacity) {
        size = capacity;
        arr = new T[size];
        front = -1;
        rear = -1;
    }

    ~QUE() {
        delete[] arr;
    }

    int SIZE() {
        return size; // return size of queue
    }

    bool Is_Empty() {
        return front == -1; // condition to empty
    }

    bool Is_Full() {
        return (rear + 1) % size == front; // condition to full
    }

    T& FRONT() {
        if (front == -1) {
            throw runtime_error("Queue is empty.");  // Handle empty case with exception
        } else {
            return arr[front];
        }
    }

    T& REAR() {
        if (rear == -1) {
            throw runtime_error("Queue is empty.");  // Handle empty case with exception
        } else {
            return arr[rear];
        }
    }

    T DEQUE() {
        if (Is_Empty()) {
            throw runtime_error("Queue is empty, cannot dequeue."); // Handle empty queue
        }

        T dequeuedValue = arr[front];
        if (front == rear) {  // If there's only one element left, reset front and rear
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % size;  // Circular increment of the front index
        }

        return dequeuedValue;  // Return the dequeued process
    }

    void ENQUE(const T& val) {
        if (Is_Full()) {
            cout << "Queue is full.\n";
            return;
        }
        if (Is_Empty()) {
            front = 0; // rear increment later...
        }
        rear = (rear + 1) % size;
        arr[rear] = val;
    }

    void Display() {
        if (Is_Empty()) {
            cout << "Queue is empty." << endl;
            return;
        } else {
            int i = front;
            while (true) {
                cout << arr[i].ID << " (" << arr[i].instructions << " instructions) ";
                if (i == rear)
                    break;
                i = (i + 1) % size;
            }
            cout << endl;
        }
    }
};

struct Process {
    string ID;
    int instructions;
};

// Modified loadingfile to return the quantum value
int loadingfile(string processes, QUE<Process>& processedQUE) {
    ifstream file(processes);
    int quantum, total_processed;
    if (!file.is_open()) {
        cout << "File not open\n";
        return -1;
    } else {
        file >> quantum >> total_processed;
        for (int i = 0; i < total_processed; ++i) {
            Process P; // instance of struct
            file >> P.ID >> P.instructions;
            processedQUE.ENQUE(P);
        }
        file.close();
        return quantum; // Return the quantum
    }
}

void scheduler(string process_file) {
    // Initialize the queue with a certain capacity, e.g., 100
    QUE<Process> processQue(100);  // No parentheses here

    // Load processes from the file into the queue and retrieve quantum
    int quantum = loadingfile(process_file, processQue); 
    if (quantum == -1) return;  // Handle file open error

    // Main scheduling loop
    while (!processQue.Is_Empty()) {
        Process p = processQue.FRONT();
        processQue.DEQUE();

        // Execute the quantum amount of instructions or the remaining if fewer
        int instructionsToExecute = min(quantum, p.instructions);
        cout << instructionsToExecute << "  of " << p.ID << " executed." << endl;

        p.instructions -= instructionsToExecute;

        // Check if the process has finished
        if (p.instructions > 0) {
            processQue.ENQUE(p);  // Reinsert the process into the queue if not finished
        } else {
            cout << p.ID << " has finished execution." << endl;
        }
    }
}

int main() {
    scheduler("processes.txt");
    return 0;
}
