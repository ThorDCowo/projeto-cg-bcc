#ifndef LINE_H
#define LINE_H

#include "object.h"
#include "border.h"
#include "coordinate.h"
#include <iostream>


#include <QLine>

class Line: public Object, public QLineF
{
public:
    Line(
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
};

#endif // LINE_H
