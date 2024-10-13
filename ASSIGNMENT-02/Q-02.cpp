#include<iostream>
#include<string>
#include<cmath>
using namespace std;

template<typename T>
class QUEUE {
public:
    T* arr;        
    int front, rear, storage;
    
    
    QUEUE(int size) : front(-1), rear(-1) {
        storage = size;
        arr = new T[storage]; 
    }
    
    ~QUEUE() {
        delete[] arr;
    }

    
    void DISPLAY() {
        if (front == -1) {
            cout << "Queue is empty!" << endl;
            return;
        }

        cout << "Queue: ";
        int i = front;
        while (i != rear) {
            cout << arr[i] << " -> ";
            i = (i + 1) % storage;
        }
        cout << arr[rear] << endl; 
    }

    void ENQUEUE(T const element) {
        
        if ((rear + 1) % storage == front) {
            cout << "Queue is full, cannot enqueue " << element << endl;
            return;
        }

        
        if (front == -1) front = 0;

        
        rear = (rear + 1) % storage;
        arr[rear] = element;
    }

    
    T DEQUEUE() {
        if (front == -1) { 
            throw runtime_error("Queue is already empty\n");
        }

        T temp = arr[front];
        
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % storage;
        }
        return temp;
    }

    char get_char(const string& str, int pos) {
        return pos < str.length() ? str[pos] : 0; 
    }

    
    void radix_sort_strings(int n) {
        
        int max_length = 0;
        for (int i = 0; i < n; i++)
            if (arr[i].length() > max_length)
                max_length = arr[i].length();
        QUEUE<string>* queues[256];

        
        for (int i = 0; i < 256; i++) {
            queues[i] = new QUEUE<string>(n); 
        }

        
        for (int pos = max_length - 1; pos >= 0; pos--) {
        
            for (int i = 0; i < n; i++) {
                int ch = get_char(arr[i], pos); 
                queues[ch]->ENQUEUE(arr[i]);    
            }
            int index = 0;
            for (int i = 0; i < 256; i++) {
                while (queues[i]->front != -1) {
                    arr[index++] = queues[i]->DEQUEUE();
                }
            }
        }
        for (int i = 0; i < 256; i++) {
            delete queues[i];
        }
    }
    int get_digit(int number, int place) {
        return (number / place) % 10;
    }

    // Radix Sort for Integers
    void radix_sort_integers(int arr[], int n) {
        int max_val = arr[0];
        for (int i = 1; i < n; i++)
            if (arr[i] > max_val)
                max_val = arr[i];

        QUEUE<int> queues[10] = { QUEUE<int>(n), QUEUE<int>(n), QUEUE<int>(n),
                                  QUEUE<int>(n), QUEUE<int>(n), QUEUE<int>(n),
                                  QUEUE<int>(n), QUEUE<int>(n), QUEUE<int>(n), QUEUE<int>(n) };

        for (int place = 1; max_val / place > 0; place *= 10) {
            for (int i = 0; i < n; i++) {
                int digit = get_digit(arr[i], place);
                queues[digit].ENQUEUE(arr[i]);
            }

            int index = 0;
            for (int i = 0; i < 10; i++) {
                while (queues[i].front != -1) {
                    arr[index++] = queues[i].DEQUEUE();
                }
            }
        }
    }
};
int main() {
    // Test with integers
    int intArr[] = { 329, 457, 657, 839, 436, 720, 355 };
    int n = sizeof(intArr) / sizeof(intArr[0]);

    cout << "Original Integer Array: ";
    for (int i = 0; i < n; i++) {
        cout << intArr[i] << " ";
    }
    cout << endl;

    // Create a queue object for sorting integers
    QUEUE<int> intQueue(n);
    intQueue.radix_sort_integers(intArr, n);

    // Display sorted integer array
    cout << "Sorted Integer Array: ";
    for (int i = 0; i < n; i++) {
        cout << intArr[i] << " ";
    }
    cout << endl;

    // Test with strings
    string strArr[] = { "word", "category", "apple", "banana", "xyz", "dog", "cat" };
    int m = sizeof(strArr) / sizeof(strArr[0]);

    cout << "Original String Array: ";
    for (int i = 0; i < m; i++) {
        cout << strArr[i] << " ";
    }
    cout << endl;

    // Create a queue object for sorting strings
    QUEUE<string> strQueue(m);

    // Copy strArr to the internal array of the queue
    for (int i = 0; i < m; i++) {
        strQueue.arr[i] = strArr[i];
    }

    // Sort the strings
    strQueue.radix_sort_strings(m);

    // Copy sorted data back to strArr
    for (int i = 0; i < m; i++) {
        strArr[i] = strQueue.arr[i];
    }

    // Display sorted string array
    cout << "Sorted String Array: ";
    for (int i = 0; i < m; i++) {
        cout << strArr[i] << " ";
    }
    cout << endl;

    return 0;
}
