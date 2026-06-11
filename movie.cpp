#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Movie::Movie(string name,
             double price,
             int qty,
             string genre,
             string rating)
    : Product("movie", name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}

set<string> Movie::keywords() const
{
    set<string> keys = parseStringToWords(getName());

    keys.insert(convToLower(genre_));

    return keys;
}

string Movie::displayString() const
{
    stringstream ss;

    ss << getName() << endl;
    ss << "Genre: " << genre_ << " Rating: " << rating_ << endl;
    ss << fixed << setprecision(2) << getPrice() << " " << getQty() << " left.";

    return ss.str();
}

void Movie::dump(ostream& os) const
{
    os << "movie" << endl;
    os << getName() << endl;
    os << fixed << setprecision(2) << getPrice() << endl;
    os << getQty() << endl;
    os << genre_ << endl;
    os << rating_ << endl;
}