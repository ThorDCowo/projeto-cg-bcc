#ifndef RECT_H
#define RECT_H

#include "object.h"
#include <QRect>

class Rect : public Object, public QRectF
{
public:
    Rect(const QString& name, const QList<std::pair<int,int>> &pointsList, Qt::GlobalColor color=Qt::black):
        Object(name, pointsList, color)
    {}


    void draw(QPainter &painter);
    void translation(int dx, int dy);
    void scale(float px, float py);
    void rotation(int teta);
};

#endif // RECT_H
