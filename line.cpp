#include "line.h"
#include <iostream>
using namespace std;

void Line::translate(float dx, float dy)
{
    pointsList[0] = pair<float, float>(pointsList[0].first + dx, pointsList[0].second + dy);
    pointsList[1] = pair<float, float>(pointsList[1].first + dx, pointsList[1].second + dy);
}

void Line::scale(float factor)
{
    pair<float, float> center = barycenter();
    translate(-center.first, -center.second);
    factor = factor/100;
    factor = 1 + factor;
    pointsList[0] = pair<float, float>(pointsList[0].first * factor, pointsList[0].second * factor);
    pointsList[1] = pair<float, float>(pointsList[1].first * factor, pointsList[1].second * factor);
    translate(center.first, center.second);
}

void Line::rotate(float teta)
{   
    pair<float, float> center = barycenter();
    translate(-center.first, -center.second);

    float radians = qDegreesToRadians(teta);
    pointsList[0] = pair<float, float>(pointsList[0].first * qCos(radians) - (pointsList[0].second * qSin(radians)), 
                                        pointsList[0].first * qSin(radians) + (pointsList[0].second * qCos(radians)));
    pointsList[1] = pair<float, float>(pointsList[1].first * qCos(radians) - (pointsList[1].second * qSin(radians)), 
                                        pointsList[1].first * qSin(radians) + (pointsList[1].second * qCos(radians)));
    translate(center.first, center.second);
}

/*
void Line:: transformWindow(float windowX,float windowY)
{
    setLine(x1() - windowX,y1() - windowY, x2() - windowX, y2() - windowY);
}

void Line::transformViewport(float viewHeight, float viewWidth)
{
    setLine(((x1() + 1) / 2) * viewWidth, (1 - ((y1() + 1) / 2)) * viewHeight, ((x2() + 1) / 2) * viewWidth, (1 - ((y2() + 1) / 2)) * viewHeight);
}
*/

