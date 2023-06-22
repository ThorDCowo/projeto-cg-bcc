#include "framework_test.h"
using namespace std;

void FrameworkTest::registerTest(TestSuite* testSuite)
{
    this->testSuites.push_back(testSuite);
}

bool FrameworkTest::expectToBeEqual(
    string testMessage,
    float value,
    float expectedValue
)
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

bool FrameworkTest::expectToBeEqual(
    string testMessage,
    qsizetype value,
    qsizetype expectedValue
)
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

bool FrameworkTest::expectToBeEqual(
    string testMessage,
    pair<qsizetype, qsizetype> value,
    pair<qsizetype, qsizetype> expectedValue
)
{
    bool result = value == expectedValue;
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

bool FrameworkTest::expectToBeEqual(
        string testMessage,
        Comparable& value,
        Comparable& expectedValue
)
{
    bool result = value == expectedValue;

    cout << testMessage << ": ";

    if (!result) {
        cout << "Falhou!" << endl;
        cout << "Valor Recebido: " << value.toString() << endl;
        cout << "Valor Esperado: " << expectedValue.toString() << endl;
        return false;
    }

    cout << "Sucesso!" << endl;
    return result;
}

bool FrameworkTest::expectToBeTrue(string testMessage, bool value)
{
    bool result = value;
    cout << testMessage << ": ";

    if (!result) {
        cout << "Falhou!" << endl;
        cout << "Valor Recebido: " << value << endl;
        cout << "Valor Esperado: " << true << endl;
        return false;
    }

    cout << "Sucesso!" << endl;
    return result;
}

bool FrameworkTest::expectToBeFalse(string testMessage, bool value)
{
    bool result = !value;
    cout << testMessage << ": ";

    if (!result) {
        cout << "Falhou!" << endl;
        cout << "Valor Recebido: " << value << endl;
        cout << "Valor Esperado: " << false << endl;
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