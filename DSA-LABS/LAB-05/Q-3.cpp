#include<iostream>
using namespace std;

void findMinMaxDigits(int n, int& minDigit, int& maxDigit) {
    if (n == 0) return;  

    int currentDigit = n % 10;  
    if (currentDigit < minDigit) {
        minDigit = currentDigit; 
    }
    if (currentDigit > maxDigit) {
        maxDigit = currentDigit;  
    }
    
    findMinMaxDigits(n / 10, minDigit, maxDigit);  // Recursive call with the remaining number
}

int differenceBetweenSmallestAndLargestDigit(int n) {
    int minDigit = 9, maxDigit = 0;  // Initialize min and max digits
    findMinMaxDigits(n, minDigit, maxDigit);  // Call the helper function
    return maxDigit - minDigit;  // Return the difference
}

int main() {
    int n = 57239;
    cout << "Difference between largest and smallest digit: " 
         << differenceBetweenSmallestAndLargestDigit(n) << endl;

    return 0;
}
