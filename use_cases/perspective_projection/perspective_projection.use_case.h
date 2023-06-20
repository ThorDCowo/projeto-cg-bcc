#ifndef PERSPECTIVE_PROJECTION_USE_CASE_H
#define PERSPECTIVE_PROJECTION_USE_CASE_H

#include "../clipp_object/clipp_object.use_case.h"

class PerspectiveProjectionUseCase {
private:
    ClippObjectUseCase* clippObjectUseCase;
public:
    PerspectiveProjectionUseCase(ClippObjectUseCase* clippObjectUseCase) {
        this->clippObjectUseCase = clippObjectUseCase;
    };

    ~PerspectiveProjectionUseCase();
    void execute(
      Object* object,
      Coordinate centerOfProjection,
      Coordinate windowCenter,
      int width,
      int height,
      float distanceFromProjection,
      float alpha,
      float beta
    );
};

#endif // PERSPECTIVE_PROJECTION_USE_CASE_H