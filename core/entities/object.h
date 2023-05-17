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
#include "coordinate.h"

using namespace std;

class Object
{

public:

    Object(
        const QString &name, 
        const QList<Coordinate> &pointsList, 
        Qt::GlobalColor color
    ):
        name(name), 
        pointsList(pointsList), 
        color(color)
    {}

    Coordinate barycenter();
    void draw(QPainter &painter);
    void rotateWorld(float teta, Coordinate axis);
    void transformToViewport(Coordinate center);
    void orthogonalProjection(Coordinate axis);
    void normalize(
        int width, 
        int height, 
        Coordinate center,
        Coordinate axis
    );

    virtual void translate(
        float dx, 
        float dy,
        float dz
    )=0;
    virtual void scale(float factor)=0;
    virtual void rotate(float teta, Coordinate axis)=0;
    
    inline QString getName()const{ return name; }
    inline QList<Coordinate> getPoints()const { return this->pointsList; }
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
    QList<Coordinate> normalizePointsList;
    Qt::GlobalColor color;

};

#endif // OBJECT_H
