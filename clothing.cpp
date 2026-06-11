#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Clothing::Clothing(string name,
                   double price,
                   int qty,
                   string size,
                   string brand)
    : Product("clothing", name, price, qty)
{
    size_ = size;
    brand_ = brand;
}

set<string> Clothing::keywords() const
{
    set<string> keys = parseStringToWords(getName());
    set<string> brandKeys = parseStringToWords(brand_);

    keys = setUnion(keys, brandKeys);

    return keys;
}

string Clothing::displayString() const
{
    stringstream ss;

    ss << getName() << endl;
    ss << "Size: " << size_ << " Brand: " << brand_ << endl;
    ss << fixed << setprecision(2) << getPrice() << " " << getQty() << " left.";

    return ss.str();
}

void Clothing::dump(ostream& os) const
{
    os << "clothing" << endl;
    os << getName() << endl;
    os << fixed << setprecision(2) << getPrice() << endl;
    os << getQty() << endl;
    os << size_ << endl;
    os << brand_ << endl;
}