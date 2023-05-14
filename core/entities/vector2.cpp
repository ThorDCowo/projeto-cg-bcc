#include <QtMath>
using namespace std;

class Vector2
{
public:
    Vector2() {
        this.vector = pair<float, float>(0, 0);
    }
    Vector2(pair<float, float> vector) :
    {
        this.vector = vector;
    }

    float getX() const { return this.vector.first; }
    float getY() const { return this.vector.second; }

    Vector2 operator+(const Vector2 &vector) const
    {
        return Vector2(this->getX() + vector.getX(), this->getY() + vector.getY());
    }

    Vector2 operator-(const Vector2 &vector) const
    {
        return Vector2(this->getX() - vector.getX(), this->getY() - vector.getY());
    }

    float operator*(const Vector2 &vector) const
    {
        return this->getX() * vector.getX() + this->getY() * vector.getY();
    }

    Vector2 operator*(float escalar) const
    {
        return Vector2(this->getX() * escalar, this->getY() * escalar);
    }

    Vector2 operator/(float escalar) const
    {
        return Vector2(this->getX() / escalar, this->getY() / escalar);
    }

    static bool areParalel(Vector2 v1, Vector2 v2)
    {
        return v1.getX() / v2.getX() == v1.getY() / v2.getY();
    }

    static Vector2 perpendicular(Vector2 direction)
    {
        float ninetyDegrees = 90.0;
        float radians = qDegreesToRadians(ninetyDegrees);

        pair<float, float>(pointsList[i].first * qCos(radians) - (pointsList[i].second * qSin(radians)), 
                                        pointsList[i].first * qSin(radians) + (pointsList[i].second * qCos(radians)));
    }

private:
    pair<float, float> vector;
};