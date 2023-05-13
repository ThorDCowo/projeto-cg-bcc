#include "point.h"
#include <iostream>
using namespace std;

void Point::translate(float dx, float dy)
{
    pointsList[0] = pair<float, float>(pointsList[0].first + dx, pointsList[0].second + dy);
}

void Point::scale(){}

void Point::rotate(){}

void Point::clipping(Border border){
    regionCodeGenerate(border);
    
    if (isInsideWindow(regionCodeList[0])) 
        return;

    if (isOutsideWindow(regionCodeList[0]))
    {
        normalizePointsList.removeAt(0);
        return;
    }
}

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