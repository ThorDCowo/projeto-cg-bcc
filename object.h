#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
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

    pair<float, float> barycenter();
    void draw(QPainter &painter);
    void rotateWorld(float teta);
    void transformToViewport(pair<float, float> center);
    void regionCodeGenerate(float upper, float lower, float left, float right);
    void normalize(int width, int height, pair<float, float> center);
    void clipping(int windowWidth, int windowHeight, pair<float, float> center);
    float lineEquation(float upper, float lower, float left, float right, float x1, float y1, float x2, float y2);

    virtual void translate(float dx, float dy)=0;
    virtual void scale(float factor)=0;
    virtual void rotate(float teta)=0;
    
    inline QString getName()const { return name; }
    inline QList<std::pair<float,float>> getPoints()const { return this->pointsList; }
    inline QList<std::pair<float,float>> getNormalizePoints()const { return this->normalizePointsList; }
    inline QList<std::vector<bool>> getRegionCode() {return this->regionCodeList;} 
    inline Qt::GlobalColor getColor()const { return color; }

    float linearInterpolation(float x, float x0, float x1, float y0, float y1);

protected:
    QString name; //id do objeto instancido
    QList<pair<float,float>> pointsList;
    QList<pair<float,float>> normalizePointsList;
    QList<vector<bool>> regionCodeList; 
    Qt::GlobalColor color;
};

#endif // OBJECT_H
