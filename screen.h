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
    QList<Object*> getObjectList();
    void setObjectList(QList<Object*> list);
    void setWidth(int width);
    void setHeight(int height);

public slots:

signals:

};

#endif // SCREEN_H
