#include <string>
#include "../../core/entities/coordinate.h"

Coordinate CoordinateParser::parse(string line) {
    int x, y, z;
    sscanf(line.c_str(), "%d %d %d", &x, &y, &z);
    return Coordinate(x, y, z);
}
