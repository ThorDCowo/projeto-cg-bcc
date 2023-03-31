#include "point.h"
#include <iostream>
using namespace std;

void Point::draw(QPainter &painter)
{
    painter.drawPoint(pointsList[0].first, pointsList[0].second);
    cout << "passou aqui-> Point::draw" << endl;
}

void Point::translate(float dx, float dy)
{
    pointsList[0] = pair<float, float>(pointsList[0].first + dx, pointsList[0].second + dy);
}

void Point::scale(float factor)
{

}

void Point::rotate(float teta)
{
    
}