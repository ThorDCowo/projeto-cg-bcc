#ifndef POLYGON_H
#define POLYGON_H

#include "object.h"
#include <QRect>

class Polygon : public Object, public QRectF
{
public:
    Polygon(
        const QString& name, 
        const QList<pair<float,float>> &pointsList, 
        Qt::GlobalColor color=Qt::black
    ):
        Object(name, pointsList, color)
    {}


    void draw(QPainter &painter);
    void translate(
        float dx, 
        float dy
    );
    void scale(float factor);
    void rotate(float teta);
    void clipping(Border border);
};

#endif // POLYGON_H
