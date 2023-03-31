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
    QList<pair<int,int>> points;

    points.append(pair<int, int>(210, 210));
    points.append(pair<int, int>(410, 210));
    points.append(pair<int, int>(410, 410));
    points.append(pair<int, int>(210, 410));
    list.append(new Rect(QString("Retangulo Vermelho"), QList(points), Qt::red));
    points.clear();


    points.append(pair<int, int>(110, 110));
    points.append(pair<int, int>(150, 180));
    points.append(pair<int, int>(360, 200));
    points.append(pair<int, int>(450, 150));
    list.append(new Rect(QString("Poligono Cyano"), QList(points), Qt::cyan));
    points.clear();

    points.append(pair<int, int>(500, 300));
    points.append(pair<int, int>(900, 100));
    list.append(new Line(QString("Linha Verde"), QList(points), Qt::green));
    points.clear();


    points.append(pair<int, int>(120, 120));
    list.append(new Point(QString("Ponto Branco"), QList(points), Qt::white));
    points.clear();

    points.append(pair<int, int>(-900, 100));
    points.append(pair<int, int>(-900, 200));
    points.append(pair<int, int>(100, 200));
    points.append(pair<int, int>(100, 100));

    list.append(new Rect(QString("Retangulo Amarelo"), QList(points), Qt::yellow));
    points.clear();

    return list;
};
