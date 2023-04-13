#include "object.h"
#include <iostream>
using namespace std;

void Object::draw(QPainter &painter)
{
    
    // cout << normalizePointsList.size() << endl;
    // for(qsizetype i = 0; i < normalizePointsList.size(); i++){
    //     if(i == pointsList.size() - 1) {
    //         painter.drawLine(normalizePointsList[i].first, normalizePointsList[i].second,
    //                      normalizePointsList[0].first, normalizePointsList[0].second);
    //         continue;
    //     }

    //     painter.drawLine(normalizePointsList[i].first, normalizePointsList[i].second,
    //                      normalizePointsList[i+1].first, normalizePointsList[i+1].second);
    // }
    
    
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

void Object::normalize(int viewportWidth, int viewportHeight)
{
    int windowWidth = 854;
    int windowHeight = 480;
    normalizePointsList.erase(normalizePointsList.begin(),normalizePointsList.end());
    float newX = 0.0;
    float newY = 0.0;
    for(qsizetype i = 0; i < pointsList.size(); i++){
        newX = linearInterpolation(pointsList[i].first, 0, windowWidth, -1, 1);
        newY = linearInterpolation(pointsList[i].second, 0, windowHeight, -1, 1);
        normalizePointsList.append(pair<float, float>(newX, newY));
        transformToViewport(viewportWidth, viewportHeight);
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

float Object::linearInterpolation(float x, float x0, float x1, float y0, float y1) {
    return y0 + ((y1 - y0) / (x1 - x0)) * (x - x0);
}

void Object::rotateWorld(float teta)
{
    pair<float, float> center = barycenter();

    float radians = qDegreesToRadians(teta);
    for(qsizetype i = 0; i < pointsList.size(); i++){
        pointsList[i] = pair<float, float>(pointsList[i].first * qCos(radians) - (pointsList[i].second * qSin(radians)), 
                                        pointsList[i].first * qSin(radians) + (pointsList[i].second * qCos(radians)));
    }

}

void Object::transformToViewport(int width, int height){
    int windowWidth = 854; //viewport
    int windowHeight = 480;
    for(qsizetype i = 0; i < normalizePointsList.size(); i++){
        normalizePointsList[i].first = (normalizePointsList[i].first / windowWidth) * width;
        normalizePointsList[i].second = 1 - (normalizePointsList[i].second / windowHeight) * height;
    }
}