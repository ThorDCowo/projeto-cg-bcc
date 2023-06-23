#include <iostream>
#include <vector>
#include <cmath>

#include "../../data/entities/object.h"
#include "../../data/entities/border.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"
#include "clipper.h"

#include "../../data/interfaces/comparable.h"

class ClipperTest : public TestSuite {
private:
    Clipper* clipper;

public:
    ClipperTest(Clipper* clipper) : TestSuite() {
        this->clipper = clipper;
    }

    void run()
    {
        cout << "-----------------------" << endl;
        cout << "Teste de lineClipping()" << endl;
        cout << "-----------------------" << endl;

        this->lineClippingTest2();
        this->lineClippingTest3();
        this->lineClippingTest4();
        this->lineClippingTest5();
        this->lineClippingTest6();
        this->lineClippingTest7();
        this->lineClippingTest8();
        this->lineClippingTest9();
        this->lineClippingTest10();
        this->lineClippingTest11();
        this->lineClippingTestCritical1();
        this->lineClippingTestCritical2();
        
    }

    // F - E Line
    void lineClippingTest2()
    {
        QList<pair<int,int>> edgesListToDraw;
        QList<Coordinate> pointsListToDraw;
        int width = 15;
        int height = 10;
        Coordinate center(7.5, 5.0);
        Border border(width, height, center);

        pair<int,int> edge = {0,1};

        QList<Coordinate> pointsList;

        Coordinate insidePoint(5, 7);
        Coordinate outsidePoint(-5, 2);

        pointsList.append(insidePoint);
        pointsList.append(outsidePoint);
        
        Coordinate expectedValue(0, 4.5);

        this->clipper->lineClipping(
            border,
            edge,
            &pointsList,
            &edgesListToDraw,
            &pointsListToDraw
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clipping pela esquerda alterarndo o ponto de fora para (0, 4.5)",
            pointsList[edge.second],
            expectedValue
        );
    }

    // K - L Line
    void lineClippingTest3()
    {
        QList<pair<int,int>> edgesListToDraw;
        QList<Coordinate> pointsListToDraw;
        int width = 15;
        int height = 10;
        Coordinate center(7.5, 5.0);
        Border border(width, height, center);

        pair<int,int> edge = {0,1};

        QList<Coordinate> pointsList;

        Coordinate upperLeftPoint(-6, 14);
        Coordinate lowerRightPoint(20, -5);

        pointsList.append(upperLeftPoint);
        pointsList.append(lowerRightPoint);
        
        Coordinate expectedValueForLowerRightPoint(1315, 0);
        Coordinate expectedValueForUpperLeftPoint(0, 961);

        this->clipper->lineClipping(
            border,
            edge,
            &pointsList,
            &edgesListToDraw,
            &pointsListToDraw
        );

        pointsList[edge.second].x = truncl(pointsList[edge.second].x * 100);
        pointsList[edge.second].y = truncl(pointsList[edge.second].y * 100);
        
        pointsList[edge.first].x = truncl(pointsList[edge.first].x * 100);
        pointsList[edge.first].y = truncl(pointsList[edge.first].y * 100);

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clippling o clipping por baixo alterarndo o ponto (20, -5) para (13.15, 0)",
            pointsList[edge.second],
            expectedValueForLowerRightPoint
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clippling o clipping por esquerda alterarndo o ponto (-6, 14) para (0, 9.61)",
            pointsList[edge.first],
            expectedValueForUpperLeftPoint
        );
    }

    // R - Q Line
    void lineClippingTest4()
    {
        QList<pair<int,int>> edgesListToDraw;
        QList<Coordinate> pointsListToDraw;
        int width = 15;
        int height = 10;
        Coordinate center(7.5, 5.0);
        Border border(width, height, center);

        pair<int,int> edge = {0,1};

        QList<Coordinate> pointsList;

        Coordinate insidePoint(2, 2);
        Coordinate outsidePoint(6, -2);

        pointsList.append(insidePoint);
        pointsList.append(outsidePoint);
        
        Coordinate expectedValue(4, 0);

        this->clipper->lineClipping(
            border,
            edge,
            &pointsList,
            &edgesListToDraw,
            &pointsListToDraw
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clipping por baixo alterarndo o ponto de fora para (4, 0)",
            pointsList[edge.second],
            expectedValue
        );
    }

    //J - I Line
    void lineClippingTest5()
    {
        QList<pair<int,int>> edgesListToDraw;
        QList<Coordinate> pointsListToDraw;
        int width = 15;
        int height = 10;
        Coordinate center(7.5, 5.0);
        Border border(width, height, center);

        pair<int,int> edge = {0,1};

        QList<Coordinate> pointsList;

        Coordinate insidePoint(11, 4);
        Coordinate outsidePoint(20, 13);

        pointsList.append(insidePoint);
        pointsList.append(outsidePoint);
        
        Coordinate expectedValue(15, 8);

        this->clipper->lineClipping(
            border,
            edge,
            &pointsList,
            &edgesListToDraw,
            &pointsListToDraw
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clipping pela diagonal pela direita alterarndo o ponto de fora para (15, 8)",
            pointsList[edge.second],
            expectedValue
        );
    }

    //O - P Line
    void lineClippingTest6()
    {
        QList<pair<int,int>> edgesListToDraw;
        QList<Coordinate> pointsListToDraw;
        int width = 15;
        int height = 10;
        Coordinate center(7.5, 5.0);
        Border border(width, height, center);

        pair<int,int> edge = {0,1};

        QList<Coordinate> pointsList;

        Coordinate insidePoint(8, 7);
        Coordinate outsidePoint(8, 12);

        pointsList.append(insidePoint);
        pointsList.append(outsidePoint);
        
        Coordinate expectedValue(8, 10);

        this->clipper->lineClipping(
            border,
            edge,
            &pointsList,
            &edgesListToDraw,
            &pointsListToDraw
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clipping por cima alterarndo o ponto de fora para (8, 10)",
            pointsList[edge.second],
            expectedValue
        );
    }

    // S - T Line
    void lineClippingTest7()
    {
        QList<pair<int,int>> edgesListToDraw;
        QList<Coordinate> pointsListToDraw;
        int width = 15;
        int height = 10;
        Coordinate center(7.5, 5.0);
        Border border(width, height, center);

        pair<int,int> edge = {0,1};

        QList<Coordinate> pointsList;

        Coordinate insidePoint(13, 3);
        Coordinate outsidePoint(17, 3);

        pointsList.append(insidePoint);
        pointsList.append(outsidePoint);
        
        Coordinate expectedValue(15, 3);

        this->clipper->lineClipping(
            border,
            edge,
            &pointsList,
            &edgesListToDraw,
            &pointsListToDraw
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clipping pela direita alterarndo o ponto de fora para (15, 3)",
            pointsList[edge.second],
            expectedValue
        );
    }

    //U - V Line
    void lineClippingTest8()
    {
        QList<pair<int,int>> edgesListToDraw;
        QList<Coordinate> pointsListToDraw;
        int width = 15;
        int height = 10;
        Coordinate center(7.5, 5.0);
        Border border(width, height, center);

        pair<int,int> edge = {0,1};

        QList<Coordinate> pointsList;

        Coordinate insidePoint(1, 1);
        Coordinate outsidePoint(-4, -4);

        pointsList.append(insidePoint);
        pointsList.append(outsidePoint);
        
        Coordinate expectedValue(0, 0);

        this->clipper->lineClipping(
            border,
            edge,
            &pointsList,
            &edgesListToDraw,
            &pointsListToDraw
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clipping diagonalmente passando pela quina alterarndo o ponto de fora para (0, 0)",
            pointsList[edge.second],
            expectedValue
        );
    }

    // M - N Line
    void lineClippingTest9()
    {
        QList<pair<int,int>> edgesListToDraw;
        QList<Coordinate> pointsListToDraw;
        int width = 15;
        int height = 10;
        Coordinate center(7.5, 5.0);
        Border border(width, height, center);

        pair<int,int> edge = {0,1};

        QList<Coordinate> pointsList;

        Coordinate upperPoint(3, 14);
        Coordinate upperRightPoint(18, 15);

        pointsList.append(upperPoint);
        pointsList.append(upperRightPoint);
        
        qsizetype expectedValue = 0;

        this->clipper->lineClipping(
            border,
            edge,
            &pointsList,
            &edgesListToDraw,
            &pointsListToDraw
        );

        FrameworkTest::expectToBeEqual(
            "Deve rejeitar a linha dos pontos (18, 15) e (3, 14)",
            pointsList.size(),
            expectedValue
        );
    }

    // G - H Line
    void lineClippingTest10()
    {
       
        QList<pair<int,int>> edgesListToDraw;
        QList<Coordinate> pointsListToDraw;
        int width = 15;
        int height = 10;
        Coordinate center(7.5, 5.0);
        Border border(width, height, center);

        pair<int,int> edge = {0,1};

        QList<Coordinate> pointsList;

        Coordinate left(5, 13);
        Coordinate upperPoint(-5, 8);

        pointsList.append(left);
        pointsList.append(upperPoint);
        
        qsizetype expectedValue = 0;

        this->clipper->lineClipping(
            border,
            edge,
            &pointsList,
            &edgesListToDraw,
            &pointsListToDraw
        );

        FrameworkTest::expectToBeEqual(
            "Deve rejeitar a linha dos pontos (-5, 8) e (5, 13)",
            pointsList.size(),
            expectedValue
        );

    }

    void lineClippingTest11()
    {
        QList<pair<int,int>> edgesListToDraw;
        QList<Coordinate> pointsListToDraw;
        int width = 15;
        int height = 10;
        Coordinate center(7.5, 5.0);
        Border border(width, height, center);

        pair<int,int> edge = {0,1};

        QList<Coordinate> pointsList;

        Coordinate rightPoint(17, 1);
        Coordinate lowerPoint(14, -4);

        pointsList.append(rightPoint);
        pointsList.append(lowerPoint);
        
        qsizetype expectedValue = 0;

        this->clipper->lineClipping(
            border,
            edge,
            &pointsList,
            &edgesListToDraw,
            &pointsListToDraw
        );

        //cout << "Reta com ponto no quadrante de baixo e quadrante da direita, sem passar por dentro" << endl;
        FrameworkTest::expectToBeEqual(
            "Deve rejeitar a linha dos pontos (14, -4) e (17, 1)",
            pointsList.size(),
            expectedValue
        );

    }
    
    void lineClippingTestCritical1()
    {
        QList<pair<int,int>> edgesListToDraw;
        QList<Coordinate> pointsListToDraw;
        int width = 854;
        int height = 480;
        Coordinate center(427, 240);
        Border border(width, height, center);

        pair<int,int> edge = {0,1};

        QList<Coordinate> pointsList;

        Coordinate rightPoint(1000, 100);
        Coordinate lowerRightPoint(900, -100);

        pointsList.append(rightPoint);
        pointsList.append(lowerRightPoint);
        
        qsizetype expectedValue = 0;

        this->clipper->lineClipping(
            border,
            edge,
            &pointsList,
            &edgesListToDraw,
            &pointsListToDraw
        );        

        FrameworkTest::expectToBeEqual(
            "Deve rejeitar a linha dos pontos (900, -100) e (1000, 100)",
            pointsList.size(),
            expectedValue
        );
    }

     void lineClippingTestCritical2()
    {
        QList<pair<int,int>> edgesListToDraw;
        QList<Coordinate> pointsListToDraw;
        int width = 854;
        int height = 480;
        Coordinate center(427, 240);
        Border border(width, height, center);

        pair<int,int> edge = {0,1};

        QList<Coordinate> pointsList;

        Coordinate upperLeftPoint(-1100, 666);
        Coordinate lowerRightPoint(960, -700);

        pointsList.append(upperLeftPoint);
        pointsList.append(lowerRightPoint);

        qsizetype expectedValue = 0;

        this->clipper->lineClipping(
            border,
            edge,
            &pointsList,
            &edgesListToDraw,
            &pointsListToDraw
        );

        FrameworkTest::expectToBeEqual(
            "Deve rejeitar a linha dos pontos (-1100, 666) e (960, -700), que cruza pelas quinas superior esquerda e inferior direita, mas não passa por dentro",
            pointsList.size(),
            expectedValue
        );
    }
};
