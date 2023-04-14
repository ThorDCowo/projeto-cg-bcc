#include "object.h"
#include <iostream>
using namespace std;

void drawNormalizedPoints(
    QList<std::pair<float,float>> pointsList,
    QList<std::pair<float,float>> normalizePointsList,
    QPainter &painter
);

void drawWorldPoints(QList<std::pair<float,float>> pointsList, QPainter &painter);

void Object::draw(QPainter &painter)
{
    // drawWorldPoints(pointsList, painter);
    drawNormalizedPoints(pointsList, normalizePointsList, painter);
}

void drawNormalizedPoints(
    QList<std::pair<float,float>> pointsList,
    QList<std::pair<float,float>> normalizePointsList,
    QPainter &painter
)
{
    for(qsizetype i = 0; i < normalizePointsList.size(); i++){
        if(i == pointsList.size() - 1) {
            painter.drawLine(normalizePointsList[i].first, normalizePointsList[i].second,
                         normalizePointsList[0].first, normalizePointsList[0].second);
            continue;
        }

        painter.drawLine(normalizePointsList[i].first, normalizePointsList[i].second,
                         normalizePointsList[i+1].first, normalizePointsList[i+1].second);
    }
}

void drawWorldPoints(QList<std::pair<float,float>> pointsList, QPainter &painter)
{
    for(qsizetype i = 0; i < pointsList.size(); i++){
        if(i == pointsList.size() - 1) {
            painter.drawLine(pointsList[i].first, pointsList[i].second,
                         pointsList[0].first, pointsList[0].second);
            continue;
        }

        painter.drawLine(pointsList[i].first, pointsList[i].second,
                         pointsList[i+1].first, pointsList[i+1].second);
    }
}

void Object::normalize(int windowWidth, int windowHeight, pair<float, float> center)
{
    normalizePointsList.erase(normalizePointsList.begin(),normalizePointsList.end());
    float newX = 0.0;
    float newY = 0.0;
    float viewportWidth = 854.0; 
    float viewportHeight = 480.0;
    float windowXBegin = center.first - (viewportWidth/2);
    float windowYBegin = center.second - (viewportHeight/2);

    for(qsizetype i = 0; i < pointsList.size(); i++){
        //newX = linearInterpolation(pointsList[i].first, 0, windowWidth, -1, 1);
        newX = (pointsList[i].first - windowXBegin)/(windowWidth) * viewportWidth;
        newY = (pointsList[i].second - windowYBegin)/(windowHeight) * viewportHeight;

        //cout << "(" << newX << ", " << newY << ")" << endl;
        //newY = linearInterpolation(pointsList[i].second, 0, windowHeight, -1, 1);
        normalizePointsList.append(pair<float, float>(newX, newY));
    }

}

float Object::linearInterpolation(
    float valueInFirstIntervalToFindInSecondInterval, 
    float startFirstInterval, 
    float endFirstInterval,
    float startSecondInterval,
    float endSecondInterval
) 
{    
    float firstIntervalRange = endFirstInterval - startFirstInterval;
    float secondIntervalRange = endSecondInterval - startSecondInterval;
    float result = startSecondInterval + 
        ((secondIntervalRange) / (firstIntervalRange)) * 
        (valueInFirstIntervalToFindInSecondInterval - startFirstInterval);

    //cout << result << endl;
    return result;
}

void Object::rotateWorld(float teta)
{
    float radians = qDegreesToRadians(teta);

    for(qsizetype i = 0; i < pointsList.size(); i++){
        pointsList[i] = pair<float, float>(pointsList[i].first * qCos(radians) - (pointsList[i].second * qSin(radians)), 
                                        pointsList[i].first * qSin(radians) + (pointsList[i].second * qCos(radians)));
    }
}

void Object::transformToViewport(pair<float, float> center)
{
    int viewportWidth = 854; 
    int viewportHeight = 480;

    float windowXBegin = center.first - (viewportWidth/2);
    float windowXEnd = center.first + (viewportWidth/2);
    float windowYBegin = center.second - (viewportHeight/2);
    float windowYEnd = center.second + (viewportHeight/2);

    for(qsizetype i = 0; i < normalizePointsList.size(); i++){
        normalizePointsList[i].first = windowXBegin + (normalizePointsList[i].first - windowXBegin)/(windowXEnd - windowXBegin) * viewportWidth;
        normalizePointsList[i].second = windowYBegin + (1 - (normalizePointsList[i].second - windowYBegin) / (windowYEnd - windowYBegin)) * viewportHeight;
    }
}

pair<float, float> Object::barycenter()

{
    pair<float, float> center;
    
    for(qsizetype i = 0; i < pointsList.size(); i++){
        center.first += pointsList[i].first;
        center.second += pointsList[i].second;
    }
    center.first = (center.first / pointsList.size());
    center.second = (center.second / pointsList.size());

    return center;
}