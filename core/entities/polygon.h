#ifndef POLYGON_H
#define POLYGON_H

#include "object.h"
#include <QRect>
#include "coordinate.h"

class Polygon : public Object, public QRectF
{
public:
    Polygon(
        const QString& name, 
        const QList<Coordinate> &pointsList, 
        Qt::GlobalColor color=Qt::black
    ):
        Object(name, pointsList, color)
    {}


    void draw(QPainter &painter);
    void translate(
        float dx, 
        float dy,
        float dz
    );
    void scale(float factor);
    void rotate(float teta, Coordinate axis);
};

#endif // POLYGON_H
