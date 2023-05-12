#include "object.h"
#include "screen.h"
#include <iostream>
#include <assert.h>
using namespace std;

void drawNormalizedPoints(
    QList<pair<float, float>> pointsList,
    QList<pair<float, float>> normalizePointsList,
    QPainter &painter);

void drawWorldPoints(QList<pair<float, float>> pointsList, QPainter &painter);

void Object::draw(QPainter &painter)
{
    // drawWorldPoints(pointsList, painter);
    drawNormalizedPoints(pointsList, normalizePointsList, painter);
}

void drawNormalizedPoints(
    QList<pair<float, float>> pointsList,
    QList<pair<float, float>> normalizePointsList,
    QPainter &painter)
{
    for (qsizetype i = 0; i < normalizePointsList.size(); i++)
    {
        if (i == pointsList.size() - 1)
        {
            painter.drawLine(normalizePointsList[i].first, normalizePointsList[i].second,
                             normalizePointsList[0].first, normalizePointsList[0].second);
            continue;
        }

        painter.drawLine(normalizePointsList[i].first, normalizePointsList[i].second,
                         normalizePointsList[i + 1].first, normalizePointsList[i + 1].second);
    }
}

void drawWorldPoints(QList<pair<float, float>> pointsList, QPainter &painter)
{
    for (qsizetype i = 0; i < pointsList.size(); i++)
    {
        if (i == pointsList.size() - 1)
        {
            painter.drawLine(pointsList[i].first, pointsList[i].second,
                             pointsList[0].first, pointsList[0].second);
            continue;
        }

        painter.drawLine(pointsList[i].first, pointsList[i].second,
                         pointsList[i + 1].first, pointsList[i + 1].second);
    }
}

void Object::normalize(int windowWidth, int windowHeight, pair<float, float> center)
{
    normalizePointsList.erase(normalizePointsList.begin(), normalizePointsList.end());
    float newX = 0.0;
    float newY = 0.0;
    float viewportWidth = 854.0;
    float viewportHeight = 480.0;
    float windowXBegin = center.first - (viewportWidth / 2);
    float windowYBegin = center.second - (viewportHeight / 2);

    for (qsizetype i = 0; i < pointsList.size(); i++)
    {
        // newX = linearInterpolation(pointsList[i].first, 0, windowWidth, -1, 1);
        newX = (pointsList[i].first - windowXBegin) / (windowWidth)*viewportWidth;
        newY = (pointsList[i].second - windowYBegin) / (windowHeight)*viewportHeight;

        // cout << "(" << newX << ", " << newY << ")" << endl;
        // newY = linearInterpolation(pointsList[i].second, 0, windowHeight, -1, 1);
        normalizePointsList.append(pair<float, float>(newX, newY));
    }
}

void Object::regionCodeGenerate(Border border)
{    
    regionCodeList.erase(regionCodeList.begin(), regionCodeList.end());
    for (qsizetype i = 0; i < normalizePointsList.size(); i++)
    {
        vector<bool> regionCode;
        regionCode.assign(4, 0);

        regionCode.at(0) = normalizePointsList[i].second > border.getUpper();
        regionCode.at(1) = normalizePointsList[i].second < border.getLower();
        regionCode.at(2) = normalizePointsList[i].first > border.getRight();
        regionCode.at(3) = normalizePointsList[i].first < border.getLeft();

        regionCodeList.append(regionCode);
    }
}

void Object::clipping(Border border)
{  
    regionCodeGenerate(border);
    
    // regionCodeList e normalizePointsList são listas com relação de 1 pra 1, o mesmo indice pode ser utilizado por ambas
    for (qsizetype i = 0; i < regionCodeList.size(); i++)
    {        
        if (i == regionCodeList.size() - 1)
        {
            clippingTwoPointsByIndex(border, i, 0);
            break;           
        }

        clippingTwoPointsByIndex(border, i, i + 1);
    }
}

void Object::rotateWorld(float teta)
{
    float radians = qDegreesToRadians(teta);

    for (qsizetype i = 0; i < pointsList.size(); i++)
    {
        pointsList[i] = pair<float, float>(pointsList[i].first * qCos(radians) - (pointsList[i].second * qSin(radians)),
                                           pointsList[i].first * qSin(radians) + (pointsList[i].second * qCos(radians)));
    }
}

void Object::transformToViewport(pair<float, float> center)
{
    int viewportWidth = 854;
    int viewportHeight = 480;

    float windowXBegin = center.first - (viewportWidth / 2);
    float windowXEnd = center.first + (viewportWidth / 2);
    float windowYBegin = center.second - (viewportHeight / 2);
    float windowYEnd = center.second + (viewportHeight / 2);

    for (qsizetype i = 0; i < normalizePointsList.size(); i++)
    {
        normalizePointsList[i].first = windowXBegin + (normalizePointsList[i].first - windowXBegin) / (windowXEnd - windowXBegin) * viewportWidth;
        normalizePointsList[i].second = windowYBegin + (1 - (normalizePointsList[i].second - windowYBegin) / (windowYEnd - windowYBegin)) * viewportHeight;
    }
}

pair<float, float> Object::barycenter()
{
    pair<float, float> center;

    for (qsizetype i = 0; i < pointsList.size(); i++)
    {
        center.first += pointsList[i].first;
        center.second += pointsList[i].second;
    }
    center.first = (center.first / pointsList.size());
    center.second = (center.second / pointsList.size());

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

void Object::clippingTwoPointsByIndex(
    Border border,
    qsizetype pointOneIndex,
    qsizetype pointTwoIndex
) 
{
    debugRegionCodes(regionCodeList[pointOneIndex], regionCodeList[pointTwoIndex]);

    if (isLineFullyInsideWindow(regionCodeList[pointOneIndex], regionCodeList[pointTwoIndex])) 
        return;

    if (isLineFullyOutsideWindow(regionCodeList[pointOneIndex], regionCodeList[pointTwoIndex]))
    {
        normalizePointsList.removeAt(pointOneIndex);
        normalizePointsList.removeAt(pointTwoIndex);
        return;
    }
    
    // Entra se TODOS os pares possuem ao menos um 0
    // return equação da reta
    // tem que atualizar o ponto que esta fora da window por um na borda 
    if(hasSomeRegionCodeTruly(regionCodeList[pointOneIndex])){
        pair <float, float> aux = normalizePointsList[pointOneIndex];
        normalizePointsList[pointOneIndex] = lineClipping(
            border,
            pointTwoIndex,
            pointOneIndex
        );
        if(aux == normalizePointsList[pointOneIndex])
            normalizePointsList.removeAt(pointOneIndex);
            
        return;
    }

    pair <float, float> aux = normalizePointsList[pointTwoIndex];
    normalizePointsList[pointTwoIndex] = lineClipping(
        border,
        pointOneIndex,
        pointTwoIndex
    );

    if(aux == normalizePointsList[pointOneIndex])
        normalizePointsList.removeAt(pointOneIndex);
}

void Object::debugRegionCodes(
    vector<bool> pointOneRegionCode, 
    vector<bool> pointTwoRegionCode
) {
    cout << " \n Analise do RC" << endl; 
    // cout << "P1 upper: " << pointOneRegionCode[0] << endl;
    // cout << "P2 upper: " << pointTwoRegionCode[0] << endl;
    // cout << "P1 lower: " << pointOneRegionCode[1] << endl;
    // cout << "P2 lower: " << pointTwoRegionCode[1] << endl;
    // cout << "P1 left: " << pointOneRegionCode[2] << endl;
    // cout << "P2 left: " << pointTwoRegionCode[2] << endl;
    // cout << "P1 right: " << pointOneRegionCode[3] << endl;
    // cout << "P2 right: " << pointTwoRegionCode[3] << endl;
    // cout << "ou em RC:" << endl;
    cout << "P1: " << pointOneRegionCode[0] << " " << pointOneRegionCode[1] << " " << pointOneRegionCode[2] << " " << pointOneRegionCode[3] << endl;
    cout << "P2: " << pointTwoRegionCode[0] << " " << pointTwoRegionCode[1] << " " << pointTwoRegionCode[2] << " " << pointTwoRegionCode[3] << endl;
}

// Totalmente dentro da window RC de pi & p2 == 0 0 0 0
bool Object::isLineFullyInsideWindow(
    vector<bool> pointOneRegionCode, 
    vector<bool> pointTwoRegionCode
) {
    return (
        !pointOneRegionCode[0] && !pointTwoRegionCode[0] &&
        !pointOneRegionCode[1] && !pointTwoRegionCode[1] &&
        !pointOneRegionCode[2] && !pointTwoRegionCode[2] &&
        !pointOneRegionCode[3] && !pointTwoRegionCode[3]
    );
}

// Totalmente fora da window RC de p1 & p2 != 0 0 0 0
bool Object::isLineFullyOutsideWindow(
    vector<bool> pointOneRegionCode, 
    vector<bool> pointTwoRegionCode
) {
    return (
        (pointOneRegionCode[0] && pointTwoRegionCode[0]) ||
        (pointOneRegionCode[1] && pointTwoRegionCode[1]) ||
        (pointOneRegionCode[2] && pointTwoRegionCode[2]) ||
        (pointOneRegionCode[3] && pointTwoRegionCode[3])
    );
}

bool Object::hasSomeRegionCodeTruly(vector<bool> regionCode) {
    return (
        regionCode[0] ||
        regionCode[1] ||
        regionCode[2] ||
        regionCode[3]
    );
}

pair<float, float> Object::lineClipping(Border border, qsizetype insidePointIndex, qsizetype outsidePointIndex)
{
    float angularCoefficient = ((normalizePointsList[insidePointIndex].second - normalizePointsList[outsidePointIndex].second) 
                            / (normalizePointsList[insidePointIndex].first - normalizePointsList[outsidePointIndex].first));
    pair<float,float> newPoint;

    if (normalizePointsList[outsidePointIndex].second > border.getUpper())
    {
        float newX = angularCoefficient * (border.getUpper() - normalizePointsList[insidePointIndex].second) 
            + normalizePointsList[insidePointIndex].first;

        if (newX >= border.getLeft() && newX <= border.getRight()) {
            newPoint.first = newX;
            newPoint.second = border.getUpper();
            return newPoint;
        }

        return normalizePointsList[outsidePointIndex];
    }

    if (normalizePointsList[outsidePointIndex].second < border.getLower())
    {
         float newX = angularCoefficient * (border.getLower() - normalizePointsList[insidePointIndex].second) 
            + normalizePointsList[insidePointIndex].first;

        if (newX >= border.getLeft() && newX <= border.getRight()) {
            newPoint.first = newX;
            newPoint.second = border.getLower();
            return newPoint;
        }

        return normalizePointsList[outsidePointIndex];
    }

   
    if (normalizePointsList[outsidePointIndex].first > border.getRight())
    {
         float newY = angularCoefficient * (border.getRight() - normalizePointsList[insidePointIndex].first) 
            + normalizePointsList[insidePointIndex].second;

        if (newY >= border.getLower() && newY <= border.getUpper()) {
            newPoint.first = border.getRight();
            newPoint.second = newY;
            return newPoint;
        }

        return normalizePointsList[outsidePointIndex];
    }

    
     float newY = angularCoefficient * (border.getLeft() - normalizePointsList[insidePointIndex].first) 
            + normalizePointsList[insidePointIndex].second;

    if (newY >= border.getLower() && newY <= border.getUpper()) {
        newPoint.first = border.getLeft();
        newPoint.second = newY;
        return newPoint;
    }

    return normalizePointsList[outsidePointIndex];
    
};
