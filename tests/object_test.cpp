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
