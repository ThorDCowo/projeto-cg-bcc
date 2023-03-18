#include "rect.h"
#include <iostream>
#include <QtMath>

using namespace std;

void Rect::desenha(QPainter &painter)
{
    painter.drawRect(*this);
    cout << "passou aqui-> Rect::desenha" << endl;
}

void Rect::ajusta(int dx, int dy)
{
    adjust(dx,dy,dx,dy);
}

void Rect::transformadaWindow(int windowX,int windowY)
{
    double aux, x2, y2;

    getCoords(&aux, &aux, &x2, &y2);
    setCoords(x() - windowX, y() - windowY, x2 - windowX, y2 - windowY);
}

void Rect::normalizacao(int windowHeight, int windowWidth)
{
    double aux, x2, y2;

    getCoords(&aux, &aux, &x2, &y2);
    setCoords(x() / windowWidth, y() / windowHeight, x2 / windowWidth, y2 / windowHeight);
}

void Rect::transformadaViewport(int viewHeight, int viewWidth)
{
    double aux, x2, y2;

    getCoords(&aux, &aux, &x2, &y2);
    setCoords(((x() + 1) / 2) * viewWidth, (1 - ((y() + 1) / 2)) * viewHeight, ((x2 + 1) / 2) * viewWidth, (1 - ((y2 + 1) / 2)) * viewHeight);
}

void Rect::translacao(int dx, int dy)
{
    double aux, x2, y2;

    getCoords(&aux, &aux, &x2, &y2);
    setCoords(x()+dx, y()+dy, x2+dx, y2+dy);
}

void Rect::escala(float px, float py)
{
    double aux, x2, y2;
    getCoords(&aux, &aux, &x2, &y2);

    int auxX = (x() + x2) / 2;
    int auxY = (y() + y2) / 2;

    setCoords(auxX-x(), auxY-y(), auxX-x2, auxY-y2);
    setCoords(x()*px, y()*py, x2*px, y2*py);
    setCoords(x()+auxX, y()+auxY, x2+auxX, y2+auxY);
}

void Rect::rotacao(int teta)
{
    double aux, x2, y2;
    getCoords(&aux, &aux, &x2, &y2);

    int auxX = (x() + x2) / 2;
    int auxY = (y() + y2) / 2;

    setCoords(auxX-x(), auxY-y(), auxX-x2, auxY-y2);
    //cout << qRadiansToDegrees(qSin(teta));
    setCoords((x()*qRadiansToDegrees(qCos(teta))-(y()*qRadiansToDegrees(qSin(teta)))), (x()*qRadiansToDegrees(qSin(teta))+(y()*qRadiansToDegrees(qCos(teta)))), (x2*qRadiansToDegrees(qCos(teta))-(y2*qRadiansToDegrees(qSin(teta)))), (x2*qRadiansToDegrees(qSin(teta))+(y2*qRadiansToDegrees(qCos(teta)))));
    setCoords(x()+auxY, y()+auxX, x2+auxY, y2+auxX);
}
