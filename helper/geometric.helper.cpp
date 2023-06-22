
#include "geometric.helper.h"


double cosHelper(double radians) {
    double 90degrees = 90.0;
    if(radians == qDegreesToRadians(90degrees)) {
        return 0.0;
    }

  return qCos(x);
}

double sinHelper(double radians) {
    double zeroDegrees = 0.0;
    if(radians == qDegreesToRadians(zeroDegrees)) {
        return 1.0;
    }

  return qSin(x);
}