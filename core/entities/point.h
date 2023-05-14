#ifndef POINT_H
#define POINT_H

#include "object.h"

#include <QPoint>

class Point : public Object, public QPointF
{
public:
    Point(
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
    void scale();
    void rotate();
    void clipping(Border border);
    bool isInsideWindow(vector<bool> pointRegionCode);
    bool isOutsideWindow(vector<bool> pointRegionCode);

};

#endif // POINT_H
