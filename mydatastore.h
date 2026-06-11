#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <string>
#include <iostream>

class MyDataStore : public DataStore {
public:
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    bool addToCart(const std::string& username,
                   int hitIndex,
                   const std::vector<Product*>& hits);

    bool viewCart(const std::string& username,
                  std::ostream& os) const;

    bool buyCart(const std::string& username);

private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*> > keywordProducts_;
    std::map<std::string, std::deque<Product*> > carts_;
};

#endif