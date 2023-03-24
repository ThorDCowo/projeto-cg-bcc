#ifndef LINE_H
#define LINE_H

#include "object.h"
#include <QLine>

class Line: public Object, public QLineF
{
public:
    Line(const QString& nome, const QList<std::pair<int,int>> &pointsList, Qt::GlobalColor color=Qt::black):
        Object(nome, pointsList, color)
    {}

    void draw(QPainter &painter);
};

#endif // LINE_H
