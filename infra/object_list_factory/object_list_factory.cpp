#include <QList>
#include "object_list_factory.h"
#include "../../core/entities/object.h"
#include "../../core/entities/point.h"
#include "../../core/entities/line.h"
#include "../../core/entities/polygon.h"
#include <string.h>

using namespace std;

QList<Object*> ObjectListFactory::createObjectList()
{
    QList<Object*> list;
    QList<Coordinate> points;
    QList<pair<qsizetype, qsizetype>> edges;

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

    // points.append(Coordinate(200.0, 200.0, 0.0));
    // points.append(Coordinate(400.0, 200.0, 0.0));
    // points.append(Coordinate(400.0, 350.0, 0.0));
    // points.append(Coordinate(200.0, 350.0, 0.0));
    // points.append(Coordinate(300.0, 275.0, 250.0));

    // list.append(new Polygon(QString("Piramide verde"), QList(points), Qt::green));
    // points.clear();    

    // points.append(Coordinate(200.0, 200.0, 0.0));
    // points.append(Coordinate(400.0, 200.0, 0.0));
    // points.append(Coordinate(400.0, 400.0, 0.0));
    // points.append(Coordinate(200.0, 400.0, 0.0));
    // points.append(Coordinate(200.0, 200.0, 0.0));
    // points.append(Coordinate(300.0, 275.0, 250.0));
    // points.append(Coordinate(400.0, 200.0, 0.0));
    // points.append(Coordinate(400.0, 400.0, 0.0));
    // points.append(Coordinate(300.0, 275.0, 250.0));
    // points.append(Coordinate(200.0, 400.0, 0.0));

    // list.append(new Polygon(QString("Piramide vermelha"), QList(points), Qt::red));
    // points.clear();    

    // points.append(Coordinate(0.0, 0.0, 0.0));
    // points.append(Coordinate(427.0, 0.0, 0.0));
    // points.append(Coordinate(427.0, 240.0, 0.0));
    // points.append(Coordinate(0.0, 240.0, 0.0));

    // points.append(Coordinate(0.0, 0.0, 0.0));
    // points.append(Coordinate(0.0, 0.0, 240.0));
    // points.append(Coordinate(427.0, 0.0, 240.0));
    // points.append(Coordinate(427.0, 0.0, 0.0));

    // points.append(Coordinate(427.0, 240.0, 0.0));
    // points.append(Coordinate(427.0, 240.0, 240.0));
    
    // points.append(Coordinate(427.0, 0.0, 240.0));
    // points.append(Coordinate(427.0, 240.0, 240.0));

    // points.append(Coordinate(0.0, 240.0, 240.0));
    // points.append(Coordinate(0.0, 0.0, 240.0));
    
    // points.append(Coordinate(0.0, 240.0, 240.0));
    // points.append(Coordinate(0.0, 240.0, 0.0));

    // list.append(new Polygon(QString("Cubo azul"), QList(points), Qt::blue));
    // points.clear();

    points.append(Coordinate(0.0, 0.0, 0.0));
    points.append(Coordinate(0.0, 150.0, 0.0));
    points.append(Coordinate(0.0, 0.0, 150.0));
    points.append(Coordinate(0.0, 150.0, 150.0));
    points.append(Coordinate(200.0, 0.0, 0.0));
    points.append(Coordinate(200.0, 150.0, 0.0));
    points.append(Coordinate(200.0, 0.0, 150.0));
    points.append(Coordinate(200.0, 150.0, 150.0));

    edges.append({0,1});
    edges.append({1,2});
    edges.append({2,3});
    edges.append({3,0});
    edges.append({4,5});
    edges.append({5,6});
    edges.append({6,7});
    edges.append({7,4});
    edges.append({0,4});
    edges.append({1,5});
    edges.append({2,6});
    edges.append({3,7});

    list.append(new Polygon(QString("Cubo vermelho"), QList(points), QList(edges), Qt::red));

    // cout << "Points / Edges" << endl;
    // cout << points[1].toString() << endl;
    // cout << edges[0].first << "," << edges[0].second << endl;
    // cout << "-------------------" << endl;

    points.clear();
    edges.clear();
    
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

//    points.append(Coordinate(400.0, 200.0, 0.0));
//    points.append(Coordinate(500.0, 300.0, 0.0));

//    list.append(new Line(QString("Linha Diagonal"), QList(points), Qt::magenta));
//    points.clear();

//     points.append(Coordinate(450.0, 220.0, 0.0));
//    points.append(Coordinate(550.0, 350.0, 0.0));

//    list.append(new Line(QString("Linha Diagonal"), QList(points), Qt::blue));
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

    // points.append(Coordinate(1200, 200));
    // points.append(Coordinate(1300, 100));
    // points.append(Coordinate(1400, 200));
    // points.append(Coordinate(1200, 200));
    // points.append(Coordinate(1200, 400));
    // points.append(Coordinate(1400, 400));
    // points.append(Coordinate(1400, 200));

    // list.append(new Polygon(QString("Casa Fora"), QList(points), Qt::blue));
    // points.clear();

    // points.append(Coordinate(625.0, 250.0, 0.0));
    // points.append(Coordinate(625.0, 150.0, 0.0));
    // points.append(Coordinate(775.0, 150.0, 0.0));
    // points.append(Coordinate(775.0, 250.0, 0.0));
    // points.append(Coordinate(625.0, 250.0, 200.0));
    // points.append(Coordinate(625.0, 150.0, 200.0));
    // points.append(Coordinate(775.0, 150.0, 200.0));
    // points.append(Coordinate(775.0, 250.0, 200.0));

    // list.append(new Polygon(QString("Casa"), QList(points), Qt::white));
    // points.clear();

    // points.append(Coordinate(625.0, 250.0, 0.0));
    // points.append(Coordinate(725.0, 250.0, 0.0));
    // points.append(Coordinate(700.0, 300.0, 0.0));
    // points.append(Coordinate(625.0, 250.0, 200.0));
    // points.append(Coordinate(725.0, 250.0, 200.0));
    // points.append(Coordinate(700.0, 300.0, 200.0));

    // list.append(new Polygon(QString("Telhado"), QList(points), Qt::red));
    // points.clear();

    // points.append(Coordinate(6500.0, 150.0, 200.0));
    // points.append(Coordinate(6500.0, 200.0, 200.0));
    // points.append(Coordinate(6750.0, 200.0, 200.0));
    // points.append(Coordinate(6750.0, 150.0, 200.0));

    // list.append(new Polygon(QString("Porta"), QList(points), Qt::magenta));
    // points.clear();

    // points.append(Coordinate(725.0, 205.0, 150.0));
    // points.append(Coordinate(725.0, 230.0, 175.0));
    // points.append(Coordinate(725.0, 230.0, 175.0));
    // points.append(Coordinate(725.0, 205.0, 150.0));

    // list.append(new Polygon(QString("Janela"), QList(points), Qt::magenta));
    // points.clear();

    // points.append(Coordinate(725.0, 165.0, 150.0));
    // points.append(Coordinate(725.0, 190.0, 175.0));
    // points.append(Coordinate(725.0, 190.0, 175.0));
    // points.append(Coordinate(725.0, 165.0, 150.0));

    // list.append(new Polygon(QString("Janela 2"), QList(points), Qt::magenta));
    // points.clear();
    return list;
};