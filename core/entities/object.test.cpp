// #include <iostream>

// #include "../../core/entities/polygon.h"
// #include "../../core/entities/object.h"
// #include "../../tests/framework_test.h"
// #include "../../tests/test_suite.h"

// class ObjectTest : public TestSuite {
// private:
    

// public:
//     ObjectTest() : TestSuite() {}

//     void run()
//     {
//         cout << "-----------------------" << endl;
//         cout << "Teste de planeProjection()" << endl;
//         cout << "-----------------------" << endl;

//         this->pyramidPlaneProjectionTest();

//         cout << "-----------------------" << endl;
//         cout << "Teste de orthogonalProjection()" << endl;
//         cout << "-----------------------" << endl;

//         this->shouldProjectPointsInPlaneYZTest();
//         this->shouldProjectPointsInPlaneXZTest();
//         this->shouldProjectPointsInPlaneXYTest();      

//         cout << "-----------------------" << endl;
//         cout << "Teste de orthogonalNormalize()" << endl;
//         cout << "-----------------------" << endl;
//         orthogonalNormalizeInYZTest();
//         orthogonalNormalizeInXZTest();
//         orthogonalNormalizeInXYTest();
//     }

//     void pyramidPlaneProjectionTest()
//     {
//         float distanceFromProjection = 10.0;
        
//         QList<Coordinate> pointsList;
//         QList<Coordinate> expectedProjectionPointsList;

//         /*
//             G = (-2, 4, 0)                      G -> L
//             J = (-4, 4, 0)                      J -> N
//             I = (-4, 6, 0)                      I -> M
//             H = (-3, 5, 2) -> Topo da piramide  H -> K
//         */
//         pointsList.append(Coordinate(-2, 4, 0));
//         pointsList.append(Coordinate(-4, 4, 0));
//         pointsList.append(Coordinate(-4, 6, 0));
//         pointsList.append(Coordinate(-3, 5, 2));

//         Object* pyramid = new Polygon(QString("Piramide Triangular"), QList(pointsList), Qt::red);

//         expectedProjectionPointsList.append((Coordinate(-1.5, 3, 0)));
//         expectedProjectionPointsList.append((Coordinate(-3, 3, 0)));
//         expectedProjectionPointsList.append((Coordinate(-2, 3, 0)));
//         expectedProjectionPointsList.append((Coordinate(-1.8, 3, 1.2)));

//         pyramid->planeProjection(distanceFromProjection);

//         QList<Coordinate> resultProjectionPointsList = pyramid->getProjectionPoints();

//         for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) {
//              FrameworkTest::expectToBeEqual(
//                 "Deve projetar o ponto" + pointsList[i].toString() + " em " + expectedProjectionPointsList[i].toString(),
//                 resultProjectionPointsList[i],
//                 expectedProjectionPointsList[i]
//             );
//         }
//     }

//     void shouldProjectPointsInPlaneYZTest() 
//     {
//         QList<Coordinate> pointsList;
//         QList<Coordinate> expectedProjectionPointsList;

//         pointsList.append(Coordinate(-2, 4, 0));
//         pointsList.append(Coordinate(-4, 4, 0));
//         pointsList.append(Coordinate(-4, 6, 0));
//         pointsList.append(Coordinate(-3, 5, 2));

//         Object* pyramid = new Polygon(QString("Piramide Triangular"), QList(pointsList), Qt::red);

//         expectedProjectionPointsList.append(Coordinate(4, 0));
//         expectedProjectionPointsList.append(Coordinate(4, 0));
//         expectedProjectionPointsList.append(Coordinate(6, 0));
//         expectedProjectionPointsList.append(Coordinate(5, 2));

//         pyramid->orthogonalProjection(Coordinate::axisX());

//         QList<Coordinate> resultProjectionPointsList = pyramid->getProjectionPoints();

//         for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) {
//              FrameworkTest::expectToBeEqual(
//                 "Deve projetar o ponto" + pointsList[i].toString() + " no plano YZ",
//                 resultProjectionPointsList[i],
//                 expectedProjectionPointsList[i]
//             );
//         }
//     }

//     void shouldProjectPointsInPlaneXZTest() 
//     {
//         QList<Coordinate> pointsList;
//         QList<Coordinate> expectedProjectionPointsList;

//         pointsList.append(Coordinate(-2, 4, 0));
//         pointsList.append(Coordinate(-4, 4, 0));
//         pointsList.append(Coordinate(-4, 6, 0));
//         pointsList.append(Coordinate(-3, 5, 2));

//         Object* pyramid = new Polygon(QString("Piramide Triangular"), QList(pointsList), Qt::red);

//         expectedProjectionPointsList.append(Coordinate(-2, 0));
//         expectedProjectionPointsList.append(Coordinate(-4, 0));
//         expectedProjectionPointsList.append(Coordinate(-4, 0));
//         expectedProjectionPointsList.append(Coordinate(-3, 2));

//         pyramid->orthogonalProjection(Coordinate::axisY());

//         QList<Coordinate> resultProjectionPointsList = pyramid->getProjectionPoints();

//         for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) {
//              FrameworkTest::expectToBeEqual(
//                 "Deve projetar o ponto" + pointsList[i].toString() + " no plano XZ",
//                 resultProjectionPointsList[i],
//                 expectedProjectionPointsList[i]
//             );
//         }
//     }
   
//     void shouldProjectPointsInPlaneXYTest() 
//     {
//         QList<Coordinate> pointsList;
//         QList<Coordinate> expectedProjectionPointsList;

//         pointsList.append(Coordinate(-2, 4, 0));
//         pointsList.append(Coordinate(-4, 4, 0));
//         pointsList.append(Coordinate(-4, 6, 0));
//         pointsList.append(Coordinate(-3, 5, 2));

//         Object* pyramid = new Polygon(QString("Piramide Triangular"), QList(pointsList), Qt::red);

//         expectedProjectionPointsList.append(Coordinate(-2, 4));
//         expectedProjectionPointsList.append(Coordinate(-4, 4));
//         expectedProjectionPointsList.append(Coordinate(-4, 6));
//         expectedProjectionPointsList.append(Coordinate(-3, 5));

//         pyramid->orthogonalProjection(Coordinate::axisZ());
        
//         QList<Coordinate> resultProjectionPointsList = pyramid->getProjectionPoints();

//         for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) {
//              FrameworkTest::expectToBeEqual(
//                  "Deve projetar o ponto" + pointsList[i].toString() + " no plano XY",
//                 resultProjectionPointsList[i],
//                 expectedProjectionPointsList[i]
//             );
//         }
//     }
   

//    void orthogonalNormalizeInYZTest()
//    {
//         int windowWidth = 854;
//         int windowHeight = 480;
//         Coordinate windowCenter(windowWidth / 2, windowHeight / 2);
//         Coordinate axisToExclude = Coordinate::axisX();
//         QList<Coordinate> pointsList;

//         pointsList.append(Coordinate(-2, 4, 0));
//         pointsList.append(Coordinate(-4, 4, 0));
//         pointsList.append(Coordinate(-4, 6, 0));
//         pointsList.append(Coordinate(-3, 5, 2));

//         Object* pyramid = new Polygon(QString("Piramide Triangular"), QList(pointsList), Qt::red);

//         QList<Coordinate> expectedProjectionPointsList;

//         pyramid->orthogonalNormalize(windowWidth, windowHeight, windowCenter, axisToExclude);

//         QList<Coordinate> resultProjectionPointsList = pyramid->getProjectionPoints();

//         for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) 
//         {
//              FrameworkTest::expectToBeEqual(
//                 "Deve normalizar o ponto " + pointsList[i].toString() + " dentro do plano YZ, resultando no ponto " + expectedProjectionPointsList[i].toString(),
//                 resultProjectionPointsList[i],
//                 expectedProjectionPointsList[i]
//             );
//         }
//    }
   
//    void orthogonalNormalizeInXZTest()
//    {
//         int windowWidth = 854;
//         int windowHeight = 480;
//         Coordinate windowCenter(windowWidth / 2, windowHeight / 2);
//         Coordinate axisToExclude = Coordinate::axisX();
//         QList<Coordinate> pointsList;

//         pointsList.append(Coordinate(-2, 4, 0));
//         pointsList.append(Coordinate(-4, 4, 0));
//         pointsList.append(Coordinate(-4, 6, 0));
//         pointsList.append(Coordinate(-3, 5, 2));

//         Object* pyramid = new Polygon(QString("Piramide Triangular"), QList(pointsList), Qt::red);

//         QList<Coordinate> expectedProjectionPointsList;

//         pyramid->orthogonalNormalize(windowWidth, windowHeight, windowCenter, axisToExclude);

//         QList<Coordinate> resultProjectionPointsList = pyramid->getProjectionPoints();

//         for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) 
//         {
//              FrameworkTest::expectToBeEqual(
//                 "Deve normalizar o ponto " + pointsList[i].toString() + " dentro do plano XZ, resultando no ponto " + expectedProjectionPointsList[i].toString(),
//                 resultProjectionPointsList[i],
//                 expectedProjectionPointsList[i]
//             );
//         }
//    }

//    void orthogonalNormalizeInXYTest()
//    {
//         int windowWidth = 854;
//         int windowHeight = 480;
//         Coordinate windowCenter(windowWidth / 2, windowHeight / 2);
//         Coordinate axisToExclude = Coordinate::axisX();
//         QList<Coordinate> pointsList;

//         pointsList.append(Coordinate(-2, 4, 0));
//         pointsList.append(Coordinate(-4, 4, 0));
//         pointsList.append(Coordinate(-4, 6, 0));
//         pointsList.append(Coordinate(-3, 5, 2));

//         Object* pyramid = new Polygon(QString("Piramide Triangular"), QList(pointsList), Qt::red);

//         QList<Coordinate> expectedProjectionPointsList;

//         pyramid->orthogonalNormalize(windowWidth, windowHeight, windowCenter, axisToExclude);

//         QList<Coordinate> resultProjectionPointsList = pyramid->getProjectionPoints();

//         for (qsizetype i = 0; i < expectedProjectionPointsList.size(); i++) 
//         {
//              FrameworkTest::expectToBeEqual(
//                 "Deve normalizar o ponto " + pointsList[i].toString() + " dentro do plano XZ, resultando no ponto " + expectedProjectionPointsList[i].toString(),
//                 resultProjectionPointsList[i],
//                 expectedProjectionPointsList[i]
//             );
//         }
//    }
// };