#include "point.h"
#include <iostream>
using namespace std;

void Point::draw(QPainter &painter)
{
    painter.drawPoint(pointsList[0].first, pointsList[0].second);
    cout << "passou aqui-> Point::draw" << endl;
}