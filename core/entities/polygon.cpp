#include "Polygon.h"
#include <iostream>
#include <QtMath>
#include "coordinate.h"

using namespace std;

void Polygon::translate(Coordinate translation)
{
    for(qsizetype i = 0; i < pointsList.size(); i++) {
        pointsList[i] += translation;
    }
}

void Polygon::scale(float factor)
{ 
    Coordinate center = barycenter();
    translate(Coordinate::invertOrientation(center));
    factor = factor/100;
    factor = 1 + factor;

    for(qsizetype i = 0; i < pointsList.size(); i++){
        pointsList[i] *= factor;
    }

    translate(center);
}

void Polygon::rotate(float teta, Coordinate axis)
{
    float radians = qDegreesToRadians(teta);
    Coordinate center = barycenter();
    translate(Coordinate::invertOrientation(center));

    if(axis.x) {
        for(qsizetype i = 0; i < pointsList.size(); i++){
            pointsList[i] = Coordinate(
                pointsList[i].x,
                pointsList[i].y * qCos(radians) - (pointsList[i].z * qSin(radians)),
                pointsList[i].y * qSin(radians) + (pointsList[i].z * qCos(radians))
            );
        }
        
        return;
    } 
    
    if(axis.y) {
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

    translate(center);
}