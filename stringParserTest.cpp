#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <set>
#include "util.h"
#include "product.h"
#include "book.h"
#include "clothing.h"
#include "book.h"

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open input file" << endl;
        return 1;
    }
    
    string inputText;
    getline(inputFile, inputText);
    
    set<string> keywords = parseStringToWords(inputText);
    
    cout << "Keywords: " << endl;
    set<string>::iterator it;
    for (it = keywords.begin(); it != keywords.end(); it++) {
        cout << *it << endl;
    }
    
    
    return 0;
}

