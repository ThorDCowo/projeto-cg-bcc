#ifndef CLIPPER_H
#define CLIPPER_H

#include <iostream>
#include <vector>
#include <QList>
#include "../../core/entities/object.h"
#include "../../core/entities/coordinate.h"


using namespace std;

class Clipper
{
public:
    void pointClipping(
        Border border, 
        QList<Coordinate>* pointsList
    );
    void lineClipping(
        Border border, 
        qsizetype pointOneIndex, 
        qsizetype pointTwoIndex,    
        QList<Coordinate>* pointsList
    );
    void polygonClipping(
        Border border, 
        QList<Coordinate>* pointsList
    );    

protected:
    QList<vector<bool>> regionCodeList; 

    vector<bool> generateRegionCode(
        Border border, 
        Coordinate point
    );
    QList<vector<bool>> generateRegionCodeList(
        Border border, 
        Coordinate pointOneIndex, 
        Coordinate pointTwoIndex
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
    Coordinate parallelToAxisClipping(
        Border border, 
        Coordinate insidePoint, 
        Coordinate outsidePoint
    );
    Coordinate diagonalClipping(
        Border border, 
        Coordinate insidePoint, 
        Coordinate outsidePoint
    );

    inline QList<vector<bool>> getRegionCode(){
        return this->regionCodeList;
    }

    Coordinate clippingAbove(
        Border border,
        Coordinate outsidePoint,
        float angularCoefficient
    );

    Coordinate clippingBelow(
        Border border,  
        Coordinate outsidePoint,
        float angularCoefficient
    );

    Coordinate clippingRight(
        Border border, 
        Coordinate outsidePoint,
        float angularCoefficient
    );

    Coordinate clippingLeft(
        Border border, 
        Coordinate outsidePoint,
        float angularCoefficient
    );

};

#endif // CLIPPER_H
