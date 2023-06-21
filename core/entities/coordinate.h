#ifndef COORDINATE_H
#define COORDINATE_H
#include <cmath>
#include "../interfaces/comparable.h"

class Coordinate : public Comparable
{
public:
  float x;
  float y;
  float z;

  Coordinate(
      float xCoord,
      float yCoord,
      float zCoord) : x(xCoord),
                      y(yCoord),
                      z(zCoord)
  {
  }

  Coordinate(
      float xCoord,
      float yCoord) : x(xCoord),
                      y(yCoord),
                      z(0)
  {
  }

  Coordinate operator/(const float scalar) const
  {
    return Coordinate(x / scalar, y / scalar, z / scalar);
  }

  Coordinate operator*(const float scalar) const
  {
    return Coordinate(x * scalar, y * scalar, z * scalar);
  }
  

  void operator*=(const float scalar)
  {
    x *= scalar;
    y *= scalar;
    z *= scalar;
  }

  void operator+=(const Coordinate &other)
  {
    x += other.x;
    y += other.y;
    z += other.z;
  }

  bool operator==(const Comparable &other) const 
  {
    const Coordinate *otherCoordinate = dynamic_cast<const Coordinate *>(&other);
    if (otherCoordinate)
    {
      return (
          x == otherCoordinate->x &&
          y == otherCoordinate->y &&
          z == otherCoordinate->z
        );
    }
    return false;
  }

  bool operator!=(const Comparable &other) const 
  {
    return !(*this == other);
  }

  string toString() const
  {
    return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
  }

  Coordinate operator-(const Comparable &other) const
  {
    const Coordinate *otherCoordinate = dynamic_cast<const Coordinate *>(&other);

      return Coordinate(
        x - otherCoordinate->x,
        y - otherCoordinate->y,
        z - otherCoordinate->z
      );


  
  }

  static Coordinate invertOrientation(Coordinate coordinate)
  {
    return coordinate * (-1);
  }

  static Coordinate axisX()
  {
    return Coordinate(1, 0, 0);
  }

  static Coordinate axisY()
  {
    return Coordinate(0, 1, 0);
  }

  static Coordinate axisZ()
  {
    return Coordinate(0, 0, 1);
  }

  static Coordinate zero()
  {
    return Coordinate(0, 0, 0);
  }

  static Coordinate one()
  {
    return Coordinate(1, 1, 1);
  }

  static Coordinate back()
  {
    return Coordinate(0, 0, -1);
  }

  static Coordinate forward()
  {
    return Coordinate(0, 0, 1);
  }

  static Coordinate left()
  {
    return Coordinate(-1, 0, 0);
  }

  static Coordinate right()
  {
    return Coordinate(1, 0, 0);
  }

  static Coordinate up()
  {
    return Coordinate(0, 1, 0);
  }

  static Coordinate down()
  {
    return Coordinate(0, -1, 0);
  }

  static Coordinate fromString(string str)
  {
    string delimiter = ",";
    string x = str.substr(0, str.find(delimiter));
    str.erase(0, str.find(delimiter) + delimiter.length());
    string y = str.substr(0, str.find(delimiter));
    str.erase(0, str.find(delimiter) + delimiter.length());
    string z = str.substr(0, str.find(delimiter));
    return Coordinate(stof(x), stof(y), stof(z));
  }

  static float magnitude(Coordinate vector)
  {
    return std::sqrt(
      vector.x * vector.x + 
      vector.y * vector.y + 
      vector.z * vector.z
    );
  }

  static Coordinate normalize(Coordinate vector) {
    return vector / Coordinate::magnitude(vector);
  }

  static float dotProduct(Coordinate vector1, Coordinate vector2) {
    return vector1.x * vector2.x + 
      vector1.y * vector2.y + 
      vector1.z * vector2.z;
  }

  static float angle(Coordinate vector1, Coordinate vector2) {
    return std::acos(
      Coordinate::dotProduct(vector1, vector2)/(Coordinate::magnitude(vector1) * Coordinate::magnitude(vector1))
    );
  }
  
};

#endif // COORDINATE_H
