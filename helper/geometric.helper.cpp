#include "geometric.helper.h"

double cosHelper(double radians) {
    double specialDegrees = 90.0;
    if(radians == qDegreesToRadians(specialDegrees)) {
        return 0.0;
    }

  return qCos(radians);
}

double sinHelper(double radians) {
    double specialDegrees = 0.0;
    if(radians == qDegreesToRadians(specialDegrees)) {
        return 1.0;
    }

  return qSin(radians);
}