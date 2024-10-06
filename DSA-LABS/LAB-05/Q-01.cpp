#include<iostream>
#include<string>
using namespace std;
string decodeString(string& s, int& index) {
    string result = "";  
    while (index < s.size() && s[index] != ']') {
        if (isdigit(s[index])) {
            int k = 0;
            while (isdigit(s[index])) {
                k = k * 10 + (s[index] - '0');  
                index++;
            }
            
            // Skip the '[' character
            index++;
            string decodedPart = decodeString(s, index);
            index++;
            
            // Repeat the decoded part k times and append it to the result
            while (k--) {
                result += decodedPart;
            }
        } else {
            // If the current character is a letter, just append it to the result
            result += s[index++];
        }
    }
    
    return result;
}

string decodeString(string s) {
    int index = 0;
    return decodeString(s, index);
}

int main() {
    string s1 = "3[a]2[bc]";
    string s2 = "3[a2[c]]";
    string s3 = "2[abc]3[cd]ef";
    
    cout << "Decoded string 1: " << decodeString(s1) << endl;
    cout << "Decoded string 2: " << decodeString(s2) << endl;
    cout << "Decoded string 3: " << decodeString(s3) << endl;

    return 0;
}
