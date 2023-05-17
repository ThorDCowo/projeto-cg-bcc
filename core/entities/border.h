#ifndef BORDER_H
#define BORDER_H
#include "coordinate.h"

#include <iostream>
using namespace std;

class Border
{
private:
    float upper;
    float lower; 
    float left; 
    float right; 

public:
    Border(float width, float height, Coordinate center) {
        this->upper = center.y + (height / 2);
        this->lower = center.y - (height / 2);
        this->left = center.x - (width / 2);
        this->right = center.x + (width / 2);
    }
       
    float getUpper()const {return this->upper;};
    float getLower()const {return this->lower;};
    float getLeft()const {return this->left;};
    float getRight()const {return this->right;};

    void setBorder(float width, float height, Coordinate center);
};

#endif // BORDER_H
