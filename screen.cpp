#include <iostream>
#include <QPainter>
#include <QDebug>
#include "screen.h"
#include "border.h"
using namespace std;

void Screen::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);  
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 2));

    Border border(getWidth(), getHeight(), getCenter());

    cout << "\n painting loop" << endl;
    for (int i = 0; i < list.size(); i++)
    {
        painter.setPen(QPen(list[i]->getColor(), 2));
        list[i]->normalize(getWidth(), getHeight(), getCenter());
        list[i]->clipping(border); 
        list[i]->transformToViewport(getCenter());
        list[i]->draw(painter);
    }
}

void Screen::setWidth(int width) 
{
    this->width = width;
}

void Screen::setHeight(int height) 
{
    this->height = height;
}

void Screen::setCenter(pair<float, float> center) 
{
    this->center.first = center.first; 
    this->center.second = center.second;
}
