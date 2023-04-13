#ifndef SCREEN_H
#define SCREEN_H

#include <QFrame>
#include <QPaintEvent>
#include <QRect>
#include <QList>
#include <QCheckBox>
#include <object.h>

class Screen : public QFrame
{
    Q_OBJECT
private:
    //Oject of the world, the "Camera"
    QList<Object*> list;
    int width = 854;  //inicialize with viewport size
    int height = 480; //inicialize with viewport size
    pair<float, float> center = {429.0,240.0};

public:
    explicit Screen(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    
    QList<Object*> getObjectList() const {return this->list;};
    int getWidth()const {return  this->width;};
    int getHeight()const {return this->height;};
    pair<float, float> getCenter()const {return this->center;};
    
    void setObjectList(QList<Object*> list) {this->list = list;};
    void setWidth(int width) {this->width = width;};
    void setHeight(int height) {this->height = height;};
    void setCenter(pair<float, float> center) {this->center.first = center.first; this->center.second = center.second;};

public slots:

signals:

};

#endif // SCREEN_H
