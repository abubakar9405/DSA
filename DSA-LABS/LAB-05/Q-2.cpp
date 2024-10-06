#include <iostream>
#include <vector>
using namespace std;

void findCombinations(vector<int>& arr, vector<int>& combination, int start, int r) {
    // Base case: if r is 0, print the current combination
    if (r == 0) {
        for (int i = 0; i < combination.size(); i++) {
            cout << combination[i] << " ";
        }
        cout << endl;
        return;
    }
    for (int i = start; i < arr.size(); i++) {
        combination.push_back(arr[i]);
        findCombinations(arr, combination, i + 1, r - 1);
        combination.pop_back();
    }
}

int main() {
    vector<int> arr = {1, 2, 3, 4};
    int r = 2;
    vector<int> combination;

    findCombinations(arr, combination, 0, r);
    
    return 0;
}
