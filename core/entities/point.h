#ifndef POINT_H
#define POINT_H

#include "object.h"
#include "coordinate.h"
#include <iostream>

#include <QPoint>

class Point : public Object, public QPointF
{
public:
    Point(
        const QString& name,
        const QList<Coordinate> &pointsList,
        const QList<pair<int,int>> &edgesList,
        Qt::GlobalColor color=Qt::black
    ):
        Object(name, pointsList, edgesList, color)
    {}

    void draw(QPainter &painter);   
    void translate(Coordinate translation);
    void translateProjection(Coordinate translation);
    void scale(float factor);
    void rotate(float teta, Coordinate axis);
    bool isInsideWindow(vector<bool> pointRegionCode);
    bool isOutsideWindow(vector<bool> pointRegionCode);

};

#endif // POINT_H
