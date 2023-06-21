#include "perspective_projection.use_case.h"

void PerspectiveProjectionUseCase::execute(
    Object* object,
    Coordinate centerOfProjection,
    Coordinate windowCenter,
    int width,
    int height,
    float distanceFromProjection,
    float alpha,
    float beta
)
{
    Border border(width, height, windowCenter);

    Coordinate camera = Coordinate::zero(); // Origin
    //translation of world
    object->translate(Coordinate::invertOrientation(centerOfProjection));
    //translation of axis X and Y to align Z
    object->rotateWorld(alpha, Coordinate::axisX());
    object->rotateWorld(beta, Coordinate::axisY());
    //projection
    object->perspectiveNormalize(width, height, windowCenter, distanceFromProjection);
    this->clippObjectUseCase->execute(object, border);
    object->transformToViewport(windowCenter);


    cout << "Points / Projection / Normalized" << endl;
    cout << object->getPoints()[0].toString() << endl;
    // cout << object->getProjectionPoints()[0].toString() << endl;
    // cout << object->getNormalizedPoints()[0].toString() << endl;
    // cout << "-------------------" << endl;
}