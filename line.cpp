#include "line.h"
#include <iostream>
using namespace std;

void Line::draw(QPainter &painter)
{
    painter.drawLine(pointsList[0].first, pointsList[0].second,
                     pointsList[1].first, pointsList[1].second);
    cout << "pasosu aqui-> Line::draw" << endl;
}

pair<float, float> Line::barycenter()
{
    pair<float, float> center;
    center.first = ((pointsList[0].first + pointsList[1].first) / 2);
    center.second = ((pointsList[0].second + pointsList[1].second) / 2);

    return center;
}

void Line::translate(float dx, float dy)
{
    pointsList[0] = pair<float, float>(pointsList[0].first + dx, pointsList[0].second + dy);
    pointsList[1] = pair<float, float>(pointsList[1].first + dx, pointsList[1].second + dy);
}

void Line::scale(float factor)
{
    pair<float, float> center = barycenter();
    translate(-center.first, -center.second);
    factor = 1 + factor;
    pointsList[0] = pair<float, float>(pointsList[0].first * factor, pointsList[0].second * factor);
    pointsList[1] = pair<float, float>(pointsList[1].first * factor, pointsList[1].second * factor);
    translate(center.first, center.second);
}

void Line::rotate(float teta)
{   /*
    pair<float, float> center = barycenter();
    translate(-center.first, -center.second);
    factor = 1 + factor;
    pointsList[0] = pair<float, float>(pointsList[0].first * factor, pointsList[0].second * factor);
    pointsList[1] = pair<float, float>(pointsList[1].first * factor, pointsList[1].second * factor);
    translate(center.first, center.second);

    setLine(auxX-x1(), auxY-y1(), auxX-x2(), auxY-y2());
    setLine((x1()*qCos(teta)-(y1()*qSin(teta))), (x1()*qSin(teta)+(y1()*qCos(teta))), (x2()*qCos(teta)-(y2()*qSin(teta))), (x2()*qSin(teta)+(y2()*qCos(teta))));
    setLine(x1()+auxX, y1()+auxY, x2()+auxX, y2()+auxY);
    */
}

/*
void Line::adjust(float dx, float dy)
{
    translate(dx,dy);
}

void Line:: transformWindow(float windowX,float windowY)
{
    setLine(x1() - windowX,y1() - windowY, x2() - windowX, y2() - windowY);
}

void Line::normalize(float windowHeight, float windowWidth)
{
    setLine(x1() / windowWidth, y1() / windowHeight, x2() / windowWidth, y2() / windowHeight);
}

void Line::transformViewport(float viewHeight, float viewWidth)
{
    setLine(((x1() + 1) / 2) * viewWidth, (1 - ((y1() + 1) / 2)) * viewHeight, ((x2() + 1) / 2) * viewWidth, (1 - ((y2() + 1) / 2)) * viewHeight);
}

*/

