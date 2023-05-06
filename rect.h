#ifndef RECT_H
#define RECT_H

#include "object.h"
#include <QRect>

class Rect : public Object, public QRectF
{
public:
    Rect(const QString& name, const QList<std::pair<float,float>> &pointsList, Qt::GlobalColor color=Qt::black):
        Object(name, pointsList, color)
    {}


    void draw(QPainter &painter);
    void translate(float dx, float dy);
    void scale(float factor);
    void rotate(float teta);
};

#endif // RECT_H
