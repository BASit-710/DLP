#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <unordered_set>
#include <regex>

using namespace std;

// Keywords in C language
unordered_set<string> keywords = {
    "int", "float", "char", "double", "void", "return", "if", "else", "while", "for",
    "do", "switch", "case", "break", "continue", "struct", "typedef", "long"
};

// Operators in C language
unordered_set<string> operators = {"+", "-", "*", "/", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||"};

// Punctuation in C language
unordered_set<char> punctuation = {';', ',', '(', ')', '{', '}', '[', ']', '.'};

// Symbol table
vector<string> symbolTable;

// Function to check if a token is a keyword
bool isKeyword(const string &word) {
    return keywords.find(word) != keywords.end();
}

// Function to check if a token is an operator
bool isOperator(const string &word) {
    return operators.find(word) != operators.end();
}

// Function to check if a token is a valid identifier
bool isValidIdentifier(const string &word) {
    if (word.empty() || isdigit(word[0])) return false;
    for (char ch : word) {
        if (!isalnum(ch) && ch != '_') return false;
    }
    return true;
}

// Function to check if a token is a valid number
bool isNumber(const string &word) {
    regex numPattern("^[0-9]+(\\.[0-9]+)?$");
    return regex_match(word, numPattern);
}

// Function to add identifier to symbol table
void addToSymbolTable(const string &identifier) {
    if (find(symbolTable.begin(), symbolTable.end(), identifier) == symbolTable.end()) {
        symbolTable.push_back(identifier);
    }
}

// Lexical Analyzer function
void lexicalAnalyzer(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open the file!" << endl;
        return;
    }

    string token;
    char ch;
    bool inComment = false;
    bool inString = false;

    cout << "\nTOKENS:\n";

    while (file.get(ch)) {
        if (inComment) { // Handling comments
            if (ch == '*' && file.peek() == '/') {
                file.get(ch);
                inComment = false;
            }
            continue;
        }

        if (ch == '/' && file.peek() == '*') { // Multi-line comment
            file.get(ch);
            inComment = true;
            continue;
        }

        if (isspace(ch)) { // Ignore white spaces
            if (!token.empty()) {
                cout << token << " -> ";
                if (isKeyword(token)) {
                    cout << "Keyword\n";
                } else if (isNumber(token)) {
                    cout << "Constant\n";
                } else if (isValidIdentifier(token)) {
                    cout << "Identifier\n";
                    addToSymbolTable(token);
                } else {
                    cout << "Invalid Token (Lexical Error)\n";
                }
                token.clear();
            }
            continue;
        }

        if (punctuation.count(ch)) { // Handling punctuation
            if (!token.empty()) {
                cout << token << " -> ";
                if (isKeyword(token)) {
                    cout << "Keyword\n";
                } else if (isNumber(token)) {
                    cout << "Constant\n";
                } else if (isValidIdentifier(token)) {
                    cout << "Identifier\n";
                    addToSymbolTable(token);
                } else {
                    cout << "Invalid Token (Lexical Error)\n";
                }
                token.clear();
            }
            cout << ch << " -> Punctuation\n";
            continue;
        }

        if (operators.count(string(1, ch))) { // Handling operators
            if (!token.empty()) {
                cout << token << " -> ";
                if (isKeyword(token)) {
                    cout << "Keyword\n";
                } else if (isNumber(token)) {
                    cout << "Constant\n";
                } else if (isValidIdentifier(token)) {
                    cout << "Identifier\n";
                    addToSymbolTable(token);
                } else {
                    cout << "Invalid Token (Lexical Error)\n";
                }
                token.clear();
            }
            cout << ch << " -> Operator\n";
            continue;
        }

        token += ch;
    }

    file.close();

    // Print Symbol Table
    cout << "\nSYMBOL TABLE:\n";
    for (size_t i = 0; i < symbolTable.size(); ++i) {
        cout << i + 1 << ") " << symbolTable[i] << endl;
    }
}

int main() {
    string filename;
    cout << "Enter the C source code filename: ";
    cin >> filename;

    lexicalAnalyzer(filename);
    return 0;
}
