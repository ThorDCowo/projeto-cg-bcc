#include "orthogonal_projection.use_case.h"

void OrthogonalProjectionUseCase::execute(
    Object* object,
    int windowWidth,
    int windowHeight,
    int viewportWidth,
    int viewportHeight,
    Coordinate windowCenter,
    Coordinate axisToExclude
)
{
    Border border(windowWidth, windowHeight, windowCenter);
    
    object->orthogonalNormalize(
        windowWidth,
        windowHeight,
        windowCenter,
        axisToExclude
    );
    // this->clippObjectUseCase->execute(object, border);
    object->transformToViewport(
        windowCenter,
        viewportWidth,
        viewportHeight
    );

    // cout << "Points / Projection / Normalized" << endl;
    // cout << object->getPoints()[0].toString() << endl;
    // cout << object->getProjectionPoints()[0].toString() << endl;
    // cout << object->getNormalizedPoints()[0].toString() << endl;
    // cout << "-------------------" << endl;
}