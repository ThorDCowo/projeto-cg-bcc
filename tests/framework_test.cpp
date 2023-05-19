#include <iostream>
#include <string>
#include <QList>
#include "framework_test.h"
#include "../core/interfaces/comparable.h"
using namespace std;

void FrameworkTest::registerTest(TestSuite* testSuite)
{
    this->testSuites.push_back(testSuite);
}

bool FrameworkTest::expectToBeEqual(string testMessage, float value, float expectedValue)
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

bool FrameworkTest::expectToBeEqual(string testMessage, qsizetype value, qsizetype expectedValue)
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

template<class T> 
bool FrameworkTest:: expectToBeEqual(
    string testMessage,
    Comparable<T>& value,
    Comparable<T>& expectedValue
)
{
    bool result = (*value) == (*expectedValue);

    cout << testMessage << ": ";

    if (!result) {
        cout << "Falhou!" << endl;
        cout << "Valor Recebido: " << value->toString() << endl;
        cout << "Valor Esperado: " << expectedValue->toString() << endl;
        return false;
    }

    cout << "Sucesso!" << endl;
    return result;
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