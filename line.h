#ifndef LINE_H
#define LINE_H

#include "object.h"
#include <QLine>

class Line: public Object, public QLineF
{
public:
    Line(const QString& name, const QList<std::pair<int,int>> &pointsList, Qt::GlobalColor color=Qt::black):
        Object(name, pointsList, color)
    {}

    void draw(QPainter &painter);
    void translation(int dx, int dy);
    void scale(float px, float py);
    void rotation(int teta);
};

#endif // LINE_H
