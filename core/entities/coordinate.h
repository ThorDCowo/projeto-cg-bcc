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

};

#endif// COORDINATE_H