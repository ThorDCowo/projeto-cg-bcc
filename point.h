#ifndef POINT_H
#define POINT_H

#include "object.h"

#include <QPoint>

class Point : public Object, public QPointF
{
public:
    Point(const QString& nome, const QList<std::pair<int,int>> &pointsList,  Qt::GlobalColor color=Qt::black):
        Object(nome, pointsList, color)
    {}

    void draw(QPainter &painter);

};

#endif // POINT_H
