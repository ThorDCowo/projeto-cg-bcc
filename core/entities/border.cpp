#include "border.h"
#include "coordinate.h"
using namespace std;

void Border::setBorder(float width, float height, Coordinate center)
{
    this->upper = center.y + (height / 2);
    this->lower = center.y - (height / 2);
    this->left = center.x - (width / 2);
    this->right = center.x + (width / 2);
}
