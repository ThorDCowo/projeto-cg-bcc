#ifndef COMPARABLE_H
#define COMPARABLE_H

#include <string>
using namespace std;

class Comparable {
public:
    virtual bool operator==(const Comparable& other) const = 0;
    virtual bool operator!=(const Comparable& other) const = 0;
    virtual string toString() const = 0;
};

#endif // COMPARABLE_H