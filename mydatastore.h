#include "datastore.h"
#include "product_parser.h"
#include "db_parser.h"
#include "util.h"
#include <queue>
#include <map>
#include <iomanip>

using namespace std;

class MyDataStore : public DataStore {
public:
    ~MyDataStore();
    
    void addProduct(Product* p);
    
    void addUser(User* u);
    
    vector<Product*> search(vector<string>& terms, int type);
    
    void dump(ostream& ofile);
    
    void addToCart(string uname, Product* selectedProduct);
    
    vector<Product*> getUserCart(string uname);
    
    void buyCart(string uname);
    
    bool checkValidUsername(string& uname);
    
    User* findUser(string uname);
    
    void displayCart(vector<Product*>& hits);

private:
    vector<Product*> products_;
    vector<User*> users_;
    map<string, queue<Product*>> user_carts;
    
};
