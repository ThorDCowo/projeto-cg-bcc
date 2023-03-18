#ifndef RECT_H
#define RECT_H

#include "object.h"
#include <QRect>

class Rect : public Object, public QRectF
{
public:
    int x1, y1, x2, y2;
    Rect(const QString& nome, const QRectF& real, int x1, int y1, int x2, int y2, Qt::GlobalColor color=Qt::black):
        Object(nome, RETANGULO,color),QRectF(real), x1(x1), y1(y1), x2(x2), y2(y2)
    {}

    void desenha(QPainter& painter);
    void ajusta(int dx, int dy);
    void transformadaWindow(int windowX,int windowY);
    void normalizacao(int windowHeight, int windowWidth);
    void transformadaViewport(int viewHeight, int viewWidth);
    void translacao(int dx, int dy);
    void escala(float px, float py);
    void rotacao(int teta);

};

#endif // RECT_H
