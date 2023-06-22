#include "coordinate_parser.h"

using namespace std;

Coordinate CoordinateParser::parse(string line) {
    float x, y, z;
    sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
    return Coordinate(x, y, z);
}

bool CoordinateParser::isParsable(string line) {
    float x, y, z;
    return sscanf(line.c_str(), "v %f %f %f", &x, &y, &z) == 3;
}
