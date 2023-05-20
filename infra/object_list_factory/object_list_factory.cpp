#include <QList>
#include "object_list_factory.h"
#include "../../core/entities/object.h"
#include "../../core/entities/point.h"
#include "../../core/entities/line.h"
#include "../../core/entities/polygon.h"

using namespace std;

QList<Object*> ObjectListFactory::createObjectList()
{
    QList<Object*> list;
    QList<Coordinate> points;

    //  points.append(Coordinate(108.97, 83.46, 68.12));
    //  points.append(Coordinate(108.97, 83.46, 179.45));
    //  points.append(Coordinate(108.97, 194.79, 68.12));
    //  points.append(Coordinate(108.97, 194.79, 179.45));
    //  points.append(Coordinate(179.45, 83.46, 68.12));
    //  points.append(Coordinate(179.45, 83.46, 179.45));
    //  points.append(Coordinate(179.45, 194.79, 68.12));
    //  points.append(Coordinate(179.45, 194.79, 179.45));

    //  list.append(new Polygon(QString("Cubo com arestas vermelhas"), QList(points), Qt::red));
    //  points.clear();
    
//    points.append(Coordinate(50, 50, 50));
//    points.append(Coordinate(50, 50, 200));
//    points.append(Coordinate(50, 200, 200));
//    points.append(Coordinate(50, 200, 50));
//    points.append(Coordinate(200, 50, 50));
//    points.append(Coordinate(200, 50, 200));
//    points.append(Coordinate(200, 200, 50));
//    points.append(Coordinate(200, 200, 200));

//    list.append(new Polygon(QString("Cubo com arestas vermelhas"), QList(points), Qt::red));
//    points.clear();

    // points.append(Coordinate(0, 83.19, 166.81));
    // points.append(Coordinate(83.19, 166.81, 0));
    // points.append(Coordinate(83.19, 0, 166.81));
    // points.append(Coordinate(166.81, 0, 83.19));
    // points.append(Coordinate(33.19, 200, 116.81));
    // points.append(Coordinate(200, 83.19, 166.81));
    // points.append(Coordinate(200, 116.81, 33.19));
    // points.append(Coordinate(200, 33.19, 116.81));
    // points.append(Coordinate(116.81, 200, 33.19));
    // points.append(Coordinate(116.81, 33.19, 200));
    // points.append(Coordinate(166.81, 200, 83.19));
    // points.append(Coordinate(33.19, 166.81, 200));

    // list.append(new Polygon(QString("Dodecaedro verde"), QList(points), Qt::green));
    // points.clear();    

    points.append(Coordinate(200.0, 200.0, 0.0));
    points.append(Coordinate(400.0, 200.0, 0.0));
    points.append(Coordinate(400.0, 350.0, 0.0));
    points.append(Coordinate(200.0, 350.0, 0.0));
    points.append(Coordinate(300.0, 450.0, 250.0));

    list.append(new Polygon(QString("Piramide verde"), QList(points), Qt::green));
    points.clear();    
  

//Coordenadas de Mundo
//    x = 100;
//    y = 200;
//    z = 200;
//    points.append(x, y, z);
//    points.append(100, 200, 300);


//    points.append(Coordinate(410, 210, 0));
//    points.append(Coordinate(410, 210, 0));
//    points.append(Coordinate(410, 410, 0));
//    points.append(Coordinate(210, 410, 0));
//    list.append(new Polygon(QString("Retangulo Vermelho"), QList(points), Qt::red));
//    points.clear();

//    points.append(Coordinate(110, 110, 0));
//    points.append(Coordinate(150, 180, 0));
//    points.append(Coordinate(360, 200, 0));
//    points.append(Coordinate(450, 150, 0));
//    list.append(new Polygon(QString("Poligono Cyano"), QList(points), Qt::cyan));
//    points.clear();

//    points.append(Coordinate(500, 300, 0));
//    points.append(Coordinate(900, 200, 0));
//    list.append(new Line(QString("Linha Verde"), QList(points), Qt::green));
//    points.clear();

//    points.append(Coordinate(120, 120, 0));
//    list.append(new Point(QString("Ponto Branco"), QList(points), Qt::white));
//    points.clear();

//    points.append(Coordinate(-900, 100, 0));
//    points.append(Coordinate(-900, 200, 0));
//    points.append(Coordinate(100, 200, 0));
//    points.append(Coordinate(100, 100, 0));

//    list.append(new Polygon(QString("Retangulo Amarelo"), QList(points), Qt::yellow));
//    points.clear();

//    points.append(Coordinate(60, 190, 0));
//    points.append(Coordinate(130, 110, 0));
//    points.append(Coordinate(20, 90, 0));
//    points.append(Coordinate(20, 70, 0));
//    points.append(Coordinate(60, 170, 0));
//    points.append(Coordinate(50, 70, 0));
//    points.append(Coordinate(80, 40, 0));

//    list.append(new Polygon(QString("Poligono Branco"), QList(points), Qt::white));
//    points.clear();

    // points.append(Coordinate(600, 100, 0));
    // points.append(Coordinate(650, 50, 0));
    // points.append(Coordinate(700, 100, 0));
    // points.append(Coordinate(600, 100, 0));
    // points.append(Coordinate(600, 200, 0));
    // points.append(Coordinate(700, 200, 0));
    // points.append(Coordinate(700, 100, 0));

    // list.append(new Polygon(QString("Casa"), QList(points), Qt::magenta));
    // points.clear();

    // points.append(Coordinate(50, 200, 0));
    // points.append(Coordinate(150, -100, 0));

    // list.append(new Polygon(QString("Linha"), QList(points), Qt::blue));
    // points.clear();  

//    points.append(Coordinate(500, 200, 0));
//    points.append(Coordinate(350, 100, 0));

//    list.append(new Line(QString("Linha Dentro"), QList(points), Qt::blue));
//    points.clear();

//    points.append(Coordinate(100, 100, 0));
//    points.append(Coordinate(-100, -100, 0));

//    list.append(new Line(QString("Linha Parcilmente Dentro"), QList(points), Qt::white));
//    points.clear();

//    points.append(Coordinate(200, 200, 0));
//    points.append(Coordinate(400, 200, 0));

//    list.append(new Line(QString("Linha Horizontal"), QList(points), Qt::red));
//    points.clear();

//    points.append(Coordinate(500, 100, 0));
//    points.append(Coordinate(500, 200, 0));

//    list.append(new Line(QString("Linha Vertical"), QList(points), Qt::green));
//    points.clear();

//    points.append(Coordinate(400, 200, 0));
//    points.append(Coordinate(500, 300, 0));

//    list.append(new Line(QString("Linha Diagonal"), QList(points), Qt::magenta));
//    points.clear();

//    points.append(Coordinate(-200, 200, 0));
//    points.append(Coordinate(-350, 100, 0));

//    list.append(new Line(QString("Linha Diagonal Fora"), QList(points), Qt::yellow));
//    points.clear();

//    points.append(Coordinate(1000, 100, 0));
//    points.append(Coordinate(900,-100, 0));

//    list.append(new Line(QString("Linha Diagonal Fora"), QList(points), Qt::cyan));
//    points.clear();

//    points.append(Coordinate(355, 923, 0));
//    points.append(Coordinate(-352, 441, 0));

//    list.append(new Line(QString("G - H"), QList(points), Qt::magenta));
//    points.clear();

    // points.append(Coordinate(-50, 200, 0));
    // points.append(Coordinate(-150, -100, 0));

    // list.append(new Line(QString("Linha Fora"), QList(points), Qt::blue));
    // points.clear();

//     points.append(Coordinate(625, 250, 100));
//     points.append(Coordinate(625, 150, 100));
//     points.append(Coordinate(675, 150, 10));
//     points.append(Coordinate(675, 250, 10));

//     list.append(new Polygon(QString("Porta"), QList(points), Qt::magenta));
//     points.clear();

    // points.append(Coordinate(625, 115));
    // points.append(Coordinate(625, 130));
    // points.append(Coordinate(640, 130));
    // points.append(Coordinate(640, 115));

    // list.append(new Polygon(QString("Janela"), QList(points), Qt::magenta));
    // points.clear();

    // points.append(Coordinate(660, 115, 0));
    // points.append(Coordinate(660, 130,0));
    // points.append(Coordinate(675, 115, 0));
    // points.append(Coordinate(675, 130,0));

    // list.append(new Polygon(QString("Janela 2"), QList(points), Qt::magenta));
    // points.clear();

    // points.append(Coordinate(1200, 200));
    // points.append(Coordinate(1300, 100));
    // points.append(Coordinate(1400, 200));
    // points.append(Coordinate(1200, 200));
    // points.append(Coordinate(1200, 400));
    // points.append(Coordinate(1400, 400));
    // points.append(Coordinate(1400, 200));

    // list.append(new Polygon(QString("Casa Fora"), QList(points), Qt::blue));
    // points.clear();

    return list;
};
