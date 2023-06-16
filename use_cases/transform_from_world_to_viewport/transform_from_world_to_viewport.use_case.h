#ifndef TRANSFORM_FROM_WORLD_TO_VIEWPORT_USE_CASE_H
#define TRANSFORM_FROM_WORLD_TO_VIEWPORT_USE_CASE_H

#include "../clipp_object/clipp_object.use_case.h"

class TransformFromWorldToViewportUseCase {
private:
    ClippObjectUseCase* clippObjectUseCase;
public:
    TransformFromWorldToViewportUseCase(ClippObjectUseCase* clippObjectUseCase) {
        this->clippObjectUseCase = clippObjectUseCase;
    };

    ~TransformFromWorldToViewportUseCase();
    void execute(
        Object* object,
        int width,
        int height,
        Coordinate center,
        float distanceFromProjection
    );

};

#endif // TRANSFORM_FROM_WORLD_TO_VIEWPORT_USE_CASE_H