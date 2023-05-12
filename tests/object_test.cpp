#include <iostream>
#include <vector>
#include "../object.h"
#include "framework_test.h"
#include "test_suite.h"
#include "object_test.h"

void ObjectTest::run() {
    cout << "-----------------------" << endl;
    cout << "Teste de Interpolação" << endl;
    cout << "-----------------------" << endl;   

    this->interpolateTest1();
    this->interpolateTest2();
    this->interpolateTest3();

    cout << "-----------------------" << endl;
    cout << "Teste de isLineFullyInsideWindow()" << endl;
    cout << "-----------------------" << endl;

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
    this->isLineFullyInsideWindowTest(
        "Deve retornar true para uma linha totalmente dentro da janela",
        1,
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    );
}

void ObjectTest::isLineFullyInsideWindowTest(
    const char* testMessage,
    bool expectedValue,
    vector<bool> pointOneRC,
    vector<bool> pointTwoRC
) {
    bool isLineFullyInsideWindow = this->objectForTest->isLineFullyInsideWindow(pointOneRC, pointTwoRC);
    FrameworkTest::expectToBeEqual(testMessage, isLineFullyInsideWindow, expectedValue);
}