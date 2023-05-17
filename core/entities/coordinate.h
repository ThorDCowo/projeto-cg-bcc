#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
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

};

#endif// COORDINATE_H