#include <iostream>
#include <QList>
#include "clipp_object.use_case.h"
#include "../../core/entities/object.h"

using namespace std;

void ClippObjectUseCase::execute(Object* object, Border border) {
    QList<Coordinate> normalizedPoints = object->getNormalizedPoints();

    qsizetype size = normalizedPoints.size();
    qsizetype firstIndex = 0;
    qsizetype secondIndex = 1;

    switch (size) {
        case 1:
            this->clipper->pointClipping(border, &normalizedPoints);
            break;
        case 2:
            this->clipper->lineClipping(border, firstIndex, secondIndex, &normalizedPoints);
            break;
        default:
            this->clipper->polygonClipping(border, &normalizedPoints);
            break;
    }    
}
