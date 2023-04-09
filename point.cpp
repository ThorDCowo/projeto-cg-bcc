#include "point.h"
#include <iostream>
using namespace std;

void Point::translate(float dx, float dy)
{
    pointsList[0] = pair<float, float>(pointsList[0].first + dx, pointsList[0].second + dy);
}

void Point::scale(float factor){}

void Point::rotate(float teta){}
