#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <iostream>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QPainter>
#include <QList>
#include "border.h"

using namespace std;

class Object
{

public:

    Object(const QString &name, const QList<pair<float,float>> &pointsList, Qt::GlobalColor color):
        name(name), pointsList(pointsList), color(color)
    {}

    pair<float, float> barycenter();
    pair<float, float> Object::lineClipping(
        Border border, 
        pair<float, float> insidePoint, 
        pair<float, float> outsidePoint
    );
    void draw(QPainter &painter);
    void rotateWorld(float teta);
    void transformToViewport(pair<float, float> center);
    void regionCodeGenerate(Border border);
    void normalize(int width, int height, pair<float, float> center);
    void debugRegionCodes(vector<bool> pointOneRegionCode, vector<bool> pointTwoRegionCode); 
    bool isLineFullyInsideWindow(vector<bool> pointOneRC, vector<bool> pointTwoRC);
    bool isLineFullyOutsideWindow(vector<bool> pointOneRC, vector<bool> pointTwoRC);
    bool hasSomeRegionCodeTruly(vector<bool> regionCode);
    void clippingTwoPointsByIndex(Border border, qsizetype pointOneIndex, qsizetype pointTwoIndex);

    virtual void translate(float dx, float dy)=0;
    virtual void scale(float factor)=0;
    virtual void rotate(float teta)=0;
    virtual void clipping(Border border)=0;

    virtual void transformFromWorldToViewport(int width, int height, pair<float, float> center);
    
    inline QString getName()const { return name; }
    inline QList<pair<float,float>> getPoints()const { return this->pointsList; }
    inline QList<pair<float,float>> getNormalizePoints()const { return this->normalizePointsList; }
    inline QList<vector<bool>> getRegionCode() {return this->regionCodeList;} 
    inline Qt::GlobalColor getColor()const { return color; }

    float linearInterpolation(float x, float x0, float x1, float y0, float y1);

protected:
    QString name; //id do objeto instanciado
    QList<pair<float,float>> pointsList;
    QList<pair<float,float>> normalizePointsList;
    QList<vector<bool>> regionCodeList; 
    Qt::GlobalColor color;

    pair<float, float> clippingAbove(
        Border border, 
        pair<float, float> insidePoint, 
        pair<float, float> outsidePoint,
        float angularCoefficient
    );

    pair<float, float> clippingBelow(
        Border border, 
        pair<float, float> insidePoint, 
        pair<float, float> outsidePoint,
        float angularCoefficient
    );

    pair<float, float> clippingight(
        Border border, 
        pair<float, float> insidePoint, 
        pair<float, float> outsidePoint,
        float angularCoefficient
    );

    pair<float, float> clippingLeft(
        Border border, 
        pair<float, float> insidePoint, 
        pair<float, float> outsidePoint,
        float angularCoefficient
    );
};

#endif // OBJECT_H
