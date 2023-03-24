#ifndef RECT_H
#define RECT_H

#include "object.h"
#include <QRect>

class Rect : public Object, public QRectF
{
public:
    Rect(const QString& nome, const QList<std::pair<int,int>> &pointsList, Qt::GlobalColor color=Qt::black):
        Object(nome, pointsList, color)
    {}

    void draw(QPainter &painter);
};

#endif // RECT_H
