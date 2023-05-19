#ifndef FRAMEWORK_TEST_H
#define FRAMEWORK_TEST_H

#include <list>
#include <iostream>
#include <QList>
#include <string>
#include "test_suite.h"
#include "../core/interfaces/comparable.h"

using namespace std;

class FrameworkTest 
{

public:
    bool static expectToBeEqual(string testMessage, float value, float expectedValue);
    bool static expectToBeEqual(string testMessage, qsizetype value, qsizetype expectedValue);
    template<class T> 
    bool static expectToBeEqual(
        string testMessage,
        Comparable<T>& value,
        Comparable<T>& expectedValue
    );
    void run();
    void registerTest(TestSuite* testSuite);

private:
    list<TestSuite*> testSuites;
};

#endif // FRAMEWORK_TEST_H
