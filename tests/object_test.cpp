#include <iostream>
#include "../object.h"
#include "framework_test.h"
#include "test_suite.h"
#include "object_test.h"


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
    FrameworkTest::test(testMessage, FrameworkTest::expectToBeEqual(interpolated, expectedValue));
}

void ObjectTest::interpolateTest1() {
    this->linearInterpolationTest(
        "Deve interpolar linearmente do intervalo [0, 255] para o intervalo [0, 100] aplicado no ponto 0 e retornar 0", 
        0, 
        0,
        0, 
        255, 
        100
    );
}

void ObjectTest::interpolateTest2() {
    this->linearInterpolation(
        "Deve interpolar linearmente do intervalo [0, 255] para o intervalo [0, 100] aplicado no ponto 255 e retornar 100", 
        100, 
        255,
        0, 
        255, 
        100
    );
}

void ObjectTest::interpolateTest3() {
    this->linearInterpolation(
        "Deve interpolar linearmente do intervalo [0, 255] para o intervalo [0, 100] aplicado no ponto 127 e retornar 50", 
        50, 
        127,
        0, 
        255, 
        100
    );
}

void ObjectTest::run() {
    this->interpolateTest1();
    this->interpolateTest2();
    this->interpolateTest3();
}