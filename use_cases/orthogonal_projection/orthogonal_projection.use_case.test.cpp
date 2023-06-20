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
        cout << "-----------------------" << endl;
        cout << "Teste de planeProjection()" << endl;
        cout << "-----------------------" << endl;

        this->pyramidPlaneProjectionTest();
        
    }

    void pyramidPlaneProjectionTest()
    {
        float distanceFromProjection = 10.0;
        
        QList<Coordinate> pointList;
        QList<Coordinate> expectedProjectionList;

        /*
            G = (-2, 4, 0)                      G -> L
            J = (-4, 4, 0)                      J -> N
            I = (-4, 6, 0)                      I -> M
            H = (-3, 5, 2) -> Topo da piramide  H -> K
        */
        pointList.append(Coordinate(-2, 4, 0));
        pointList.append(Coordinate(-4, 4, 0));
        pointList.append(Coordinate(-4, 6, 0));
        pointList.append(Coordinate(-3, 5, 2));

        Object* pyramid = new Polygon(QString("Piramide Triangular"), QList(pointList), Qt::red);

        expectedProjectionList.append((Coordinate(-1.5, 3, 0)));
        expectedProjectionList.append((Coordinate(-3, 3, 0)));
        expectedProjectionList.append((Coordinate(-2, 3, 0)));
        expectedProjectionList.append((Coordinate(-1.8, 3, 1.2)));

        pyramid->planeProjection(distanceFromProjection);

        QList<Coordinate> resultProjectionPointList = pyramid->getProjectionPoints();
        for (qsizetype i = 0; i < expectedProjectionList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                "Deve projetar o ponto" + resultProjectionPointList[i].toString() + "em " + 
                expectedProjectionList[i].toString(),
                resultProjectionPointList[i],
                expectedProjectionList[i]
            );
        }
    }
};