#include <iostream>
#include <QList>
#include "framework_test.h"
using namespace std;

void FrameworkTest::registerTest(TestSuite* testSuite)
{
    this->testSuites.push_back(testSuite);
}

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

bool FrameworkTest::expectToBeEqual(const char* testMessage, qsizetype value, qsizetype expectedValue)
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

bool FrameworkTest::expectToBeEqual(const char* testMessage, pair<float, float> value, pair<float, float> expectedValue)
{
    bool result = 
        (value.first == expectedValue.first) &&
        (value.second == expectedValue.second);

    cout << testMessage << ": ";

    if (!result) {
        cout << "Falhou!" << endl;
        cout << "Valor Recebido: (" << value.first << ", " << value.second << ")" << endl;
        cout << "Valor Esperado: (" << expectedValue.first << ", " << expectedValue.second << ")" << endl;
        return false;
    }

    cout << "Sucesso!" << endl;
    return result;
}

bool FrameworkTest::expectToBeTruly(const char* testMessage, bool value) {
    cout << testMessage << ": ";

    if (value) {
        cout << "Falhou!" << endl;
        cout << "Valor Recebido: " << value << endl;
        cout << "Valor Esperado: " << true << endl;
        return false;
    }

    cout << "Sucesso!" << endl;
    return true;
}
bool FrameworkTest::expectToBeFalsy(const char* testMessage, bool value) {
    cout << testMessage << ": ";

    if (!value) {
        cout << "Falhou!" << endl;
        cout << "Valor Recebido: " << value << endl;
        cout << "Valor Esperado: " << false << endl;
        return false;
    }

    cout << "Sucesso!" << endl;
    return true;
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