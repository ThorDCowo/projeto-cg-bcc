#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QPainter>
#include <QList>

class Object
{

public:

    Object(const QString &nome, const QList<std::pair<int,int>> &pointsList, Qt::GlobalColor color):
        nome(nome), pointsList(pointsList), color(color)
    {}

    void nothing();
    virtual void draw(QPainter &painter)=0;

    inline QString getNome()const { return nome; }
    inline QList<std::pair<int,int>> getPontos()const { return this->pointsList; }
    inline Qt::GlobalColor getColor()const { return color; }

protected:
    QString nome; //id do objeto instancido
    QList<std::pair<int,int>> pointsList;
    Qt::GlobalColor color;
};

#endif // OBJECT_H
