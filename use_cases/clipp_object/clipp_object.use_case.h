#ifndef CLIPP_OBJECT_USE_CASE_H
#define CLIPP_OBJECT_USE_CASE_H
#include <iostream>
#include <QList>

#include "../../core/entities/object.h"
#include "../../infra/clipper/clipper.h"

class ClippObjectUseCase {
private:
    Clipper* clipper;

public:
    ClippObjectUseCase(Clipper* clipper)  {
        this->clipper = clipper;
    };
    
  void execute(Object* object, Border border);
};

#endif // CLIPP_OBJECT_USE_CASE_H
