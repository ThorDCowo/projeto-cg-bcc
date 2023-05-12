#include <iostream>
#include "framework_test.h"
using namespace std;

bool FrameworkTest::expectToBeEqual(const char* testMessage, float value, float expectedValue)
{
    bool result = value == expectedValue;
    cout << testMessage << ": ";

    if (!result) {
        cout << "Falhou!" << endl;
        cout << "Valor Recebido: " << value << endl;
        cout << "Valor Esperado: " << expectedValue << endl;
        return false;
    }

    cout << "Sucesso!" << endl;
    return result;
}

void FrameworkTest::registerTest(TestSuite* testSuite)
{
    this->testSuites.push_back(testSuite);
}

void FrameworkTest::run()
{
    for (TestSuite* testSuite : this->testSuites) {
        testSuite->run();
    }

    cout << "-----------------------" << endl;
    cout << "Fim dos testes" << endl;
    cout << "-----------------------" << endl;
}