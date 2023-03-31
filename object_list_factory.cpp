#include <QList>
#include "object_list_factory.h"
#include "object.h"
#include "point.h"
#include "line.h"
#include "rect.h"

using namespace std;

QList<Object*> ObjectListFactory::createObjectList()
{
    QList<Object*> list;
    QList<pair<float,float>> points;

    points.append(pair<float, float>(210, 210));
    points.append(pair<float, float>(410, 210));
    points.append(pair<float, float>(410, 410));
    points.append(pair<float, float>(210, 410));
    list.append(new Rect(QString("Retangulo Vermelho"), QList(points), Qt::red));
    points.clear();


    points.append(pair<float, float>(110, 110));
    points.append(pair<float, float>(150, 180));
    points.append(pair<float, float>(360, 200));
    points.append(pair<float, float>(450, 150));
    list.append(new Rect(QString("Poligono Cyano"), QList(points), Qt::cyan));
    points.clear();

    points.append(pair<float, float>(500, 300));
    points.append(pair<float, float>(900, 100));
    list.append(new Line(QString("Linha Verde"), QList(points), Qt::green));
    points.clear();


    points.append(pair<float, float>(120, 120));
    list.append(new Point(QString("Ponto Branco"), QList(points), Qt::white));
    points.clear();

    points.append(pair<float, float>(-900, 100));
    points.append(pair<float, float>(-900, 200));
    points.append(pair<float, float>(100, 200));
    points.append(pair<float, float>(100, 100));

    list.append(new Rect(QString("Retangulo Amarelo"), QList(points), Qt::yellow));
    points.clear();

    return list;
};
