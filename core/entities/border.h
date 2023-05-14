#ifndef BORDER_H
#define BORDER_H

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
    Border(float width, float height, pair<float, float> center) {
        this->upper = center.second + (height / 2);
        this->lower = center.second - (height / 2);
        this->left = center.first - (width / 2);
        this->right = center.first + (width / 2);
    }
       

    float getUpper()const {return this->upper;};
    float getLower()const {return this->lower;};
    float getLeft()const {return this->left;};
    float getRight()const {return this->right;};

    void setBorder(float width, float height, pair<float, float> center);
};

#endif // BORDER_H
