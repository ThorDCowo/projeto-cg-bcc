#include <iostream>
#include <QPainter>
#include <QDebug>
#include "screen.h"
using namespace std;

Screen::Screen(QWidget *parent)
    : QFrame{parent}
{
    
}

void Screen::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 2));

    for (int i = 0; i < list.size(); i++)
    {
        painter.setPen(QPen(list[i]->getColor(), 2));
        list[i]->normalize(getWidth(), getHeight());
        list[i]->transformToViewport(getCenter());
        list[i]->draw(painter);
    }
}

