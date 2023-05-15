#include "transform_from_world_to_viewport.use_case.h"

void TransformFromWorldToViewportUseCase::execute(
    Object* object,
    int width,
    int height,
    pair<float, float> center
)
{
    Border border(width, height, center);
    
    object->normalize(width, height, center);
    object->transformToViewport(center);
    this->clippObjectUseCase->execute(object, border);
}
