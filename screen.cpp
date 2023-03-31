#include <iostream>
#include <QPainter>
#include <QDebug>
#include "screen.h"
using namespace std;

Screen::Screen(QWidget *parent)
    : QFrame{parent}
{
    
}


void Screen::setObjectList(QList<Object*> list) {
    this->list = list; 
}

QList<Object*> Screen::getObjectList() {
    return this->list; 
}

void Screen::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 2));

    for (int i = 0; i < list.size(); i++)
    {
        painter.setPen(QPen(list[i]->getColor(), 2));
        printf(" %d \n", i);
        list[i]->draw(painter);
    }
}

