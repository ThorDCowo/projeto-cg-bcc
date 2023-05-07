#include "border.h"
using namespace std;

void Border::setBorder(float width, float height, pair<float, float> center)
{
    this->upper = center.second + (height / 2);
    this->lower = center.second - (height / 2);
    this->left = center.first - (width / 2);
    this->right = center.first + (width / 2);
}
