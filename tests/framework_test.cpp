#include <iostream>
#include "framework_test.h"
using namespace std;

void FrameworkTest::test(const char* testMessage, bool testResult)
{
    cout << testMessage << ": ";

    if (!testResult) {
        cout << "Test failed!" << endl;
        return;
    }

    cout << "Test passed!" << endl;
}

bool FrameworkTest::expectToBeEqual(float value, float expectedValue)
{
    return value == expectedValue;
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
}