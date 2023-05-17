#include "point.h"
#include <iostream>
#include "coordinate.h"
using namespace std;

void Point::translate(float dx, float dy, float dz)
{
    pointsList[0] = Coordinate(pointsList[0].x + dx, pointsList[0].y + dy, pointsList[0].z + dz);
}

void Point::scale(){}

void Point::rotate(){}

bool Point::isInsideWindow(
    vector<bool> pointRegionCode
) {
    return (
        !pointRegionCode[0] && 
        !pointRegionCode[1] && 
        !pointRegionCode[2] && 
        !pointRegionCode[3]    );
}

bool Point::isOutsideWindow(
    vector<bool> pointRegionCode
) {
    return (
        pointRegionCode[0] || 
        pointRegionCode[1] || 
        pointRegionCode[2] || 
        pointRegionCode[3]    );
}