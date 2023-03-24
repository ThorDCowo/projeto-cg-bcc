#include "main_frame.h"
#include <QPainter>
#include <iostream>
#include <QDebug>

using namespace std;

#include "object.h"
#include "point.h"
#include "line.h"
#include "rect.h"
#include "window.h"

Main_frame::Main_frame(QWidget *parent)
    : QFrame{parent}
{
    Window janela(QPoint(0, 0), 400, 300); // metade do tamanho do viewport
    QList<pair<int,int>> pontos;

    pontos.append(pair<int, int>(200, 200));
    pontos.append(pair<int, int>(400, 200));
    pontos.append(pair<int, int>(400, 400));
    pontos.append(pair<int, int>(400, 200));
    list.append(new Rect(QString("Retangulo-001"), QList(pontos), Qt::red));
    pontos.clear();


    pontos.append(pair<int, int>(100, 100));
    pontos.append(pair<int, int>(100, 200));
    pontos.append(pair<int, int>(400, 200));
    pontos.append(pair<int, int>(400, 100));
    list.append(new Rect(QString("Retangulo-002"), QList(pontos), Qt::cyan));
    pontos.clear();

    pontos.append(pair<int, int>(500, 100));
    pontos.append(pair<int, int>(900, 100));
    list.append(new Line(QString("Linha-001"), QList(pontos), Qt::green));
    pontos.clear();


    pontos.append(pair<int, int>(12000, 12000));
    list.append(new Point(QString("Ponto-01"), QList(pontos), Qt::white));
    pontos.clear();

    pontos.append(pair<int, int>(-900, 100));
    pontos.append(pair<int, int>(-900, 200));
    pontos.append(pair<int, int>(100, 200));
    pontos.append(pair<int, int>(100, 100));
    
    list.append(new Rect(QString("Retangulo-03"), QList(pontos), Qt::yellow));
    pontos.clear();
}

void Main_frame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 2));

    for (int i = 0; i < list.size(); i++)
    {
        painter.setPen(QPen(list[i]->getColor(), 2));
        printf(" %d \n", i);
        // list[i]->transformadaWindow(0, 0);       // centro da janela (x,y)
        // list[i]->normalizacao(300, 400);         // tamanho da janela (alt,lar)
        // list[i]->transformadaViewport(600, 800); // tamanho do view (alt,lar)
        // list[i]->translacao(150, 80);            // movimentacao (x,y)
        // list[i]->escala(0.5, 0.5);               // escala da proporcao
        // list[i]->rotacao(30);                    // grau da rotacao
        list[i]->draw(painter);
    }
}

// void Main_frame::muda(int i)
// {
//     cout << "entrou no Main_frame::muda" << endl;
//     update();
// }

// void Main_frame::muda()
// {
//     for (int i = 0; i < list.size(); ++i)
//     {
//         muda(i);
//     }
// }
