#include <iostream>
#include <cmath>

#include "../../data/entities/polygon.h"
#include "../../data/entities/object.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"
#include "../../helper/geometric.helper.h"

class ObjectTest : public TestSuite {
private:
    

public:
    ObjectTest() : TestSuite() {}

    void run()
    {
        cout << "-----------------------" << endl;
        cout << "Teste de planeProjection()" << endl;
        cout << "-----------------------" << endl;

        this->pyramidPlaneProjectionTest();

        cout << "-----------------------" << endl;
        cout << "Teste de orthogonalProjection()" << endl;
        cout << "-----------------------" << endl;

        this->shouldProjectPointsInPlaneXYTest();      
        this->shouldProjectPointsInPlaneXZTest();
        this->shouldProjectPointsInPlaneYZTest();

        cout << "-----------------------" << endl;
        cout << "Teste de orthogonalNormalize()" << endl;
        cout << "-----------------------" << endl;
        orthogonalNormalizeInXYTest();
        orthogonalNormalizeInXZTest();
        orthogonalNormalizeInYZTest();

        cout << "-----------------------" << endl;
        cout << "Teste de rotateWorld()" << endl;
        cout << "-----------------------" << endl;
        rotateWorldInX();
        rotateWorldInY();
        // rotateWorldInZ();
    }

    void pyramidPlaneProjectionTest()
    {
        float distanceFromProjection = 10.0;
        
        /*
            Piramide triangular, base GJI
            G = (-2.0, 4.0, 0.0)                      G -> L
            J = (-4.0, 4.0, 0.0)                      J -> N
            I = (-4.0, 6.0, 0.0)                      I -> M
            H = (-3.0, 5.0, 2.0) -> Topo da piramide  H -> K
        */

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
            Qt::red
        );

        QList<Coordinate> expectedProjectionPointsList;
        expectedProjectionPointsList.append((Coordinate(-1.5, 3.0, 10.0)));
        expectedProjectionPointsList.append((Coordinate(-3.0, 3.0, 10.0)));
        expectedProjectionPointsList.append((Coordinate(-2.0, 3.0, 10.0)));
        expectedProjectionPointsList.append((Coordinate(-15.0, 25.0, 10.0)));

        pyramid->planeProjection(distanceFromProjection);

        QList<Coordinate> resultProjectionPointsList = pyramid->getProjectionPoints();

        for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                "Deve projetar o ponto" + pointsList[i].toString() + " em " + expectedProjectionPointsList[i].toString(),
                resultProjectionPointsList[i],
                expectedProjectionPointsList[i]
            );
        }
    }

    void shouldProjectPointsInPlaneYZTest() 
    {
        /*
            Piramide triangular, base GJI
            G = (-2.0, 4.0, 0.0)                      G -> L
            J = (-4.0, 4.0, 0.0)                      J -> N
            I = (-4.0, 6.0, 0.0)                      I -> M
            H = (-3.0, 5.0, 2.0) -> Topo da piramide  H -> K
        */

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
            Qt::red
        );

        QList<Coordinate> expectedProjectionPointsList;
        expectedProjectionPointsList.append(Coordinate(4.0, 0.0));
        expectedProjectionPointsList.append(Coordinate(4.0, 0.0));
        expectedProjectionPointsList.append(Coordinate(6.0, 0.0));
        expectedProjectionPointsList.append(Coordinate(5.0, 2.0));

        pyramid->orthogonalProjection(Coordinate::axisX());

        QList<Coordinate> resultProjectionPointsList = pyramid->getProjectionPoints();

        for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                "Deve projetar o ponto" + pointsList[i].toString() + " no plano YZ",
                resultProjectionPointsList[i],
                expectedProjectionPointsList[i]
            );
        }
    }

    void shouldProjectPointsInPlaneXZTest() 
    {
       /*
            Piramide triangular, base GJI
            G = (-2.0, 4.0, 0.0)                      G -> L
            J = (-4.0, 4.0, 0.0)                      J -> N
            I = (-4.0, 6.0, 0.0)                      I -> M
            H = (-3.0, 5.0, 2.0) -> Topo da piramide  H -> K
        */

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
            Qt::red
        );

        QList<Coordinate> expectedProjectionPointsList;
        expectedProjectionPointsList.append(Coordinate(-2.0, 0.0));
        expectedProjectionPointsList.append(Coordinate(-4.0, 0.0));
        expectedProjectionPointsList.append(Coordinate(-4.0, 0.0));
        expectedProjectionPointsList.append(Coordinate(-3.0, 2.0));

        pyramid->orthogonalProjection(Coordinate::axisY());

        QList<Coordinate> resultProjectionPointsList = pyramid->getProjectionPoints();

        for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                "Deve projetar o ponto" + pointsList[i].toString() + " no plano XZ",
                resultProjectionPointsList[i],
                expectedProjectionPointsList[i]
            );
        }
    }
   
    void shouldProjectPointsInPlaneXYTest() 
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
            Qt::red
        );

        QList<Coordinate> expectedProjectionPointsList;
        expectedProjectionPointsList.append(Coordinate(-2.0, 4.0));
        expectedProjectionPointsList.append(Coordinate(-4.0, 4.0));
        expectedProjectionPointsList.append(Coordinate(-4.0, 6.0));
        expectedProjectionPointsList.append(Coordinate(-3.0, 5.0));

        // Act
        pyramid->orthogonalProjection(Coordinate::axisZ());
        
        // Assert
        QList<Coordinate> resultProjectionPointsList = pyramid->getProjectionPoints();

        for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                 "Deve projetar o ponto" + pointsList[i].toString() + " no plano XY",
                resultProjectionPointsList[i],
                expectedProjectionPointsList[i]
            );
        }
    }
   

   void orthogonalNormalizeInYZTest()
   {
        int windowWidth = 854;
        int windowHeight = 480;
        Coordinate windowCenter(windowWidth / 2.0, windowHeight / 2.0);
        Coordinate axisToExclude = Coordinate::axisX();
        
        /*
            Piramide triangular, base GJI
            G = (-2.0, 4.0, 0.0)                      G -> L
            J = (-4.0, 4.0, 0.0)                      J -> N
            I = (-4.0, 6.0, 0.0)                      I -> M
            H = (-3.0, 5.0, 2.0) -> Topo da piramide  H -> K
        */

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
            Qt::red
        );

        QList<Coordinate> expectedNormalizedPointsList;
        expectedNormalizedPointsList.append(Coordinate(4.0, windowHeight));
        expectedNormalizedPointsList.append(Coordinate(4.0, windowHeight));
        expectedNormalizedPointsList.append(Coordinate(6.0, windowHeight));
        expectedNormalizedPointsList.append(Coordinate(5.0, windowHeight - 2.0));

        pyramid->orthogonalNormalize(windowWidth, windowHeight, windowCenter, axisToExclude);

        QList<Coordinate> resultNormalizedPointsList = pyramid->getNormalizedPoints();

        Coordinate a(-2.0, 4.0, 0.0);
        Coordinate b(4.0, windowHeight);

        for (qsizetype i = 0; i < expectedNormalizedPointsList.size(); i++) 
        {
             FrameworkTest::expectToBeEqual(
                "Deve normalizar o ponto " + pointsList[i].toString() + " dentro do plano YZ, resultando no ponto " + expectedNormalizedPointsList[i].toString(),
                resultNormalizedPointsList[i],
                expectedNormalizedPointsList[i]
            );
        }
   }
   
   void orthogonalNormalizeInXZTest()
   {
        int windowWidth = 854;
        int windowHeight = 480;
        Coordinate windowCenter(windowWidth / 2.0, windowHeight / 2.0);
        Coordinate axisToExclude = Coordinate::axisY();
        /*
            Piramide triangular, base GJI
            G = (-2.0, 4.0, 0.0)                      G -> L
            J = (-4.0, 4.0, 0.0)                      J -> N
            I = (-4.0, 6.0, 0.0)                      I -> M
            H = (-3.0, 5.0, 2.0) -> Topo da piramide  H -> K
        */

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
            Qt::red
        );

        QList<Coordinate> expectedProjectionPointsList;
        expectedProjectionPointsList.append(Coordinate(-2.0, windowHeight));
        expectedProjectionPointsList.append(Coordinate(-4.0, windowHeight));
        expectedProjectionPointsList.append(Coordinate(-4.0, windowHeight));
        expectedProjectionPointsList.append(Coordinate(-3.0, windowHeight - 2.0));

        pyramid->orthogonalNormalize(windowWidth, windowHeight, windowCenter, axisToExclude);

        QList<Coordinate> resultProjectionPointsList = pyramid->getNormalizedPoints();

        for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) 
        {
             FrameworkTest::expectToBeEqual(
                "Deve normalizar o ponto " + pointsList[i].toString() + " dentro do plano XZ, resultando no ponto " + expectedProjectionPointsList[i].toString(),
                resultProjectionPointsList[i],
                expectedProjectionPointsList[i]
            );
        }
   }

   void orthogonalNormalizeInXYTest()
   {
        int windowWidth = 854;
        int windowHeight = 480;
        Coordinate windowCenter(windowWidth / 2.0, windowHeight / 2.0);
        Coordinate axisToExclude = Coordinate::axisZ();
        /*
            Piramide triangular, base GJI
            G = (-2.0, 4.0, 0.0)                      G -> L
            J = (-4.0, 4.0, 0.0)                      J -> N
            I = (-4.0, 6.0, 0.0)                      I -> M
            H = (-3.0, 5.0, 2.0) -> Topo da piramide  H -> K
        */

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
            Qt::red
        );

        QList<Coordinate> expectedProjectionPointsList;
        expectedProjectionPointsList.append(Coordinate(-2.0, windowHeight - 4.0));
        expectedProjectionPointsList.append(Coordinate(-4.0, windowHeight - 4.0));
        expectedProjectionPointsList.append(Coordinate(-4.0, windowHeight - 6.0));
        expectedProjectionPointsList.append(Coordinate(-3.0, windowHeight - 5.0));

        pyramid->orthogonalNormalize(windowWidth, windowHeight, windowCenter, axisToExclude);

        QList<Coordinate> resultProjectionPointsList = pyramid->getNormalizedPoints();

        for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) 
        {
            // cout << "Resultado: " << resultProjectionPointsList[i].toString() << endl;
            // cout << "Esperado: " << expectedProjectionPointsList[i].toString() << endl;
             FrameworkTest::expectToBeEqual(
                "Deve normalizar o ponto " + pointsList[i].toString() + " dentro do plano XY, resultando no ponto " + expectedProjectionPointsList[i].toString(),
                resultProjectionPointsList[i],
                expectedProjectionPointsList[i]
            );
        }
   }

   void rotateWorldInX() 
    {
        /*
            Piramide quadrada, base ABCD
            A = (200.0, 200.0, 0.0)
            B = (400.0, 400.0, 0.0)
            C = (400.0, 350.0, 0.0)
            D = (200.0, 350.0, 0.0)
            E = (300.0, 275.0, 250.0)
        */

        float angleInDegrees = 90.0f;
        float radians =  qDegreesToRadians(angleInDegrees);

        Coordinate axis = Coordinate::axisX();

        QList<Coordinate> pointsList;       
        pointsList.append(Coordinate(200.0, 200.0, 0.0));
        pointsList.append(Coordinate(400.0, 200.0, 0.0));
        pointsList.append(Coordinate(400.0, 350.0, 0.0));
        pointsList.append(Coordinate(200.0, 350.0, 0.0));
        pointsList.append(Coordinate(300.0, 275.0, 250.0));
        
        QList<pair<int, int>> edges;
        edges.append({0, 1});
        edges.append({0, 3});
        edges.append({0, 4});
        edges.append({1, 2});
        edges.append({1, 4});
        edges.append({2, 3});
        edges.append({2, 4});

        
        Object* pyramid = new Polygon(
            QString("Piramide Triangular"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedPointsList;
        expectedPointsList.append(Coordinate(200.0, -0.0, 200.0));
        expectedPointsList.append(Coordinate(400.0, -0.0, 200.0));
        expectedPointsList.append(Coordinate(400.0, -0.0, 350.0));
        expectedPointsList.append(Coordinate(200.0, -0.0, 350.0));
        expectedPointsList.append(Coordinate(300.0, -250.0, 275.0));

        pyramid->rotateWorld(radians, axis);
        
        QList<Coordinate> resultPointsList = pyramid->getPoints();

        for (qsizetype i = 0; i < expectedPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                "Deve rotacionar o mundo pelo eixo X, movendo o ponto" + 
                    pointsList[i].toString() + " para " + 
                    expectedPointsList[i].toString(),
                resultPointsList[i],
                expectedPointsList[i]
            );
        }
    }


   void rotateWorldInY() 
    {
        /*
            Piramide quadrada, base ABCD
            A = (200.0, 200.0, 0.0)
            B = (400.0, 400.0, 0.0)
            C = (400.0, 350.0, 0.0)
            D = (200.0, 350.0, 0.0)
            E = (300.0, 275.0, 250.0)
        */

        double angleInDegrees = 0.0f;
        double radians =  angleInDegrees * M_PI / 180;
        cout << "Degrees: " << angleInDegrees << endl;
        cout << "Radianos: " << radians << endl;

        cout << "Cos(rad): " << cosHelper(qDegreesToRadians(90.0)) << endl;
        cout << "Sin(rad): " << sinHelper(radians) << endl;

        cout << "Cos(deg): " << cosHelper(angleInDegrees) << endl;
        cout << "Sin(deg): " << sinHelper(angleInDegrees) << endl;
        Coordinate axis = Coordinate::axisY();

        QList<Coordinate> pointsList;       
        pointsList.append(Coordinate(200.0, 0.0, 200.0));
        pointsList.append(Coordinate(400.0, 0.0, 200.0));
        pointsList.append(Coordinate(400.0, 0.0, 350.0));
        pointsList.append(Coordinate(200.0, 0.0, 350.0));
        pointsList.append(Coordinate(300.0, -250.0, 275.0));
        
        QList<pair<int, int>> edges;
        edges.append({0, 1});
        edges.append({0, 3});
        edges.append({0, 4});
        edges.append({1, 2});
        edges.append({1, 4});
        edges.append({2, 3});
        edges.append({2, 4});

        
        Object* pyramid = new Polygon(
            QString("Piramide Triangular"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedPointsList;
        expectedPointsList.append(Coordinate(200.0, 0.0, -200.0));
        expectedPointsList.append(Coordinate(200.0, 0.0, -400.0));
        expectedPointsList.append(Coordinate(350.0, 0.0, -400.0));
        expectedPointsList.append(Coordinate(350.0, 0.0, -200.0));
        expectedPointsList.append(Coordinate(275.0, -250.0, -300.0));

        pyramid->rotateWorld(radians, axis);
        
        QList<Coordinate> resultPointsList = pyramid->getPoints();

        for (qsizetype i = 0; i < expectedPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                 "Deve rotacionar o mundo pelo eixo Y, movendo o ponto" + 
                    pointsList[i].toString() + " para " + 
                    expectedPointsList[i].toString(),
                resultPointsList[i],
                expectedPointsList[i]
            );
        }
    }

   void rotateWorldInZ() 
    {
        /*
            Piramide quadrada, base ABCD
            A = (200.0, 200.0, 0.0)
            B = (400.0, 400.0, 0.0)
            C = (400.0, 350.0, 0.0)
            D = (200.0, 350.0, 0.0)
            E = (300.0, 275.0, 250.0)
        */

        float angleInDegrees = 90.0f;
        float radians =  qDegreesToRadians(angleInDegrees);

        Coordinate axis = Coordinate::axisY();

        QList<Coordinate> pointsList;       
        pointsList.append(Coordinate(200.0, 0.0, 200.0));
        pointsList.append(Coordinate(400.0, 0.0, 200.0));
        pointsList.append(Coordinate(400.0, 0.0, 350.0));
        pointsList.append(Coordinate(200.0, 0.0, 350.0));
        pointsList.append(Coordinate(300.0, -250.0, 275.0));
        
        QList<pair<int, int>> edges;
        edges.append({0, 1});
        edges.append({0, 3});
        edges.append({0, 4});
        edges.append({1, 2});
        edges.append({1, 4});
        edges.append({2, 3});
        edges.append({2, 4});

        
        Object* pyramid = new Polygon(
            QString("Piramide Triangular"),
            QList(pointsList),
            QList(edges),
            Qt::blue
        );

        QList<Coordinate> expectedPointsList;
        expectedPointsList.append(Coordinate(200.0, 0.0, -200.0));
        expectedPointsList.append(Coordinate(200.0, 0.0, -400.0));
        expectedPointsList.append(Coordinate(350.0, 0.0, -400.0));
        expectedPointsList.append(Coordinate(350.0, 0.0, -200.0));
        expectedPointsList.append(Coordinate(275.0, -250.0, -300.0));

        pyramid->rotateWorld(radians, axis);
        
        QList<Coordinate> resultPointsList = pyramid->getPoints();

        for (qsizetype i = 0; i < expectedPointsList.size(); i++) {
             FrameworkTest::expectToBeEqual(
                 "Deve rotacionar o mundo pelo eixo Y, movendo o ponto" + 
                    pointsList[i].toString() + " para " + 
                    expectedPointsList[i].toString(),
                resultPointsList[i],
                expectedPointsList[i]
            );
        }
    }
};