#include "perspective_projection.use_case.h"

void PerspectiveProjectionUseCase::execute(
    Object* object,
    Coordinate centerOfProjection,
    Coordinate windowCenter,
    int windowWidth,
    int windowHeight,
    int viewportWidth,
    int viewportHeight,
    float distanceFromProjection,
    float alpha,
    float beta
)
{
    Border border(windowWidth, windowHeight, windowCenter); 
    //translation of world
    object->translate(Coordinate::invertOrientation(centerOfProjection));
    //translation of axis X and Y to align Z
    object->rotateWorld(alpha, Coordinate::axisX());
    object->rotateWorld(beta, Coordinate::axisY());
    //projection
    object->perspectiveNormalize(windowWidth, windowHeight, windowCenter, distanceFromProjection);
    this->clippObjectUseCase->execute(object, border);
    object->transformToViewport(
        windowCenter,
        viewportWidth,
        viewportHeight
    );

    cout << "Perspective Projection" << endl;
    cout << "Points / Projection / Normalized / Viewport" << endl;
    cout << object->getPoints()[0].toString() << endl;
    cout << object->getProjectionPoints()[0].toString() << endl;
    cout << object->getNormalizedPoints()[0].toString() << endl;
    cout << object->getViewportPoints()[0].toString() << endl;
}