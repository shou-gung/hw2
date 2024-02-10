#include "mydatastore.h"

using namespace std;

MyDataStore::~MyDataStore() {
    for (size_t i = 0; i < products_.size(); i++) {
        Product* p = products_[i];
        delete p;
    }
    
    for (size_t i = 0; i < users_.size(); i++) {
        User* u = users_[i];
        delete u;
    }
    
    /* map<string, queue<Product*>>::iterator it;
    for (it = user_carts.begin(); it != user_carts.end(); it++) {
        queue<Product*>& cart = it->second;
        while (!cart.empty()) {
            cart.pop();
        }
    } */
}

void MyDataStore::addProduct(Product* p) {
    products_.push_back(p);
}

void MyDataStore::addUser(User* u) {
    users_.push_back(u);
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    vector<Product*> results;
    
    if (terms.size() == 0) {
        return results;
    }
    
    set<Product*> totalResults;
    bool firstTerm = true;
    
    for (size_t i = 0; i < terms.size(); i++) {
        string term = terms[i];
        set<Product*> termResults;
        
        for (size_t j = 0; j < products_.size(); j++) {
            Product* product = products_[j];
            set<string>keywordSet = product->keywords();
            if (keywordSet.find(term) != keywordSet.end()) {
                termResults.insert(product);
            }
        }
        
        if (firstTerm) {
            totalResults = termResults;
            firstTerm = false;
        } else {
            if (type == 0) { // AND (setIntersection)
                totalResults = setIntersection(totalResults, termResults);
            } else if (type == 1) { // OR (setUnion)
                totalResults = setUnion(totalResults, termResults);
            }
        }
        
        
    }
    
    set<Product*>::iterator it;
    for (it = totalResults.begin(); it != totalResults.end(); it++) {
        results.push_back(*it);
    }
    
    return results;
    
}

void MyDataStore::dump(ostream& ofile) {
    ofile << "<products>" << endl;
    for (size_t i = 0; i < products_.size(); i++) {
        Product* product = products_[i];
        product->dump(ofile);
    }
    ofile << "</products>" << endl;
    
    ofile << "<users>" << endl;
    for (size_t i = 0; i < users_.size(); i++) {
        User* user = users_[i];
        user->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addToCart(string uname, Product* selectedProduct) {
    if (!checkValidUsername(uname)) {
        cout << "Invalid request" << endl;
        return;
    }
    
    if (user_carts.find(uname) == user_carts.end()) {
        queue<Product*> cart;
        cart.push(selectedProduct);
        user_carts.insert(make_pair(uname, cart));
    } else {
        user_carts[uname].push(selectedProduct);
    }
}

vector<Product*> MyDataStore::getUserCart(string uname) {
    vector<Product*> vectCart;
    uname = convToLower(uname);
    if (user_carts.find(uname) == user_carts.end()) {
        cout << "Invalid username" << endl;
        return vectCart;
    }
    
    queue<Product*> initCart = user_carts[uname];
    
    while (!initCart.empty()) {
        vectCart.push_back(initCart.front());
        initCart.pop();
    }
    
    return vectCart;
}

void MyDataStore::buyCart(string uname) {
    if (!checkValidUsername(uname)) {
        cout << "Invalid username" << endl;
        return;
    }
    
    queue<Product*>& userCart = user_carts[uname];
    queue<Product*> tempCart;
    User* user = findUser(uname);
    
    while (!userCart.empty()) {
        Product* product = userCart.front();
        double price = product->getPrice();
        int qty = product->getQty();
        double balance = user->getBalance();
        
        if (balance >= price && qty > 0) {
            user->deductAmount(price);
            product->subtractQty(1);
        } else {
            tempCart.push(product);
        }
        
        userCart.pop();
    }
    
    while (!tempCart.empty()) {
        userCart.push(tempCart.front());
        tempCart.pop();
    }
}

bool MyDataStore::checkValidUsername(string& uname) {
    uname = convToLower(uname);
    
    for (size_t i = 0; i < users_.size(); i++) {
        User* user = users_[i];
        if (uname == convToLower(user->getName())) {
            return true;
        }
    }
    
    return false;
}

User* MyDataStore::findUser(string uname) {
    uname = convToLower(uname);
    
    for (size_t i = 0; i < users_.size(); i++) {
        string verName = convToLower(users_[i]->getName());
        if (verName == uname) {
            return users_[i];
        }
    }
    
    return nullptr;
}

void MyDataStore::displayCart(vector<Product*>& hits) {
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
        cout << "No results found!" << endl;
        return;
    }
    
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
