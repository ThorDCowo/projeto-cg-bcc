#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <iostream>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QPainter>
#include <QList>
#include <assert.h>
#include "border.h"
#include "coordinate.h"
#include "../../helper/geometric.helper.h"

using namespace std;

class Object
{

public:

    Object(
        const QString &name, 
        const QList<Coordinate> &pointsList, 
        const QList<pair<int,int>> &edgesList,
        Qt::GlobalColor color
    ):
        name(name), 
        pointsList(pointsList), 
        edgesList(edgesList),
        color(color)
    {}

    Coordinate barycenter();
    void rotateWorld(float radians, Coordinate axis);
    void transformToViewport(Coordinate center);
    void orthogonalProjection(Coordinate axisToExclude);
    void planeProjection(float distanceBetweenCOPandPlane);
    void perspectiveNormalize(
        int windowWidth, 
        int windowHeight, 
        Coordinate windowCenter,
        float distanceFromProjection);
    void orthogonalNormalize(
        int width, 
        int height, 
        Coordinate center,
        Coordinate axisToExclude);
    void perspectiveProjection(
        Coordinate centerOfProjection, 
        Coordinate axisX, 
        Coordinate axisY, 
        float alpha, 
        float beta);

    void draw(QPainter &painter);
    void drawNormalizedPoints(QPainter &painter);
    void drawWorldPoints(QPainter &painter);
    void drawProjectedPoints(QPainter &painter);
    void drawEdges(QPainter &painter);


    virtual void translate(Coordinate translation)=0;
    virtual void translateProjection(Coordinate translation) = 0;
    virtual void scale(float factor)=0;
    virtual void rotate(float teta, Coordinate axis)=0;
    
    inline QString getName()const{ return name; }
    inline QList<Coordinate> getPoints()const { return this->pointsList; }
    inline QList<pair<int, int>> getEdges()const { return this->edgesList; } 
    inline QList<Coordinate> getProjectionPoints()const { return this->projectionPointsList; } 
    inline QList<Coordinate> getNormalizedPoints()const { return this->normalizePointsList; } 
    inline Qt::GlobalColor getColor()const { return color; }

    float linearInterpolation(
        float x, 
        float x0, 
        float x1, 
        float y0, 
        float y1
    );

protected:
    QString name; //id do objeto instanciado
    QList<Coordinate> pointsList;
    QList<pair<int, int>> edgesList;
    QList<Coordinate> projectionPointsList;
    QList<Coordinate> normalizePointsList;
    Qt::GlobalColor color;

    void normalizeCoordinates(int windowWidth, int windowHeight, Coordinate windowCenter, QList<Coordinate> list);
};

#endif // OBJECT_H
