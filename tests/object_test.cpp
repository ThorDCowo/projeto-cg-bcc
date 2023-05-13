#include <iostream>
#include <vector>
#include "../object.h"
#include "../border.h"
#include "framework_test.h"
#include "test_suite.h"
#include "object_test.h"

void ObjectTest::run() {
    // cout << "-----------------------" << endl;
    // cout << "Teste de Interpolação" << endl;
    // cout << "-----------------------" << endl;   

    // this->interpolateTest1();
    // this->interpolateTest2();
    // this->interpolateTest3();

    cout << "-----------------------" << endl;
    cout << "Teste de clippingPoint()" << endl;
    cout << "-----------------------" << endl;

    this->parallelToAxisClipping2();
    this->parallelToAxisClipping3();
    this->parallelToAxisClipping4();
    this->parallelToAxisClipping5();
    this->parallelToAxisClipping6();
    this->parallelToAxisClipping7();
    this->parallelToAxisClipping8();
    this->parallelToAxisClipping9();
    this->parallelToAxisClipping10();
    this->parallelToAxisClipping11();
    this->parallelToAxisClippingCritical1();
}

void ObjectTest::interpolateTest1() {
    this->linearInterpolationTest(
        "Deve interpolar linearmente do intervalo [0, 255] para o intervalo [0, 100] aplicado no ponto 0 e retornar 0",
        0.0,
        0.0,
        0.0,
        0.0,
        255.0,
        100.0
    );
}

void ObjectTest::interpolateTest2() {
    this->linearInterpolationTest(
        "Deve interpolar linearmente do intervalo [0, 255] para o intervalo [0, 100] aplicado no ponto 255 e retornar 100", 
        100.0,
        255.0,
        0.0,
        0.0,
        255.0,
        100.0
    );
}

void ObjectTest::interpolateTest3() {
    this->linearInterpolationTest(
        "Deve interpolar linearmente do intervalo [0, 255] para o intervalo [0, 100] aplicado no ponto 127 e retornar 50", 
        50.0,
        127.0,
        0.0,
        0.0,
        255.0,
        100.0
    );
}

void ObjectTest::linearInterpolationTest(
    const char* testMessage,
    float expectedValue,
    float x,
    float x0,
    float x1,
    float y0,
    float y1
) {
    float interpolated = this->objectForTest->linearInterpolation(x, x0, x1, y0, y1);
    FrameworkTest::expectToBeEqual(testMessage, interpolated, expectedValue);
}

void ObjectTest::isLineFullyInsideWindowTest1() {
    /*
        Considere que pointOneRC e pointTwoRC são vetores de booleanos que representam regiões de uma janela de recorte.
        pointOneRC e pointTwoRC possuem os mesmo conjunto de valores válidos.
        O primeiro indice do vetor representa a região de cima da janela de recorte.
        O segundo indice do vetor representa a região de baixo da janela de recorte.
        O terceiro indice do vetor representa a região da esquerda da janela de recorte.
        O quarto indice do vetor representa a região da direita da janela de recorte.
        Se ao menos um dos indices do vetor for verdadeiro, então o ponto está dentro da janela de recorte.
        Logo, se todos os indices forem falsos, então o ponto está fora da janela de recorte.
        Não é possível que todos os indices sejam verdadeiros, pois isso significaria que o ponto está dentro de todas as regiões da janela de recorte.
        Sabendo disso escreva os casos de teste para a função isLineFullyInsideWindow().
        Use 0 e 1 para representar os valores dos vetores.
    */

    // vector<bool> pointOneRC = {0, 0, 0, 0};
    // vector<bool> pointTwoRC = {0, 0, 0, 0};
    // this->isLineFullyInsideWindowTest(
    //     "Deve retornar true quando os dois pontos estão dentro da janela de recorte",
    //     true,
    //     pointOneRC,
    //     pointTwoRC
    // );

    // pointOneRC = {0, 0, 0, 0};
    // pointTwoRC = {0, 0, 0, 1};

    // this->isLineFullyInsideWindowTest(
    //     "Deve retornar false quando um dos pontos está fora da janela de recorte",
    //     false,
    //     pointOneRC,
    //     pointTwoRC
    // );
    
    // pointOneRC = {0, 0, 0, 0};
    
}

void ObjectTest::isLineFullyInsideWindowTest(
    const char* testMessage,
    bool expectedValue,
    vector<bool> pointOneRC,
    vector<bool> pointTwoRC
) {
    bool isLineFullyInsideWindow = this->objectForTest->isLineFullyInsideWindow(pointOneRC, pointTwoRC);
    FrameworkTest::expectToBeTruly(testMessage, isLineFullyInsideWindow);
}

// F - E Line
void ObjectTest::parallelToAxisClipping2()
{
    int width = 15;
    int height = 10;
    pair<float, float> center = {7.5, 5.0};
    Border border(width, height, center);

    pair<float, float> insidePoint(5, 7);
    pair<float, float> outsidePoint(-5, 2);
    
    pair<float, float> expectedValue(0, 4.5);

    pair<float, float> resultPoint = this->objectForTest->parallelToAxisClipping(
        border,
        insidePoint,
        outsidePoint
    );

    FrameworkTest::expectToBeEqual(
        "Deve realizar o clipping pela esquerda alterarndo o ponto de fora para (0, 4.5)",
        resultPoint,
        expectedValue
    );
}

// K - L Line
void ObjectTest::parallelToAxisClipping3()
{
    int width = 15;
    int height = 10;
    pair<float, float> center = {7.5, 5.0};
    Border border(width, height, center);

    pair<float, float> abovePoint(-6, 14);
    pair<float, float> belowPoint(20, -5);
    
    // pair<float, float> expectedValue1(13.1579, 0);
    // pair<float, float> expectedValue2(0, 9.615);

    cout << "Upper:" << border.getUpper() << endl;
    pair<float, float> expectedValue1(13.1579, 0);
    pair<float, float> expectedValue2(-6, 14);

    // Tenta clippar por baixo
    pair<float, float> resultPoint1 = this->objectForTest->parallelToAxisClipping(
        border,
        abovePoint,
        belowPoint
    );

    // Tenta clippar por cima
    pair<float, float> resultPoint2 = this->objectForTest->parallelToAxisClipping(
        border,
        belowPoint,
        abovePoint
    );

    FrameworkTest::expectToBeEqual(
        "Deve realizar o clippling o clipping por esquerda alterarndo o ponto (-6, 14) para (0, 9.615)",
        resultPoint1,
        expectedValue1
    );

    FrameworkTest::expectToBeEqual(
        "Deve retornar o ponto (20, -5) por não conseguir realizar o clipping por baixo alterarndo o ponto (20, -5) para (13.15, 0)",
        resultPoint2,
        expectedValue2
    );
}

// R - Q Line
void ObjectTest::parallelToAxisClipping4()
{
    int width = 15;
    int height = 10;
    pair<float, float> center = {7.5, 5.0};
    Border border(width, height, center);

    pair<float, float> insidePoint(2, 2);
    pair<float, float> outsidePoint(6, -2);
    
    pair<float, float> expectedValue(4, 0);

    pair<float, float> resultPoint = this->objectForTest->parallelToAxisClipping(
        border,
        insidePoint,
        outsidePoint
    );

    FrameworkTest::expectToBeEqual(
        "Deve realizar o clipping por baixo alterarndo o ponto de fora para (4, 0)",
        resultPoint,
        expectedValue
    );
}

//J - I Line
void ObjectTest::parallelToAxisClipping5()
{
    int width = 15;
    int height = 10;
    pair<float, float> center = {7.5, 5.0};
    Border border(width, height, center);

    pair<float, float> insidePoint(11, 4);
    pair<float, float> outsidePoint(20, 13);
    
    pair<float, float> expectedValue(20, 13);

    pair<float, float> resultPoint = this->objectForTest->parallelToAxisClipping(
        border,
        insidePoint,
        outsidePoint
    );

    FrameworkTest::expectToBeEqual(
        "Deve retornar o ponto (20, 13) por nãoconseguir realizar o clipping pela diagonal.",
        resultPoint,
        expectedValue
    );
}

//O - P Line
void ObjectTest::parallelToAxisClipping6()
{
    int width = 15;
    int height = 10;
    pair<float, float> center = {7.5, 5.0};
    Border border(width, height, center);

    pair<float, float> insidePoint(8, 7);
    pair<float, float> outsidePoint(8, 12);
    
    pair<float, float> expectedValue(8, 10);

    pair<float, float> resultPoint = this->objectForTest->parallelToAxisClipping(
        border,
        insidePoint,
        outsidePoint
    );

    FrameworkTest::expectToBeEqual(
        "Deve realizar o clipping por cima alterarndo o ponto de fora para (8, 10)",
        resultPoint,
        expectedValue
    );
}

// S - T Line
void ObjectTest::parallelToAxisClipping7()
{
    int width = 15;
    int height = 10;
    pair<float, float> center = {7.5, 5.0};
    Border border(width, height, center);

    pair<float, float> insidePoint(13, 3);
    pair<float, float> outsidePoint(17, 3);
    
    pair<float, float> expectedValue(15, 3);

    pair<float, float> resultPoint = this->objectForTest->parallelToAxisClipping(
        border,
        insidePoint,
        outsidePoint
    );

    FrameworkTest::expectToBeEqual(
        "Deve realizar o clipping pela direita alterarndo o ponto de fora para (15, 3)",
        resultPoint,
        expectedValue
    );
}

//U - V Line
void ObjectTest::parallelToAxisClipping8()
{
    int width = 15;
    int height = 10;
    pair<float, float> center = {7.5, 5.0};
    Border border(width, height, center);

    pair<float, float> insidePoint(1, 1);
    pair<float, float> outsidePoint(-4, -4);
    
    pair<float, float> expectedValue(0, 0);

    pair<float, float> resultPoint = this->objectForTest->parallelToAxisClipping(
        border,
        insidePoint,
        outsidePoint
    );

    FrameworkTest::expectToBeEqual(
        "Deve realizar o clipping diagonalmente passando pela quina alterarndo o ponto de fora para (0, 0)",
        resultPoint,
        expectedValue
    );
}

// M - N Line
void ObjectTest::parallelToAxisClipping9()
{
    int width = 15;
    int height = 10;
    pair<float, float> center = {7.5, 5.0};
    Border border(width, height, center);

    pair<float, float> insidePoint(3, 14);
    pair<float, float> outsidePoint(18, 15);
    
    pair<float, float> expectedValue1(18, 15);
    pair<float, float> expectedValue2(3, 14);

    pair<float, float> resultPoint1 = this->objectForTest->parallelToAxisClipping(
        border,
        insidePoint,
        outsidePoint
    );

    pair<float, float> resultPoint2 = this->objectForTest->parallelToAxisClipping(
        border,
        outsidePoint,
        insidePoint
    );

    FrameworkTest::expectToBeEqual(
        "Deve rejeitar o clipping por cima deletando o ponto (18, 15)",
        resultPoint1,
        expectedValue1
    );

    FrameworkTest::expectToBeEqual(
        "Deve rejeitar o clipping por cima deletando o ponto (3, 14)",
        resultPoint2,
        expectedValue2
    );
}

// G - H Line
void ObjectTest::parallelToAxisClipping10()
{
    int width = 15;
    int height = 10;
    pair<float, float> center = {7.5, 5.0};
    Border border(width, height, center);

    pair<float, float> insidePoint(5, 13);
    pair<float, float> outsidePoint(-5, 8);
    
    pair<float, float> expectedValue1(-5, 8);
    pair<float, float> expectedValue2(5, 13);

    pair<float, float> resultPoint1 = this->objectForTest->parallelToAxisClipping(
        border,
        insidePoint,
        outsidePoint
    );

    pair<float, float> resultPoint2 = this->objectForTest->parallelToAxisClipping(
        border,
        outsidePoint,
        insidePoint
    );

    FrameworkTest::expectToBeEqual(
        "Deve rejeitar o clipping pela esquerda deletando o ponto (-5, 8)",
        resultPoint1,
        expectedValue1
    );

    FrameworkTest::expectToBeEqual(
        "Deve rejeitar o clipping por cima deletando o ponto (5, 13)",
        resultPoint2,
        expectedValue2
    );
}

void ObjectTest::parallelToAxisClipping11()
{
    int width = 15;
    int height = 10;
    pair<float, float> center = {7.5, 5.0};
    Border border(width, height, center);

    pair<float, float> insidePoint(17, 1);
    pair<float, float> outsidePoint(14, -4);
    
    pair<float, float> expectedValue1(14, -4);
    pair<float, float> expectedValue2(17, 1);

    pair<float, float> resultPoint1 = this->objectForTest->parallelToAxisClipping(
        border,
        insidePoint,
        outsidePoint
    );

    pair<float, float> resultPoint2 = this->objectForTest->parallelToAxisClipping(
        border,
        outsidePoint,
        insidePoint
    );

    cout << "Reta com ponto no quadrante de baixo e quadrante da direita, sem passar por dentro" << endl;
    FrameworkTest::expectToBeEqual(
        "Deve rejeitar o clipping pela esquerda deletando o ponto (14, -4)",
        resultPoint1,
        expectedValue1
    );

    FrameworkTest::expectToBeEqual(
        "Deve rejeitar o clipping por cima deletando o ponto (17, 1)",
        resultPoint2,
        expectedValue2
    );
}

// Esta crashando
void ObjectTest::parallelToAxisClippingCritical1()
{
    int width = 854;
    int height = 480;
    pair<float, float> center = {427, 240};
    Border border(width, height, center);

    pair<float, float> insidePoint(1000, 100);
    pair<float, float> outsidePoint(900, -100);
    
    pair<float, float> expectedValue1(900, -100);
    pair<float, float> expectedValue2(1000, 100);

    pair<float, float> resultPoint1 = this->objectForTest->parallelToAxisClipping(
        border,
        insidePoint,
        outsidePoint
    );

    pair<float, float> resultPoint2 = this->objectForTest->parallelToAxisClipping(
        border,
        outsidePoint,
        insidePoint
    );

    FrameworkTest::expectToBeEqual(
        "Deve rejeitar o clipping pelo canto inferior direito deletando o ponto (900, -100)",
        resultPoint1,
        expectedValue1
    );

    FrameworkTest::expectToBeEqual(
        "Deve rejeitar o clipping pela direita deletando o ponto (1000, 100)",
        resultPoint2,
        expectedValue2
    );
}