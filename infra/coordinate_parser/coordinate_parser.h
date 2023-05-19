#ifndef COORDINATE_PARSER_H
#define COORDINATE_PARSER_H

#include <string>
#include "../../core/entities/coordinate.h"

using namespace std;

class CoordinateParser {
public:
    Coordinate parse(string);
};

#endif // COORDINATE_PARSER_H
