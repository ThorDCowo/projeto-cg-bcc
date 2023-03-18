#ifndef LINE_H
#define LINE_H

#include "object.h"
#include <QLine>

class Line : public Object, public QLineF
{
public:
    int iniX, iniY, endX, endY;
    Line(const QString& nome, const QLineF& r, int iniX, int iniY, int endX, int endY, Qt::GlobalColor color=Qt::black):
        Object(nome, LINHA, color),QLineF(r), iniX(iniX), iniY(iniY), endX(endX), endY(endY)
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

#endif // LINE_H
