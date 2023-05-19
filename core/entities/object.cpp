#include <iostream>
#include <assert.h>

#include "object.h"
#include "coordinate.h"

using namespace std;

void drawNormalizedPoints(
    QList<Coordinate> pointsList,
    QList<Coordinate> normalizePointsList,
    QPainter &painter);

void drawWorldPoints(QList<Coordinate> pointsList, QPainter &painter);

void Object::draw(QPainter &painter)
{
    // drawWorldPoints(pointsList, painter);
    drawNormalizedPoints(pointsList, normalizePointsList, painter);
}

void drawNormalizedPoints(
    QList<Coordinate> pointsList,
    QList<Coordinate> normalizePointsList,
    QPainter &painter)
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

void drawWorldPoints(QList<Coordinate> pointsList, QPainter &painter)
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

void Object::normalize(int windowWidth, int windowHeight, Coordinate center, Coordinate axisToExclude)
{
    orthogonalProjection(axisToExclude);
    float newX = 0.0;
    float newY = 0.0;
    float viewportWidth = 854.0;
    float viewportHeight = 480.0;
    float windowXBegin = center.x - (viewportWidth / 2);
    float windowYBegin = center.y - (viewportHeight / 2);

    for (qsizetype i = 0; i < pointsList.size(); i++)
    {
        newX = (normalizePointsList[i].x - windowXBegin) / (windowWidth)*viewportWidth;
        newY = (normalizePointsList[i].y - windowYBegin) / (windowHeight)*viewportHeight;

        normalizePointsList.replace(i, Coordinate(newX, newY, 0));
    }
}

void Object::orthogonalProjection(Coordinate axisToExclude){
    normalizePointsList.erase(normalizePointsList.begin(), normalizePointsList.end());

    if(axisToExclude.x) {
        for (qsizetype i = 0; i < pointsList.size(); i++)
            normalizePointsList.append(Coordinate(pointsList[i].y, pointsList[i].z));
        return;    

    }

    if(axisToExclude.y) {
        for (qsizetype i = 0; i < pointsList.size(); i++)
            normalizePointsList.append(Coordinate(pointsList[i].x, pointsList[i].z));
        return; 
    }

    for (qsizetype i = 0; i < pointsList.size(); i++)
        normalizePointsList.append(Coordinate(pointsList[i].x, pointsList[i].y));
}

void Object::rotateWorld(float teta, Coordinate axis)
{
    float radians = qDegreesToRadians(teta);

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

    // for (qsizetype i = 0; i < pointsList.size(); i++)
    // {
    //     pointsList[i] = Coordinate(pointsList[i].x * qCos(radians) - (pointsList[i].y * qSin(radians)),
    //                                        pointsList[i].x * qSin(radians) + (pointsList[i].y * qCos(radians)));
    // }
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
        normalizePointsList[i].x = windowXBegin + (normalizePointsList[i].x - windowXBegin) / (windowXEnd - windowXBegin) * viewportWidth;
        normalizePointsList[i].y = windowYBegin + (1 - (normalizePointsList[i].y - windowYBegin) / (windowYEnd - windowYBegin)) * viewportHeight;
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

    // cout << result << endl;
    return result;
}
