#include "line.h"
#include <iostream>
using namespace std;

void Line::desenha(QPainter &painter)
{
    painter.drawLine(*this);
    cout << "pasosu aqui-> Line::desenha" << endl;
}

void Line::ajusta(int dx, int dy)
{
    translate(dx,dy);
}

void Line:: transformadaWindow(int windowX,int windowY)
{
    setLine(x1() - windowX,y1() - windowY, x2() - windowX, y2() - windowY);
}

void Line::normalizacao(int windowHeight, int windowWidth)
{
    setLine(x1() / windowWidth, y1() / windowHeight, x2() / windowWidth, y2() / windowHeight);
}

void Line::transformadaViewport(int viewHeight, int viewWidth)
{
    setLine(((x1() + 1) / 2) * viewWidth, (1 - ((y1() + 1) / 2)) * viewHeight, ((x2() + 1) / 2) * viewWidth, (1 - ((y2() + 1) / 2)) * viewHeight);
}

void Line::translacao(int dx, int dy)
{
    setLine(x1()+dx, y1()+dy, x2()+dx, y2()+dy);
}

void Line::escala(float px, float py)
{
    int auxX = (x1() + x2()) / 2;
    int auxY = (y1() + y2()) / 2;

    setLine(auxX-x1(), auxY-y1(), auxX-x2(), auxY-y2());
    setLine(x1()*px, y1()*py, x2()*px, y2()*py);
    setLine(auxX+x1(), y1()+auxY, x2()+auxX, y2()+auxY);
}

void Line::rotacao(int teta)
{
    int auxX = (x1() + x2()) / 2;
    int auxY = (y1() + y2()) / 2;

    setLine(auxX-x1(), auxY-y1(), auxX-x2(), auxY-y2());
    setLine((x1()*qCos(teta)-(y1()*qSin(teta))), (x1()*qSin(teta)+(y1()*qCos(teta))), (x2()*qCos(teta)-(y2()*qSin(teta))), (x2()*qSin(teta)+(y2()*qCos(teta))));
    setLine(x1()+auxX, y1()+auxY, x2()+auxX, y2()+auxY);
}
