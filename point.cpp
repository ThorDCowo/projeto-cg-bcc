#include "point.h"
#include <iostream>
using namespace std;

void Point::desenha(QPainter &painter)
{
    painter.drawPoint(*this);
    cout << "passou aqui-> Point::desenha" << endl;
}

void Point::ajusta(int dx, int dy)
{
    setX((*this + QPoint(dx,dy)).x());
    setY((*this + QPoint(dx,dy)).y());
}

void Point::transformadaWindow(int windowX,int windowY)
{
    rx() = x() - windowX;
    ry() = y() - windowY;
}

void Point::normalizacao(int windowHeight, int windowWidth)
{
    rx() = x() / windowWidth;
    ry() = y() / windowHeight;
}

void Point::transformadaViewport(int viewHeight, int viewWidth)
{
    rx() = ((x() + 1) / 2) * viewWidth;
    ry() = ((1 - (y() + 1) / 2)) * viewHeight;
}

void Point::translacao(int dx, int dy)
{
    rx() = x() + dx;
    ry() = y() + dy;
}

void Point::escala(float px, float py){}

void Point::rotacao(int teta){}

