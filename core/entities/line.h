#ifndef LINE_H
#define LINE_H

#include "object.h"
#include "border.h"

#include <QLine>

class Line: public Object, public QLineF
{
public:
    Line(
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

#endif // LINE_H
