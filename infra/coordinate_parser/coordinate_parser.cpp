#include <string>
#include "../../core/entities/coordinate.h"
#include "coordinate_parser.h"

Coordinate CoordinateParser::parse(string line) {
    float x, y, z;
    sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
    return Coordinate(x, y, z);
}