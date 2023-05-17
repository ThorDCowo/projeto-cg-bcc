#include "transform_from_world_to_viewport.use_case.h"

void TransformFromWorldToViewportUseCase::execute(
    Object* object,
    int width,
    int height,
    Coordinate center
)
{
    Border border(width, height, center);
    
    object->normalize(width, height, center);
    this->clippObjectUseCase->execute(object, border);
    object->transformToViewport(center);
}
