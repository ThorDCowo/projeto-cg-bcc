#ifndef POINT_H
#define POINT_H

#include "object.h"
#include "coordinate.h"

#include <QPoint>

class Point : public Object, public QPointF
{
public:
    Point(
        const QString& name, 
        const QList<Coordinate> &pointsList, 
        Qt::GlobalColor color=Qt::black
    ):
        Object(name, pointsList, color)
    {}

    void draw(QPainter &painter);   
    void translate(Coordinate translation);
    void scale();
    void rotate();
    bool isInsideWindow(vector<bool> pointRegionCode);
    bool isOutsideWindow(vector<bool> pointRegionCode);

};

#endif // POINT_H