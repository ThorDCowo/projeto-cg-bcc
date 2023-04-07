#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


// class Vector2
// {
// public:
//     Vector2() {
//         this.vector = pair<float, float>(0, 0);
//     }
//     Vector2(pair<float, float> vector) :
//     {
//         this.vector = vector;
//     }

//     float getX() const { return this.vector.first; }
//     float getY() const { return this.vector.second; }

//     Vector2 operator+(const Vector2 &vector) const
//     {
//         return Vector2(this->getX() + vector.getX(), this->getY() + vector.getY());
//     }

//     Vector2 operator-(const Vector2 &vector) const
//     {
//         return Vector2(this->getX() - vector.getX(), this->getY() - vector.getY());
//     }

//     float operator*(const Vector2 &vector) const
//     {
//         return this->getX() * vector.getX() + this->getY() * vector.getY();
//     }

//     Vector2 operator*(float escalar) const
//     {
//         return Vector2(this->getX() * escalar, this->getY() * escalar);
//     }

//     Vector2 operator/(float escalar) const
//     {
//         return Vector2(this->getX() / escalar, this->getY() / escalar);
//     }

//     bool areParalel(Vector2 v1, Vector2, v2)
//     {
//         return v1.getX() / v2.getX() == v1.getY() / v2.getY();
//     }

// private:
//     pair<float, float> vector;
// };