#include "point.h"
#include "polygon.h"

#include "object.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"

class PointTest : public TestSuite {
public:
    PointTest() : TestSuite() {}

    void run()
    {
        cout << "-----------------------" << endl;
        cout << "Teste da translate()" << endl;
        cout << "-----------------------" << endl;
        translateTest(Coordinate(2.0, 2.0, 2.0));

    }

    void translateTest(Coordinate translation) 
    {
        /*
            Ponto Z, 
            Z = (-2.0, 4.0, 0.0)                                       
         */

        //Arrange

        QList<Coordinate> pointsList;
        pointsList.append(Coordinate(-2.0, 4.0, 0.0));

        QList<pair<int, int>> edges;
        edges.append({0,0});
        Object* point = new Point(
            QString("Ponto P"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedTranslatedPointsList;
        expectedTranslatedPointsList.append(Coordinate(0.0, 6.0, 2.0));

        // Act
        point->translate(translation);
        
        // Assert
        QList<Coordinate> resultProjectionPointsList = point->getPoints();

        for (qsizetype i = 0; i < expectedTranslatedPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                 "Deve transladar a reta em" + translation.toString(),
                resultProjectionPointsList[i],
                expectedTranslatedPointsList[i]
            );
        }
    }
};