#ifndef FACE_PARSER_H
#define FACE_PARSER_H

#include <string.h>
#include <iostream>
#include "../../core/interfaces/comparable.h"

using namespace std;

class Face : public Comparable {
public:
    int v1, v2, v3;

    Face(int v1Index, int v2Index, int v3Index) 
    :  v1(v1Index), v2(v2Index), v3(v3Index){}

    string toString() const;
    bool operator==(const Comparable &other) const;
    bool operator!=(const Comparable &other) const;
}; 

class FaceParser {
public:
    Face parse(string line);
    bool isParsable(string line);
};

#endif // FACE_PARSER_H