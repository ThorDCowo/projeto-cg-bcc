#include "clipp_object.use_case.h"

using namespace std;

void ClippObjectUseCase::execute(Object* object, Border border) {
    QList<Coordinate> normalizedPoints = object->getNormalizedPoints();
    QList<Coordinate> pointsListToDraw = object->getPointsListToDraw();
    QList<pair<int, int>> edgesListToDraw = object->getEdgesListToDraw();
    QList<pair<int, int>> edges = object->getEdges();

    qsizetype size = normalizedPoints.size();
    pair<int,int> edge = {0,1};

    switch (size) {
        case 1:
            this->clipper->pointClipping(
                border,
                &normalizedPoints,
                &edgesListToDraw,
                &pointsListToDraw
            );
            break;
        case 2:
            this->clipper->lineClipping(
                border,
                edge,
                &normalizedPoints,
                &edgesListToDraw,
                &pointsListToDraw
            );
            break;
        default:
            this->clipper->polygonClipping(
                border,
                &normalizedPoints,
                &edges,
                &edgesListToDraw,
                &pointsListToDraw
            );
            break;
    }    
}
