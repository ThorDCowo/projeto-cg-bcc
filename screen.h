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
    QList<Object*> list;
    int width;
    int height;

public:
    explicit Screen(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    
    QList<Object*> getObjectList() const {return this->list;};
    int getWidth()const {return  this->width;};
    int getHeight()const {return this->height;};
    
    void setObjectList(QList<Object*> list) {this->list = list;};
    void setWidth(int width) {this->width = width;};
    void setHeight(int height) {this->height = height;};

public slots:

signals:

};

#endif // SCREEN_H
