#include "clipp_object.use_case.h"

using namespace std;

void ClippObjectUseCase::execute(Object* object, Border border) {
    // QList<Coordinate> normalizedPoints = object->getNormalizedPoints();
    // cout << "S;ORUJHGD;LRUIGHS;EORTHB " << normalizedPoints.size() << endl;
    // QList<Coordinate>* normalizedPointsPointer = &(normalizedPoints);
    // QList<Coordinate> pointsListToDraw = object->getPointsListToDraw();
    // QList<Coordinate>* pointsListToDrawPointer = &(pointsListToDraw);
    // QList<pair<int, int>> edgesListToDraw = object->getEdgesListToDraw();
    // QList<pair<int, int>>* edgesListToDrawPointer = &(edgesListToDraw);
    // QList<pair<int, int>> edges = object->getEdges();
    // QList<pair<int, int>>* edgesPointer = &(edges);

    // qsizetype size = normalizedPoints.size();
    pair<int,int> edge = {0,1};

    switch (size) {
        case 1:
            this->clipper->pointClipping(
                border,
                &object->getNormalizedPoints(),
                &object->getEdgesListToDraw(),
                &object->getPointsListToDraw()
            );
            break;
        case 2:
            this->clipper->lineClipping(
                border,
                &object->getEdges(),
                &object->getNormalizedPoints(),
                &object->getEdgesListToDraw(),
                &object->getPointsListToDraw()
            );
            break;
        default:
            this->clipper->polygonClipping(
                border,
                &object->getNormalizedPoints(),
                &object->getEdges(),
                &object->getEdgesListToDraw(),
                &object->getPointsListToDraw()
            );
            break;
    }    
}
