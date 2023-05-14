#include <QList>
#include "object_list_factory.h"
#include "object.h"
#include "point.h"
#include "line.h"
#include "polygon.h"

using namespace std;

QList<Object*> ObjectListFactory::createObjectList()
{
    QList<Object*> list;
    QList<pair<float,float>> points;

    //Coordenadas de Mundo
//    points.append(pair<float, float>(210, 210));
//    points.append(pair<float, float>(410, 210));
//    points.append(pair<float, float>(410, 410));
//    points.append(pair<float, float>(210, 410));
//    list.append(new Rect(QString("Retangulo Vermelho"), QList(points), Qt::red));
//    points.clear();

//    points.append(pair<float, float>(110, 110));
//    points.append(pair<float, float>(150, 180));
//    points.append(pair<float, float>(360, 200));
//    points.append(pair<float, float>(450, 150));
//    list.append(new Rect(QString("Poligono Cyano"), QList(points), Qt::cyan));
//    points.clear();

//    points.append(pair<float, float>(500, 300));
//    points.append(pair<float, float>(900, 200));
//    list.append(new Line(QString("Linha Verde"), QList(points), Qt::green));
//    points.clear();

//    points.append(pair<float, float>(120, 120));
//    list.append(new Point(QString("Ponto Branco"), QList(points), Qt::white));
//    points.clear();

//    points.append(pair<float, float>(-900, 100));
//    points.append(pair<float, float>(-900, 200));
//    points.append(pair<float, float>(100, 200));
//    points.append(pair<float, float>(100, 100));

//    list.append(new Rect(QString("Retangulo Amarelo"), QList(points), Qt::yellow));
//    points.clear();

//    points.append(pair<float, float>(60, 190));
//    points.append(pair<float, float>(130, 110));
//    points.append(pair<float, float>(20, 90));
//    points.append(pair<float, float>(20, 70));
//    points.append(pair<float, float>(60, 170));
//    points.append(pair<float, float>(50, 70));
//    points.append(pair<float, float>(80, 40));

//    list.append(new Rect(QString("Poligono Branco"), QList(points), Qt::white));
//    points.clear();

    // points.append(pair<float, float>(600, 100));
    // points.append(pair<float, float>(650, 50));
    // points.append(pair<float, float>(700, 100));
    // points.append(pair<float, float>(600, 100));
    // points.append(pair<float, float>(600, 200));
    // points.append(pair<float, float>(700, 200));
    // points.append(pair<float, float>(700, 100));

    // list.append(new Rect(QString("Casa"), QList(points), Qt::magenta));
    // points.clear();

    // points.append(pair<float, float>(50, 200));
    // points.append(pair<float, float>(150, -100));

    // list.append(new Rect(QString("Linha"), QList(points), Qt::blue));
    // points.clear();  

    points.append(pair<float, float>(500, 200));
    points.append(pair<float, float>(350, 100));

    list.append(new Line(QString("Linha Dentro"), QList(points), Qt::blue));
    points.clear();

    points.append(pair<float, float>(100, 100));
    points.append(pair<float, float>(-100, -100));

    list.append(new Line(QString("Linha Parcilmente Dentro"), QList(points), Qt::white));
    points.clear();

    points.append(pair<float, float>(200, 200));
    points.append(pair<float, float>(400, 200));

    list.append(new Line(QString("Linha Horizontal"), QList(points), Qt::red));
    points.clear();

    points.append(pair<float, float>(500, 100));
    points.append(pair<float, float>(500, 200));

    list.append(new Line(QString("Linha Vertical"), QList(points), Qt::green));
    points.clear();

    points.append(pair<float, float>(400, 200));
    points.append(pair<float, float>(500, 300));

    list.append(new Line(QString("Linha Diagonal"), QList(points), Qt::magenta));
    points.clear();

    points.append(pair<float, float>(-200, 200));
    points.append(pair<float, float>(-350, 100));

    list.append(new Line(QString("Linha Diagonal Fora"), QList(points), Qt::yellow));
    points.clear();

    points.append(pair<float, float>(1000, 100));
    points.append(pair<float, float>(900,-100));

    list.append(new Line(QString("Linha Diagonal Fora"), QList(points), Qt::cyan));
    points.clear();

    points.append(pair<float, float>(355, 923));
    points.append(pair<float, float>(-352, 441));

    list.append(new Line(QString("G - H"), QList(points), Qt::magenta));
    points.clear();

    // points.append(pair<float, float>(-50, 200));
    // points.append(pair<float, float>(-150, -100));

    // list.append(new Line(QString("Linha Fora"), QList(points), Qt::blue));
    // points.clear();

    // points.append(pair<float, float>(625, 250));
    // points.append(pair<float, float>(625, 150));
    // points.append(pair<float, float>(675, 150));
    // points.append(pair<float, float>(675, 250));

    // list.append(new Rect(QString("Porta"), QList(points), Qt::magenta));
    // points.clear();

    // points.append(pair<float, float>(625, 115));
    // points.append(pair<float, float>(625, 130));
    // points.append(pair<float, float>(640, 130));
    // points.append(pair<float, float>(640, 115));

    // list.append(new Rect(QString("Janela"), QList(points), Qt::magenta));
    // points.clear();

    // points.append(pair<float, float>(660, 115));
    // points.append(pair<float, float>(660, 130));
    // points.append(pair<float, float>(675, 130));
    // points.append(pair<float, float>(675, 115));

    // list.append(new Rect(QString("Janela 2"), QList(points), Qt::magenta));
    // points.clear();

    // points.append(pair<float, float>(1200, 200));
    // points.append(pair<float, float>(1300, 100));
    // points.append(pair<float, float>(1400, 200));
    // points.append(pair<float, float>(1200, 200));
    // points.append(pair<float, float>(1200, 400));
    // points.append(pair<float, float>(1400, 400));
    // points.append(pair<float, float>(1400, 200));

    // list.append(new Rect(QString("Casa Fora"), QList(points), Qt::blue));
    // points.clear();

    return list;
};
