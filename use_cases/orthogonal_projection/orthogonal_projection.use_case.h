#ifndef ORTHOGONAL_PROJECTION_USE_CASE_H
#define ORTHOGONAL_PROJECTION_USE_CASE_H

#include "../clipp_object/clipp_object.use_case.h"

class OrthogonalProjectionUseCase {
private:
    ClippObjectUseCase* clippObjectUseCase;
public:
    OrthogonalProjectionUseCase(ClippObjectUseCase* clippObjectUseCase) {
        this->clippObjectUseCase = clippObjectUseCase;
    };

    ~OrthogonalProjectionUseCase();
    void execute(
        Object* object,
        int width,
        int height,
        Coordinate center,
        Coordinate axisToExclude
    );

};

#endif // ORTHOGONAL_PROJECTION_USE_CASE_H