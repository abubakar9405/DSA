#include<iostream>
#include<vector>
using namespace std;

// Recursive function to find binary representation of a number
void convertToBinary(int n, vector<int>& binary) {
    if (n == 0) return;  // Base case: stop when n becomes 0

    int remainder = n % 2;  // Find the current binary digit
    convertToBinary(n / 2, binary);  // Recursive call with n / 2
    binary.push_back(remainder);  // Store the remainder (binary digit)
}

int main() {
    int n = 25;  // Example number
    vector<int> binary;  // Vector to hold binary digits
    
    if (n == 0) {
        binary.push_back(0);  // Special case for n = 0
    } else {
        convertToBinary(n, binary);
    }

    // Print the binary representation
    cout << "Binary representation of " << n << " is: ";
    for (int bit : binary) {
        cout << bit;
    }
    cout << endl;

    return 0;
}
