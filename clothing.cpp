#include "clothing.h"
#include <sstream>

Clothing::Clothing(const string category, const string name, double price, int qty,
                   string size, string brand) : Product(category, name, price, qty), size_(size), brand_(brand) {}

set<string> Clothing::keywords() const {
    string rawWords = name_ + " " + brand_;
    set<string> keywords = parseStringToWords(rawWords);
    return keywords;
}

bool Clothing::isMatch(vector<string>& searchTerms) const{
    set<string> keywordSet = keywords();
    vector<string>::iterator it;
    for (size_t i = 0; i < searchTerms.size(); i++) {
        if (keywordSet.find(searchTerms[i]) != keywordSet.end()) {
            return true;
        }
    }
        
    return false;
}

string Clothing::displayString() const {
    string productInfo;
    stringstream ss;
    ss << name_ + "\n";
    ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    
    productInfo = ss.str();
    
    return productInfo;
}

void Clothing::dump(ostream& os) const {
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}

string Clothing::getSize() const {
    return size_;
}

string Clothing::getBrand() const {
    return brand_;
}
