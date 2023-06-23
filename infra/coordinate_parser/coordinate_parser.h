#ifndef COORDINATE_PARSER_H
#define COORDINATE_PARSER_H

#include <string>
#include <iostream>
#include "../../data/entities/coordinate.h"


using namespace std;

class CoordinateParser {
public:
    Coordinate parse(string);
    bool isParsable(string line);
};

#endif // COORDINATE_PARSER_H
