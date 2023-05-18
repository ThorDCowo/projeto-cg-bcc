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

  bool operator==(const Coordinate& other) const {
      return (x == other.x && y == other.y && z == other.z);
  }

  bool operator!=(const Coordinate& other) const {
    return (x != other.x || y != other.y || z != other.z);
  }

  string toString() const {
    return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
  }
};

#endif// COORDINATE_H