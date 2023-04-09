#include "object.h"
#include <iostream>
using namespace std;

void Object::draw(QPainter &painter)
{
    /*    
    for(qsizetype i = 0; i < nPointsList.size(); i++){
        if(i == pointsList.size() - 1) {
            painter.drawLine(normalizePointsList[i].first, normalizePointsList[i].second,
                         normalizePointsList[0].first, normalizePointsList[0].second);
            continue;
        }

        painter.drawLine(normalizePointsList[i].first, normalizePointsList[i].second,
                         normalizePointsList[i+1].first, normalizePointsList[i+1].second);
    }
    */
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

void Object::normalize(int width, int height)
{
    for(qsizetype i = 0; i < normalizePointsList.size(); i++){
        normalizePointsList[i].first = pointsList[i].first/width;
        normalizePointsList[i].second = pointsList[i].second/height;
    }
}

pair<float, float> Object::barycenter()
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
