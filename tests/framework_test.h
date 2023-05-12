#ifndef FRAMEWORK_TEST_H
#define FRAMEWORK_TEST_H

#include <list>
#include <iostream>
#include "test_suite.h"

using namespace std;

class FrameworkTest 
{

public:
    void static test(const char* testMessage, bool testResult);
    bool static expectToBeEqual(float a, float b);
    void run();
    void registerTest(TestSuite* testSuite);

private:
    list<TestSuite*> testSuites;
};

#endif // FRAMEWORK_TEST_H
