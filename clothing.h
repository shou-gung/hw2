#include "product.h"
#include "util.h"

using namespace std;

class Clothing : public Product {
public:
    Clothing(const string category, const string name, double price, int qty, 
             string size, string brand);
    
    set<string> keywords() const override;
    
    bool isMatch(std::vector<std::string>& searchTerms) const override;
    
    string displayString() const override;
    
    void dump(ostream& os) const override;
    
    string getSize() const;
    
    string getBrand() const;
    
private:
    string size_;
    string brand_;
};


