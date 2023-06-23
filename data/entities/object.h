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
    void transformToViewport(
        Coordinate center,
        int viewportWidth,
        int viewportHeight
    );
    void orthogonalProjection(Coordinate axisToExclude);
    void planeProjection(float distanceBetweenCOPandPlane);
    void perspectiveNormalize(
        int windowWidth, 
        int windowHeight, 
        Coordinate windowCenter,
        float distanceFromProjection);
    void orthogonalNormalize(
        int windowWidth,
        int windowHeight,
        Coordinate center,
        Coordinate axisToExclude
    );
    void perspectiveProjection(
        Coordinate centerOfProjection, 
        Coordinate axisX, 
        Coordinate axisY, 
        float alpha, 
        float beta
    );

    void drawEdges(QPainter &painter);

    virtual void translate(Coordinate translation)=0;
    virtual void translateProjection(Coordinate translation)=0;
    virtual void scale(float factor)=0;
    virtual void rotate(float teta, Coordinate axis)=0;
    
    inline QString getName()const{ return name; }
    inline QList<Coordinate> getPoints()const { return this->pointsList; }
    inline QList<pair<int, int>> getEdges()const { return this->edgesList; } 
    inline QList<pair<int, int>> getEdgesListToDraw()const { return this->edgesListToDraw; } 
    inline QList<Coordinate> getPointsListToDraw() { return this->pointsListToDraw; } 
    inline QList<Coordinate> getProjectionPoints() { return this->projectionPointsList; } 
    inline QList<Coordinate> getNormalizedPoints() { return this->normalizedPointsList; } 
    inline QList<Coordinate> getViewportPoints() { return this->viewportPointsList; } 

    // inline QList<Coordinate> &getRefPointsListToDraw() { return pointsListToDraw; } 
    // inline QList<Coordinate> &getRefProjectionPoints() { return projectionPointsList; } 
    // inline QList<Coordinate> &getRefNormalizedPoints() { return normalizedPointsList; } 
    // inline QList<Coordinate> &getRefViewportPoints() { return viewportPointsList; } 
    inline Qt::GlobalColor getColor()const { return color; }
    
protected:  
    QString name; //id do objeto instanciado
    QList<Coordinate> pointsList;
    QList<pair<int, int>> edgesList;
    QList<pair<int,int>> edgesListToDraw;

    QList<Coordinate> pointsListToDraw;
    QList<Coordinate> projectionPointsList;
    QList<Coordinate> normalizedPointsList;
    QList<Coordinate> viewportPointsList;
    Qt::GlobalColor color;

    void normalizeCoordinates(
        int windowWidth,
        int windowHeight,
        Coordinate windowCenter
    );
};

#endif // OBJECT_H
