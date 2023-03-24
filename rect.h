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
    //void ajusta(int dx, int dy);
    //void transformadaWindow(int windowX,int windowY);
    //void normalizacao(int windowHeight, int windowWidth);
    //void transformadaViewport(int viewHeight, int viewWidth);
    //void translacao(int dx, int dy);
    //void escala(float px, float py);
    //void rotacao(int teta);

};

#endif // RECT_H
