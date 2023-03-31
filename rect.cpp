#include "rect.h"
#include <iostream>
#include <QtMath>

using namespace std;

void Rect::draw(QPainter &painter)
{
    
    // painter.drawLine(pointsList[0].first, pointsList[0].second,
    //                  pointsList[1].first, pointsList[1].second);
    // painter.drawLine(pointsList[1].first, pointsList[1].second,
    //                  pointsList[2].first, pointsList[2].second);
    // painter.drawLine(pointsList[2].first, pointsList[2].second,
    //                  pointsList[3].first, pointsList[3].second);
    // painter.drawLine(pointsList[3].first, pointsList[3].second,
    //                  pointsList[0].first, pointsList[0].second);
    
    for(qsizetype i = 0; i < pointsList.size(); i++){
        if(i == pointsList.size() - 1) {
            painter.drawLine(pointsList[i].first, pointsList[i].second,
                         pointsList[0].first, pointsList[0].second);
            continue;
        }

        painter.drawLine(pointsList[i].first, pointsList[i].second,
                         pointsList[i+1].first, pointsList[i+1].second);
    }
}

pair<float, float> Rect::barycenter()
{
    pair<float, float> center;
    
    for(qsizetype i = 0; i < pointsList.size(); i++){
        center.first += pointsList[i].first;
        center.second += pointsList[i].second;
    }
    center.first = (center.first / pointsList.size());
    center.second = (center.second / pointsList.size());

    return center;
}

void Rect::translate(float dx, float dy)
{
    for(qsizetype i = 0; i < pointsList.size(); i++){
        pointsList[i] = pair<float, float>(pointsList[i].first + dx, pointsList[i].second + dy);
    }
}

void Rect::scale(float factor)
{
    pair<float, float> center = barycenter();
    translate(-center.first, -center.second);
    factor = 1 + factor;

    for(qsizetype i = 0; i < pointsList.size(); i++){
        pointsList[i] = pair<float, float>(pointsList[i].first * factor, pointsList[i].second * factor);
    }
    translate(center.first, center.second);
}

void Rect::rotate(float teta)
{
    /*
    double aux, x2, y2;
    getCoords(&aux, &aux, &x2, &y2);

    float auxX = (x() + x2) / 2;
    float auxY = (y() + y2) / 2;

    setCoords(auxX-x(), auxY-y(), auxX-x2, auxY-y2);
    //cout << qRadiansToDegrees(qSin(teta));
    setCoords((x()*qRadiansToDegrees(qCos(teta))-(y()*qRadiansToDegrees(qSin(teta)))), (x()*qRadiansToDegrees(qSin(teta))+(y()*qRadiansToDegrees(qCos(teta)))), (x2*qRadiansToDegrees(qCos(teta))-(y2*qRadiansToDegrees(qSin(teta)))), (x2*qRadiansToDegrees(qSin(teta))+(y2*qRadiansToDegrees(qCos(teta)))));
    setCoords(x()+auxY, y()+auxX, x2+auxY, y2+auxX);
    */
}

/*
void Rect::ajusta(float dx, float dy)
{
    adjust(dx,dy,dx,dy);
}

void Rect::transformWindow(float windowX,float windowY)
{
    double aux, x2, y2;

    getCoords(&aux, &aux, &x2, &y2);
    setCoords(x() - windowX, y() - windowY, x2 - windowX, y2 - windowY);
}

void Rect::normalize(float windowHeight, float windowWidth)
{
    double aux, x2, y2;

    getCoords(&aux, &aux, &x2, &y2);
    setCoords(x() / windowWidth, y() / windowHeight, x2 / windowWidth, y2 / windowHeight);
}

void Rect::transformViewport(float viewHeight, float viewWidth)
{
    double aux, x2, y2;

    getCoords(&aux, &aux, &x2, &y2);
    setCoords(((x() + 1) / 2) * viewWidth, (1 - ((y() + 1) / 2)) * viewHeight, ((x2 + 1) / 2) * viewWidth, (1 - ((y2 + 1) / 2)) * viewHeight);
}

*/
