#include <iostream>
#include <assert.h>

#include "object.h"
#include "coordinate.h"

using namespace std;



void Object::draw(QPainter &painter)
{
    // drawWorldPoints(painter);
    // drawNormalizedPoints(painter);
    drawProjectedPoints(painter);

}

void Object::drawEdges(QPainter &painter)
{
    for (qsizetype i = 0; i < edges.size(); i++)
    {
        painter.drawLine(projectionPointsList[edges[i].first].x, projectionPointsList[edges[i].first].y,
                        projectionPointsList[edges[i].second].x, projectionPointsList[edges[i].second].y);
    }
}

void Object::drawNormalizedPoints(QPainter &painter)
{
    for (qsizetype i = 0; i < normalizePointsList.size(); i++)
    {
        if (i == pointsList.size() - 1)
        {
            painter.drawLine(normalizePointsList[i].x, normalizePointsList[i].y,
                             normalizePointsList[0].x, normalizePointsList[0].y);
            continue;
        }

        painter.drawLine(normalizePointsList[i].x, normalizePointsList[i].y,
                         normalizePointsList[i + 1].x, normalizePointsList[i + 1].y);
    }
}

void Object::drawProjectedPoints(QPainter &painter) 
{
    for (qsizetype i = 0; i < projectionPointsList.size(); i++)
    {
        if (i == pointsList.size() - 1)
        {
            painter.drawLine(projectionPointsList[i].x, projectionPointsList[i].y,
                            projectionPointsList[0].x, projectionPointsList[0].y);
            continue;
        }

        painter.drawLine(projectionPointsList[i].x, projectionPointsList[i].y,
                        projectionPointsList[i + 1].x, projectionPointsList[i + 1].y);
    }
}

void Object::drawWorldPoints(QPainter &painter)
{
    for (qsizetype i = 0; i < pointsList.size(); i++)
    {
        if (i == pointsList.size() - 1)
        {
            painter.drawLine(pointsList[i].x, pointsList[i].y,
                             pointsList[0].x, pointsList[0].y);
            continue;
        }

        painter.drawLine(pointsList[i].x, pointsList[i].y,
                         pointsList[i + 1].x, pointsList[i + 1].y);
    }
}

void Object::orthogonalNormalize(int windowWidth, int windowHeight, Coordinate windowCenter, Coordinate axisToExclude)
{
    orthogonalProjection(axisToExclude);
    normalizeCoordinates(windowWidth, windowHeight, windowCenter, projectionPointsList);
}

void Object::perspectiveNormalize(int windowWidth, int windowHeight, Coordinate windowCenter, float distanceFromProjection)
{    
    planeProjection(distanceFromProjection);
    normalizeCoordinates(windowWidth, windowHeight, windowCenter, projectionPointsList);
}

void Object::normalizeCoordinates(int windowWidth, int windowHeight, Coordinate windowCenter, QList<Coordinate> list)
{
    normalizePointsList.erase(normalizePointsList.begin(), normalizePointsList.end());
    
    float newX = 0.0;
    float newY = 0.0;
    float viewportWidth = 854.0;
    float viewportHeight = 480.0;
    float windowXBegin = windowCenter.x - (viewportWidth / 2);
    float windowYBegin = windowCenter.y - (viewportHeight / 2);

    for (qsizetype i = 0; i < list.size(); i++)
    {
        newX = ((list[i].x - windowXBegin) / windowWidth) * viewportWidth;
        newY = (1 -  ((list[i].y - windowYBegin)  / windowHeight)) * viewportWidth;

        normalizePointsList.append(Coordinate(newX, newY));
    }
}

void Object::orthogonalProjection(Coordinate axisToExclude){
    projectionPointsList.erase(projectionPointsList.begin(), projectionPointsList.end());

    if(axisToExclude.x) {
        //cout << "Exclude X" << endl;
        for (qsizetype i = 0; i < pointsList.size(); i++)
            projectionPointsList.append(Coordinate(pointsList[i].y, pointsList[i].z));
        return;    
    }

    if(axisToExclude.y) {
        //cout << "Exclude Y" << endl;
        for (qsizetype i = 0; i < pointsList.size(); i++)
            projectionPointsList.append(Coordinate(pointsList[i].x, pointsList[i].z));
        return; 
    }

    //cout << "Exclude Z" << endl;
    for (qsizetype i = 0; i < pointsList.size(); i++)
        projectionPointsList.append(Coordinate(pointsList[i].x, pointsList[i].y));
}


void Object::planeProjection(float distanceBetweenCenterOfProjectionandPlane) {
    projectionPointsList.erase(projectionPointsList.begin(), projectionPointsList.end());

    float projectionAxisX = 0.0;
    float projectionAxisY = 0.0;

    for (qsizetype i = 0; i < pointsList.size(); i++) {

        projectionAxisX = (pointsList[i].x * distanceBetweenCenterOfProjectionandPlane)/pointsList[i].z;
        projectionAxisY = (pointsList[i].y * distanceBetweenCenterOfProjectionandPlane)/pointsList[i].z;

        projectionPointsList.append(Coordinate(
            projectionAxisX, 
            projectionAxisY, 
            distanceBetweenCenterOfProjectionandPlane
        ));
    }
}

void Object::rotateWorld(float teta, Coordinate axis)
{
    // float radians = qDegreesToRadians(teta);

    if(axis.x) {
        for(qsizetype i = 0; i < pointsList.size(); i++){
            pointsList[i] = Coordinate(
                pointsList[i].x,
                pointsList[i].y * qCos(teta) - (pointsList[i].z * qSin(teta)),
                pointsList[i].y * qSin(teta) + (pointsList[i].z * qCos(teta))
            );
        }
        return;
    } if(axis.y) {
        for(qsizetype i = 0; i < pointsList.size(); i++){
            pointsList[i] = Coordinate(
                pointsList[i].x * qCos(teta) + (pointsList[i].z * qSin(teta)),
                pointsList[i].y,
                pointsList[i].z * qCos(teta) - (pointsList[i].x * qSin(teta))
            );
        }
        return;
    }

    for(qsizetype i = 0; i < pointsList.size(); i++){
        pointsList[i] = Coordinate(
            pointsList[i].x * qCos(teta) - (pointsList[i].y * qSin(teta)),
            pointsList[i].x * qSin(teta) + (pointsList[i].y * qCos(teta)),
            pointsList[i].z
        );
    }

}

void Object::transformToViewport(Coordinate center)
{
    int viewportWidth = 854;
    int viewportHeight = 480;

    float windowXBegin = center.x - (viewportWidth / 2);
    float windowXEnd = center.x + (viewportWidth / 2);
    float windowYBegin = center.y - (viewportHeight / 2);
    float windowYEnd = center.y + (viewportHeight / 2);

    for (qsizetype i = 0; i < normalizePointsList.size(); i++)
    {
        projectionPointsList[i].x = windowXBegin + (normalizePointsList[i].x - windowXBegin) / (windowXEnd - windowXBegin) * viewportWidth;
        projectionPointsList[i].y = windowYBegin + (1 - (normalizePointsList[i].y - windowYBegin) / (windowYEnd - windowYBegin)) * viewportHeight;
    }
}

Coordinate Object::barycenter()
{
    Coordinate center(0,0,0);

    for (qsizetype i = 0; i < pointsList.size(); i++)
    {
        center.x += pointsList[i].x;
        center.y += pointsList[i].y;
        center.z += pointsList[i].z;
    }
    center.x = (center.x / pointsList.size());
    center.y = (center.y / pointsList.size());
    center.z = (center.z / pointsList.size());

    return center;
}

float Object::linearInterpolation(
    float valueInFirstIntervalToFindInSecondInterval,
    float startFirstInterval,
    float endFirstInterval,
    float startSecondInterval,
    float endSecondInterval
) {
    float firstIntervalRange = endFirstInterval - startFirstInterval;
    float secondIntervalRange = endSecondInterval - startSecondInterval;
    float result = startSecondInterval +
                   ((secondIntervalRange) / (firstIntervalRange)) *
                       (valueInFirstIntervalToFindInSecondInterval - startFirstInterval);

    // //cout << result << endl;
    return result;
}
