#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

template<class T>
class stack {
public:
    int top;
    T* arr;
    int size;
    
    // Constructor
    stack(int capacity) : top(-1), size(capacity) {
        arr = new T[size];
    }
    
    // Destructor
    ~stack() {
        delete[] arr;
    }
    
    bool IS_FULL() {
        return top == (size - 1);
    }
    
    bool IS_EMPTY() {
        return top == -1;
    }
    
    void push(T const element) {
        if (IS_FULL()) {
            cerr << "STACK OVERFLOW\n";
            return;
        }
        top++;
        arr[top] = element;
    }
    
    T pop() {
        if (IS_EMPTY()) {
            cerr << "Stack is empty\n";
            return T();  // Return a default-constructed T
        }
        T element_to_return = arr[top];
        top--;
        return element_to_return;
    }

    T peek() {
        if (!IS_EMPTY()) {
            return arr[top];
        }
        return T();  // Return a default-constructed T if stack is empty
    }
};

class HtmlParser {
    stack<string> tagStack;  // for HTML-tags
    stack<char> quoteStack;  // for quotes
    int errorCount;
    bool DOCTYPE;
    
public:
    // Constructor
    HtmlParser() : tagStack(100), quoteStack(100), errorCount(0), DOCTYPE(false) {}

    // Function to parse the file
    void parseFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file\n";
            return;
        }

        string line;
        int lineNumber = 0;
        while (getline(file, line)) {
            lineNumber++;//iterating through the whole
            checkLine(line, lineNumber);
        }

        // Check for unclosed tags after reading the file
        while (!tagStack.IS_EMPTY()) {
            cout << "Error: Unclosed tag <" << tagStack.pop() << "> found\n";
            errorCount++;
        }

        if (!DOCTYPE) {
            cout << "Error: No DOCTYPE declaration found\n";
            errorCount++;
        }

        // Print the total number of errors found
        cout << "Total Errors: " << errorCount << endl;
    }

    // Function to check each line for tags and quotes
    void checkLine(const string& line, int lineNumber) {
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == '<') {
                if (line.compare(i, 9, "<!DOCTYPE") == 0) {
                    if (DOCTYPE) {
                        cout << "Error: Multiple DOCTYPE declarations found at line " << lineNumber << endl;
                        errorCount++;
                    } else {
                        DOCTYPE = true;
                    }
                } else {
                    handleTag(line, i, lineNumber);
                }
            } else if (line[i] == '"' || line[i] == '\'') {
                handleQuote(line[i], lineNumber);
            }
        }
    }

    // Function to handle tags
    void handleTag(const string& line, size_t& pos, int lineNumber) {
        bool isClosing = (line[pos + 1] == '/');
        string tag;
        bool isSelfClosing = false;

        pos++;  // Skip '<'
        if (isClosing) pos++;  // Skip '/'

        // Read tag name until '>' or space
        while (pos < line.size() && line[pos] != '>' && !isspace(line[pos])) {
            tag += line[pos++];
        }

        // Check if the tag is self-closing (ends with '/>')
        if (line.find("/>", pos) != string::npos) {
            isSelfClosing = true;
        }

        if (isClosing) {
            if (!tagStack.IS_EMPTY() && tagStack.peek() == tag) {
                tagStack.pop();
            } else {
                cout << "Error: Mismatched closing tag </" << tag << "> at line " << lineNumber << endl;
                errorCount++;
            }
        } else if (!isSelfClosing) {
            tagStack.push(tag);
        }
    }

    // Function to handle quotes
    void handleQuote(char quote, int lineNumber) {
        if (!quoteStack.IS_EMPTY() && quoteStack.peek() == quote) {
            quoteStack.pop();
        } else {
            quoteStack.push(quote);
        }
    }
};

int main() {
    HtmlParser parser;
    parser.parseFile("NO_ERROR.txt");
    return 0;
}
