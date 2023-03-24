#ifndef WINDOW_H
#define WINDOW_H
#include <QPoint>

class Window : public QPoint
{
public:
    int width, height;
    Window(const QPoint& center, int width, int height):
        QPoint(center),width(width), height(height)
    {}
};

#endif // WINDOW_H
