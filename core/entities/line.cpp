#include "line.h"

using namespace std;

void Line::translate(Coordinate translation)
{
    pointsList[0] += translation;
    pointsList[1] += translation;
}

void Line::translateProjection(Coordinate translation)
{
    projectionPointsList[0] += translation;
    projectionPointsList[1] += translation;
}

void Line::scale(float factor)
{
    Coordinate center = barycenter();
    translate(Coordinate::invertOrientation(center));
    factor = factor/100;
    factor = 1 + factor;
    pointsList[0] *= factor;
    pointsList[1] *= factor;
    translate(center);
}

void Line::rotate(float teta, Coordinate axis)
{   
    float radians = qDegreesToRadians(teta);
    Coordinate center = barycenter();
    translate(Coordinate::invertOrientation(center));

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


    translate(center);
}