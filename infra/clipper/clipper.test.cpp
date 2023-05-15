#include <iostream>
#include <vector>
#include <cmath>


#include "../../core/entities/object.h"
#include "../../core/entities/border.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"
#include "../../tests/object_test.h"
#include "clipper.h"

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
        int width = 15;
        int height = 10;
        pair<float, float> center = {7.5, 5.0};
        Border border(width, height, center);

        qsizetype insidePointIndex = 0;
        qsizetype outsidePointIndex = 1;

        QList<pair<float,float>> pointsList;

        pair<float, float> insidePoint(5, 7);
        pair<float, float> outsidePoint(-5, 2);

        pointsList.append(insidePoint);
        pointsList.append(outsidePoint);
        
        pair<float, float> expectedValue(0, 4.5);

        this->clipper->lineClipping(
            border,
            insidePointIndex,
            outsidePointIndex,
            &pointsList
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clipping pela esquerda alterarndo o ponto de fora para (0, 4.5)",
            pointsList[outsidePointIndex],
            expectedValue
        );
    }

    // K - L Line
    void lineClippingTest3()
    {
        int width = 15;
        int height = 10;
        pair<float, float> center = {7.5, 5.0};
        Border border(width, height, center);

        qsizetype upperLeftPointIndex = 0;
        qsizetype lowerRightPointIndex = 1;

        QList<pair<float,float>> pointsList;

        pair<float, float> upperLeftPoint(-6, 14);
        pair<float, float> lowerRightPoint(20, -5);

        pointsList.append(upperLeftPoint);
        pointsList.append(lowerRightPoint);
        
        pair<float, float> expectedValueForLowerRightPoint(1315, 0);
        pair<float, float> expectedValueForUpperLeftPoint(0, 961);

        this->clipper->lineClipping(
            border,
            upperLeftPointIndex,
            lowerRightPointIndex,
            &pointsList
        );

        pointsList[lowerRightPointIndex].first = truncl(pointsList[lowerRightPointIndex].first * 100);
        pointsList[lowerRightPointIndex].second = truncl(pointsList[lowerRightPointIndex].second * 100);
        
        pointsList[upperLeftPointIndex].first = truncl(pointsList[upperLeftPointIndex].first * 100);
        pointsList[upperLeftPointIndex].second = truncl(pointsList[upperLeftPointIndex].second * 100);

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clippling o clipping por baixo alterarndo o ponto (20, -5) para (13.15, 0)",
            pointsList[lowerRightPointIndex],
            expectedValueForLowerRightPoint
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clippling o clipping por esquerda alterarndo o ponto (-6, 14) para (0, 9.61)",
            pointsList[upperLeftPointIndex],
            expectedValueForUpperLeftPoint
        );
    }

    // R - Q Line
    void lineClippingTest4()
    {
        int width = 15;
        int height = 10;
        pair<float, float> center = {7.5, 5.0};
        Border border(width, height, center);

        qsizetype insidePointIndex = 0;
        qsizetype outsidePointIndex = 1;

        QList<pair<float,float>> pointsList;

        pair<float, float> insidePoint(2, 2);
        pair<float, float> outsidePoint(6, -2);

        pointsList.append(insidePoint);
        pointsList.append(outsidePoint);
        
        pair<float, float> expectedValue(4, 0);

        this->clipper->lineClipping(
            border,
            insidePointIndex,
            outsidePointIndex,
            &pointsList
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clipping por baixo alterarndo o ponto de fora para (4, 0)",
            pointsList[outsidePointIndex],
            expectedValue
        );
    }

    //J - I Line
    void lineClippingTest5()
    {
        int width = 15;
        int height = 10;
        pair<float, float> center = {7.5, 5.0};
        Border border(width, height, center);

        qsizetype insidePointIndex = 0;
        qsizetype outsidePointIndex = 1;

        QList<pair<float,float>> pointsList;

        pair<float, float> insidePoint(11, 4);
        pair<float, float> outsidePoint(20, 13);

        pointsList.append(insidePoint);
        pointsList.append(outsidePoint);
        
        pair<float, float> expectedValue(15, 8);

        this->clipper->lineClipping(
            border,
            insidePointIndex,
            outsidePointIndex,
            &pointsList
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clipping pela diagonal pela direita alterarndo o ponto de fora para (15, 8)",
            pointsList[outsidePointIndex],
            expectedValue
        );
    }

    //O - P Line
    void lineClippingTest6()
    {
        int width = 15;
        int height = 10;
        pair<float, float> center = {7.5, 5.0};
        Border border(width, height, center);

        qsizetype insidePointIndex = 0;
        qsizetype outsidePointIndex = 1;

        QList<pair<float,float>> pointsList;

        pair<float, float> insidePoint(8, 7);
        pair<float, float> outsidePoint(8, 12);

        pointsList.append(insidePoint);
        pointsList.append(outsidePoint);
        
        pair<float, float> expectedValue(8, 10);

        this->clipper->lineClipping(
            border,
            insidePointIndex,
            outsidePointIndex,
            &pointsList
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clipping por cima alterarndo o ponto de fora para (8, 10)",
            pointsList[outsidePointIndex],
            expectedValue
        );
    }

    // S - T Line
    void lineClippingTest7()
    {
        int width = 15;
        int height = 10;
        pair<float, float> center = {7.5, 5.0};
        Border border(width, height, center);

        qsizetype insidePointIndex = 0;
        qsizetype outsidePointIndex = 1;

        QList<pair<float,float>> pointsList;

        pair<float, float> insidePoint(13, 3);
        pair<float, float> outsidePoint(17, 3);

        pointsList.append(insidePoint);
        pointsList.append(outsidePoint);
        
        pair<float, float> expectedValue(15, 3);

        this->clipper->lineClipping(
            border,
            insidePointIndex,
            outsidePointIndex,
            &pointsList
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clipping pela direita alterarndo o ponto de fora para (15, 3)",
            pointsList[outsidePointIndex],
            expectedValue
        );
    }

    //U - V Line
    void lineClippingTest8()
    {
        int width = 15;
        int height = 10;
        pair<float, float> center = {7.5, 5.0};
        Border border(width, height, center);

        qsizetype insidePointIndex = 0;
        qsizetype outsidePointIndex = 1;

        QList<pair<float,float>> pointsList;

        pair<float, float> insidePoint(1, 1);
        pair<float, float> outsidePoint(-4, -4);

        pointsList.append(insidePoint);
        pointsList.append(outsidePoint);
        
        pair<float, float> expectedValue(0, 0);

        this->clipper->lineClipping(
            border,
            insidePointIndex,
            outsidePointIndex,
            &pointsList
        );

        FrameworkTest::expectToBeEqual(
            "Deve realizar o clipping diagonalmente passando pela quina alterarndo o ponto de fora para (0, 0)",
            pointsList[outsidePointIndex],
            expectedValue
        );
    }

    // M - N Line
    void lineClippingTest9()
    {
        int width = 15;
        int height = 10;
        pair<float, float> center = {7.5, 5.0};
        Border border(width, height, center);

        qsizetype upperPointIndex = 0;
        qsizetype upperRightPointIndex = 1;

        QList<pair<float,float>> pointsList;

        pair<float, float> upperPoint(3, 14);
        pair<float, float> upperRightPoint(18, 15);

        pointsList.append(upperPoint);
        pointsList.append(upperRightPoint);
        
        qsizetype expectedValue = 0;

        this->clipper->lineClipping(
            border,
            upperPointIndex,
            upperRightPointIndex,
            &pointsList
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
        int width = 15;
        int height = 10;
        pair<float, float> center = {7.5, 5.0};
        Border border(width, height, center);

        qsizetype leftPointIndex = 0;
        qsizetype upperPointIndex = 1;

        QList<pair<float,float>> pointsList;

        pair<float, float> left(5, 13);
        pair<float, float> upperPoint(-5, 8);

        pointsList.append(left);
        pointsList.append(upperPoint);
        
        qsizetype expectedValue = 0;

        this->clipper->lineClipping(
            border,
            leftPointIndex,
            upperPointIndex,
            &pointsList
        );

        FrameworkTest::expectToBeEqual(
            "Deve rejeitar a linha dos pontos (-5, 8) e (5, 13)",
            pointsList.size(),
            expectedValue
        );

    }

    void lineClippingTest11()
    {
        int width = 15;
        int height = 10;
        pair<float, float> center = {7.5, 5.0};
        Border border(width, height, center);

        qsizetype lowerPointIndex = 0;
        qsizetype rightPointIndex = 1;

        QList<pair<float,float>> pointsList;

        pair<float, float> rightPoint(17, 1);
        pair<float, float> lowerPoint(14, -4);

        pointsList.append(rightPoint);
        pointsList.append(lowerPoint);
        
        qsizetype expectedValue = 0;

        this->clipper->lineClipping(
            border,
            lowerPointIndex,
            rightPointIndex,
            &pointsList
        );

        cout << "Reta com ponto no quadrante de baixo e quadrante da direita, sem passar por dentro" << endl;
        FrameworkTest::expectToBeEqual(
            "Deve rejeitar a linha dos pontos (14, -4) e (17, 1)",
            pointsList.size(),
            expectedValue
        );

    }
    
    void lineClippingTestCritical1()
    {
        int width = 854;
        int height = 480;
        pair<float, float> center = {427, 240};
        Border border(width, height, center);

        qsizetype rightPointIndex = 0;
        qsizetype lowerRightPointIndex = 1;

        QList<pair<float,float>> pointsList;

        pair<float, float> rightPoint(1000, 100);
        pair<float, float> lowerRightPoint(900, -100);

        pointsList.append(rightPoint);
        pointsList.append(lowerRightPoint);
        
        qsizetype expectedValue = 0;

        this->clipper->lineClipping(
            border,
            rightPointIndex,
            lowerRightPointIndex,
            &pointsList
        );        

        FrameworkTest::expectToBeEqual(
            "Deve rejeitar a linha dos pontos (900, -100) e (1000, 100)",
            pointsList.size(),
            expectedValue
        );
    }

     void lineClippingTestCritical2()
    {
        int width = 854;
        int height = 480;
        pair<float, float> center = {427, 240};
        Border border(width, height, center);

        qsizetype upperLeftPointIndex = 0;
        qsizetype lowerRightPointIndex = 1;

        QList<pair<float,float>> pointsList;

        pair<float, float> upperLeftPoint(-1100, 666);
        pair<float, float> lowerRightPoint(960, -700);

        pointsList.append(upperLeftPoint);
        pointsList.append(lowerRightPoint);

        qsizetype expectedValue = 0;

        this->clipper->lineClipping(
            border,
            upperLeftPointIndex,
            lowerRightPointIndex,
            &pointsList
        );

        FrameworkTest::expectToBeEqual(
            "Deve rejeitar a linha dos pontos (-1100, 666) e (960, -700), que cruza pelas quinas superior esquerda e inferior direita, mas não passa por dentro",
            pointsList.size(),
            expectedValue
        );
    }
};
