#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include <QFrame>
#include <QPaintEvent>
#include <QRect>
#include <QList>
#include <object.h>

class Main_frame : public QFrame
{
    Q_OBJECT
private:
    QList<Object*> list;
public:
    explicit Main_frame(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

public slots:

signals:

};

#endif // MAIN_FRAME_H
