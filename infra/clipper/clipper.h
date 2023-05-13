#ifndef CLIPPER_H
#define CLIPPER_H

#include <iostream>
#include <vector>
#include <QList>
#include "border.h"

using namespace std;

class Clipper
{
public:
    void pointClipping(
        Border border, 
        QList<pair<float, float>>* pointsList
    );
    void lineClipping(
        Border border, 
        qsizetype pointOneIndex, 
        qsizetype pointTwoIndex,    
        QList<pair<float, float>>* pointsList
    );
    void polygonClipping(
        Border border, 
        QList<pair<float, float>>* pointsList
    );    

protected:
    QList<vector<bool>> regionCodeList; 

    vector<bool> generateRegionCode(
        Border border, 
        pair<float, float> point
    );
    QList<vector<bool>> generateRegionCodeList(
        Border border, 
        pair<float, float> pointOneIndex, 
        pair<float, float> pointTwoIndex
    );
    void debugRegionCodes(
        vector<bool> pointOneRegionCode, 
        vector<bool> pointTwoRegionCode
    ); 
    bool isPointInsideWindow(
        vector<bool> pointRC
    );
    bool isLineFullyInsideWindow(
        vector<bool> pointOneRC, 
        vector<bool> pointTwoRC
    );
    bool isLineFullyOutsideWindow(
        vector<bool> pointOneRC, 
        vector<bool> pointTwoRC
    );
    bool isLineFullyDiagonal(
        vector<bool> pointOneRC, 
        vector<bool> pointTwoRC
    );
    bool hasSomeRegionCodeTruly(
        vector<bool> regionCode
    );
    bool hasTwoRegionCodeTruly(
        vector<bool> regionCode
    );
    pair<float, float> parallelToAxisClipping(
        Border border, 
        pair<float, float> insidePoint, 
        pair<float, float> outsidePoint
    );
    pair<float, float> diagonalClipping(
        Border border, 
        pair<float, float> insidePoint, 
        pair<float, float> outsidePoint
    );

    inline QList<vector<bool>> getRegionCode(){
        return this->regionCodeList;
    }

    pair<float, float> clippingAbove(
        Border border,
        pair<float, float> outsidePoint,
        float angularCoefficient
    );

    pair<float, float> clippingBelow(
        Border border,  
        pair<float, float> outsidePoint,
        float angularCoefficient
    );

    pair<float, float> clippingRight(
        Border border, 
        pair<float, float> outsidePoint,
        float angularCoefficient
    );

    pair<float, float> clippingLeft(
        Border border, 
        pair<float, float> outsidePoint,
        float angularCoefficient
    );

};

#endif // CLIPPER_H
