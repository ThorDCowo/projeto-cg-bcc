#include "transform_from_world_to_viewport.use_case.h"

void TransformFromWorldToViewportUseCase::execute(
    Object* object,
    int width,
    int height,
    Coordinate center,
    float distanceFromProjection
)
{
    Border border(width, height, center);
    
    // object->parallelNormalize(width, height, center, Coordinate::axisZ());
    object->planeProjection(distanceFromProjection);
    object->perspectiveNormalize(width, height, center);
    this->clippObjectUseCase->execute(object, border);
    object->transformToViewport(center);

    cout << "Points / Projection / Normalized" << endl;
    cout << object->getPoints()[0].toString() << endl;
    cout << object->getProjectionPoints()[0].toString() << endl;
    cout << object->getNormalizedPoints()[0].toString() << endl;
    cout << "-------------------" << endl;
}