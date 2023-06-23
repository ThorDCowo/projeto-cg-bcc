#include <iostream>
#include <vector>
#include <cmath>

#include "../../data/entities/object.h"
#include "../../data/entities/border.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"
#include "orthogonal_projection.use_case.h"
#include "../../data/interfaces/comparable.h"
#include "../../data/entities/polygon.h"

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