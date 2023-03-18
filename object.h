#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QPainter>

class Object
{

public:

    enum Tipos {
        PONTO,
        LINHA,
        RETANGULO
    };

    Object(const QString &nome, const Tipos &tipo, Qt::GlobalColor color):
        nome(nome),tipo(tipo), color(color)
    {}

    void nothing();
    virtual void desenha(QPainter& painter)=0;
    virtual void ajusta(int dx, int dy)=0; //implementa uma translação
    virtual void transformadaWindow(int windowX,int windowY)=0;
    virtual void normalizacao(int windowHeight, int windowWidth)=0;
    virtual void transformadaViewport(int viewHeight, int viewWidth)=0;
    virtual void translacao(int dx, int dy)=0;
    virtual void escala(float px, float py)=0;
    virtual void rotacao(int teta)=0;

    inline QString getNome()const { return nome; }
    inline enum Tipos getTipo()const { return tipo; }
    inline Qt::GlobalColor getColor()const { return color; }

private:
    QString nome; //id do objeto instancido
    enum Tipos tipo;
    Qt::GlobalColor color;
};

#endif // OBJECT_H
