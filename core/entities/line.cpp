#include "line.h"
#include <iostream>
#include "coordinate.h"
using namespace std;

void Line::translate(float dx, float dy, float dz)
{   
    pointsList[0] = Coordinate(pointsList[0].x + dx, pointsList[0].y + dy, pointsList[0].z + dz);
    pointsList[1] = Coordinate(pointsList[1].x + dx, pointsList[1].y + dy, pointsList[0].z + dz);
}

void Line::scale(float factor)
{
    Coordinate center = barycenter();
    translate(-center.x, -center.y, -center.z);
    factor = factor/100;
    factor = 1 + factor;
    pointsList[0] = Coordinate(pointsList[0].x * factor, pointsList[0].y * factor, pointsList[0].z * factor);
    pointsList[1] = Coordinate(pointsList[1].x * factor, pointsList[1].y * factor, pointsList[0].z * factor);
    translate(center.x, center.y, center.z);
}

void Line::rotate(float teta, Coordinate axis)
{   
    float radians = qDegreesToRadians(teta);
    Coordinate center = barycenter();
    translate(-center.x, -center.y, -center.z);

    if(axis.x){
        pointsList[0] = Coordinate(
            pointsList[0].x,
            pointsList[0].y * qCos(radians) - (pointsList[0].z * qSin(radians)),
            pointsList[0].y * qSin(radians) + (pointsList[0].z * qCos(radians))
        );

        pointsList[1] = Coordinate(
            pointsList[1].x,
            pointsList[1].y * qCos(radians) - (pointsList[1].z * qSin(radians)),
            pointsList[1].y * qSin(radians) + (pointsList[1].z * qCos(radians))
        );
    }
        
    if(axis.y){
        pointsList[0] = Coordinate(
            pointsList[0].x * qCos(radians) + (pointsList[0].z * qSin(radians)),
            pointsList[0].y,
            pointsList[0].z * qCos(radians) - (pointsList[0].x * qSin(radians))
        );

        pointsList[1] = Coordinate(
            pointsList[1].x * qCos(radians) + (pointsList[1].z * qSin(radians)),
            pointsList[1].y,
            pointsList[1].z * qCos(radians) - (pointsList[1].x * qSin(radians))
        );
    }

    if(axis.z){
        pointsList[0] = Coordinate(
            pointsList[0].x * qCos(radians) - (pointsList[0].y * qSin(radians)),
            pointsList[0].x * qSin(radians) + (pointsList[0].y * qCos(radians)),
            pointsList[0].z
        );

        pointsList[1] = Coordinate(
            pointsList[1].x * qCos(radians) - (pointsList[1].y * qSin(radians)), 
            pointsList[1].x * qSin(radians) + (pointsList[1].y * qCos(radians)),
            pointsList[1].z
        );
    }


    translate(center.x, center.y, center.z);
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

