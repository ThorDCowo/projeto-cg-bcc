#include <iostream>
#include <vector>
#include <cmath>

#include "../../core/entities/object.h"
#include "../../core/entities/border.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"
#include "orthogonal_projection.use_case.h"
#include "../../core/interfaces/comparable.h"
#include "../../core/entities/polygon.h"

class OrthogonalProjectionUseCaseTest : public TestSuite {
private:
    Clipper* clipper;

public:
    OrthogonalProjectionUseCaseTest(Clipper* clipper) : TestSuite() {
        this->clipper = clipper;
    }

    void run()
    {
               
    }
    
};