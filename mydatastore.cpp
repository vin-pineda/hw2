#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::~MyDataStore()
{
    for(size_t i = 0; i < products_.size(); i++) {
        delete products_[i];
    }

    map<string, User*>::iterator it;
    for(it = users_.begin(); it != users_.end(); ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);

    set<string> keys = p->keywords();

    set<string>::iterator it;
    for(it = keys.begin(); it != keys.end(); ++it) {
        keywordProducts_[convToLower(*it)].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    string name = convToLower(u->getName());
    users_[name] = u;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    vector<Product*> hits;
    set<Product*> result;

    if(terms.size() == 0) {
        return hits;
    }

    for(size_t i = 0; i < terms.size(); i++) {
        terms[i] = convToLower(terms[i]);
    }

    if(type == 0) {
        map<string, set<Product*> >::iterator firstTerm;
        firstTerm = keywordProducts_.find(terms[0]);

        if(firstTerm == keywordProducts_.end()) {
            return hits;
        }

        result = firstTerm->second;

        for(size_t i = 1; i < terms.size(); i++) {
            map<string, set<Product*> >::iterator termIt;
            termIt = keywordProducts_.find(terms[i]);

            set<Product*> temp;

            if(termIt != keywordProducts_.end()) {
                temp = termIt->second;
            }

            result = setIntersection(result, temp);
        }
    }
    else {
        for(size_t i = 0; i < terms.size(); i++) {
            map<string, set<Product*> >::iterator termIt;
            termIt = keywordProducts_.find(terms[i]);

            if(termIt != keywordProducts_.end()) {
                result = setUnion(result, termIt->second);
            }
        }
    }

    set<Product*>::iterator pit;
    for(pit = result.begin(); pit != result.end(); ++pit) {
        hits.push_back(*pit);
    }

    return hits;
}

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;

    for(size_t i = 0; i < products_.size(); i++) {
        products_[i]->dump(ofile);
    }

    ofile << "</products>" << endl;

    ofile << "<users>" << endl;

    map<string, User*>::iterator it;
    for(it = users_.begin(); it != users_.end(); ++it) {
        it->second->dump(ofile);
    }

    ofile << "</users>" << endl;
}

bool MyDataStore::addToCart(const string& username,
                            int hitIndex,
                            const vector<Product*>& hits)
{
    string name = convToLower(username);

    if(users_.find(name) == users_.end()) {
        return false;
    }

    if(hitIndex < 1 || hitIndex > (int)hits.size()) {
        return false;
    }

    carts_[name].push_back(hits[hitIndex - 1]);

    return true;
}

bool MyDataStore::viewCart(const string& username,
                           ostream& os) const
{
    string name = convToLower(username);

    map<string, User*>::const_iterator userIt;
    userIt = users_.find(name);

    if(userIt == users_.end()) {
        return false;
    }

    map<string, deque<Product*> >::const_iterator cartIt;
    cartIt = carts_.find(name);

    if(cartIt == carts_.end()) {
        return true;
    }

    int count = 1;

    deque<Product*>::const_iterator it;
    for(it = cartIt->second.begin(); it != cartIt->second.end(); ++it) {
        os << "Item " << count << endl;
        os << (*it)->displayString() << endl;
        os << endl;

        count++;
    }

    return true;
}

bool MyDataStore::buyCart(const string& username)
{
    string name = convToLower(username);

    map<string, User*>::iterator userIt;
    userIt = users_.find(name);

    if(userIt == users_.end()) {
        return false;
    }

    deque<Product*>& cart = carts_[name];
    deque<Product*> remaining;

    while(cart.size() > 0) {
        Product* p = cart.front();
        cart.pop_front();

        if(p->getQty() > 0 &&
           userIt->second->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            userIt->second->deductAmount(p->getPrice());
        }
        else {
            remaining.push_back(p);
        }
    }

    cart = remaining;

    return true;
}