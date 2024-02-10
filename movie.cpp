#include "movie.h"
#include <sstream>

Movie::Movie(const std::string category, const std::string name, double price, int qty, string genre, string rating) : Product(category, name, price, qty),
            genre_(genre), rating_(rating) {}

set<string> Movie::keywords() const {
    string rawWords = name_ + " " + genre_;
    set<string> keywords = parseStringToWords(rawWords);
    return keywords;
}

string Movie::displayString() const {
    string productInfo;
    stringstream ss;
    ss << name_ + "\n";
    ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    
    productInfo = ss.str();
    
    return productInfo;
}

string Movie::getGenre() const {
    return genre_;
}

string Movie::getRating() const {
    return rating_;
}

void Movie::dump(ostream& os) const {
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}
