#include "line.h"
#include "object.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"



class LineTest : public TestSuite {
public:
    LineTest() : TestSuite() {}

    void run()
    {
        cout << "-----------------------" << endl;
        cout << "Teste da translate()" << endl;
        cout << "-----------------------" << endl;
        translateTest(Coordinate(2.0, 2.0, 2.0));
        rotateTestAxisX();
        rotateTestAxisY();
        rotateTestAxisZ();

    }

    void translateTest(Coordinate translation) 
    {
        /*
            Reta AB, 
            A = (-2.0, 4.0, 0.0)                      
            B = (-4.0, 4.0, 0.0)                      

        */

        //Arrange

        QList<Coordinate> pointsList;       
        pointsList.append(Coordinate(-2.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 4.0, 0.0));

        QList<pair<int, int>> edges;
        edges.append({0, 1});

        Line* line = new Line(
            QString("Reta AB"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedTranslatedPointsList;
        expectedTranslatedPointsList.append(Coordinate(0.0, 6.0, 2.0));
        expectedTranslatedPointsList.append(Coordinate(-2.0, 6.0, 2.0));

        // Act
        line->translate(translation);
        
        // Assert
        QList<Coordinate> resultProjectionPointsList = line->getPoints();

        for (qsizetype i = 0; i < expectedTranslatedPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                 "Deve transladar a reta em" + translation.toString(),
                resultProjectionPointsList[i],
                expectedTranslatedPointsList[i]
            );
        }
    }

    void rotateTestAxisX() {
        QList<Coordinate> pointsList;
        float angleInDegrees = 90.0;
        float teta = qDegreesToRadians(angleInDegrees);

        pointsList.append(Coordinate(-2.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 4.0, 0.0));

        QList<pair<int, int>> edges;
        edges.append({0, 1});

        Line* line = new Line(
            QString("Reta AB"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedTranslatedPointsList;
        expectedTranslatedPointsList.append(Coordinate(-2.0, 0.0, 4.0));
        expectedTranslatedPointsList.append(Coordinate(-4.0, 0.0, 4.0));

        // Act
        line->rotate(teta, Coordinate::axisX());
        
        // Assert
        QList<Coordinate> resultProjectionPointsList = line->getPoints();

        for (qsizetype i = 0; i < expectedTranslatedPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                 "Deve rotacionar a reta no eixo X em " + to_string(teta),
                resultProjectionPointsList[i],
                expectedTranslatedPointsList[i]
            );
        }
    }

    void rotateTestAxisY() {
        QList<Coordinate> pointsList;
        float angleInDegrees = 90.0;
        float teta = qDegreesToRadians(angleInDegrees);


        pointsList.append(Coordinate(-2.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 4.0, 0.0));

        QList<pair<int, int>> edges;
        edges.append({0, 1});

        Line* line = new Line(
            QString("Reta AB"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedTranslatedPointsList;
        expectedTranslatedPointsList.append(Coordinate(0.0, 4.0, 2.0));
        expectedTranslatedPointsList.append(Coordinate(0.0, 4.0, 4.0));

        // Act
        line->rotate(teta, Coordinate::axisY());
        
        // Assert
        QList<Coordinate> resultProjectionPointsList = line->getPoints();

        for (qsizetype i = 0; i < expectedTranslatedPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                 "Deve rotacionar a reta no eixo Y em " + to_string(teta),
                resultProjectionPointsList[i],
                expectedTranslatedPointsList[i]
            );
        }
    }

    void rotateTestAxisZ() {
        QList<Coordinate> pointsList;
        float angleInDegrees = 90.0;
        float teta = qDegreesToRadians(angleInDegrees);

        pointsList.append(Coordinate(-2.0, 4.0, 0.0));
        pointsList.append(Coordinate(-4.0, 4.0, 0.0));

        QList<pair<int, int>> edges;
        edges.append({0, 1});

        Line* line = new Line(
            QString("Reta AB"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedTranslatedPointsList;
        expectedTranslatedPointsList.append(Coordinate(-4.0, -2.0, 0.0));
        expectedTranslatedPointsList.append(Coordinate(-4.0, -4.0, 0.0));

        // Act
        line->rotate(teta, Coordinate::axisZ());
        
        // Assert
        QList<Coordinate> resultProjectionPointsList = line->getPoints();

        for (qsizetype i = 0; i < expectedTranslatedPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                "Deve rotacionar a reta no eixo Z em " + to_string(teta),
                resultProjectionPointsList[i],
                expectedTranslatedPointsList[i]
            );
        }
    }
};