#include "main_frame.h"
#include <QPainter>
#include <iostream>
#include <QDebug>

using namespace std;

#include "object.h"
#include "point.h"
#include "line.h"
#include "rect.h"
#include "window.h"

Main_frame::Main_frame(QWidget *parent)
    : QFrame{parent}
{
    QList<pair<int,int>> points;

    polygonCheckBox = new QCheckBox("Checkbox Text", this);
    polygonCheckBox->setChecked(false);

    points.append(pair<int, int>(200, 200));
    points.append(pair<int, int>(400, 200));
    points.append(pair<int, int>(400, 400));
    points.append(pair<int, int>(400, 200));
    list.append(new Rect(QString("Retangulo-001"), QList(points), Qt::red));
    points.clear();


    points.append(pair<int, int>(100, 100));
    points.append(pair<int, int>(100, 200));
    points.append(pair<int, int>(400, 200));
    points.append(pair<int, int>(400, 100));
    list.append(new Rect(QString("Retangulo-002"), QList(points), Qt::cyan));
    points.clear();

    points.append(pair<int, int>(500, 100));
    points.append(pair<int, int>(900, 100));
    list.append(new Line(QString("Linha-001"), QList(points), Qt::green));
    points.clear();


    points.append(pair<int, int>(12000, 12000));
    list.append(new Point(QString("Ponto-01"), QList(points), Qt::white));
    points.clear();

    points.append(pair<int, int>(-900, 100));
    points.append(pair<int, int>(-900, 200));
    points.append(pair<int, int>(100, 200));
    points.append(pair<int, int>(100, 100));
    
    list.append(new Rect(QString("Retangulo-03"), QList(points), Qt::yellow));
    points.clear();
}

void Main_frame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 2));

    for (int i = 0; i < list.size(); i++)
    {
        painter.setPen(QPen(list[i]->getColor(), 2));
        printf(" %d \n", i);
        list[i]->draw(painter);
        list[i]->getName();
    }
}


