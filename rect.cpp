#include "rect.h"
#include <iostream>
#include <QtMath>

using namespace std;

void Rect::translate(float dx, float dy)
{
    for(qsizetype i = 0; i < pointsList.size(); i++){
            pointsList[i] = pair<float, float>(pointsList[i].first + dx, pointsList[i].second + dy);
    }
}

void Rect::scale(float factor)
{
    pair<float, float> center = barycenter();
    translate(-center.first, -center.second);
    factor = factor/100;
    factor = 1 + factor;

    for(qsizetype i = 0; i < pointsList.size(); i++){
        pointsList[i] = pair<float, float>(pointsList[i].first * factor, pointsList[i].second * factor);
    }
    translate(center.first, center.second);
}

void Rect::rotate(float teta)
{
    pair<float, float> center = barycenter();
    translate(-center.first, -center.second);

    float radians = qDegreesToRadians(teta);
    for(qsizetype i = 0; i < pointsList.size(); i++){
        pointsList[i] = pair<float, float>(pointsList[i].first * qCos(radians) - (pointsList[i].second * qSin(radians)), 
                                        pointsList[i].first * qSin(radians) + (pointsList[i].second * qCos(radians)));
    }

    translate(center.first, center.second);
}
    
void Rect::clipping(Border border)
{  
    regionCodeGenerate(border);
     cout << "Polygon -> Clipping" << endl;
    
    // regionCodeList e normalizePointsList são listas com relação de 1 pra 1, o mesmo indice pode ser utilizado por ambas
    for (qsizetype i = 0; i < regionCodeList.size(); i++)
    {        
        if (i == regionCodeList.size() - 1)
        {
            lineClipping(border, i, 0);
            break;           
        }

        lineClipping(border, i, i + 1);
    }
}

/*
void Rect::transformWindow(float windowX,float windowY)
{
    double aux, x2, y2;

    getCoords(&aux, &aux, &x2, &y2);
    setCoords(x() - windowX, y() - windowY, x2 - windowX, y2 - windowY);
}

void Rect::transformViewport(float viewHeight, float viewWidth)
{
    double aux, x2, y2;

    getCoords(&aux, &aux, &x2, &y2);
    setCoords(((x() + 1) / 2) * viewWidth, (1 - ((y() + 1) / 2)) * viewHeight, ((x2 + 1) / 2) * viewWidth, (1 - ((y2 + 1) / 2)) * viewHeight);
}
*/
