#ifndef COMPARABLE_H
#define COMPARABLE_H

#include <string>
using namespace std;

template<typename T>
class Comparable {
public:
    virtual bool operator==(const T& other) const = 0;
    virtual bool operator!=(const T& other) const = 0;
    virtual string toString() const = 0;
};

#endif // COMPARABLE_H