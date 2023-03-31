#ifndef POINT_H
#define POINT_H

#include "object.h"

#include <QPoint>

class Point : public Object, public QPointF
{
public:
    Point(const QString& name, const QList<std::pair<float,float>> &pointsList,  Qt::GlobalColor color=Qt::black):
        Object(name, pointsList, color)
    {}

    void draw(QPainter &painter);
    void translate(float dx, float dy);
    void scale(float factor);
    void rotate(float teta);
};

#endif // POINT_H
