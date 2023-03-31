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

    return list;
};
