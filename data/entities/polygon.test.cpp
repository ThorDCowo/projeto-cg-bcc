#include <iostream>
#include "polygon.h"
#include "object.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"

class PolygonTest : public TestSuite {
public:
    PolygonTest() : TestSuite() {}

    void run()
    {
        cout << "-----------------------" << endl;
        cout << "Teste da translate()" << endl;
        cout << "-----------------------" << endl;
        translateTest(Coordinate(10.0, 10.0, 10.0));

        cout << "-----------------------" << endl;
        cout << "Teste da Escala()" << endl;
        cout << "-----------------------" << endl;
        scaleTest(200);
        rotateTestAxisX();
        rotateTestAxisY();
        rotateTestAxisZ();
    }

    void translateTest(Coordinate translation) 
    {
        /*
            Piramide triangular, base GJI
            G = (-2.0, 4.0, 0.0)                      G -> L
            J = (-4.0, 4.0, 0.0)                      J -> N
            I = (-4.0, 6.0, 0.0)                      I -> M
            H = (-3.0, 5.0, 2.0) -> Topo da piramide  H -> K
        */

        //Arrange

        QList<Coordinate> pointsList;       
        pointsList.append(Coordinate(-2.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 6.0, 0.0));
        pointsList.append(Coordinate(-3.0, 5.0, 2.0));
        
        QList<pair<int, int>> edges;
        edges.append({0, 1});
        edges.append({1, 2});
        edges.append({3, 0});
        edges.append({3, 1});
        edges.append({3, 2});

        
        Object* pyramid = new Polygon(
            QString("Piramide Triangular"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedTranslatedPointsList;
        expectedTranslatedPointsList.append(Coordinate(8.0, 14.0, 10.0));
        expectedTranslatedPointsList.append(Coordinate(6.0, 14.0, 10.0));
        expectedTranslatedPointsList.append(Coordinate(6.0, 16.0, 10.0));
        expectedTranslatedPointsList.append(Coordinate(7.0, 15.0, 12.0));

        // Act
        pyramid->translate(translation);
        
        // Assert
        QList<Coordinate> resultProjectionPointsList = pyramid->getPoints();

        for (qsizetype i = 0; i < expectedTranslatedPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                 "Deve transladar a Piramide em" + translation.toString(),
                resultProjectionPointsList[i],
                expectedTranslatedPointsList[i]
            );
        }
    }

    void scaleTest(float scale) 
    {
        /*
            Piramide triangular, base GJI
            G = (-2.0, 4.0, 0.0)                      G -> L
            J = (-4.0, 4.0, 0.0)                      J -> N
            I = (-4.0, 6.0, 0.0)                      I -> M
            H = (-3.0, 5.0, 2.0) -> Topo da piramide  H -> K
        */

        //Arrange

        QList<Coordinate> pointsList;       
        pointsList.append(Coordinate(-2.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 6.0, 0.0));
        pointsList.append(Coordinate(-3.0, 5.0, 2.0));
        
        QList<pair<int, int>> edges;
        edges.append({0, 1});
        edges.append({1, 2});
        edges.append({3, 0});
        edges.append({3, 1});
        edges.append({3, 2});

        
        Object* pyramid = new Polygon(
            QString("Piramide Triangular"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedPointsInScaleList;
        expectedPointsInScaleList.append(Coordinate(8.0, 14.0, 10.0));
        expectedPointsInScaleList.append(Coordinate(6.0, 14.0, 10.0));
        expectedPointsInScaleList.append(Coordinate(6.0, 16.0, 10.0));
        expectedPointsInScaleList.append(Coordinate(7.0, 15.0, 12.0));

        // Act
        pyramid->scale(scale);
        
        // Assert
        QList<Coordinate> resultProjectionPointsList = pyramid->getPoints();

        for (qsizetype i = 0; i < expectedPointsInScaleList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                 "Deve aumentar a escala da Piramide em" + to_string(scale),
                resultProjectionPointsList[i],
                expectedPointsInScaleList[i]
            );
        }
    }

    void rotateTestAxisX() {
        QList<Coordinate> pointsList;
        float angleInDegrees = 90.0;
        float teta = qDegreesToRadians(angleInDegrees);

        pointsList.append(Coordinate(-2.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 6.0, 0.0));
        pointsList.append(Coordinate(-3.0, 5.0, 2.0));
        
        QList<pair<int, int>> edges;
        edges.append({0, 1});
        edges.append({1, 2});
        edges.append({3, 0});
        edges.append({3, 1});
        edges.append({3, 2});
        
        Object* pyramid = new Polygon(
            QString("Piramide Triangular"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedRotatePointsList;
        expectedRotatePointsList.append(Coordinate(-2.0, 0.0, 4.0));
        expectedRotatePointsList.append(Coordinate(-4.0, 0.0, 4.0));
        expectedRotatePointsList.append(Coordinate(-4.0, 0.0, 6.0));
        expectedRotatePointsList.append(Coordinate(-3.0, -2.0, 5.0));

        // Act
        pyramid->rotate(teta, Coordinate::axisX());
        
        // Assert
        QList<Coordinate> resultProjectionPointsList = pyramid->getPoints();

        for (qsizetype i = 0; i < expectedRotatePointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                 "Deve rotacionar a reta no eixo X em " + to_string(teta),
                resultProjectionPointsList[i],
                expectedRotatePointsList[i]
            );
        }
    }

    void rotateTestAxisY() {
        QList<Coordinate> pointsList;
        float angleInDegrees = 90.0;
        float teta = qDegreesToRadians(angleInDegrees);

        pointsList.append(Coordinate(-2.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 6.0, 0.0));
        pointsList.append(Coordinate(-3.0, 5.0, 2.0));
        
        QList<pair<int, int>> edges;
        edges.append({0, 1});
        edges.append({1, 2});
        edges.append({3, 0});
        edges.append({3, 1});
        edges.append({3, 2});

        
        Object* pyramid = new Polygon(
            QString("Piramide Triangular"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedRotatePointsList;
        expectedRotatePointsList.append(Coordinate(0.0, 4.0, 2.0));
        expectedRotatePointsList.append(Coordinate(0.0, 4.0, 4.0));
        expectedRotatePointsList.append(Coordinate(0.0, 6.0, 40.0));
        expectedRotatePointsList.append(Coordinate(2.0, 5.0, 3.0));

        // Act
        pyramid->rotate(teta, Coordinate::axisY());
        
        // Assert
        QList<Coordinate> resultProjectionPointsList = pyramid->getPoints();

        for (qsizetype i = 0; i < expectedRotatePointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                 "Deve rotacionar a reta no eixo X em " + to_string(teta),
                resultProjectionPointsList[i],
                expectedRotatePointsList[i]
            );
        }
    }

    void rotateTestAxisZ() {
        QList<Coordinate> pointsList;
        float angleInDegrees = 90.0;
        float teta = qDegreesToRadians(angleInDegrees);

        pointsList.append(Coordinate(-2.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 6.0, 0.0));
        pointsList.append(Coordinate(-3.0, 5.0, 2.0));
        
        QList<pair<int, int>> edges;
        edges.append({0, 1});
        edges.append({1, 2});
        edges.append({3, 0});
        edges.append({3, 1});
        edges.append({3, 2});

        
        Object* pyramid = new Polygon(
            QString("Piramide Triangular"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedRotatePointsList;
        expectedRotatePointsList.append(Coordinate(-4.0, -2.0, 0.0));
        expectedRotatePointsList.append(Coordinate(-4.0, -4.0, 0.0));
        expectedRotatePointsList.append(Coordinate(-6.0, -4.0, 0.0));
        expectedRotatePointsList.append(Coordinate(-5.0, -3.0, 2.0));

        // Act
        pyramid->rotate(teta, Coordinate::axisZ());
        
        // Assert
        QList<Coordinate> resultProjectionPointsList = pyramid->getPoints();

        for (qsizetype i = 0; i < expectedRotatePointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                 "Deve rotacionar a reta no eixo X em " + to_string(teta),
                resultProjectionPointsList[i],
                expectedRotatePointsList[i]
            );
        }
    }
};