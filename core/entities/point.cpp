#include "point.h"
#include <iostream>
#include "coordinate.h"
using namespace std;

void Point::translate(Coordinate translation)
{
    pointsList[0] += translation;
}

void Point::translateProjection(Coordinate translation)
{
    projectionPointsList[0] += translation;
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