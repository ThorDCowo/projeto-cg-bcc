#include <iostream>
#include <QPainter>
#include <QDebug>
#include "screen.h"
#include "core/entities/object.h"
using namespace std;

void Screen::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);  
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 2));

    //cout << "\n painting loop" << endl;
    for (int i = 0; i < list.size(); i++)
    {
        painter.setPen(QPen(list[i]->getColor(), 2));
        list[i]->drawEdges(painter);
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

void Screen::setCenter(Coordinate center) 
{
    this->center.x = center.x; 
    this->center.y = center.y;
}
