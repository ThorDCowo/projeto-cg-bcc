#include "../../data/entities/polygon.h"
#include "../../data/entities/object.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"
#include "perspective_projection.use_case.h"

class ObjectTest : public TestSuite {
private:
    PerspectiveProjectionUseCase *perspectiveProjectionUseCase;
    Object *object;
    
public:
    ObjectTest() : TestSuite() {}

    void run()
    {
        cout << "-----------------------" << endl;
        cout << "Teste de execute()" << endl;
        cout << "-----------------------" << endl;

        this->testExecute();
    }

    void testExecute() {
        QList<Coordinate> pointsList;
        QList<pair<int, int>> edges;
        
        pointsList.append(Coordinate(-2, 4, 0));
        pointsList.append(Coordinate(-4, 4, 0));
        pointsList.append(Coordinate(-4, 6, 0));
        pointsList.append(Coordinate(-3, 5, 2));

        edges.append({0,1});
        edges.append({1,2});
        edges.append({2,0});
        edges.append({0,3});
        edges.append({1,3});    
        edges.append({2,3});

        Object* pyramid = new Polygon(QString("Piramide Triangular"), QList(pointsList), QList(edges), Qt::red);

        int windowWidth = 854;
        int windowHeight = 480;
        int viewportWidth = 854;
        int viewportHeight = 480;
        float distanceFromProjection = 10.0;
        float alpha = 90.0;
        float beta = 90.0;

        Coordinate centerOfProjection = Coordinate::zero();
        Coordinate windowCenter = Coordinate(windowWidth / 2, windowHeight / 2);

        QList<Coordinate> expectedNormalizedPointsList;

        this->perspectiveProjectionUseCase->execute(
            object,
            centerOfProjection,
            windowCenter,
            windowWidth,
            windowHeight,
            viewportWidth,
            viewportHeight,
            distanceFromProjection,
            alpha,
            beta
        );


        QList<Coordinate> resultNormalizedPointsList = object->getNormalizedPoints();

        for (qsizetype i = 0; i < expectedNormalizedPointsList.size(); i++) 
        {
             FrameworkTest::expectToBeEqual(
                "Deve normalizar o ponto " + pointsList[i].toString() + " dentro do plano XZ, resultando no ponto " + expectedNormalizedPointsList[i].toString(),
                resultNormalizedPointsList[i],
                expectedNormalizedPointsList[i]
            );
        }
    }
};