#include "orthogonal_projection.use_case.h"

void OrthogonalProjectionUseCase::execute(
    Object* object,
    int width,
    int height,
    Coordinate center,
    Coordinate axisToExclude
)
{
    Border border(width, height, center);
    
    object->orthogonalNormalize(width, height, center, axisToExclude);
    this->clippObjectUseCase->execute(object, border);
    object->transformToViewport(center);

    cout << "Points / Projection / Normalized" << endl;
    cout << object->getPoints()[0].toString() << endl;
    cout << object->getProjectionPoints()[0].toString() << endl;
    cout << object->getNormalizedPoints()[0].toString() << endl;
    cout << "-------------------" << endl;
}