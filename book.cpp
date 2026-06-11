#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Book::Book(string name,
           double price,
           int qty,
           string isbn,
           string author)
    : Product("book", name, price, qty)
{
    isbn_ = isbn;
    author_ = author;
}

set<string> Book::keywords() const
{
    set<string> keys = parseStringToWords(getName());
    set<string> authorKeys = parseStringToWords(author_);
    keys = setUnion(keys, authorKeys);
    keys.insert(convToLower(isbn_));

    return keys;
}

string Book::displayString() const
{
    stringstream ss;
    ss << getName() << endl;
    ss << "Author: " << author_ << " ISBN: " << isbn_ << endl;
    ss << fixed << setprecision(2) << getPrice() << " " << getQty() << " left.";
    
    return ss.str();
}

void Book::dump(ostream& os) const
{
    os << "book" << endl;
    os << getName() << endl;
    os << fixed << setprecision(2) << getPrice() << endl;
    os << getQty() << endl;
    os << isbn_ << endl;
    os << author_ << endl;
}