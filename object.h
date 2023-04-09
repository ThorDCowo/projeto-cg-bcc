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

    void normalize(int width, int height);
    pair<float, float> barycenter();
    void draw(QPainter &painter);
    virtual void translate(float dx, float dy)=0;
    virtual void scale(float factor)=0;
    virtual void rotate(float teta)=0;
    
    inline QString getName()const { return name; }
    inline QList<std::pair<float,float>> getPoints()const { return this->pointsList; }
    inline QList<std::pair<float,float>> getNormalizePoints()const { return this->normalizePointsList; }
    inline Qt::GlobalColor getColor()const { return color; }

protected:
    QString name; //id do objeto instancido
    QList<std::pair<float,float>> pointsList;
    QList<std::pair<float,float>> normalizePointsList;
    Qt::GlobalColor color;
};

#endif // OBJECT_H
