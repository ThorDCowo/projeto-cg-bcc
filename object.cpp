#include "object.h"
#include <iostream>
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

void drawWorldPoints(QList<std::pair<float, float>> pointsList, QPainter &painter)
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

void Object::regionCodeGenerate(float upper, float lower, float left, float right)
{
    regionCodeList.erase(regionCodeList.begin(), regionCodeList.end());
    for (qsizetype i = 0; i < normalizePointsList.size(); i++)
    {
        vector<bool> regionCode;
        regionCode.assign(4, 0);

        regionCode.at(0) = normalizePointsList[i].second > upper;
        regionCode.at(1) = normalizePointsList[i].second > lower;
        regionCode.at(2) = normalizePointsList[i].first > right;
        regionCode.at(3) = normalizePointsList[i].first > left;

        regionCodeList.append(regionCode);
    }
}

void Object::clipping(int windowWidth, int windowHeight, pair<float, float> center)
{
    float upper = center.second + (windowHeight / 2);
    float lower = center.second - (windowHeight / 2);
    float left = center.first - (windowWidth / 2);
    float right = center.first + (windowWidth / 2);

    regionCodeGenerate(upper, lower, left, right);

    QList<vector<bool>> regionCodeList = getRegionCode();

    for (qsizetype i = 0; i < regionCodeList.size(); i++)
    {
        if (i == regionCodeList.size() - 1)
        {
            // Completamente dentro da window RC de p1 | p2 == 0 0 0 0
            if (
                regionCodeList[i - 1][0] && regionCodeList[i][0] == 0 &&
                regionCodeList[i - 1][1] && regionCodeList[i][1] == 0 &&
                regionCodeList[i - 1][2] && regionCodeList[i][2] == 0 &&
                regionCodeList[i - 1][3] && regionCodeList[i][3] == 0

            )
            {
                // continue;
            }
            // Totalmente fora da window RC de p1 & p2 != 0 0 0 0
            if (
                (regionCodeList[i - 1][0] == 1 && regionCodeList[i][0] == 1) ||
                (regionCodeList[i - 1][1] == 1 && regionCodeList[i][1] == 1) ||
                (regionCodeList[i - 1][2] == 1 && regionCodeList[i][2] == 1) ||
                (regionCodeList[i - 1][3] == 1 && regionCodeList[i][3] == 1))
            {
                normalizePointsList.removeAt(i);
            }
            // Parcialmente dentro da window RC de p1 & p2 == 0 0 0 0
            if (
                (regionCodeList[i - 1][0] == 0 || regionCodeList[i][0] == 0) &&
                (regionCodeList[i - 1][1] == 0 || regionCodeList[i][1] == 0) &&
                (regionCodeList[i - 1][2] == 0 || regionCodeList[i][2] == 0) &&
                (regionCodeList[i - 1][3] == 0 || regionCodeList[i][3] == 0))
            {
                // return equação
            }
        }
        else
        {
            // Completamente dentro da window RC de p1 | p2 == 0 0 0 0
            if (
                regionCodeList[i][0] && regionCodeList[i + 1][0] == 0 &&
                regionCodeList[i][1] && regionCodeList[i + 1][1] == 0 &&
                regionCodeList[i][2] && regionCodeList[i + 1][2] == 0 &&
                regionCodeList[i][3] && regionCodeList[i + 1][3] == 0

            )
            {
                // continue;
            }
            // Totalmente fora da window RC de p1 & p2 != 0 0 0 0
            if (
                (regionCodeList[i][0] == 1 && regionCodeList[i + 1][0] == 1) ||
                (regionCodeList[i][1] == 1 && regionCodeList[i + 1][1] == 1) ||
                (regionCodeList[i][2] == 1 && regionCodeList[i + 1][2] == 1) ||
                (regionCodeList[i][3] == 1 && regionCodeList[i + 1][3] == 1))
            {
                normalizePointsList.remove(i);
            }
            // Parcialmente dentro da window RC de p1 & p2 == 0 0 0 0
            if (
                (regionCodeList[i][0] == 0 || regionCodeList[i + 1][0] == 0) &&
                (regionCodeList[i][1] == 0 || regionCodeList[i + 1][1] == 0) &&
                (regionCodeList[i][2] == 0 || regionCodeList[i + 1][2] == 0) &&
                (regionCodeList[i][3] == 0 || regionCodeList[i + 1][3] == 0))
            {
                // return equação
            }
        }
    }
}

float Object::linearInterpolation(
    float valueInFirstIntervalToFindInSecondInterval,
    float startFirstInterval,
    float endFirstInterval,
    float startSecondInterval,
    float endSecondInterval)
{
    float firstIntervalRange = endFirstInterval - startFirstInterval;
    float secondIntervalRange = endSecondInterval - startSecondInterval;
    float result = startSecondInterval +
                   ((secondIntervalRange) / (firstIntervalRange)) *
                       (valueInFirstIntervalToFindInSecondInterval - startFirstInterval);

    // cout << result << endl;
    return result;
}

float Object::lineEquation(float upper, float lower, float left, float right, float x1, float y1, float x2, float y2)
{

    float angularCoefficient = (y2 - y1) / (x2 - x1);
    float newX;
    float newY;

    if (y2 > upper)
    {
        newX = x2 * (upper - y2) / angularCoefficient;
        return newX;
    }

    if (y2 > lower)
    {
        newX = x2 * (lower - y2) / angularCoefficient;
        return newX;
    }

    if (lower < y2 && y2 < upper)
    {
        if (x2 > right)
        {
            newY = angularCoefficient * (right - x2) + y2;
            return newY;
        }
        if (x2 < left)
        {
            newY = angularCoefficient * (left - x2) + y2;
            return newY;
        }
    }
};

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