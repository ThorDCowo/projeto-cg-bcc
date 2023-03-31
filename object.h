#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QPainter>
#include <QList>

using namespace std;

class Object
{

public:

    Object(const QString &name, const QList<std::pair<float,float>> &pointsList, Qt::GlobalColor color):
        name(name), pointsList(pointsList), color(color)
    {}

    void nothing();
    virtual void draw(QPainter &painter)=0;
    virtual void translate(float dx, float dy)=0;
    virtual void scale(float factor)=0;
    virtual void rotate(float teta)=0;

    inline QString getName()const { return name; }
    inline QList<std::pair<float,float>> getPontos()const { return this->pointsList; }
    inline Qt::GlobalColor getColor()const { return color; }

protected:
    QString name; //id do objeto instancido
    QList<std::pair<float,float>> pointsList;
    Qt::GlobalColor color;
};

#endif // OBJECT_H
