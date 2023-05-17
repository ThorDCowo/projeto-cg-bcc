#include "Polygon.h"
#include <iostream>
#include <QtMath>
#include "coordinate.h"

using namespace std;

void Polygon::translate(float dx, float dy, float dz)
{
    for(qsizetype i = 0; i < pointsList.size(); i++){
            pointsList[i] = Coordinate(pointsList[i].x + dx, pointsList[i].y + dy, pointsList[i].z + dz);
    }
}

void Polygon::scale(float factor)
{ 
    Coordinate center = barycenter();
    translate(-center.x, -center.y, -center.z);
    factor = factor/100;
    factor = 1 + factor;

    for(qsizetype i = 0; i < pointsList.size(); i++){
        pointsList[i] = Coordinate(pointsList[i].x * factor, pointsList[i].y * factor, pointsList[i].z * factor);
    }
    translate(center.x, center.y, center.z);
}

void Polygon::rotate(float teta, Coordinate axis)
{
    float radians = qDegreesToRadians(teta);
    Coordinate center = barycenter();
    translate(-center.x, -center.y, -center.z);

    if(axis.x) {
        for(qsizetype i = 0; i < pointsList.size(); i++){
            pointsList[i] = Coordinate(
                pointsList[i].x,
                pointsList[i].y * qCos(radians) - (pointsList[i].z * qSin(radians)),
                pointsList[i].y * qSin(radians) + (pointsList[i].z * qCos(radians))
            );
        }
        
        return;
    } if(axis.y) {
        for(qsizetype i = 0; i < pointsList.size(); i++){
            pointsList[i] = Coordinate(
                pointsList[i].x * qCos(radians) + (pointsList[i].z * qSin(radians)),
                pointsList[i].y,
                pointsList[i].z * qCos(radians) - (pointsList[i].x * qSin(radians))
            );
        }
        
        return;
    }

    for(qsizetype i = 0; i < pointsList.size(); i++){
        pointsList[i] = Coordinate(
            pointsList[i].x * qCos(radians) - (pointsList[i].y * qSin(radians)),
            pointsList[i].x * qSin(radians) + (pointsList[i].y * qCos(radians)),
            pointsList[i].z
        );
    }

    translate(center.x, center.y, center.z);
}

/*
void Polygon::transformWindow(float windowX,float windowY)
{
    double aux, x2, y2;

    getCoords(&aux, &aux, &x2, &y2);
    setCoords(x() - windowX, y() - windowY, x2 - windowX, y2 - windowY);
}

void Polygon::transformViewport(float viewHeight, float viewWidth)
{
    double aux, x2, y2;

    getCoords(&aux, &aux, &x2, &y2);
    setCoords(((x() + 1) / 2) * viewWidth, (1 - ((y() + 1) / 2)) * viewHeight, ((x2 + 1) / 2) * viewWidth, (1 - ((y2 + 1) / 2)) * viewHeight);
}
*/
