#include "book.h"
#include <sstream>

using namespace std;

Book::Book(const string category, const string name, double price, int qty,
           string ISBN, string author) : Product(category, name, price, qty), ISBN_(ISBN), author_(author) {}

set<string> Book::keywords() const {
    string rawWords = name_ + " " + ISBN_ + " " + author_;
    set<string> keywords = parseStringToWords(rawWords);
    return keywords;
    
}

bool Book::isMatch(vector<string>& searchTerms) const{
    set<string> keywordSet = keywords();
    vector<string>::iterator it;
    for (size_t i = 0; i < searchTerms.size(); i++) {
        if (keywordSet.find(searchTerms[i]) != keywordSet.end()) {
            return true;
        }
    }
        
    return false;
}

string Book::displayString() const {
    string productInfo;;
    stringstream ss;
    ss << name_ + "\n";
    ss << "Author: " << author_ << " ISBN: " << ISBN_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    
    productInfo = ss.str();
    
    return productInfo;
}

void Book::dump(ostream& os) const {
    Product::dump(os);
    os << ISBN_ << "\n" << author_ << endl;
}

string Book::getISBN() const {
    return ISBN_;
}

string Book::getAuthor() const {
    return author_;
}
