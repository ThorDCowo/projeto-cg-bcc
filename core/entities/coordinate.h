#ifndef COORDINATE_H
#define COORDINATE_H

#include "../interfaces/comparable.h"

class Coordinate : public Comparable<Coordinate>
{
public: 
   float x;
   float y; 
   float z;

  Coordinate(
    float xCoord, 
    float yCoord, 
    float zCoord
  ):
    x(xCoord), 
    y(yCoord), 
    z(zCoord)
 {}

  Coordinate(
    float xCoord, 
    float yCoord
  ):
    x(xCoord), 
    y(yCoord), 
    z(0)
 {}

  Coordinate operator*(const float scalar) const {
    return Coordinate(x * scalar, y * scalar, z * scalar);
  }

  void operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
  }

  void operator+=(const Coordinate& other) {
    x += other.x;
    y += other.y;
    z += other.z;
  }

  bool operator==(const Coordinate& other) const {
      return (x == other.x && y == other.y && z == other.z);
  }

  bool operator!=(const Coordinate& other) const {
    return (x != other.x || y != other.y || z != other.z);
  }

  string toString() const {
    return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
  }

  static Coordinate invertOrientation(Coordinate coordinate) {
    return coordinate * (-1);
  } 

  static Coordinate axisX() {
    return Coordinate(1, 0, 0);
  }

  static Coordinate axisY() {
    return Coordinate(0, 1, 0);
  }

  static Coordinate axisZ() {
    return Coordinate(0, 0, 1);
  }

  static Coordinate zero() {
    return Coordinate(0, 0, 0);
  }

  static Coordinate one() {
    return Coordinate(1, 1, 1);
  }

  static Coordinate back() {
    return Coordinate(0, 0, -1);
  }

  static Coordinate forward() {
    return Coordinate(0, 0, 1);
  }

  static Coordinate left() {
    return Coordinate(-1, 0, 0);
  }

  static Coordinate right() {
    return Coordinate(1, 0, 0);
  }

  static Coordinate up() {
    return Coordinate(0, 1, 0);
  }

  static Coordinate down() {
    return Coordinate(0, -1, 0);
  }

  static Coordinate fromString(string str) {
    string delimiter = ",";
    string x = str.substr(0, str.find(delimiter));
    str.erase(0, str.find(delimiter) + delimiter.length());
    string y = str.substr(0, str.find(delimiter));
    str.erase(0, str.find(delimiter) + delimiter.length());
    string z = str.substr(0, str.find(delimiter));
    return Coordinate(stof(x), stof(y), stof(z));
  }
};

#endif// COORDINATE_H