#ifndef POINT_H
#define POINT_H

#include "object.h"

#include <QPoint>

class Point : public Object, public QPointF
{
public:
    int xx, yy;
    Point(const QString& nome, const QPointF& p, int xx, int yy, Qt::GlobalColor color=Qt::black):
        Object(nome, PONTO,color),QPointF(p), xx(xx), yy(yy)
    {}

    void desenha(QPainter& painter);
    void ajusta (int dx, int dy);
    void transformadaWindow(int windowX,int windowY);
    void normalizacao(int windowHeight, int windowWidth);
    void transformadaViewport(int viewHeight, int viewWidth);
    void translacao(int dx, int dy);
    void escala(float px, float py);
    void rotacao(int teta);

};

#endif // POINT_H
