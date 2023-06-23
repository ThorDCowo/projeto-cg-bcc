#ifndef CLIPPER_H
#define CLIPPER_H

#include <iostream>
#include <vector>
#include <QList>
#include "../../data/entities/object.h"
#include "../../data/entities/coordinate.h"

using namespace std;

class Clipper
{
public:
    void pointClipping(
        Border border, 
        QList<Coordinate>* normalizedPointsList,
        QList<pair<int,int>>* edgesListToDraw,
        QList<Coordinate>* pointsListToDraw
    );
    void lineClipping(
        Border border, 
        pair<int,int> edge,
        QList<Coordinate>* normalizedPointsList,
        QList<pair<int,int>>* edgesListToDraw,
        QList<Coordinate>* pointsListToDraw
    );
    void polygonClipping(
        Border border, 
        QList<Coordinate>* normalizedPointsList,
        QList<pair<int,int>>* edgesList,
        QList<pair<int,int>>* edgesListToDraw,
        QList<Coordinate>* pointsListToDraw
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

    void appendToNewLists(
        Coordinate pointOne,
        Coordinate pointTwo,
        QList<pair<int,int>>* edgesListToDraw,
        QList<Coordinate>* pointsListToDraw
    );

};

#endif // CLIPPER_H
