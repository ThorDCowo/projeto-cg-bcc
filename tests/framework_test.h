#ifndef FRAMEWORK_TEST_H
#define FRAMEWORK_TEST_H

#include <list>
#include <iostream>
#include <QList>
#include "test_suite.h"

using namespace std;

class FrameworkTest 
{

public:
    bool static expectToBeEqual(const char* testMessage, float value, float expectedValue);
    bool static expectToBeEqual(const char* testMessage, qsizetype value, qsizetype expectedValue);
    bool static expectToBeEqual(const char* testMessage, pair<float, float> value, pair<float, float> expectedValue);
    bool static expectToBeTruly(const char* testMessage, bool value);
    bool static expectToBeFalsy(const char* testMessage, bool value);
    void run();
    void registerTest(TestSuite* testSuite);

private:
    list<TestSuite*> testSuites;
};

#endif // FRAMEWORK_TEST_H
