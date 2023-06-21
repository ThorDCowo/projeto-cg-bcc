#include "../../core/entities/polygon.h"
#include "../../core/entities/object.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"

class ObjectTest : public TestSuite {
private:
    

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
        QList<pair<qsizetype, qsizetype>> edges;
        
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

        int width = 854;
        int height = 480;
        float distanceFromProjection = 10.0;
        float alpha = 90.0;
        float beta = 90.0;

        Coordinate centerOfProjection = Coordinate::zero();
        Coordinate windowCenter = Coordinate(width / 2, height / 2);

        this->perspectiveProjectionUseCase->execute(
            object,
            centerOfProjection,
            windowCenter,
            width,
            height,
            distanceFromProjection,
            alpha,
            beta
        );

        QList<Coordinate> expectedProjectionPointsList;       
        QList<Coordinate> expectedNormalizedPointsList;       

    }
};