#include "point.h"
#include <iostream>
using namespace std;

void Point::draw(QPainter &painter)
{
    painter.drawPoint(pointsList[0].first, pointsList[0].second);
    cout << "passou aqui-> Point::draw" << endl;
}

void Point::translation(int dx, int dy)
{
    pointsList[0] = pair<int, int>(pointsList[0].first + dx, pointsList[0].second + dy);
}

void Point::scale(float px, float py)
{
    
}

void Point::rotation(int teta)
{
    
}