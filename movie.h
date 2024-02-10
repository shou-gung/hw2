#include "product.h"
#include "util.h"

using namespace std;

class Movie : public Product {
public:
    Movie(const std::string category, const std::string name, double price, int qty,
          string genre, string rating);
    
    set<string> keywords() const override;
    
    string displayString() const override;
    
    void dump(ostream& os) const override;
    
    string getGenre() const;
    
    string getRating() const;
    
private:
    string genre_;
    string rating_;
};
