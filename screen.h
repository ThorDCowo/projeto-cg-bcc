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

public:
    explicit Screen(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void setObjectList(QList<Object*> list);
    QList<Object*> getObjectList();

public slots:

signals:

};

#endif // SCREEN_H
