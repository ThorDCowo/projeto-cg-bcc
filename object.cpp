#include <iostream>
#include <assert.h>

#include "object.h"
#include "screen.h"
#include "border.h"

using namespace std;

void drawNormalizedPoints(
    QList<pair<float, float>> pointsList,
    QList<pair<float, float>> normalizePointsList,
    QPainter &painter);

void drawWorldPoints(QList<pair<float, float>> pointsList, QPainter &painter);

void Object::transformFromWorldToViewport(int width, int height, pair<float, float> center) {
    Border border(width, height, center);
    
    this->normalize(width, height, center);
    this->clipping(border); 
    this->transformToViewport(center);
}

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

void Object::lineClipping(
    Border border,
    qsizetype pointOneIndex,
    qsizetype pointTwoIndex
) 
{
    cout << "border upper: " << border.getUpper() << endl;
    cout << "border lower: " << border.getLower() << endl;
    cout << "border left: " << border.getLeft() << endl;
    cout << "border right: " << border.getRight() << endl;

    cout << "pointOneIndex: " << pointOneIndex << endl;
    cout << "pointTwoIndex: " << pointTwoIndex << endl;

    debugRegionCodes(regionCodeList[pointOneIndex], regionCodeList[pointTwoIndex]);

    if (isLineFullyInsideWindow(regionCodeList[pointOneIndex], regionCodeList[pointTwoIndex])) 
        return;

    if (isLineFullyOutsideWindow(regionCodeList[pointOneIndex], regionCodeList[pointTwoIndex]))
    {
        cout << "Index: " << pointOneIndex << " " << pointTwoIndex << endl;
        cout << normalizePointsList.size() << endl;
        normalizePointsList.removeAt(pointTwoIndex);
        normalizePointsList.removeAt(pointOneIndex);
        return;
    }

    if(hasTwoRegionCodeTruly(regionCodeList[pointOneIndex])){
        pair <float, float> control = normalizePointsList[pointOneIndex];
        normalizePointsList[pointOneIndex] = diagonalClipping(
            border,
            normalizePointsList[pointTwoIndex],
            normalizePointsList[pointOneIndex]
        );

        if(control == normalizePointsList[pointOneIndex]){
            cout << "Edging 1" << endl;
            normalizePointsList.removeAt(pointOneIndex);
            return;
        }

    }

    if(hasTwoRegionCodeTruly(regionCodeList[pointTwoIndex])){
        pair <float, float> control = normalizePointsList[pointTwoIndex];
        normalizePointsList[pointTwoIndex] = diagonalClipping(
            border,
            normalizePointsList[pointOneIndex],
            normalizePointsList[pointTwoIndex]
        );

        if(control == normalizePointsList[pointTwoIndex]){            
            cout << "Edging 2" << endl;
            normalizePointsList.removeAt(pointTwoIndex);
            return;
        }

    }

    if(hasSomeRegionCodeTruly(regionCodeList[pointOneIndex])){
        pair <float, float> aux = normalizePointsList[pointOneIndex];
        normalizePointsList[pointOneIndex] = parallelToAxisClipping(
            border,
            normalizePointsList[pointTwoIndex],
            normalizePointsList[pointOneIndex]
        );
        if(aux == normalizePointsList[pointOneIndex]){
            cout << "Killing Machine" << endl;
            normalizePointsList.removeAt(pointTwoIndex);
            normalizePointsList.removeAt(pointOneIndex);
            return;
        }
    }

    pair <float, float> aux = normalizePointsList[pointTwoIndex];
    normalizePointsList[pointTwoIndex] = parallelToAxisClipping(
        border,
        normalizePointsList[pointOneIndex],
        normalizePointsList[pointTwoIndex]
    );
}

void Object::debugRegionCodes(
    vector<bool> pointOneRegionCode, 
    vector<bool> pointTwoRegionCode
) {
    cout << " \n Analise do RC" << endl; 
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

bool Object::hasTwoRegionCodeTruly(vector<bool> regionCode) {
    return (
        ((regionCode[0] ||
        regionCode[1] )&&
        (regionCode[2] ||
        regionCode[3]) )
    );
}

pair<float, float> Object::parallelToAxisClipping(
    Border border, 
    pair<float, float> insidePoint, 
    pair<float, float> outsidePoint
)
{
    cout << "Vertical or Horizontal Clipping " << endl;
    float angularCoefficient = ((insidePoint.second - outsidePoint.second) 
                            / (insidePoint.first - outsidePoint.first));

    if (outsidePoint.second > border.getUpper())
        return clippingAbove(border,  outsidePoint, angularCoefficient);

    if (outsidePoint.second < border.getLower())
        return clippingBelow(border, outsidePoint, angularCoefficient);

    if (outsidePoint.first > border.getRight())
        return clippingRight(border, outsidePoint, angularCoefficient);

    
    return clippingLeft(border, outsidePoint, angularCoefficient);
};

pair<float, float> Object:: diagonalClipping(   
    Border border, 
    pair<float, float> insidePoint, 
    pair<float, float> outsidePoint
)
{
    cout << "Diagonal Clipping " << endl;
    pair <float, float> control = outsidePoint;
    float angularCoefficient = ((insidePoint.second - outsidePoint.second) 
                            / (insidePoint.first - outsidePoint.first));

    if (outsidePoint.second > border.getUpper()){
        outsidePoint = clippingAbove(border, outsidePoint, angularCoefficient);
        
        if(control != outsidePoint) return outsidePoint;
    }

    if (outsidePoint.second < border.getLower()){
        outsidePoint = clippingBelow(border, outsidePoint, angularCoefficient);

        if(control != outsidePoint) return outsidePoint;
    }

    if (outsidePoint.first > border.getRight()){
        outsidePoint = clippingRight(border, outsidePoint, angularCoefficient);

        if(control != outsidePoint) return outsidePoint;
    }

    if (outsidePoint.first > border.getLeft())
        return clippingLeft(border, outsidePoint, angularCoefficient);

};

pair<float, float> Object::clippingAbove(
    Border border, 
    pair<float, float> outsidePoint,
    float angularCoefficient
)
{
    cout << "Above" << endl;
    float newX = outsidePoint.first + (border.getUpper() - outsidePoint.second) / angularCoefficient;
    pair<float,float> newPoint;

    if (newX >= border.getLeft() && newX <= border.getRight()) {
        cout << "Accepted !" << endl;
        newPoint.first = newX;
        newPoint.second = border.getUpper();
        return newPoint;
    }

    cout << "Not Accepted" << endl;
    return outsidePoint;
}

pair<float, float> Object::clippingBelow(
    Border border, 
    pair<float, float> outsidePoint,
    float angularCoefficient
)
{    
    cout << "Below" << endl;
    float newX = outsidePoint.first + (1  / angularCoefficient) * (border.getLower() - outsidePoint.second);
    pair<float,float> newPoint;

    if (newX >= border.getLeft() && newX <= border.getRight()) {
        cout << "Accepted !" << endl;
        newPoint.first = newX;
        newPoint.second = border.getLower();
        return newPoint;
    }

    cout << "Not Accepted" << endl;
    return outsidePoint;
}

pair<float, float> Object::clippingRight(
    Border border,  
    pair<float, float> outsidePoint,
    float angularCoefficient
)
{   
    cout << "Right" << endl;
    float newY = angularCoefficient * (border.getRight() - outsidePoint.first) 
        + outsidePoint.second;
    pair<float,float> newPoint;

    if (newY >= border.getLower() && newY <= border.getUpper()) {
        cout << "Accepted !" << endl;
        newPoint.first = border.getRight();
        newPoint.second = newY;
        return newPoint;
    }

    cout << "Not Accepted" << endl;
    return outsidePoint;
}

pair<float, float> Object::clippingLeft(
    Border border,  
    pair<float, float> outsidePoint,
    float angularCoefficient
)
{
    cout << "Left" << endl;
    float newY = angularCoefficient * (border.getLeft() - outsidePoint.first) 
        + outsidePoint.second;
    pair<float,float> newPoint;

    if (newY >= border.getLower() && newY <= border.getUpper()) {
        cout << "Accepted !" << endl;
        newPoint.first = border.getLeft();
        newPoint.second = newY;
        return newPoint;
    }

    cout << "Not Accepted" << endl;
    return outsidePoint;
}