#include "product.h"
#include "util.h"

using namespace std;

class Book : public Product {
public:
    Book(const string category, const string name, double price, int qty, 
         string ISBN, string author);
    
    set<string> keywords() const override;
    
    bool isMatch(vector<string>& searchTerms) const override;
    
    string displayString() const override;
        
    void dump(ostream& os) const override;
    
    string getISBN() const;
    
    string getAuthor() const;
    
private:
    string ISBN_;
    string author_;
};

