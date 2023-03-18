#include "main_frame.h"
#include <QPainter>
#include <iostream>
#include <QDebug>

using namespace std;

#include "point.h"
#include "line.h"
#include "rect.h"
#include "window.h"

Main_frame::Main_frame(QWidget *parent)
    : QFrame{parent}
{
    Window janela(QPoint(0, 0), 400, 300); // metade do tamanho do viewport

    list.append(
        new Rect(
            QString("ret-01"), 
            QRect(QPoint(120, 20),
            QSize(20, 20)), 
            20, 
            20, 
            20, 
            20, 
            Qt::red
        )
    );

    list.append(
        new Rect(
            QString("ret-02"),
            QRect(QPoint(150, 115),
            QSize(300,50)),
            15,
            15,
            300,
            50,
            Qt::cyan
        )
    );

    list.append(
        new Line(QString("line-01"),
        QLine(QPoint(10,
        10),
        QPoint(90,
        90)),
        10,
        10,
        90,
        90,
        Qt::green
        )
    );

    list.append(
        new Point(QString("Point-01"),
        QPoint(30,50),
        30,
        50,
        Qt::white
        )
    );

    list.append(
        new Rect(
            QString("ret-03"),
            QRect(QPoint(-15, 300),
            QSize(300, 50)),
            15,
            15,
            300,
            50,
            Qt::yellow
        )
    );
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
        list[i]->desenha(painter);
    }
}

void Main_frame::muda(int i)
{
    cout << "entrou no Main_frame::muda" << endl;
    list[i]->ajusta(5, 2);
    update();
}

void Main_frame::muda()
{
    for (int i = 0; i < list.size(); ++i)
    {
        muda(i);
    }
}
