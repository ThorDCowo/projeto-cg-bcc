#include "face_parser.h"

using namespace std;

Face FaceParser::parse(string line) {
    int x, y, z;

    sscanf(line.c_str(), "f %d/%*s %d/%*s %d/%*s", &x, &y, &z);
    return Face(x - 1, y - 1, z - 1);
}

bool FaceParser::isParsable(string line) {
    int x, y, z;
    return sscanf(line.c_str(), "f %d/%*s %d/%*s %d/%*s", &x, &y, &z) == 3;
}

string Face::toString() const{
    return "Face Index: (" + to_string(v1) + ", " + to_string(v2) + ", " + to_string(v3) + ")";
}

bool Face::operator==(const Comparable &other) const {
    const Face *otherFace = dynamic_cast<const Face *>(&other);
    if (otherFace)
    {
        return (
            v1 == otherFace->v1 &&
            v2 == otherFace->v2 &&
            v3 == otherFace->v3
        );
    }
    return false;
}

bool Face::operator!=(const Comparable &other) const {
    return !(*this == other);
}